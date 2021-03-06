###############################################################################
# Copyright (c) 2018-2020 LunarG, Inc.
# Copyright (c) 2019-2020 Advanced Micro Devices, Inc.
# All rights reserved
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#
# Author: LunarG Team
# Author: AMD Developer Tools Team
# Description: CMake script for framework util target
###############################################################################

add_library(gfxrecon_application STATIC "")

target_sources(gfxrecon_application
               PRIVATE
                    ${CMAKE_CURRENT_LIST_DIR}/application.h
                    ${CMAKE_CURRENT_LIST_DIR}/application.cpp
                    $<$<BOOL:${XCB_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/xcb_application.h>
                    $<$<BOOL:${XCB_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/xcb_window.h>
                    $<$<BOOL:${XCB_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/xcb_application.cpp>
                    $<$<BOOL:${XCB_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/xcb_window.cpp>
                    $<$<BOOL:${X11_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/xlib_application.h>
                    $<$<BOOL:${X11_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/xlib_window.h>
                    $<$<BOOL:${X11_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/xlib_application.cpp>
                    $<$<BOOL:${X11_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/xlib_window.cpp>
                    $<$<BOOL:${WAYLAND_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/wayland_application.h>
                    $<$<BOOL:${WAYLAND_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/wayland_window.h>
                    $<$<BOOL:${WAYLAND_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/wayland_application.cpp>
                    $<$<BOOL:${WAYLAND_FOUND}>:${CMAKE_CURRENT_LIST_DIR}/wayland_window.cpp>
                    $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_LIST_DIR}/win32_application.h>
                    $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_LIST_DIR}/win32_window.h>
                    $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_LIST_DIR}/win32_application.cpp>
                    $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_LIST_DIR}/win32_window.cpp>
              )

target_include_directories(gfxrecon_application
                           PUBLIC
                               $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)

target_link_libraries(gfxrecon_application
                      gfxrecon_decode
                      gfxrecon_graphics
                      gfxrecon_format
                      gfxrecon_util
                      vulkan_registry
                      platform_specific
                     )

common_build_directives(gfxrecon_application)

if (${RUN_TESTS})
    add_executable(gfxrecon_application_test "")
    target_sources(gfxrecon_application_test PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/test/main.cpp)
    target_link_libraries(gfxrecon_application_test PRIVATE gfxrecon_application)
    common_build_directives(gfxrecon_application_test)
    common_test_directives(gfxrecon_application_test)
endif()

