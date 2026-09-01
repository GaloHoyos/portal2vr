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
    { "MsgFunc_EntityPortalled", "client.dll", 0, "", 0 },  // sin derivar: retail ya usa PlayerPortalled
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
    { "RenderView", "client.dll", 0x197F10, "55 8B EC 83 E4 C0 81 EC 34 02 00 00 53 56 57 8B F9 6A 00 8D 8F ? ? ? ? 89 7C 24", 0 },  // RTTI CViewRender[6]; el [3] es Shutdown()
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
    { "MsgFunc_EntityPortalled", "client.dll", 0, "", 0 },  // TODO: el string existe pero el registro no usa push
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

// Build corehub / 852_0 - Portal 2 dev, Exe build: Jul 28 2009
//   El mas lejano de retail de todos los builds filtrados: 21 meses de drift.
//   Ninguna firma de 852_6 sirve aca, hay que derivarlas de cero.
static const OffsetDef kBuild852_0[] = {
    { "GetFullScreenTexture", "client.dll", 0, "", 0 },  // TODO Fase E
    { "RenderView", "client.dll", 0x181120, "81 EC BC 01 00 00 53 55 8B E9 6A 00 8D 8D ? ? ? ? E8", 0 },  // RTTI CViewRender[6]; el [3] es Shutdown()
    { "g_pClientMode", "client.dll", 0, "", 2 },  // TODO Fase E
    { "CalcViewModelView", "client.dll", 0x143D0, "83 EC 74 8B 84 24 80 00 00 00 F3 0F 7E 00 53 56 8B F1 8B 48 08", 0 },  // C_BaseViewModel::CalcViewModelView(owner, pos, ang): unico lector de viewmodel_offset_x, y slot [204] de C_BaseViewModel
    { "CreateMove", "client.dll", 0x95940, "6A FF E8 ? ? ? ? 83 C4 04 85 C0 75 ? B0 01 C2 08 00 8B 4C 24 08", 0 },  // ClientModeShared::CreateMove, RTTI ClientModePortalNormal[23]
    { "WriteUsercmd", "client.dll", 0, "", 0 },  // TODO Fase E
    { "g_pppInput", "client.dll", 0, "", 2 },  // TODO Fase E
    { "PrePushRenderTarget", "client.dll", 0, "", 0 },  // TODO Fase E
    { "ReadUserCmd", "server.dll", 0, "", 0 },  // TODO Fase E
    { "ProcessUsercmds", "server.dll", 0, "", 0 },  // TODO Fase E
    { "CBaseEntity_entindex", "server.dll", 0x1A150, "8B 41 1C 85 C0 75 01 C3 8B 0D ? ? ? ? 2B 41 58 C1 F8 04 C3 CC", 0 },  // la firma de retail sirve sin cambios
    { "EyePosition", "server.dll", 0, "", 0 },  // TODO Fase E
    { "PushRenderTargetAndViewport", "materialsystem.dll", 0x27DF0, "83 EC 24 8B 44 24 ? 8B 54 24 ? 89 04 24 33 C0 56 8B F1", 0 },  // CMatRenderContext[104], el overload de 6 args
    { "PopRenderTargetAndViewport", "materialsystem.dll", 0x276F0, "56 8B F1 83 7E 50 00 74 ? 8B 06 8B 50 10", 0 },  // CMatRenderContext[108]; retail usa +0x4C, aca +0x50
    { "TraceFirePortalServer", "server.dll", 0x3269F0, "55 8B EC 83 E4 F0 81 EC 24 07 00 00 53 56 57 8B F1 33 DB 53 56 8D 4C 24 ?", 0 },  // this+5 params (Vector*, Vector*, bool, int, trace*); unico llamado desde FirePortal
    { "CWeaponPortalgun_FirePortal", "server.dll", 0x326EE0, "81 EC 18 01 00 00 53 55 56 57 8B E9 C6 44 24 12 00 E8 ? ? ? ? 8B D8 85 DB", 0 },  // this+2 params (bool, Vector*); unico llamador de TraceFirePortal
    { "VGui_Paint", "engine.dll", 0, "", 0 },  // TODO Fase E
    { "PlayerPortalled", "client.dll", 0, "", 0 },  // TODO Fase E
    { "MsgFunc_EntityPortalled", "client.dll", 0x1D4BD0, "81 EC ? ? ? ? 53 55 56 8B B4 24 ? ? ? ? 8B 4E 14 33 DB 83 F9 20", 0 },  // handler del user message, ubicado por HookMessage("EntityPortalled", handler)
    { "DrawSelf", "client.dll", 0xD60C0, "56 8B F1 80 BE 80 00 00 00 00 74 ? 8B 0D ? ? ? ? 8B 01 8B 96 84 00 00 00 8B 40 50", 0 },  // CHudTexture::DrawSelf(x,y,w,h,clr): ret 0x14, sin flApparentZ. Lo llama el overload de 3 args desde CHudCrosshair::Paint
    { "ClipTransform", "client.dll", 0x16D550, "8B 0D ? ? ? ? 8B 01 8B 90 94 00 00 00 FF D2 8B 4C 24 04 F3 0F 10 40 08 F3 0F 59 41 08", 0 },  // engine->WorldToScreenMatrix() en el slot 0x94, transform 4x4 y divide por w
    { "VGui_GetClientDLLRootPanel", "client.dll", 0, "", 0 },  // TODO Fase E
    { "g_pFullscreenRootPanel", "client.dll", 0, "", 2 },  // TODO Fase E
    { "CreatePingPointer", "client.dll", 0, "", 0 },  // TODO Fase E
    { "GetPortalPlayer", "client.dll", 0, "", 0 },  // TODO Fase E
    { "PrecacheParticleSystem", "server.dll", 0x13DEE0, "8B 0D ? ? ? ? 8B 54 24 04 8B 01 8B 40 20 6A 00 6A FF 52 6A 01 FF D0 C3", 0 },  // 3 vecinas identicas salvo el global; el hint desambigua (no se puede fijar la direccion: el loader la reubica)
    { "Precache", "server.dll", 0x327D70, "E8 ? ? ? ? 68 ? ? ? ? E8 ? ? ? ? 68 ? ? ? ? E8 ? ? ? ? 68 ? ? ? ? E8 ? ? ? ? 68 ? ? ? ? E8", 0 },  // CWeaponPortalgun::Precache: cadena de push/call de precacheo
    { "SetControlPoint", "client.dll", 0, "", 0 },  // TODO Fase E
    { "SetDrawOnlyForSplitScreenUser", "client.dll", 0, "", 0 },  // TODO Fase E
    { "StopEmission", "client.dll", 0, "", 0 },  // TODO Fase E
    { "CHudCrosshair_ShouldDraw", "client.dll", 0, "", 0 },  // TODO Fase E
    { "UTIL_Portal_FirstAlongRay", "server.dll", 0, "", 0 },  // TODO Fase E
    { "UTIL_IntersectRayWithPortal", "server.dll", 0, "", 0 },  // TODO Fase E
    { "UTIL_Portal_AngleTransform", "server.dll", 0, "", 0 },  // TODO Fase E
    { "Weapon_ShootPosition", "server.dll", 0, "", 0 },  // TODO Fase E
    { "ComputeError", "server.dll", 0, "", 0 },  // TODO Fase E
    { "UpdateObject", "server.dll", 0, "", 0 },  // TODO Fase E
    { "UpdateObjectVM", "server.dll", 0, "", 0 },  // TODO Fase E
    { "RotateObject", "server.dll", 0, "", 0 },  // TODO Fase E
    { "EyeAngles", "server.dll", 0, "", 0 },  // TODO Fase E
    { "MatrixBuildPerspectiveX", "engine.dll", 0, "", 0 },  // TODO Fase E
    { "GetFOV", "client.dll", 0, "", 0 },  // TODO Fase E
    { "GetDefaultFOV", "client.dll", 0, "", 0 },  // TODO Fase E
    { "GetViewModelFOV", "client.dll", 0x964C0, "A1 ? ? ? ? D9 40 2C C3", 0 },  // lee viewmodel_fov+0x1C (m_pParent); unico lector en el modulo
    { "GetOwner", "server.dll", 0, "", 0 },  // TODO Fase E
};

