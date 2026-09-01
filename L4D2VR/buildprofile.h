#pragma once
#include <string>
#include <vector>
#include <cstdint>

// Una entrada de la tabla de offsets de un build concreto.
//   hint      : RVA conocido. Se valida contra la firma; si no coincide se escanea.
//   signature : patron de bytes con '?' como comodin. nullptr/"" = no portado a este build.
//   sigOffset : se suma al resultado (para apuntar al operando de un global, p.ej.).
struct OffsetDef
{
    const char *name;
    const char *module;
    int         hint;
    const char *signature;
    int         sigOffset;
};

// Offsets de los campos de CViewSetup que toca dRenderView. -1 = el campo no
// existe en ese build (escribirlo es un no-op, leerlo devuelve 0).
//
// Los defaults son los de retail, que es lo que declara sdk/sdk.h.
// Verificado volcando el struct crudo que pasa el engine: en corehub width y
// height aparecen en +0x08/+0x0C con 1280/720, y los DoF por defecto
// (20/100/250/1000/10/5) confirman donde termina el bloque de zNear/zFar.
struct ViewSetupLayout
{
    int x              = 0x00;
    int y              = 0x08;
    int width          = 0x10;
    int height         = 0x18;
    int unscaledWidth  = 0x14;   // splitscreen: no existe antes de retail
    int unscaledHeight = 0x1C;
    int fov            = 0x68;
    int fovViewmodel   = 0x6C;
    int origin         = 0x70;   // Vector
    int angles         = 0x7C;   // QAngle
    int zNear          = 0x88;
    int zNearViewmodel = 0x90;
    int aspectRatio    = 0x98;
};

// Valores especiales para los indices de vtable de AbiLayout.
enum : int
{
    // Usar la declaracion de C++ de sdk/material.h y sdk/sdk.h, que es la de
    // retail. Es el default, y hace que el perfil de retail no dependa de que
    // alguien haya contado bien los slots a mano: sigue pasando por el compilador.
    kAbiCxx = -1,

    // El metodo existe en este build pero todavia no se identifico en que slot
    // cae. La llamada se saltea y se registra una vez en el log. Adivinar el
    // indice de un metodo que escribe estado de render es la forma mas rapida
    // de crashear lejos de la causa.
    kAbiUnknown = -2,
};

// Indices de vtable y offsets de struct que cambian entre builds *sin* que
// cambie el numero de version de la interfaz: los tres builds reportan
// VMaterialSystem080 y aun asi Valve movio metodos dentro de la vtable.
//
// Regla aprendida en 852_6 y reconfirmada en corehub: el corrimiento NO es
// uniforme. En corehub el delta contra retail es -2 hasta GetBackBufferFormat
// y -3 desde SupportsHDRMode (falta GetAspectRatioInfo, agregado despues de
// 2009), y -10 en la zona de los render targets. Cada metodo se verifica por
// separado; no se extrapola un delta.
struct AbiLayout
{
    // --- IMaterialSystem: indices de vtable ---
    int msGetBackBufferFormat              = kAbiCxx;
    int msBeginRenderTargetAllocation      = kAbiCxx;
    int msEndRenderTargetAllocation        = kAbiCxx;
    int msCreateNamedRenderTargetTextureEx = kAbiCxx;

    // --- CMaterialSystem: offsets de struct ---

    // El CMatRenderContext de hardware esta embebido dentro de CMaterialSystem.
    // Cuando esto es != 0 se lo toma de (char*)m_MaterialSystem + offset en vez
    // de llamar a GetRenderContext, que en los builds de desarrollo cae en otro
    // indice y devuelve basura (0xFFFFFFFF en 852_6).
    // Ojo: ese camino NO hace AddRef. Ver Game::ReleaseRenderContext.
    int msRenderContextEmbedded = 0;

    // RVA de la vtable de CMatRenderContext dentro de materialsystem.dll,
    // ubicada por RTTI con tools/vrport (Get-P2VRVtable).
    //
    // Si msRenderContextEmbedded es 0 y esto no lo es, el offset se busca en
    // runtime: se escanea el objeto CMaterialSystem hasta encontrar el dword
    // que apunta a esta vtable. Evita tener que derivar el offset a mano para
    // cada build, y queda verificado contra el proceso vivo en vez de asumido.
    int msRenderContextVtableRva = 0;

    // Offset del bool isGameRunning dentro de CMaterialSystem. -1 = no escribirlo.
    // En retail vive en +0x2BB0, pero en los builds de desarrollo el struct es
    // mas chico (en 852_6 el render context embebido ya esta en +0x22B4), asi
    // que escribir en el offset de retail cae fuera de la asignacion.
    int msIsGameRunning = -1;

    // --- IVEngineClient: indices de vtable ---
    //
    // corehub y 852_6 exponen los dos VEngineClient013 y aun asi la vtable NO
    // es la misma: corehub tiene un metodo insertado en el slot 14, asi que
    // desde ahi va corrido +1. IsInGame en particular lo llama DXVK una vez
    // por frame desde el hilo de render, y por el indice equivocado se termina
    // llamando otra funcion que espera un puntero.
    int ecClientCmd             = kAbiCxx;
    int ecClientCmdUnrestricted = kAbiCxx;
    int ecGetLocalPlayer        = kAbiCxx;
    int ecGetViewAngles         = kAbiCxx;
    int ecSetViewAngles         = kAbiCxx;
    int ecIsInGame              = kAbiCxx;

