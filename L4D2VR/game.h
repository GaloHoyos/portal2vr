#pragma once
#include <cstdint>
#include <array>
#include <initializer_list>
#include "vector.h"
// Por ImageFormat, RenderTargetSizeMode_t y MaterialRenderTargetDepth_t, que
// aparecen en las firmas de los thunks MatSys_*. No genera ciclo: material.h
// solo incluye texture.h.
#include "material.h"

struct AbiLayout;
struct ViewSetupLayout;

// Acceso a los campos de CViewSetup por los offsets del build activo, en vez de
// por la declaracion de C++ de sdk/sdk.h, que es la de retail.
//
// Retail intercala cuatro campos m_nUnscaled* que los builds de 2009/2010 no
// tienen, asi que todo lo de abajo queda corrido: escribir setup.width con el
// offset de retail pisa las bounds del ortho, y setup.angles pisa parametros de
// depth of field. Un campo con offset -1 no existe en el build: escribirlo es
// un no-op y leerlo devuelve cero.
class ViewSetupRef
{
public:
    ViewSetupRef(void *setup, const ViewSetupLayout &layout)
        : m_p((char *)setup), m_L(&layout) {}

    // Los offsets salen de ViewSetupLayout; ver buildprofile.h.
    int &X();
    int &Y();
    int &Width();
    int &Height();
    float &Fov();
    float &FovViewmodel();
    float &AspectRatio();
    float &ZNear();
    float &ZNearViewmodel();
    Vector &Origin();
    QAngle &Angles();

    // Estos dos no existen antes de retail, asi que son setters y no
    // referencias: no hay a donde apuntar cuando el campo no esta.
    void SetUnscaledWidth(int v);
    void SetUnscaledHeight(int v);

private:
    char *m_p;
    const ViewSetupLayout *m_L;

    // Devuelve un descarte cuando el campo no existe, para que el llamador
    // pueda escribirlo sin ramificar.
    template <typename T> T &At(int off)
    {
        static T discard{};
        if (off < 0) { discard = T{}; return discard; }
        return *(T *)(m_p + off);
    }
};

class IClientEntityList;
class IMatRenderContext;
class IEngineTrace;
class IEngineClient;
class IMaterialSystem;
class IBaseClientDLL;
class IViewRender;
class IViewRender;
class CBaseEntity;
class IModelInfo;
class IModelRender;
class IMaterial;
class IInput;
class ISurface;
class IClientMode;
class C_BasePlayer;
struct model_t;

class Game;
class Offsets;
class VR;
class Hooks;

inline Game *g_Game;

struct Player
{
    C_BasePlayer *pPlayer;
    bool isUsingVR;
    QAngle controllerAngle;
    Vector controllerPos;
    QAngle prevControllerAngle;

    Player()
        : isUsingVR(false),
        controllerAngle({ 0,0,0 }),
        controllerPos({ 0,0,0 }),
        prevControllerAngle({ 0,0,0 })
    {}
};

class Game
{
public:
    IClientEntityList* m_ClientEntityList = nullptr;
    IEngineTrace* m_EngineTrace = nullptr;
    IEngineClient* m_EngineClient = nullptr;
    IMaterialSystem* m_MaterialSystem = nullptr;
    IBaseClientDLL* m_BaseClientDll = nullptr;
    IViewRender* m_ClientViewRender = nullptr;
    IViewRender* m_EngineViewRender = nullptr;
    IModelInfo* m_ModelInfo = nullptr;
    IModelRender* m_ModelRender = nullptr;
    IInput* m_VguiInput = nullptr;
    ISurface* m_VguiSurface = nullptr;
    IClientMode* m_ClientMode = nullptr;

    uintptr_t m_BaseEngine;
    uintptr_t m_BaseClient;
    uintptr_t m_BaseServer;
    uintptr_t m_BaseMaterialSystem;
    uintptr_t m_BaseVgui2;

    Vector m_singlePlayerPortalColors[3] = { Vector(255.0f, 255.0f, 255.0f), Vector(64.0f, 160.0f, 255.0f), Vector(255.0f, 160.0f, 32.0f) };

    Offsets *m_Offsets = nullptr;
    VR *m_VR = nullptr;
    Hooks *m_Hooks = nullptr;

    bool m_Initialized = false;