// --- Capas ABI por build -----------------------------------------------------
//
// Los indices se derivaron con tools/vrport (vtable por RTTI) mas Ghidra
// (prototipos decompilados). Cada uno se verifico por separado: el corrimiento
// contra retail no es uniforme dentro de una misma vtable.

// El CViewSetup de Source antes del splitscreen: sin los cuatro m_nUnscaled*
// que retail intercala entre x/y/width/height, asi que todo lo de abajo queda
// corrido. Lo usan corehub (jul 2009) y 852_6 (dic 2010).
static constexpr ViewSetupLayout ViewSetupClassicSource()
{
    ViewSetupLayout v{};
    v.x              = 0x00;
    v.y              = 0x04;
    v.width          = 0x08;
    v.height         = 0x0C;
    v.unscaledWidth  = -1;      // no existen todavia
    v.unscaledHeight = -1;
    v.fov            = 0x24;
    v.fovViewmodel   = 0x28;
    v.origin         = 0x2C;
    v.angles         = 0x38;
    v.zNear          = 0x44;
    v.zNearViewmodel = 0x4C;
    v.aspectRatio    = 0x54;
    return v;
}

static constexpr AbiLayout AbiRetail2011()
{
    AbiLayout a{};
    // Todos los indices quedan en kAbiCxx: las declaraciones de sdk/material.h
    // y sdk/sdk.h son justamente las de retail, asi que las pone el compilador.
    // Lo unico que hace falta explicito es el offset de struct.
    a.msIsGameRunning = 0x2BB0;   // = offsetof(CMaterialSystem, isGameRunning)
    return a;
}

