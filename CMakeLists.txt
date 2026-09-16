# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# lvgl/lvgl 9.6.0 (published Sept 2026) is the first LVGL release whose registry
# manifest carries optional dependencies gated on LVGL-9-only Kconfig symbols:
# LV_USE_LIBPNG, LV_USE_LZ4, LV_USE_LIBJPEG_TURBO. This project is pinned to
# LVGL 8.4, which does not define any of them, but esp_lvgl_port and the
# Waveshare BSP both declare "lvgl/lvgl >=8,<10", so the component manager's
# "check for new versions" pass evaluates 9.6.0's manifest anyway, finds those
# symbols missing, and aborts with:
#     CMake Error ... Missing required kconfig option after retry.
# Every dependency here is deliberately pinned, so the update notice has no
# value — turn the check off. Revisit if/when this project moves to LVGL 9.
set(ENV{IDF_COMPONENT_CHECK_NEW_VERSION} "0")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

add_compile_options(-Wno-format)
add_compile_options(-Wno-ignored-qualifiers)
project(trailcurrent_fluidcnc_pendant)