    std::array<Player, 24> m_PlayersVRInfo;
    int m_CurrentUsercmdID = -1;

    model_t *m_ArmsModel = nullptr;
    IMaterial *m_ArmsMaterial = nullptr;
    bool m_CachedArmsModel = false;

    Game();

    void *GetInterface(const char *dllname, const char *interfacename);
    void *GetInterfaceAny(const char *dllname, std::initializer_list<const char *> versions);

    // Reemplaza IMatRenderContext::GetWindowSize (indice de vtable dependiente del build).
    void GetGameWindowSize(int &width, int &height);
    void *m_GameWindow = nullptr;

    // Usar siempre estos dos en vez de m_MaterialSystem->GetRenderContext():
    // el indice de vtable de GetRenderContext cambia entre builds.
    IMatRenderContext *GetRenderContext();
    void ReleaseRenderContext(IMatRenderContext *ctx);

    // Offset del CMatRenderContext embebido en CMaterialSystem, o 0 para usar
    // la llamada virtual. Se resuelve una vez y se cachea; si el perfil trae el
    // RVA de la vtable, valida el offset contra el objeto vivo.
    int ResolveEmbeddedRenderContextOffset();

    // --- ABI dependiente del build ---------------------------------------
    //
    // Toda llamada virtual a IMaterialSystem o IMatRenderContext pasa por aca.
    // Los builds reportan la misma version de interfaz (VMaterialSystem080) con
    // vtables distintas, asi que el indice no se puede fijar en tiempo de
    // compilacion. El perfil decide: kAbiCxx usa la declaracion de sdk/, que es
    // la de retail; un indice explicito usa el slot medido en ese build;
    // kAbiUnknown saltea la llamada y lo registra una vez.
    const AbiLayout &Abi() const;

    ImageFormat MatSys_GetBackBufferFormat();
    void        MatSys_BeginRenderTargetAllocation();
    void        MatSys_EndRenderTargetAllocation();
    ITexture   *MatSys_CreateNamedRenderTargetTextureEx(
                    const char *name, int w, int h,
                    RenderTargetSizeMode_t sizeMode, ImageFormat format,
                    MaterialRenderTargetDepth_t depth, unsigned int textureFlags);
    // No hace nada si el perfil no ubica isGameRunning en este build.
    void        MatSys_SetGameRunning(bool running);

    // IVEngineClient. Ec_IsInGame la llama DXVK una vez por frame desde el
    // hilo de render, asi que el indice tiene que ser el de este build.
    void Ec_ClientCmd(const char *cmd);
    void Ec_ClientCmdUnrestricted(const char *cmd);
    int  Ec_GetLocalPlayer();
    void Ec_GetViewAngles(QAngle &angles);
    void Ec_SetViewAngles(QAngle &angles);
    bool Ec_IsInGame();

    // ISurface. Sf_IsCursorVisible se llama una vez por frame, asi que el
    // indice tiene que ser el de este build.
    bool Sf_IsCursorVisible();
    void Sf_GetScreenSize(int &wide, int &tall);
    void Sf_ForceScreenSizeOverride(bool state, int wide, int tall);
    void Sf_OnScreenSizeChanged(int oldWide, int oldTall);
    bool Sf_IsScreenSizeOverrideActive();
    // false cuando el build no expone el override de tamano de pantalla.
    bool Sf_HasScreenSizeOverride() const;

    void Rc_SetRenderTarget(IMatRenderContext *rc, ITexture *tex);
    void Rc_ClearBuffers(IMatRenderContext *rc, bool color, bool depth, bool stencil);
    void Rc_ClearColor4ub(IMatRenderContext *rc, unsigned char r, unsigned char g,
                          unsigned char b, unsigned char a);
    void Rc_OverrideAlphaWriteEnable(IMatRenderContext *rc, bool overrideEnable,
                                     bool alphaWriteEnable);

    static void errorMsg(const char *msg);
    static void LogInit(const char *what, const void *ptr);

    CBaseEntity *GetClientEntity(int entityIndex);
    char *getNetworkName(uintptr_t *entity);
    void ClientCmd(const char *szCmdString);
    void ClientCmd_Unrestricted(const char *szCmdString);

    typedef void *(__cdecl *tCreateInterface)(const char *name, int *returnCode);
};

