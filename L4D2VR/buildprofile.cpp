// GENERADO - tablas de offsets por build
#include "buildprofile.h"

// Portal 2 retail (Abril 2011) - tabla original de Gistix/portal2vr
static const OffsetDef kRetail2011[] = {
    { "GetFullScreenTexture", "client.dll", 0x1A83F0, "A1 ? ? ? ? 85 C0 75 53 8B 0D ? ? ? ? 8B 01 8B 90 ? ? ? ? 6A 00 6A 01 68 ? ? ? ? 68 ? ? ? ? FF D2 50 B9 ? ? ? ? E8 ? ? ? ? 80 3D ? ? ? ? ? 75 1C 8B 0D ? ? ? ? 8B 01 8B 90 ? ? ? ? 68 ? ? ? ? C6 05 ? ? ? ? ? FF D2 A1 ? ? ? ? C3", 0 },
    { "RenderView", "client.dll", 0x1F2120, "55 8B EC 83 EC 2C 53 56 8B F1 6A 00 8D 8E ? ? ? ? E8 ? ? ? ?", 0 },
    { "g_pClientMode", "client.dll", 0x28A600, "8B 0D ? ? ? ? 8B", 2 },
    { "CalcViewModelView", "client.dll", 0x27D750, "55 8B EC 83 EC 34 53 8B D9 80 BB", 0 },
    { "CreateMove", "client.dll", 0x27A440, "55 8B EC A1 ? ? ? ? 83 EC 0C 83 78 30 00 56 8B 75 0C 57 8B F9 74 43", 0 },
    { "WriteUsercmd", "client.dll", 0x1C2060, "55 8B EC A1 ? ? ? ? 83 78 30 00 53 8B 5D 0C 56 57", 0 },
    { "g_pppInput", "client.dll", 0xD12A0, "8B 0D ? ? ? ? 8B 01 8B 50 68 FF E2", 2 },
    { "PrePushRenderTarget", "client.dll", 0xA8C80, "55 8B EC 8B C1 56 8B 75 08 8B 0E 89 08 8B 56 04 89", 0 },
    { "ReadUserCmd", "server.dll", 0x205100, "55 8B EC 53 8B 5D 10 56 57 8B 7D 0C 53", 0 },
    { "ProcessUsercmds", "server.dll", 0x170300, "55 8B EC B8 ? ? ? ? E8 ? ? ? ? 0F 57 C0 53 56 57 B9 ? ? ? ? 8D 85 ? ? ? ? 33 DB", 0 },
    { "CBaseEntity_entindex", "server.dll", 0x39F00, "8B 41 1C 85 C0 75 01 C3 8B 0D ? ? ? ? 2B 41 58 C1 F8 04 C3 CC", 0 },
    { "EyePosition", "server.dll", 0xF40E0, "55 8B EC 56 8B F1 8B 86 ? ? ? ? C1 E8 0B A8 01 74 05 E8 ? ? ? ? 8B 45 08 F3", 0 },
    { "PushRenderTargetAndViewport", "materialsystem.dll", 0x2D5F0, "55 8B EC 83 EC 24 8B 45 08 8B 55 10 89", 0 },
    { "PopRenderTargetAndViewport", "materialsystem.dll", 0x2CE80, "56 8B F1 83 7E 4C 00", 0 },
    { "TraceFirePortalServer", "server.dll", 0x400D50, "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 56 57 8B F1 6A", 0 },
    { "CWeaponPortalgun_FirePortal", "server.dll", 0x401370, "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 56 57 8B F9 89 7D EC E8 ? ? ? ?", 0 },
    { "VGui_Paint", "engine.dll", 0x115CE0, "55 8B EC E8 ? ? ? ? 8B 10 8B C8 8B 52 38", 0 },
    { "PlayerPortalled", "client.dll", 0x27C9D0, "55 8B EC 83 EC 78 53 56 8B D9 8B 0D ? ? ? ? 8B 01 8B 90 ? ? ? ? 57 33 FF 57 FF D2", 0 },
    { "DrawSelf", "client.dll", 0x12CC90, "55 8B EC 56 8B F1 80 BE ? ? ? ? ? 0F 84 ? ? ? ? 8B 0D", 0 },
    { "ClipTransform", "client.dll", 0x1DD130, "55 8B EC 8B 0D ? ? ? ? 8B 01 8B 90 ? ? ? ? FF D2 8B 4D", 0 },
    { "VGui_GetClientDLLRootPanel", "client.dll", 0x26EDF0, "8B 0D ? ? ? ? 8B 01 8B 90 ? ? ? ? FF D2 8B 04 85 ? ? ? ? 8B 48 04", 0 },
    { "g_pFullscreenRootPanel", "client.dll", 0x26EE20, "A1 ? ? ? ? C3", 2 },
    { "CreatePingPointer", "client.dll", 0x280660, "55 8B EC 83 EC 14 53 56 8B F1 8B 8E ? ? ? ? 57 85 C9 74 30", 0 },
    { "GetPortalPlayer", "client.dll", 0x8DCA0, "55 8B EC 8B 45 08 83 F8 FF 75 10 8B 0D ? ? ? ? 8B 01 8B 90 ? ? ? ? FF D2", 0 },
    { "PrecacheParticleSystem", "server.dll", 0x16DF40, "55 8B EC 8B 0D ? ? ? ? 8B 55 08 8B 01 8B 40 20 6A 00 6A FF", 0 },
    { "Precache", "server.dll", 0x35A2C0, "E8 ? ? ? ? 68 ? ? ? ? E8 ? ? ? ?", 0 },
    { "SetControlPoint", "client.dll", 0x17BD30, "55 8B EC 53 56 8B 75 0C 57 8B F9 BB ? ? ? ? 84 9F ? ? ? ?", 0 },
    { "SetDrawOnlyForSplitScreenUser", "client.dll", 0x17B9E0, "55 8B EC 8B 45 08 53 8B D9 3B 83 ? ? ? ? 74 55", 0 },
    { "StopEmission", "client.dll", 0x17B6A0, "55 8B EC 53 8B 5D 08 57 8B F9 F6 87 ? ? ? ? ? 74 7F", 0 },
    { "CHudCrosshair_ShouldDraw", "client.dll", 0x141BE0, "57 8B F9 80 BF ? ? ? ? ? 74 04 32 C0 5F C3", 0 },
    { "UTIL_Portal_FirstAlongRay", "server.dll", 0x377200, "55 8B EC 8B 0D ? ? ? ? 85 C9 74 19 A1 ? ? ? ?", 0 },
    { "UTIL_IntersectRayWithPortal", "server.dll", 0x376730, "55 8B EC 83 EC 48 56 8B 75 0C 85 F6 0F 84 ? ? ? ?", 0 },
    { "UTIL_Portal_AngleTransform", "server.dll", 0x375CA0, "55 8B EC 8B 45 08 8B 4D 0C 83 EC 0C 50 51 8D 55 F4", 0 },
    { "Weapon_ShootPosition", "server.dll", 0x1033C0, "55 8B EC 8B 01 8B 90 ? ? ? ? 56 8B 75 08 56 FF D2 8B C6 5E 5D C2 04 00", 0 },
    { "ComputeError", "server.dll", 0x3C8140, "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 56 8B F1 8B 86 ? ? ? ? 57 83 F8 FF 74 2A", 0 },
    { "UpdateObject", "server.dll", 0x3CA010, "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 56 57 8B F9 8B 87 ? ? ? ? 89 BD", 0 },
    { "UpdateObjectVM", "server.dll", 0x3CBB10, "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 56 57 8B F9 8B 87 ? ? ? ? 83 F8", 0 },
    { "RotateObject", "server.dll", 0x3C7890, "55 8B EC 0F 57 C0 F3 0F 10 4D ? 81 EC ? ? ? ? 0F 2E C8 9F 57 8B F9 F6 C4 44 7A 12", 0 },
    { "EyeAngles", "server.dll", 0x103A50, "55 8B EC 8B 81 ? ? ? ? 83 EC 60 56 57 8B 3D ? ? ? ? 83 F8 FF 74 1D", 0 },
    { "MatrixBuildPerspectiveX", "engine.dll", 0x2737E0, "55 8B EC 83 EC 08 F2 0F 10 45 ? F2 0F 59 05 ? ? ? ?", 0 },
    { "GetFOV", "client.dll", 0x2772B0, "55 8B EC 51 56 8B F1 E8 ? ? ? ? D9 5D FC 8B 06 8B 90 ? ? ? ? 8B CE FF D2", 0 },
    { "GetDefaultFOV", "client.dll", 0x279020, "A1 ? ? ? ? F3 0F 2C 40 ? C3", 0 },
    { "GetViewModelFOV", "client.dll", 0x28AB80, "A1 ? ? ? ? D9 40 2C C3", 0 },
    { "GetOwner", "server.dll", 0xD7550, "8B 81 ? ? ? ? 83 F8 FF 74 23 8B 15 ? ? ? ?", 0 },
};

