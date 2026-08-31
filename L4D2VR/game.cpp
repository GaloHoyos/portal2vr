#include "game.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "sdk.h"
#include "vr.h"
#include "hooks.h"
#include "offsets.h"
#include "sigscanner.h"

// Traza de inicializacion con flush por linea: si el proceso muere a mitad,
// el archivo dice exactamente hasta donde llego.
void Game::LogInit(const char *what, const void *ptr)
{
    // P2VR_NOLOG=1 desactiva la traza. Sirve para descartar que escribir en el
    // directorio del juego sea lo que altera al engine.
    {
        char v[8]; size_t n = 0;
        if (getenv_s(&n, v, sizeof(v), "P2VR_NOLOG") == 0 && n > 1)
            return;
    }

    static bool truncated = false;
    char exePath[MAX_PATH]{};
    DWORD n = GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    std::string path = "Portal2VR_init.log";
    if (n > 0)
    {
        std::string full(exePath, n);
        size_t slash = full.find_last_of("\\/");
        if (slash != std::string::npos)
            path = full.substr(0, slash + 1) + "Portal2VR_init.log";
    }
    std::ofstream f(path, truncated ? std::ios::app : std::ios::trunc);
    truncated = true;
    if (!f) return;
    char line[512];
    if (ptr) sprintf_s(line, "%-34s %p\n", what, ptr);
    else     sprintf_s(line, "%-34s %s\n", what, "NULL");
    f << line;
    f.flush();
}

// P2VR_STAGE=N corta la inicializacion despues de la etapa N:
//   1 modulos, 2 interfaces, 3 offsets, 4 VR, 5+ completo (default)
static int InitStageLimit()
{
    char v[8]; size_t n = 0;
    if (getenv_s(&n, v, sizeof(v), "P2VR_STAGE") == 0 && n > 1)
        return atoi(v);
    return 99;
}

