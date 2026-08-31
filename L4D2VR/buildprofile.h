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
