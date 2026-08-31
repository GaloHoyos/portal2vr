// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include "game.h"
#include "hooks.h"
#include "vr.h"
#include "sdk.h"

DWORD WINAPI InitL4D2VR(HMODULE hModule)
{
// Release if buggy, so we'll be releasing the debug binary
#ifdef _DEBUG
    AllocConsole();
    FILE *fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
#endif

    // P2VR_DISABLE=1 deja DXVK puro, sin nada del mod. Control de aislamiento.
    {
        char off[8]; size_t n = 0;
        if (getenv_s(&n, off, sizeof(off), "P2VR_DISABLE") == 0 && n > 1)
            return 0;
    }

    // Make sure -insecure is used
    LPWSTR *szArglist;
    int nArgs;
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    bool insecureEnabled = false;
    for (int i = 0; i < nArgs; ++i)
    {
        if (wcscmp(szArglist[i], L"-insecure") == 0)
            insecureEnabled = true;
    }
    LocalFree(szArglist);

    if (!insecureEnabled)
        ExitProcess(0);

    // P2VR_STAGE=0 corta aca: se hizo el chequeo de -insecure pero no se
    // construye Game. Aisla el chequeo de los bucles de espera de modulos.
    {
        char v[8]; size_t n = 0;
        if (getenv_s(&n, v, sizeof(v), "P2VR_STAGE") == 0 && n > 1 && atoi(v) == 0)
            return 0;
    }

    // Construir primero y publicar despues: el hilo de render de DXVK consulta
    // g_Game, y el constructor tarda (espera a que carguen los modulos del
    // juego). Si se asigna antes, ese hilo ve un Game a medio armar.
    Game *game = new Game();
    g_Game = game;

    return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitL4D2VR, hModule, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


