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

struct BuildProfile
{
    const char      *id;               // "retail-2011", "852_6-dec2010", ...
    const char      *engineBuildDate;  // "Dec  1 2010" tal cual aparece en engine.dll
    const OffsetDef *defs;
    int              count;

    // IMaterialSystem::GetRenderContext cae en distinto indice de vtable segun
    // el build, y llamarlo por el indice equivocado devuelve basura (0xFFFFFFFF
    // en 852_6). Cuando este campo es != 0 el render context de hardware se toma
    // directo de (char*)m_MaterialSystem + offset, sin llamada virtual.
    // 0 = usar la llamada virtual normal (retail).
    int              matRenderContextOffset;
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
