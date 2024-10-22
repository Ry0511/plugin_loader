cmake_minimum_required(VERSION 3.30)
project(plugin_loader VERSION 1.0.0 DESCRIPTION "DLL Plugin Loader from preset proxies")

add_subdirectory(./vendor/dxwrappers)

################################################################################
# PLUGIN LOADER
################################################################################

add_library(
        plugin_loader
        STATIC
        ./src/PluginLoader/PluginLoaderCore.cpp
)
set_target_properties(
        plugin_loader
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
target_include_directories(plugin_loader PUBLIC ./src)

################################################################################
# PROXIES
################################################################################

# Generic 'Build All' target
add_custom_target(plugin_loader_all DEPENDS)

foreach (target IN LISTS DXWRAPPERS_ALL_TARGETS)
    get_target_property(target_dll_name ${target} OUTPUT_NAME)
    get_target_property(target_sources ${target} SOURCES)
    get_target_property(target_link_flags ${target} LINK_FLAGS)

    set(THIS_TARGET "proxy_${target_dll_name}")
    add_library(
            ${THIS_TARGET}
            SHARED
            ./src/DllMain.cpp
            ${target_sources}
    )
    target_include_directories(${THIS_TARGET} PRIVATE ./src)
    target_link_libraries(${THIS_TARGET} PRIVATE ${target})
    target_link_libraries(${THIS_TARGET} PRIVATE plugin_loader)

    # dxwrappers use templating which relies on <17 semantics
    set_target_properties(
            ${THIS_TARGET}
            PROPERTIES
            OUTPUT_NAME ${target_dll_name}
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target_dll_name}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target_dll_name}"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target_dll_name}"
            LINK_FLAGS ${target_link_flags}
    )

    install(
            TARGETS ${THIS_TARGET}
            RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}"
    )

    message(STATUS "Created Proxy Target: '${THIS_TARGET}' for '${target_dll_name}.dll'")
    add_dependencies(plugin_loader_all ${THIS_TARGET})
endforeach ()