static constexpr AbiLayout AbiBuild852_6()
{
    AbiLayout a{};
    // Verificado en runtime: ahi vive el CMatRenderContext embebido, y su
    // primer dword es la vtable en RVA 0x9C974.
    a.msRenderContextEmbedded  = 0x22B4;
    a.msRenderContextVtableRva = 0x9C974;

    // IMaterialSystem. Mismo patron que corehub: delta -2 hasta
    // GetBackBufferFormat (SpewDriverInfo, retail 33, cae en 31) y -3 desde
    // SupportsHDRMode (BeginFrame, retail 41, cae en 38). O sea que a este
    // build tampoco le existe GetAspectRatioInfo, que es posterior a dic 2010.
    a.msGetBackBufferFormat = 33;   // retail 35
    // Y -4 en la zona de los render targets. El grupo se identifica por el
    // conteo de parametros: [88] y [89] 0 params, [90] 5, [91] 8, [92] 8 con
    // dos char (CreateNamedRenderTargetTexture) y [93] 8.
    a.msBeginRenderTargetAllocation      = 88;   // retail 92
    a.msEndRenderTargetAllocation        = 89;   // retail 93
    a.msCreateNamedRenderTargetTextureEx = 91;   // retail 95

    // Esta era la causa del crash historico de este build. El mod llamaba el
    // indice 92 creyendo que era BeginRenderTargetAllocation; en 852_6 el 92 es
    // CreateNamedRenderTargetTexture, de ocho argumentos, invocada sin ninguno.
    // "Completaba" y dejaba la pila rota, y el proceso moria despues.

    // BeginRenderTargetAllocation decompilado se autoidentifica por su Warning
    // y solo incrementa el contador si this[0x2b58] es 0.
    a.msIsGameRunning = 0x2B58;   // retail 0x2BB0, corehub 0x2A88

    // IMatRenderContext. SetRenderTarget y ClearBuffers coinciden en shape con
    // los de corehub, que estan verificados por decompilacion.
    a.rcRelease         = 1;
    a.rcSetRenderTarget = 6;
    a.rcClearBuffers    = 12;

    // Sin derivar. Retail los tiene en 74 y 185, pero la vtable de este build
    // esta corrida (Viewport 38 vs 39, Pop 109 vs 111) y no de forma uniforme,
    // asi que el indice de retail no sirve. Se saltean: solo los usa el camino
    // del HUD. Llamarlos por el indice equivocado corrompe la pila, que es
    // justo el bug que costo mas caro encontrar en corehub.
    a.rcClearColor4ub            = kAbiUnknown;
    a.rcOverrideAlphaWriteEnable = kAbiUnknown;

    // Retail lo tiene en 108, pero ese slot en este build es un setter de un
    // byte de estado (E8 <call>; mov cl,[esp+4]), o sea SetRestrictServerCommands.
    // Pasarle un const char* a eso escribe basura. Se saltea hasta derivarlo.
    a.ecClientCmdUnrestricted = kAbiUnknown;

    // ISurface: corehub esta -2 contra este build, y el 54 de corehub esta
    // verificado en runtime, asi que estos dos son los de retail.
    a.sfIsCursorVisible = 56;
    a.sfGetScreenSize   = 42;

    // Mismo layout clasico que corehub. Dic 2010 sigue sin los m_nUnscaled*,
    // que llegan con el splitscreen de retail. Sin verificar contra el struct
    // vivo: si el estereo sale deformado aca, esto es lo primero que hay que
    // volcar (ver el bloque VS+ de dRenderView).
    a.vs = ViewSetupClassicSource();

    // vtable[242] de C_Portal_Player no esta verificado en este build, y los
    // offsets de C_Portal_Player y CWeaponPortalBase tampoco.
    a.laserAimSupported = false;
    return a;
}