// Build 852_6 - Portal 2 dev, Exe build: Dec  1 2010
//   hint = RVA verificado. signature vacia = todavia sin portar.
static const OffsetDef kBuild852_6[] = {
    { "GetFullScreenTexture", "client.dll", 0, "", 0 },  // TODO portar
    { "RenderView", "client.dll", 0x17BAF0, "56 8B F1 6A 00 8D 8E ? ? ? ? E8 ? ? ? ?", 0 },
    { "g_pClientMode", "client.dll", 0, "", 2 },  // TODO portar
    { "CalcViewModelView", "client.dll", 0, "", 0 },  // TODO portar
    { "CreateMove", "client.dll", 0x1CC970, "A1 ? ? ? ? 83 EC 0C 83 78 30 00 57 8B F9", 0 },
    { "WriteUsercmd", "client.dll", 0x46E80, "A1 ? ? ? ? 83 78 30 00 53 8B 5C 24 ? 56 57", 0 },
    { "g_pppInput", "client.dll", 0, "", 2 },  // TODO portar
    { "PrePushRenderTarget", "client.dll", 0x8C670, "8B C1 56 8B 74 24 ? 8B 0E 89 08 8B 56 04 89", 0 },
    { "ReadUserCmd", "server.dll", 0, "", 0 },  // TODO portar
    { "ProcessUsercmds", "server.dll", 0, "", 0 },  // TODO portar
    { "CBaseEntity_entindex", "server.dll", 0, "8B 41 1C 85 C0 75 01 C3 8B 0D ? ? ? ? 2B 41 58 C1 F8 04 C3 CC", 0 },  // firma de retail sirve sin cambios
    { "EyePosition", "server.dll", 0, "", 0 },  // TODO portar
    { "PushRenderTargetAndViewport", "materialsystem.dll", 0x2C1A0, "83 EC 24 8B 44 24 ? 8B 54 24 ? 89", 0 },
    { "PopRenderTargetAndViewport", "materialsystem.dll", 0, "56 8B F1 83 7E 4C 00", 0 },  // firma de retail sirve sin cambios
    { "TraceFirePortalServer", "server.dll", 0, "", 0 },  // TODO portar
    { "CWeaponPortalgun_FirePortal", "server.dll", 0, "", 0 },  // TODO portar
    { "VGui_Paint", "engine.dll", 0, "", 0 },  // TODO portar
    { "PlayerPortalled", "client.dll", 0, "", 0 },  // TODO portar
    { "DrawSelf", "client.dll", 0, "", 0 },  // TODO portar
    { "ClipTransform", "client.dll", 0, "", 0 },  // TODO portar
    { "VGui_GetClientDLLRootPanel", "client.dll", 0, "", 0 },  // TODO portar
    { "g_pFullscreenRootPanel", "client.dll", 0, "", 2 },  // TODO portar
    { "CreatePingPointer", "client.dll", 0, "", 0 },  // TODO portar
    { "GetPortalPlayer", "client.dll", 0, "", 0 },  // TODO portar
    { "PrecacheParticleSystem", "server.dll", 0, "", 0 },  // TODO portar
    { "Precache", "server.dll", 0, "", 0 },  // TODO portar
    { "SetControlPoint", "client.dll", 0, "", 0 },  // TODO portar
    { "SetDrawOnlyForSplitScreenUser", "client.dll", 0, "", 0 },  // TODO portar
    { "StopEmission", "client.dll", 0x128D30, "53 8B 5C 24 ? 57 8B F9 F6 87 ? ? ? ? ? 74 7F", 0 },
    { "CHudCrosshair_ShouldDraw", "client.dll", 0, "57 8B F9 80 BF ? ? ? ? ? 74 04 32 C0 5F C3", 0 },  // firma de retail sirve sin cambios
    { "UTIL_Portal_FirstAlongRay", "server.dll", 0, "", 0 },  // TODO portar
    { "UTIL_IntersectRayWithPortal", "server.dll", 0x314170, "83 EC 48 56 8B 74 24 ? 85 F6 0F 84", 0 },
    { "UTIL_Portal_AngleTransform", "server.dll", 0x313730, "8B 44 24 ? 8B 4C 24 ? 83 EC 0C 50 51 8D 54 24", 0 },
    { "Weapon_ShootPosition", "server.dll", 0, "", 0 },  // TODO portar
    { "ComputeError", "server.dll", 0, "", 0 },  // TODO portar
    { "UpdateObject", "server.dll", 0, "", 0 },  // TODO portar
    { "UpdateObjectVM", "server.dll", 0, "", 0 },  // TODO portar
    { "RotateObject", "server.dll", 0, "", 0 },  // TODO portar
    { "EyeAngles", "server.dll", 0, "", 0 },  // TODO portar
    { "MatrixBuildPerspectiveX", "engine.dll", 0, "", 0 },  // TODO portar
    { "GetFOV", "client.dll", 0, "", 0 },  // TODO portar
    { "GetDefaultFOV", "client.dll", 0, "", 0 },  // TODO portar
    { "GetViewModelFOV", "client.dll", 0, "", 0 },  // TODO portar
    { "GetOwner", "server.dll", 0, "8B 81 ? ? ? ? 83 F8 FF 74 23 8B 15 ? ? ? ?", 0 },  // firma de retail sirve sin cambios
};

