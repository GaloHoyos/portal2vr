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
    m_EngineTrace = (IEngineTrace *)GetInterface("engine.dll", "EngineTraceClient004");
    // El build 852_6 (dic 2010) expone VEngineClient013, retail expone 015.
    // Los indices de vtable que usa el mod (ClientCmd 7, GetLocalPlayer 12,
    // GetViewAngles 18, SetViewAngles 19, IsInGame 25) son identicos en ambas,
    // asi que alcanza con probar las versiones de mas nueva a mas vieja.
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

// Devuelve el render context evitando IMaterialSystem::GetRenderContext cuando
// el perfil del build indica el offset del contexto embebido (ver BuildProfile).
// Ese camino NO incrementa el refcount, asi que el llamador no debe hacer
// Release: usar ReleaseRenderContext, que sabe cual de los dos casos aplica.
IMatRenderContext *Game::GetRenderContext()
{
    if (!m_MaterialSystem)
        return nullptr;

    const int off = m_Offsets && m_Offsets->profile ? m_Offsets->profile->matRenderContextOffset : 0;
    if (off != 0)
        return (IMatRenderContext *)((char *)m_MaterialSystem + off);

    return m_MaterialSystem->GetRenderContext();
}

void Game::ReleaseRenderContext(IMatRenderContext *ctx)
{
    if (!ctx)
        return;

    const int off = m_Offsets && m_Offsets->profile ? m_Offsets->profile->matRenderContextOffset : 0;
    if (off != 0)
        return;   // contexto embebido: nunca se hizo AddRef

    ctx->Release();
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
    m_EngineClient->ClientCmd(szCmdString);
}

void Game::ClientCmd_Unrestricted(const char *szCmdString)
{
    m_EngineClient->ClientCmd_Unrestricted(szCmdString);
}