    // --- CViewSetup: layout del struct ---
    //
    // sdk/sdk.h lo declara con el layout de retail, y dRenderView no solo lee
    // sus campos: los escribe. Si el layout no es el de este build, esas
    // escrituras pisan lo que sea que viva en esos offsets, y el engine se cae
    // bastante despues.
    //
    // Retail intercala los campos m_nUnscaled* (splitscreen), que corren todo
    // lo demas; los builds de 2009/2010 usan el layout clasico de Source.
    // -1 = el campo no existe en este build, y escribirlo es un no-op.
    ViewSetupLayout vs{};

    // El laser sight (AimMode=2) llama vtable[242] de C_Portal_Player para
    // sacar el arma activa, y despues usa offsets de struct de C_Portal_Player
    // y CWeaponPortalBase. Todo con layout de retail, y solo se ejecuta dentro
    // de una partida: en el menu no se nota. false = AimMode se fuerza a 0.
    bool laserAimSupported = true;

    // Calibracion del viewmodel, en unidades de Source sobre los ejes del
    // control (adelante, derecha, arriba). Se RESTA de la posicion del control,
    // asi que subir un valor aleja el modelo en sentido contrario a ese eje.
    //
    // El default es el de upstream, que viene del mod original de Left 4 Dead 2
    // y nunca se recalibro para el portalgun: por eso el arma se ve despegada
    // de la mano hasta que se ajusta.
    float viewmodelOffsetX = 4.5f;
    float viewmodelOffsetY = -1.0f;
    float viewmodelOffsetZ = 1.5f;

    // CHudTexture::DrawSelf lleva flApparentZ? En corehub no: ese parametro se
    // agrego despues, y su DrawSelf termina en "ret 0x14" (5 params + this)
    // contra los 6 de retail. Cambia la firma del detour, no lo que hace.
    bool drawSelfHasApparentZ = true;

    // De que clase es el CalcViewModelView al que apunta el offset.
    //
    // Retail engancha C_BasePlayer::CalcViewModelView(pos, ang), que recorre
    // los viewmodels y delega. En corehub esa funcion no quedo como simbolo
    // separado, pero si esta C_BaseViewModel::CalcViewModelView(owner, pos,
    // ang) -- la que de verdad posiciona el modelo, un nivel mas cerca del
    // efecto. Cambia la firma del detour, no lo que hace.
    bool calcViewModelViewTakesOwner = false;

    // --- ISurface (vguimatsurface): indices de vtable ---
    //
    // IsCursorVisible se llama una vez por frame. Por el indice equivocado en
    // corehub caia en un "mov al,1; ret 8": ese ret 8 limpia 8 bytes que el
    // llamador nunca puso, y el chequeo /GS del llamador termina abortando el
    // proceso con STATUS_STACK_BUFFER_OVERRUN, lejos de la causa.
    //
    // corehub tiene ~90 slots contra los ~186 de 852_6: varios metodos de esta
    // interfaz directamente no existen en 2009.
    int sfIsCursorVisible            = kAbiCxx;
    int sfGetScreenSize              = kAbiCxx;
    int sfForceScreenSizeOverride    = kAbiCxx;
    int sfOnScreenSizeChanged        = kAbiCxx;
    int sfIsScreenSizeOverrideActive = kAbiCxx;

    // --- IMatRenderContext: indices de vtable ---
    // Solo los que el codigo vivo llama. El resto de las llamadas del mod
    // estan comentadas y no hace falta mapearlas.
    int rcRelease                  = kAbiCxx;
    int rcSetRenderTarget          = kAbiCxx;
    int rcClearBuffers             = kAbiCxx;
    int rcClearColor4ub            = kAbiCxx;
    int rcOverrideAlphaWriteEnable = kAbiCxx;
};

struct BuildProfile
{
    const char      *id;               // "retail-2011", "852_6-dec2010", ...
    const char      *engineBuildDate;  // "Dec  1 2010" tal cual aparece en engine.dll
    const OffsetDef *defs;
    int              count;
    AbiLayout        abi;
};

enum class ResolveStatus { Ok, Ambiguous, NotFound, NotPorted };

struct ResolvedOffset
{
    std::string   name;
    std::string   module;
    int           rva        = 0;
    uintptr_t     address    = 0;
    int           matchCount = 0;
    ResolveStatus status     = ResolveStatus::NotPorted;
    bool          usedHint   = false;
};

// Lee "Exe build: HH:MM:SS Mon DD YYYY" de engine.dll y devuelve la parte de fecha.
std::string DetectEngineBuild();

// Elige el perfil segun el build detectado. Nunca devuelve nullptr (cae al de retail).
const BuildProfile *SelectProfile();

// Resuelve una entrada por nombre dentro del perfil activo.
ResolvedOffset ResolveOffset(const BuildProfile *profile, const char *name);

// Vuelca el informe completo a Portal2VR_offsets.log junto al exe.
void WriteOffsetReport(const BuildProfile *profile, const std::vector<ResolvedOffset> &all);
