project(pihud)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)
include(GenerateExportHeader)

set(PIHUD_VERSION_MAJOR "0" CACHE STRING "Major-Version")
set(PIHUD_VERSION_MINOR "6" CACHE STRING "Minor-Version")
set(PIHUD_VERSION_PATCH "0" CACHE STRING "Patch-Version")
set(PIHUD_VERSION_TWEAK "0" CACHE STRING "Tweak-Version")
set(PIHUD_VERSION ${PIHUD_VERSION_MAJOR}.${PIHUD_VERSION_MINOR}.${PIHUD_VERSION_PATCH}.${PIHUD_VERSION_TWEAK})

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRCS
    ${SRC}/HudContainer.cpp
    ${SRC}/InputEvent.cpp
    ${SRC}/Event.cpp
    ${SRC}/Widget.cpp
    ${SRC}/Config.cpp
    ${SRC}/Font.cpp
    ${SRC}/FontManager.cpp
    ${SRC}/Label.cpp
    ${SRC}/pihud.cpp
    ${SRC}/Texture.cpp
    ${SRC}/Image.cpp
    ${SRC}/IconHealthIndicator.cpp
    ${SRC}/HealthAndNameDisplay.cpp
    ${SRC}/Rect.cpp
    ${SRC}/Layout.cpp
    ${SRC}/Layouter.cpp
    ${SRC}/HorizontalListLayout.cpp
    ${SRC}/VerticalListLayout.cpp
    ${SRC}/FocusManager.cpp
    ${SRC}/FocusEvent.cpp
    ${SRC}/QueueDisplayWidget.cpp
    ${SRC}/Particle.cpp
    ${SRC}/ParticleSource.cpp
    ${SRC}/WeHaveAWinnerWidget.cpp
    ${SRC}/PigaEvent.cpp
    ${SRC}/TextureManager.cpp
    ${SRC}/MenuContainer.cpp
    ${SRC}/PushButton.cpp
)

set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/pihud/)
set(HDRS
    ${HDR}/HudContainer.hpp
    ${HDR}/Widget.hpp
    ${HDR}/Rect.hpp
    ${HDR}/Event.hpp
    ${HDR}/InputEvent.hpp
    ${HDR}/Direction.hpp
    ${HDR}/Config.hpp
    ${HDR}/pihud.hpp
    ${HDR}/Font.hpp
    ${HDR}/Label.hpp
    ${HDR}/FontManager.hpp
    ${HDR}/Texture.hpp
    ${HDR}/Image.hpp
    ${HDR}/IconHealthIndicator.hpp
    ${HDR}/HealthAndNameDisplay.hpp
    ${HDR}/QueueDisplayWidget.hpp
    ${HDR}/Particle.hpp
    ${HDR}/Layout.hpp
    ${HDR}/Layouter.hpp
    ${HDR}/HorizontalListLayout.hpp
    ${HDR}/VerticalListLayout.hpp
    ${HDR}/FocusManager.hpp
    ${HDR}/FocusEvent.hpp
    ${HDR}/WeHaveAWinnerWidget.hpp
    ${HDR}/PigaEvent.hpp
    ${HDR}/TextureManager.hpp
    ${HDR}/MenuContainer.hpp
    ${HDR}/PushButton.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

add_library(${PROJECT_NAME} SHARED ${SRCS} ${HDRS})

find_package(SDL2)
if(${SDL2_FOUND})
    target_link_libraries(pihud ${SDL2_LIBRARY})
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

find_package(SDL2image)
if(${SDL2IMAGE_FOUND})
    target_link_libraries(pihud ${SDL2IMAGE_LIBRARY})
    include_directories(${SDL2IMAGE_INCLUDE_DIRS})
endif()

find_package(SDL2ttf)
if(${SDL2TTF_FOUND})
    target_link_libraries(pihud ${SDL2TTF_LIBRARY})
    include_directories(${SDL2TTF_INCLUDE_DIRS})
endif()

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(${PROJECT_NAME} ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

find_package(Libpiga REQUIRED)
if(${Libpiga_FOUND})
    target_link_libraries(pihud ${Libpiga_LIBRARIES})
    include_directories(${Libpiga_INCLUDE_DIRS})
endif()

# Package creation code

generate_export_header(pihud)

set_property(TARGET pihud PROPERTY VESION ${PIHUD_VERSION})
set_property(TARGET pihud PROPERTY SOVERSION ${PIHUD_VERSION_MAJOR})
set_property(TARGET pihud PROPERTY
    INTERFACE_pihud_MAJOR_VERSION ${PIHUD_VERSION_MAJOR})

install(TARGETS pihud EXPORT PihudTargets
    LIBRARY DESTINATION lib
    INCLUDES DESTINATION include)

install(DIRECTORY ${HDR}
    DESTINATION include/pihud)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/PihudConfigVersion.cmake"
  VERSION ${PIHUD_VERSION}
  COMPATIBILITY AnyNewerVersion
)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/PihudConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/PihudConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cmake)

install(EXPORT PihudTargets
  FILE
    PihudTargets.cmake
  NAMESPACE
    Upstream::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/PihudConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/PihudConfig.cmake"
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindSDL2.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindSDL2image.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindSDL2ttf.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindSigC++.cmake"
  DESTINATION
    "${ConfigPackageLocation}/pihud"
)


set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A utility library to provide UI elements to SDL2 games using the piga library.")
set(CPACK_PACKAGE_VENDOR "Pigaco")
set(CPACK_PACKAGE_VERSION_MAJOR ${PIHUD_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PIHUD_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PIHUD_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PIHUD_VERSION_TWEAK})
set(CPACK_DEBIAN_PACKAGE_HOMEPAHE "https://github.com/pigaco/pihud")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libstdc++6 (>= 4.9.2-10), piga-libpiga (>= 0.6.0), libsigc++-2.0-0c2a (>= 2.4.0-1), libsdl2-2.0-0 (>= 2.0.2), libsdl2-image-2.0-0 (>= 2.0.0), libsdl2-ttf-2.0-0 (>= 2.0.12)")
set(CPACK_DEBIAN_PACKAGE_NAME "piga-libpihud")
set(CPACK_PACKAGE_NAME "piga-libpihud")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Max Heisinger <mail@maximaximal.com>")
include(CPack)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
