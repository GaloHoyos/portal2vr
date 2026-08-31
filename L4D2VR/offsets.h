#pragma once
#include "buildprofile.h"
#include <vector>
#include <string>

// Una direccion ya resuelta contra el modulo cargado.
// Se conservan los nombres de campo del proyecto original para no tocar hooks.cpp.
struct Offset
{
    std::string   moduleName;
    int           offset  = 0;
    uintptr_t     address = 0;
    ResolveStatus status  = ResolveStatus::NotPorted;

    bool ok() const { return status == ResolveStatus::Ok; }
};

#define P2VR_RESOLVE(NAME)                         \
    do {                                           \
        ResolvedOffset r = ResolveOffset(profile, #NAME); \
        NAME.moduleName = r.module;                \
        NAME.offset     = r.rva;                   \
        NAME.address    = r.address;               \
        NAME.status     = r.status;                \
        report.push_back(r);                       \
    } while (0)

class Offsets
{
public:
    const BuildProfile         *profile = nullptr;
    std::vector<ResolvedOffset> report;

    Offset GetFullScreenTexture;
    Offset RenderView;
    Offset g_pClientMode;
    Offset CalcViewModelView;
    Offset CreateMove;
    Offset WriteUsercmd;
    Offset g_pppInput;
    Offset PrePushRenderTarget;
    Offset ReadUserCmd;
    Offset ProcessUsercmds;
    Offset CBaseEntity_entindex;
    Offset EyePosition;
    Offset PushRenderTargetAndViewport;
    Offset PopRenderTargetAndViewport;
    Offset TraceFirePortalServer;
    Offset CWeaponPortalgun_FirePortal;
    Offset VGui_Paint;
    Offset PlayerPortalled;
    Offset MsgFunc_EntityPortalled;
    Offset DrawSelf;
    Offset ClipTransform;
    Offset VGui_GetClientDLLRootPanel;
    Offset g_pFullscreenRootPanel;
    Offset CreatePingPointer;
    Offset GetPortalPlayer;
    Offset PrecacheParticleSystem;
    Offset Precache;
    Offset SetControlPoint;
    Offset SetDrawOnlyForSplitScreenUser;
    Offset StopEmission;
    Offset CHudCrosshair_ShouldDraw;
    Offset UTIL_Portal_FirstAlongRay;
    Offset UTIL_IntersectRayWithPortal;
    Offset UTIL_Portal_AngleTransform;
    Offset Weapon_ShootPosition;
    Offset ComputeError;
    Offset UpdateObject;
    Offset UpdateObjectVM;
    Offset RotateObject;
    Offset EyeAngles;
    Offset MatrixBuildPerspectiveX;
    Offset GetFOV;
    Offset GetDefaultFOV;
    Offset GetViewModelFOV;
    Offset GetOwner;

    Offsets()
    {
        profile = SelectProfile();
        P2VR_RESOLVE(GetFullScreenTexture);
        P2VR_RESOLVE(RenderView);
        P2VR_RESOLVE(g_pClientMode);
        P2VR_RESOLVE(CalcViewModelView);
        P2VR_RESOLVE(CreateMove);
        P2VR_RESOLVE(WriteUsercmd);
        P2VR_RESOLVE(g_pppInput);
        P2VR_RESOLVE(PrePushRenderTarget);
        P2VR_RESOLVE(ReadUserCmd);
        P2VR_RESOLVE(ProcessUsercmds);
        P2VR_RESOLVE(CBaseEntity_entindex);
        P2VR_RESOLVE(EyePosition);
        P2VR_RESOLVE(PushRenderTargetAndViewport);
        P2VR_RESOLVE(PopRenderTargetAndViewport);
        P2VR_RESOLVE(TraceFirePortalServer);
        P2VR_RESOLVE(CWeaponPortalgun_FirePortal);
        P2VR_RESOLVE(VGui_Paint);
        P2VR_RESOLVE(PlayerPortalled);
        P2VR_RESOLVE(MsgFunc_EntityPortalled);
        P2VR_RESOLVE(DrawSelf);
        P2VR_RESOLVE(ClipTransform);
        P2VR_RESOLVE(VGui_GetClientDLLRootPanel);
        P2VR_RESOLVE(g_pFullscreenRootPanel);
        P2VR_RESOLVE(CreatePingPointer);
        P2VR_RESOLVE(GetPortalPlayer);
        P2VR_RESOLVE(PrecacheParticleSystem);
        P2VR_RESOLVE(Precache);
        P2VR_RESOLVE(SetControlPoint);
        P2VR_RESOLVE(SetDrawOnlyForSplitScreenUser);
        P2VR_RESOLVE(StopEmission);
        P2VR_RESOLVE(CHudCrosshair_ShouldDraw);
        P2VR_RESOLVE(UTIL_Portal_FirstAlongRay);
        P2VR_RESOLVE(UTIL_IntersectRayWithPortal);
        P2VR_RESOLVE(UTIL_Portal_AngleTransform);
        P2VR_RESOLVE(Weapon_ShootPosition);
        P2VR_RESOLVE(ComputeError);
        P2VR_RESOLVE(UpdateObject);
        P2VR_RESOLVE(UpdateObjectVM);
        P2VR_RESOLVE(RotateObject);
        P2VR_RESOLVE(EyeAngles);
        P2VR_RESOLVE(MatrixBuildPerspectiveX);
        P2VR_RESOLVE(GetFOV);
        P2VR_RESOLVE(GetDefaultFOV);
        P2VR_RESOLVE(GetViewModelFOV);
        P2VR_RESOLVE(GetOwner);
        WriteOffsetReport(profile, report);
    }
};
