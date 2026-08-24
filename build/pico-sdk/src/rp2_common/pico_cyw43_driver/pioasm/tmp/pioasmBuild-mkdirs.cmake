# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/vyl/pico/pico-sdk/tools/pioasm"
  "/Users/vyl/Desktop/MusicBox/build/pioasm"
  "/Users/vyl/Desktop/MusicBox/build/pioasm-install"
  "/Users/vyl/Desktop/MusicBox/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/Users/vyl/Desktop/MusicBox/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "/Users/vyl/Desktop/MusicBox/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/Users/vyl/Desktop/MusicBox/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/vyl/Desktop/MusicBox/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/vyl/Desktop/MusicBox/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