static const BuildProfile kProfiles[] = {
    // 0x22B4: verificado en runtime -- ahi vive el CMatRenderContext embebido,
    // su primer dword es la vtable en RVA 0x9C974.
    { "852_6-dec2010", "Dec  1 2010", kBuild852_6, (int)(sizeof(kBuild852_6)/sizeof(OffsetDef)), 0x22B4 },
    { "retail-2011",   nullptr,        kRetail2011, (int)(sizeof(kRetail2011)/sizeof(OffsetDef)), 0 },
};
static const int kProfileCount = (int)(sizeof(kProfiles)/sizeof(BuildProfile));

#include <Windows.h>
#include <psapi.h>
#include <sstream>
#include <fstream>
#include <cstring>

namespace {

struct ModuleImage { uint8_t *base = nullptr; size_t size = 0; };

ModuleImage GetImage(const char *moduleName)
{
    ModuleImage img;
    HMODULE h = GetModuleHandleA(moduleName);
    if (!h) return img;
    MODULEINFO mi{};
    if (!GetModuleInformation(GetCurrentProcess(), h, &mi, sizeof(mi))) return img;
    img.base = (uint8_t *)mi.lpBaseOfDll;
    img.size = mi.SizeOfImage;
    return img;
}

std::vector<int> ParsePattern(const char *signature)
{
    std::vector<int> pattern;
    std::stringstream ss(signature);
    std::string token;
    while (ss >> token)
        pattern.push_back((token == "?" || token == "??") ? -1 : (int)strtoul(token.c_str(), nullptr, 16));
    return pattern;
}

bool MatchesAt(const uint8_t *p, const std::vector<int> &pat)
{
    for (size_t i = 0; i < pat.size(); ++i)
        if (pat[i] != -1 && p[i] != (uint8_t)pat[i]) return false;
    return true;
}

} // namespace

