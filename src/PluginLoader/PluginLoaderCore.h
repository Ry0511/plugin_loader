//
// Date       : 22/10/2024
// Project    : plugin_loader
// Author     : -Ry
//
#ifndef PLUGIN_LOADER_PLUGINLOADERCORE_H
#define PLUGIN_LOADER_PLUGINLOADERCORE_H

#include <windows.h>

namespace plugin_loader {
    void initialise(HMODULE hmodule);
    void terminate(void);
}

#endif
