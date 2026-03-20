cmake_minimum_required(VERSION 3.21)
project(numops VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library target
add_library(numops src/numops.cpp)
add_library(numops::numops ALIAS numops)

target_include_directories(numops
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Install rules
include(GNUInstallDirs)

install(TARGETS numops
  EXPORT numopsTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/numops
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# CMake package config for find_package(numops CONFIG REQUIRED)
install(EXPORT numopsTargets
  FILE numopsTargets.cmake
  NAMESPACE numops::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/numops
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/numopsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/numopsConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/numops
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/numopsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/numopsConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/numopsConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/numops
)

# Testing
option(BUILD_TESTING "Build unit tests" ON)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
