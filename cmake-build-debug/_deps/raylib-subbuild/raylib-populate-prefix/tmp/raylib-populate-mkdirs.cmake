# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-src"
  "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-build"
  "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix"
  "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/tmp"
  "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
  "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src"
  "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Volumes/2TBSSD/Dev/C/GameOfLive/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