std::string DetectEngineBuild()
{
    ModuleImage img = GetImage("engine.dll");
    if (!img.base) return "";
    static const char kNeedle[] = "Exe build: ";
    const size_t nlen = sizeof(kNeedle) - 1;
    for (size_t i = 0; i + nlen + 32 < img.size; ++i)
    {
        if (memcmp(img.base + i, kNeedle, nlen) != 0) continue;
        // formato: "Exe build: HH:MM:SS Mon DD YYYY" -> nos quedamos con "Mon DD YYYY"
        const char *s = (const char *)(img.base + i + nlen);
        int spaces = 0; int j = 0;
        while (j < 24 && spaces < 1) { if (s[j] == ' ') spaces++; j++; }
        std::string date;
        for (int k = j; k < j + 12 && s[k]; ++k) date.push_back(s[k]);
        while (!date.empty() && (date.back() == ' ' || date.back() == '(')) date.pop_back();
        return date;
    }
    return "";
}

const BuildProfile *SelectProfile()
{
    std::string build = DetectEngineBuild();
    if (!build.empty())
        for (int i = 0; i < kProfileCount; ++i)
            if (kProfiles[i].engineBuildDate && build == kProfiles[i].engineBuildDate)
                return &kProfiles[i];
    // fallback: el ultimo perfil (retail)
    return &kProfiles[kProfileCount - 1];
}