static constexpr AbiLayout AbiBuild852_0()
{
    AbiLayout a{};

    // IMaterialSystem. Delta contra retail: -2 hasta GetBackBufferFormat, -3
    // desde SupportsHDRMode (falta GetAspectRatioInfo, que es posterior a 2009),
    // y -10 en la zona de los render targets.
    a.msGetBackBufferFormat              = 33;   // retail 35
    a.msBeginRenderTargetAllocation      = 82;   // retail 92, 0 params
    a.msEndRenderTargetAllocation        = 83;   // retail 93, 0 params
    a.msCreateNamedRenderTargetTextureEx = 85;   // retail 95, 8 params

    // De CMaterialSystem::BeginFrame decompilado: cuando el contexto
    // thread-local es null cae a (CMaterialSystem*)this + 0x899 ints = +0x2264.
    a.msRenderContextEmbedded  = 0x2264;
    a.msRenderContextVtableRva = 0x943C4;

    // Identificado decompilando BeginRenderTargetAllocation, que se autoidentifica
    // por su Warning "Tried BeginRenderTargetAllocation after game startup":
    //
    //   if (this[0x2a88] == 0) { this[0x2a84]++; ... } else { Warning(...); }
    //
    // y CreateNamedRenderTargetTextureEx devuelve NULL si this[0x2a84] == 0.
    // O sea que sin bajar este flag no se puede asignar ningun render target
    // despues del arranque, que es exactamente para lo que el mod lo usa.
    a.msIsGameRunning = 0x2A88;  // retail 0x2BB0

    // IVEngineClient. corehub tiene un metodo insertado en el slot 14, asi que
    // de ahi en adelante va corrido +1 contra retail. Verificado decompilando:
    // el slot 20 contiene el literal
    //   "CEngineClient::SetViewAngles:  rejecting invalid value [%f %f %f]"
    // y el 26 hace return state[0x68] == 6, o sea SIGNONSTATE_FULL.
    a.ecClientCmd      = 7;      // igual que retail
    a.ecGetLocalPlayer = 12;     // igual que retail
    a.ecGetViewAngles  = 19;     // retail 18
    a.ecSetViewAngles  = 20;     // retail 19
    a.ecIsInGame       = 26;     // retail 25

    // Verificado decompilando: es ClientCmd (slot 7) sin la envoltura de
    // restriccion. ClientCmd empuja los marcadores 99 y 100 alrededor del
    // comando si el flag state[0x49f5] esta puesto; este hace el mismo
    // MakeStr + Exec del comando y del separador sin esos marcadores, y
    // despues llama a Cbuf_Execute.
    //
    // El indice de retail (108) no servia: ese slot en este build es
    // SetRestrictServerCommands, que toma un bool.
    a.ecClientCmdUnrestricted = 105;   // retail 108

    // ISurface. CMatSystemSurface va corrido -2 contra 852_6, verificado
    // comparando las shapes de los slots 40-43 y 54-58.
    a.sfIsCursorVisible = 54;   // retail 56
    a.sfGetScreenSize   = 40;   // retail 42

    // CViewSetup: layout clasico de Source, sin los m_nUnscaled* que retail
    // intercala. Verificado volcando el struct crudo que pasa el engine:
    //   +0x08/+0x0C = 1280/720 (el viewport)
    //   +0x24 = 73.74 (fov), +0x2C = origin, +0x38 = angles
    //   +0x58..+0x6C = 20/100/250/1000/10/5, los DoF por defecto, que marcan
    //   donde termina el bloque de zNear/zFar/aspect.
    a.vs = ViewSetupClassicSource();

    // vtable[242] de C_Portal_Player no esta verificado en este build, y los
    // offsets de C_Portal_Player y CWeaponPortalBase tampoco.
    a.laserAimSupported = false;

    // El offset apunta a C_BaseViewModel::CalcViewModelView, no a la del
    // jugador: en corehub esa no quedo como funcion separada.
    a.calcViewModelViewTakesOwner = true;

    // Su DrawSelf termina en "ret 0x14": 5 params + this, sin flApparentZ.
    a.drawSelfHasApparentZ = false;

    // Calibrado con el visor puesto: equivale a viewmodel_offset_x/y/z en
    // -9/-9/9 sobre el default de upstream. Va con el signo invertido porque
    // esas ConVars suman y este offset se resta.
    a.viewmodelOffsetX = 13.5f;
    a.viewmodelOffsetY = 8.0f;
    a.viewmodelOffsetZ = -7.5f;

    // Retail los tiene en 114/133/139, y la vtable de corehub tiene ~90 slots:
    // el override de tamano de pantalla no existe en este build. Los tres se
    // usan juntos en VR::SetScreenSizeOverride, que queda como no-op.
    a.sfForceScreenSizeOverride    = kAbiUnknown;
    a.sfOnScreenSizeChanged        = kAbiUnknown;
    a.sfIsScreenSizeOverrideActive = kAbiUnknown;

    // IInput (CInputWin32) no necesita entradas: las vtables de corehub y 852_6
    // coinciden byte a byte en los slots que usa el mod (SetCursorPos 7,
    // InternalMouseWheeled 71).

    // IMatRenderContext.
    a.rcRelease         = 1;     // heredado de IRefCounted
    a.rcSetRenderTarget = 6;     // igual que retail
    a.rcClearBuffers    = 12;    // igual que retail: llama vt[8] y shaderapi+0xF8
    a.rcClearColor4ub   = 73;    // retail 74; shaderapi+0x100

    // Sin identificar: el dump paso el final real de la vtable y no se puede
    // confiar en los slots del final. Solo lo usa el camino del HUD, que no
    // esta en el camino critico de estereo + head tracking.
    a.rcOverrideAlphaWriteEnable = kAbiUnknown;
    return a;
}

static const BuildProfile kProfiles[] = {
    { "852_0-jul2009", "Jul 28 2009", kBuild852_0, (int)(sizeof(kBuild852_0)/sizeof(OffsetDef)), AbiBuild852_0() },
    { "852_6-dec2010", "Dec  1 2010", kBuild852_6, (int)(sizeof(kBuild852_6)/sizeof(OffsetDef)), AbiBuild852_6() },
    { "retail-2011",   nullptr,       kRetail2011, (int)(sizeof(kRetail2011)/sizeof(OffsetDef)), AbiRetail2011() },
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