Game::Game()
{
    const int stageLimit = InitStageLimit();
    LogInit("--- Game::Game inicio ---", (void *)(intptr_t)stageLimit);

    // etapa 1: el objeto se construyo pero no se toca nada del juego todavia.
    if (stageLimit <= 1) { m_Initialized = true; return; }
    while (!(m_BaseClient = (uintptr_t)GetModuleHandle("client.dll")))
        Sleep(50);
    while (!(m_BaseEngine = (uintptr_t)GetModuleHandle("engine.dll")))
        Sleep(50);
    while (!(m_BaseMaterialSystem = (uintptr_t)GetModuleHandle("materialsystem.dll")))
        Sleep(50);
    while (!(m_BaseServer = (uintptr_t)GetModuleHandle("server.dll")))
        Sleep(50);
    while (!(m_BaseVgui2 = (uintptr_t)GetModuleHandle("vgui2.dll")))
        Sleep(50);

    LogInit("etapa 2: modulos resueltos", (void *)1);
    if (stageLimit <= 2) { m_Initialized = true; return; }

    m_ClientEntityList = (IClientEntityList *)GetInterface("client.dll", "VClientEntityList003");
    // corehub (852_0, jul 2009) expone EngineTraceClient003; retail y 852_6, 004.
    m_EngineTrace = (IEngineTrace *)GetInterfaceAny("engine.dll",
        { "EngineTraceClient004", "EngineTraceClient003" });
    // 852_6 y corehub exponen VEngineClient013, retail expone 015. Se prueba de
    // la mas nueva a la mas vieja.
    //
    // Ojo: que la version coincida NO implica que la vtable sea la misma.
    // corehub y 852_6 dicen los dos 013 y corehub tiene un metodo insertado en
    // el slot 14, asi que de ahi va corrido +1. Los indices salen del perfil
    // (AbiLayout.ec*) y se llaman con los thunks Ec_*, nunca directo.
    m_EngineClient = (IEngineClient *)GetInterfaceAny("engine.dll",
        { "VEngineClient015", "VEngineClient014", "VEngineClient013" });
    m_MaterialSystem = (IMaterialSystem *)GetInterface("MaterialSystem.dll", "VMaterialSystem080");
    m_ClientViewRender = (IViewRender *)GetInterface("client.dll", "VEngineRenderView013");
    m_EngineViewRender = (IViewRender *)GetInterface("engine.dll", "VEngineRenderView013");
    m_ModelInfo = (IModelInfo *)GetInterface("engine.dll", "VModelInfoClient004");
    m_ModelRender = (IModelRender *)GetInterface("engine.dll", "VEngineModel016");
    m_VguiInput = (IInput *)GetInterface("vgui2.dll", "VGUI_InputInternal001");
    m_VguiSurface = (ISurface *)GetInterface("vguimatsurface.dll", "VGUI_Surface031");

    LogInit("m_ClientEntityList", m_ClientEntityList);
    LogInit("m_EngineTrace",      m_EngineTrace);
    LogInit("m_EngineClient",     m_EngineClient);
    LogInit("m_MaterialSystem",   m_MaterialSystem);
    LogInit("m_ClientViewRender", m_ClientViewRender);
    LogInit("m_EngineViewRender", m_EngineViewRender);
    LogInit("m_ModelInfo",        m_ModelInfo);
    LogInit("m_ModelRender",      m_ModelRender);
    LogInit("m_VguiInput",        m_VguiInput);
    LogInit("m_VguiSurface",      m_VguiSurface);

    LogInit("etapa 2: interfaces resueltas", (void *)1);
    if (stageLimit <= 2) { m_Initialized = true; return; }

    m_Offsets = new Offsets();
    LogInit("etapa 3: Offsets construidos", m_Offsets);
    if (stageLimit <= 3) { m_Initialized = true; return; }

    // m_ClientMode hoy no tiene ningun consumidor vivo (su unico uso, en
    // VR::GetViewport, esta comentado), asi que no resolverlo no es fatal:
    // lo dejamos en null y seguimos. Si alguna vez se reactiva ese codigo,
    // hay que chequear m_ClientMode antes de usarlo.
    if (m_Offsets->g_pClientMode.ok())
        m_ClientMode = **(IClientMode***)(m_Offsets->g_pClientMode.address);

    // P2VR_NOVR=1 deja correr DXVK pero saltea toda la capa VR. Sirve para
    // aislar si un problema viene del render o de la sumision al compositor.
    {
        char novr[8]; size_t n = 0;
        if (getenv_s(&n, novr, sizeof(novr), "P2VR_NOVR") == 0 && n > 1)
        {
            LogInit("--- P2VR_NOVR: se saltea VR y Hooks ---", (void *)1);
            m_Initialized = true;
            return;
        }
    }

    LogInit("antes de new VR", (void *)1);
    m_VR = new VR(this);
    LogInit("etapa 4: VR construido", m_VR);
    if (stageLimit <= 4) { m_Initialized = true; return; }

    LogInit("antes de new Hooks", (void *)1);
    m_Hooks = new Hooks(this);
    LogInit("Hooks construidos", m_Hooks);

    m_Initialized = true;
    LogInit("--- Game::Game completo ---", (void *)1);
}

void *Game::GetInterface(const char *dllname, const char *interfacename)
{
    HMODULE mod = GetModuleHandle(dllname);
    if (!mod)
        return nullptr;

    tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(mod, "CreateInterface");
    if (!CreateInterface)
        return nullptr;

    int returnCode = 0;
    void *createdInterface = CreateInterface(interfacename, &returnCode);

    return createdInterface;
}

// Distintos builds de Portal 2 exponen distintas versiones de la misma interfaz.
// Probamos de la mas nueva a la mas vieja y devolvemos la primera que exista.
void *Game::GetInterfaceAny(const char *dllname, std::initializer_list<const char *> versions)
{
    for (const char *v : versions)
    {
        void *iface = GetInterface(dllname, v);
        if (iface)
            return iface;
    }
    return nullptr;
}