ResolvedOffset ResolveOffset(const BuildProfile *profile, const char *name)
{
    ResolvedOffset out;
    out.name = name;

    const OffsetDef *def = nullptr;
    for (int i = 0; i < profile->count; ++i)
        if (strcmp(profile->defs[i].name, name) == 0) { def = &profile->defs[i]; break; }

    if (!def) { out.status = ResolveStatus::NotPorted; return out; }
    out.module = def->module;

    // Biseccion: P2VR_ONLY=Nombre resuelve solo ese offset (o una lista separada
    // por comas). Sirve para aislar cual offset mal derivado hace que MinHook
    // parchee la funcion equivocada, sin tener que recompilar en cada prueba.
    {
        char only[512];
        size_t len = 0;
        if (getenv_s(&len, only, sizeof(only), "P2VR_ONLY") == 0 && len > 1)
        {
            std::string list(only);
            std::string needle = std::string(",") + name + ",";
            std::string hay = "," + list + ",";
            if (hay.find(needle) == std::string::npos)
            {
                out.status = ResolveStatus::NotPorted;
                return out;
            }
        }
    }

    if (!def->signature || def->signature[0] == '\0')
    {
        out.status = ResolveStatus::NotPorted;
        return out;
    }

    ModuleImage img = GetImage(def->module);
    if (!img.base) { out.status = ResolveStatus::NotFound; return out; }

    std::vector<int> pat = ParsePattern(def->signature);
    if (pat.empty()) { out.status = ResolveStatus::NotFound; return out; }

    // camino rapido: el hint ya coincide con la firma
    if (def->hint > 0 && (size_t)(def->hint - def->sigOffset + pat.size()) < img.size)
    {
        if (MatchesAt(img.base + def->hint - def->sigOffset, pat))
        {
            out.rva = def->hint; out.address = (uintptr_t)img.base + def->hint;
            out.matchCount = 1; out.status = ResolveStatus::Ok; out.usedHint = true;
            return out;
        }
    }

    // escaneo completo contando coincidencias (a diferencia del original, no nos
    // quedamos con la primera a ciegas: una firma ambigua es un bug, no un acierto)
    int first = -1;
    for (size_t i = 0; i + pat.size() < img.size; ++i)
    {
        if (!MatchesAt(img.base + i, pat)) continue;
        if (first < 0) first = (int)i;
        if (++out.matchCount >= 2) break;
    }

    if (out.matchCount == 0) { out.status = ResolveStatus::NotFound; return out; }
    if (out.matchCount >= 2) { out.status = ResolveStatus::Ambiguous; out.rva = first + def->sigOffset; return out; }

    out.rva = first + def->sigOffset;
    out.address = (uintptr_t)img.base + out.rva;
    out.status = ResolveStatus::Ok;
    return out;
}

void WriteOffsetReport(const BuildProfile *profile, const std::vector<ResolvedOffset> &all)
{
    char exePath[MAX_PATH]{};
    DWORD n = GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    std::string path = "Portal2VR_offsets.log";   // fallback: directorio actual
    if (n > 0)
    {
        std::string full(exePath, n);
        size_t slash = full.find_last_of("\\/");
        if (slash != std::string::npos)
            path = full.substr(0, slash + 1) + "Portal2VR_offsets.log";
    }

    std::ofstream f(path, std::ios::trunc);
    if (!f) return;

    int ok = 0, amb = 0, nf = 0, np = 0;
    for (const auto &r : all)
        switch (r.status) {
            case ResolveStatus::Ok: ok++; break;
            case ResolveStatus::Ambiguous: amb++; break;
            case ResolveStatus::NotFound: nf++; break;
            default: np++; break;
        }

    f << "Portal2VR - informe de offsets\n";
    f << "engine build detectado : " << DetectEngineBuild() << "\n";
    f << "perfil activo          : " << profile->id << "\n";
    f << "total " << all.size() << "  ok " << ok << "  ambiguas " << amb
      << "  no encontradas " << nf << "  sin portar " << np << "\n";
    f << "--------------------------------------------------------------------\n";
    for (const auto &r : all)
    {
        const char *st = "SIN_PORTAR";
        switch (r.status) {
            case ResolveStatus::Ok:        st = r.usedHint ? "OK(hint)" : "OK(scan)"; break;
            case ResolveStatus::Ambiguous: st = "AMBIGUA";  break;
            case ResolveStatus::NotFound:  st = "NO_HALLADA"; break;
            default: break;
        }
        char line[256];
        sprintf_s(line, "%-30s %-18s %-11s RVA=0x%X\n",
                  r.name.c_str(), r.module.c_str(), st, r.rva);
        f << line;
    }
    f.close();
}
