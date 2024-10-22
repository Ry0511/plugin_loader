# Plugin Loader

An extension of [DLL Plugin Loader](https://github.com/bl-sdk/pluginloader) by apple1417 which
loads DLL files from a `./Plugins` folder.

# Notes

I have only tested `d3d9.dll` and `dsound.dll` for x86. All other targets have not been tested.

# Credits

- - -

`src/PluginLoader/PluginLoader.cpp` is adapted from [DLL Plugin Loader](https://github.com/bl-sdk/pluginloader)
and has been modified slightly. Granted this snippet is just getting execting directory and then
calling `LoadLibrary` it was still copied.

- - -

vendor/dxwrappers is from [DirectX-Wrappers](https://github.com/elishacloud/DirectX-Wrappers)
and has been modified. Where modifications are made comments are present using the format:
'NOTE: Modified by plugin_loader; -Ry (2024/10/22)'. The license can be found at
[LICENSE](./vendor/dxwrapper/License.txt)

Full changes are:

1. Disable/removed logging
2. All DllMain functions became `BOOL WINAPI plugin_loader_dll_main_wrapped(HMODULE, DWORD, LPVOID);`
3. Added: CMakeLists.txt which creates the proxy targets
4. Added: NOTE.txt which contains information about where the content was obtained