// --- Capa ABI ----------------------------------------------------------------
//
// Llamar un metodo virtual por el indice equivocado no falla: devuelve basura o
// ejecuta otra cosa, y el crash aparece lejos del origen. Por eso ninguna
// llamada a IMaterialSystem / IMatRenderContext se hace directo: todas pasan
// por estos thunks, que consultan el perfil del build.

namespace {

// Toma el slot `index` de la vtable de `obj` y lo interpreta como Fn.
template <typename Fn>
inline Fn VFn(void *obj, int index)
{
    return (Fn)(*(void ***)obj)[index];
}

// Un metodo sin identificar se saltea, pero tiene que quedar registrado: si algo
// se ve raro despues, el log dice que llamada no se hizo. Una vez por metodo.
void LogAbiSkipOnce(const char *what)
{
    static const char *reported[16] = {};
    static int count = 0;
    for (int i = 0; i < count; ++i)
        if (reported[i] == what) return;
    if (count < (int)(sizeof(reported) / sizeof(reported[0])))
        reported[count++] = what;
    Game::LogInit(what, nullptr);
}

const AbiLayout kAbiDefault{};

} // namespace

const AbiLayout &Game::Abi() const
{
    if (m_Offsets && m_Offsets->profile)
        return m_Offsets->profile->abi;
    return kAbiDefault;   // antes de resolver offsets: comportamiento de retail
}

// Devuelve el offset del CMatRenderContext embebido dentro de CMaterialSystem, o
// 0 si hay que usar la llamada virtual.
//
// El perfil puede dar el offset directo, el RVA de la vtable de
// CMatRenderContext, o los dos. Con los dos se valida uno contra otro: es la
// unica forma de enterarse de que el offset derivado estaticamente esta mal
// *antes* de que el mod empiece a escribir a traves de ese puntero.
int Game::ResolveEmbeddedRenderContextOffset()
{
    static int cached = -1;
    if (cached >= 0)
        return cached;

    const AbiLayout &abi = Abi();
    if (!m_MaterialSystem)
        return 0;

    uintptr_t wantVtable = 0;
    if (abi.msRenderContextVtableRva != 0 && m_BaseMaterialSystem)
        wantVtable = m_BaseMaterialSystem + (uintptr_t)abi.msRenderContextVtableRva;

    if (abi.msRenderContextEmbedded != 0)
    {
        cached = abi.msRenderContextEmbedded;
        if (wantVtable)
        {
            const uintptr_t got = *(uintptr_t *)((char *)m_MaterialSystem + cached);
            LogInit(got == wantVtable ? "render context embebido: OK"
                                      : "render context embebido: NO COINCIDE",
                    (void *)(uintptr_t)cached);
        }
        return cached;
    }

    if (!wantVtable)
    {
        cached = 0;
        return 0;
    }

    // Buscarlo. El objeto vive en el heap, asi que se acota el barrido al final
    // de la region committed en vez de confiar en un tamano inventado.
    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(m_MaterialSystem, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT)
    {
        cached = 0;
        return 0;
    }
    const uintptr_t regionEnd = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
    const uintptr_t start     = (uintptr_t)m_MaterialSystem;
    const uintptr_t limit     = (regionEnd - start) < 0x4000 ? (regionEnd - start) : 0x4000;

    for (uintptr_t off = sizeof(void *); off + sizeof(void *) <= limit; off += sizeof(void *))
    {
        if (*(uintptr_t *)((char *)m_MaterialSystem + off) == wantVtable)
        {
            cached = (int)off;
            LogInit("render context embebido: encontrado", (void *)off);
            return cached;
        }
    }

    LogInit("render context embebido: NO ENCONTRADO", nullptr);
    cached = 0;
    return 0;
}

