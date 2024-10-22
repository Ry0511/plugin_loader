cmake_minimum_required(VERSION 3.23)

function(dxwrapper_init_target target dllname src_dir)
    file(
            GLOB_RECURSE
            TARGET_SOURCE_FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/${src_dir}/*.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/${src_dir}/*.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/${src_dir}/*.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/${src_dir}/*.cpp"
    )
    file(
            GLOB_RECURSE
            TARGET_EXPORT_DEF
            "${CMAKE_CURRENT_SOURCE_DIR}/${src_dir}/*.def"
    )

    # Pedantic
    list(LENGTH TARGET_EXPORT_DEF DXWRAPPER_EXPORT_DEF_COUNT)
    if (DXWRAPPER_EXPORT_DEF_COUNT GREATER 1)
        message(FATAL_ERROR "More than one .def file found: ${TARGET_EXPORT_DEF}")
    elseif (DXWRAPPER_EXPORT_DEF_COUNT EQUAL 0)
        message(FATAL_ERROR "Failed to find .def file for: ${TARGET_EXPORT_DEF}")
    endif ()

    # Init Target
    add_library(${target} INTERFACE ${TARGET_SOURCE_FILES})
    set_target_properties(${target} PROPERTIES OUTPUT_NAME ${dllname})
    target_include_directories(${target} INTERFACE ./)
    target_include_directories(${target} INTERFACE ./DirectX81SDK/include)

    # Definitions
    if (DXWRAPPER_EXPORT_DEF_COUNT EQUAL 1)
        set_target_properties(
                ${target}
                PROPERTIES
                LINK_FLAGS "/DEF:${TARGET_EXPORT_DEF}"
        )
    endif ()

    # Hacky but we copy the list and then modify because... cmake.
    set(DXWRAPPERS_ALL_TARGETS ${ARGN} PARENT_SCOPE)
    list(APPEND DXWRAPPERS_ALL_TARGETS ${target})
    set(DXWRAPPERS_ALL_TARGETS ${DXWRAPPERS_ALL_TARGETS} PARENT_SCOPE)

    message(STATUS "Created target ${target} with sources: ${TARGET_SOURCE_FILES}")

endfunction()

dxwrapper_init_target(_dxwrapper_dsound dsound dsound)
dxwrapper_init_target(_dxwrapper_d3d8 d3d8 d3d8)
dxwrapper_init_target(_dxwrapper_d3d9 d3d9 d3d9)
dxwrapper_init_target(_dxwrapper_ddraw ddraw ddraw)
dxwrapper_init_target(_dxwrapper_dinput dinput dinput)
dxwrapper_init_target(_dxwrapper_dinput8 dinput8 dinput8)

# Expose to parent
set(DXWRAPPERS_ALL_TARGETS ${ARGN} PARENT_SCOPE)
set(DXWRAPPERS_ALL_TARGETS ${DXWRAPPERS_ALL_TARGETS} PARENT_SCOPE)