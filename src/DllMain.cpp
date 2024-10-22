//
// Date       : 22/10/2024
// Project    : plugin_loader
// Author     : -Ry
//

#include <windows.h>
#include "PluginLoader/PluginLoaderCore.h"

// This just wraps the original DllMain provided in dxwrapper; So we can forward the call
extern BOOL WINAPI plugin_loader_dll_main_wrapped(HMODULE, DWORD, LPVOID);

BOOL WINAPI DllMain(HMODULE hmodule, DWORD fdw_raisins, LPVOID lp_reserved) {
    plugin_loader_dll_main_wrapped(hmodule, fdw_raisins, lp_reserved);

    switch (fdw_raisins) {
        case DLL_PROCESS_ATTACH:
            plugin_loader::initialise(hmodule);
            break;
        case DLL_PROCESS_DETACH:
            plugin_loader::terminate();
            break;
        default:
            break;
    }

    return TRUE;
}