IMatRenderContext *Game::GetRenderContext()
{
    if (!m_MaterialSystem)
        return nullptr;

    const int off = ResolveEmbeddedRenderContextOffset();
    if (off != 0)
        return (IMatRenderContext *)((char *)m_MaterialSystem + off);

    return m_MaterialSystem->GetRenderContext();
}

void Game::ReleaseRenderContext(IMatRenderContext *ctx)
{
    if (!ctx)
        return;

    if (ResolveEmbeddedRenderContextOffset() != 0)
        return;   // contexto embebido: nunca se hizo AddRef

    const int idx = Abi().rcRelease;
    if (idx == kAbiCxx) { ctx->Release(); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Rc_Release"); return; }

    typedef int(__thiscall * Fn)(void *);
    VFn<Fn>(ctx, idx)(ctx);
}

ImageFormat Game::MatSys_GetBackBufferFormat()
{
    if (!m_MaterialSystem) return IMAGE_FORMAT_UNKNOWN;

    const int idx = Abi().msGetBackBufferFormat;
    if (idx == kAbiCxx) return m_MaterialSystem->GetBackBufferFormat();
    if (idx < 0)
    {
        LogAbiSkipOnce("ABI sin identificar: MatSys_GetBackBufferFormat");
        return IMAGE_FORMAT_UNKNOWN;
    }

    typedef ImageFormat(__thiscall * Fn)(void *);
    return VFn<Fn>(m_MaterialSystem, idx)(m_MaterialSystem);
}

void Game::MatSys_BeginRenderTargetAllocation()
{
    if (!m_MaterialSystem) return;

    const int idx = Abi().msBeginRenderTargetAllocation;
    if (idx == kAbiCxx) { m_MaterialSystem->BeginRenderTargetAllocation(); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: BeginRenderTargetAllocation"); return; }

    typedef void(__thiscall * Fn)(void *);
    VFn<Fn>(m_MaterialSystem, idx)(m_MaterialSystem);
}

void Game::MatSys_EndRenderTargetAllocation()
{
    if (!m_MaterialSystem) return;

    const int idx = Abi().msEndRenderTargetAllocation;
    if (idx == kAbiCxx) { m_MaterialSystem->EndRenderTargetAllocation(); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: EndRenderTargetAllocation"); return; }

    typedef void(__thiscall * Fn)(void *);
    VFn<Fn>(m_MaterialSystem, idx)(m_MaterialSystem);
}

ITexture *Game::MatSys_CreateNamedRenderTargetTextureEx(
    const char *name, int w, int h, RenderTargetSizeMode_t sizeMode,
    ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags)
{
    if (!m_MaterialSystem) return nullptr;

    const int idx = Abi().msCreateNamedRenderTargetTextureEx;
    if (idx == kAbiCxx)
        return m_MaterialSystem->CreateNamedRenderTargetTextureEx(
            name, w, h, sizeMode, format, depth, textureFlags);
    if (idx < 0)
    {
        LogAbiSkipOnce("ABI sin identificar: CreateNamedRenderTargetTextureEx");
        return nullptr;
    }

    // El 8vo parametro (renderTargetFlags) va explicito: por indice no hay
    // argumentos por defecto que lo completen.
    typedef ITexture *(__thiscall * Fn)(void *, const char *, int, int,
                                        RenderTargetSizeMode_t, ImageFormat,
                                        MaterialRenderTargetDepth_t, unsigned int, unsigned int);
    return VFn<Fn>(m_MaterialSystem, idx)(
        m_MaterialSystem, name, w, h, sizeMode, format, depth, textureFlags, 0);
}

// isGameRunning es un offset de struct, no un indice de vtable: en retail vive
// en +0x2BB0, pero en los builds de desarrollo CMaterialSystem es mas chico y
// escribir ahi cae fuera de la asignacion.
void Game::MatSys_SetGameRunning(bool running)
{
    if (!m_MaterialSystem) return;

    const int off = Abi().msIsGameRunning;
    if (off < 0)
    {
        LogAbiSkipOnce("ABI sin identificar: isGameRunning (no se escribe)");
        return;
    }
    *((bool *)((char *)m_MaterialSystem + off)) = running;
}

void Game::Ec_ClientCmd(const char *cmd)
{
    if (!m_EngineClient) return;

    const int idx = Abi().ecClientCmd;
    if (idx == kAbiCxx) { m_EngineClient->ClientCmd(cmd); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Ec_ClientCmd"); return; }

    typedef void *(__thiscall * Fn)(void *, const char *);
    VFn<Fn>(m_EngineClient, idx)(m_EngineClient, cmd);
}

void Game::Ec_ClientCmdUnrestricted(const char *cmd)
{
    if (!m_EngineClient) return;

    const int idx = Abi().ecClientCmdUnrestricted;
    if (idx == kAbiCxx) { m_EngineClient->ClientCmd_Unrestricted(cmd); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Ec_ClientCmdUnrestricted"); return; }

    typedef void *(__thiscall * Fn)(void *, const char *);
    VFn<Fn>(m_EngineClient, idx)(m_EngineClient, cmd);
}

int Game::Ec_GetLocalPlayer()
{
    if (!m_EngineClient) return -1;

    const int idx = Abi().ecGetLocalPlayer;
    if (idx == kAbiCxx) return m_EngineClient->GetLocalPlayer();
    if (idx < 0)
    {
        LogAbiSkipOnce("ABI sin identificar: Ec_GetLocalPlayer");
        return -1;
    }

    typedef int(__thiscall * Fn)(void *);
    return VFn<Fn>(m_EngineClient, idx)(m_EngineClient);
}

void Game::Ec_GetViewAngles(QAngle &angles)
{
    if (!m_EngineClient) return;

    const int idx = Abi().ecGetViewAngles;
    if (idx == kAbiCxx) { m_EngineClient->GetViewAngles(angles); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Ec_GetViewAngles"); return; }

    typedef QAngle *(__thiscall * Fn)(void *, QAngle &);
    VFn<Fn>(m_EngineClient, idx)(m_EngineClient, angles);
}

void Game::Ec_SetViewAngles(QAngle &angles)
{
    if (!m_EngineClient) return;

    const int idx = Abi().ecSetViewAngles;
    if (idx == kAbiCxx) { m_EngineClient->SetViewAngles(angles); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Ec_SetViewAngles"); return; }

    typedef QAngle *(__thiscall * Fn)(void *, QAngle &);
    VFn<Fn>(m_EngineClient, idx)(m_EngineClient, angles);
}

// Cuando el indice no se conoce se devuelve true, o sea "en partida". Es el
// valor conservador: el unico consumidor que dispara una escritura riesgosa es
// el override de viewport de DXVK, y esta guardado por !IsInGame().
bool Game::Ec_IsInGame()
{
    if (!m_EngineClient) return false;

    const int idx = Abi().ecIsInGame;
    if (idx == kAbiCxx) return m_EngineClient->IsInGame();
    if (idx < 0)
    {
        LogAbiSkipOnce("ABI sin identificar: Ec_IsInGame (se asume en partida)");
        return true;
    }

    typedef bool(__thiscall * Fn)(void *);
    return VFn<Fn>(m_EngineClient, idx)(m_EngineClient);
}

// Cuando el indice no se conoce se devuelve false, o sea "sin cursor", que es
// el camino de juego normal. Nunca deberia pasar: los tres perfiles lo tienen.
bool Game::Sf_IsCursorVisible()
{
    if (!m_VguiSurface) return false;

    const int idx = Abi().sfIsCursorVisible;
    if (idx == kAbiCxx) return m_VguiSurface->IsCursorVisible();
    if (idx < 0)
    {
        LogAbiSkipOnce("ABI sin identificar: Sf_IsCursorVisible");
        return false;
    }

    typedef bool(__thiscall * Fn)(void *);
    return VFn<Fn>(m_VguiSurface, idx)(m_VguiSurface);
}

void Game::Sf_GetScreenSize(int &wide, int &tall)
{
    wide = 0; tall = 0;
    if (!m_VguiSurface) return;

    const int idx = Abi().sfGetScreenSize;
    if (idx == kAbiCxx) { m_VguiSurface->GetScreenSize(wide, tall); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Sf_GetScreenSize"); return; }

    typedef void(__thiscall * Fn)(void *, int &, int &);
    VFn<Fn>(m_VguiSurface, idx)(m_VguiSurface, wide, tall);
}

void Game::Sf_ForceScreenSizeOverride(bool state, int wide, int tall)
{
    if (!m_VguiSurface) return;

    const int idx = Abi().sfForceScreenSizeOverride;
    if (idx == kAbiCxx) { m_VguiSurface->ForceScreenSizeOverride(state, wide, tall); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Sf_ForceScreenSizeOverride"); return; }

    typedef bool(__thiscall * Fn)(void *, bool, int, int);
    VFn<Fn>(m_VguiSurface, idx)(m_VguiSurface, state, wide, tall);
}

void Game::Sf_OnScreenSizeChanged(int oldWide, int oldTall)
{
    if (!m_VguiSurface) return;

    const int idx = Abi().sfOnScreenSizeChanged;
    if (idx == kAbiCxx) { m_VguiSurface->OnScreenSizeChanged(oldWide, oldTall); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Sf_OnScreenSizeChanged"); return; }

    typedef void(__thiscall * Fn)(void *, int, int);
    VFn<Fn>(m_VguiSurface, idx)(m_VguiSurface, oldWide, oldTall);
}

bool Game::Sf_IsScreenSizeOverrideActive()
{
    if (!m_VguiSurface) return false;

    const int idx = Abi().sfIsScreenSizeOverrideActive;
    if (idx == kAbiCxx) return m_VguiSurface->IsScreenSizeOverrideActive();
    if (idx < 0)
    {
        LogAbiSkipOnce("ABI sin identificar: Sf_IsScreenSizeOverrideActive");
        return false;
    }

    typedef bool(__thiscall * Fn)(void *);
    return VFn<Fn>(m_VguiSurface, idx)(m_VguiSurface);
}

// El override de tamano de pantalla es un bloque: sin los tres metodos no tiene
// sentido llamar ninguno, porque se dejaria a VGUI en un estado a medias.
bool Game::Sf_HasScreenSizeOverride() const
{
    const AbiLayout &abi = Abi();
    return abi.sfForceScreenSizeOverride    != kAbiUnknown
        && abi.sfOnScreenSizeChanged        != kAbiUnknown
        && abi.sfIsScreenSizeOverrideActive != kAbiUnknown
        && abi.sfGetScreenSize              != kAbiUnknown;
}

void Game::Rc_SetRenderTarget(IMatRenderContext *rc, ITexture *tex)
{
    if (!rc) return;

    const int idx = Abi().rcSetRenderTarget;
    if (idx == kAbiCxx) { rc->SetRenderTarget(tex); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Rc_SetRenderTarget"); return; }

    typedef void(__thiscall * Fn)(void *, ITexture *);
    VFn<Fn>(rc, idx)(rc, tex);
}

void Game::Rc_ClearBuffers(IMatRenderContext *rc, bool color, bool depth, bool stencil)
{
    if (!rc) return;

    const int idx = Abi().rcClearBuffers;
    if (idx == kAbiCxx) { rc->ClearBuffers(color, depth, stencil); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Rc_ClearBuffers"); return; }

    typedef void(__thiscall * Fn)(void *, bool, bool, bool);
    VFn<Fn>(rc, idx)(rc, color, depth, stencil);
}

void Game::Rc_ClearColor4ub(IMatRenderContext *rc, unsigned char r, unsigned char g,
                            unsigned char b, unsigned char a)
{
    if (!rc) return;

    const int idx = Abi().rcClearColor4ub;
    if (idx == kAbiCxx) { rc->ClearColor4ub(r, g, b, a); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Rc_ClearColor4ub"); return; }

    typedef void(__thiscall * Fn)(void *, unsigned char, unsigned char, unsigned char, unsigned char);
    VFn<Fn>(rc, idx)(rc, r, g, b, a);
}

void Game::Rc_OverrideAlphaWriteEnable(IMatRenderContext *rc, bool overrideEnable,
                                       bool alphaWriteEnable)
{
    if (!rc) return;

    const int idx = Abi().rcOverrideAlphaWriteEnable;
    if (idx == kAbiCxx) { rc->OverrideAlphaWriteEnable(overrideEnable, alphaWriteEnable); return; }
    if (idx < 0)        { LogAbiSkipOnce("ABI sin identificar: Rc_OverrideAlphaWriteEnable"); return; }

    typedef void(__thiscall * Fn)(void *, bool, bool);
    VFn<Fn>(rc, idx)(rc, overrideEnable, alphaWriteEnable);
}

// El equivalente a IMatRenderContext::GetWindowSize, pero via Win32.
// Motivo: la vtable de IMatRenderContext difiere entre retail y los builds de
// desarrollo (852_6 tiene dos metodos insertados en puntos distintos, asi que
// el indice no es el mismo). El tamano de la ventana de cliente es exactamente
// lo que el mod necesita y no depende del build.
static BOOL CALLBACK FindGameWindowProc(HWND hwnd, LPARAM lParam)
{
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != GetCurrentProcessId() || !IsWindowVisible(hwnd))
        return TRUE;
    if (GetWindow(hwnd, GW_OWNER) != nullptr)
        return TRUE;   // saltear dialogos
    *(HWND *)lParam = hwnd;
    return FALSE;
}

void Game::GetGameWindowSize(int &width, int &height)
{
    if (!m_GameWindow || !IsWindow((HWND)m_GameWindow))
    {
        HWND found = nullptr;
        EnumWindows(FindGameWindowProc, (LPARAM)&found);
        m_GameWindow = found;
    }

    RECT rc{};
    if (m_GameWindow && GetClientRect((HWND)m_GameWindow, &rc) && rc.right > 0 && rc.bottom > 0)
    {
        width = rc.right - rc.left;
        height = rc.bottom - rc.top;
        return;
    }

    // Ultimo recurso: no dejar valores basura que propaguen divisiones raras.
    width = 1280;
    height = 720;
}

void Game::errorMsg(const char *msg)
{
    MessageBox(0, msg, "L4D2VR", MB_ICONERROR | MB_OK);
}

CBaseEntity *Game::GetClientEntity(int entityIndex)
{
    return (CBaseEntity *)(m_ClientEntityList->GetClientEntity(entityIndex));
}

char *Game::getNetworkName(uintptr_t *entity)
{
    uintptr_t *IClientNetworkableVtable = (uintptr_t *)*(entity + 0x8);
    uintptr_t *GetClientClassPtr = (uintptr_t *)*(IClientNetworkableVtable + 0x8);
    uintptr_t *ClientClassPtr = (uintptr_t *)*(GetClientClassPtr + 0x1);
    char *m_pNetworkName = (char *)*(ClientClassPtr + 0x8);
    int classID = (int)*(ClientClassPtr + 0x10);
    std::cout << "ClassID: " << classID << std::endl;
    return m_pNetworkName;
}

void Game::ClientCmd(const char *szCmdString)
{
    Ec_ClientCmd(szCmdString);
}

void Game::ClientCmd_Unrestricted(const char *szCmdString)
{
    Ec_ClientCmdUnrestricted(szCmdString);
}


