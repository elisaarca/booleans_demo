# Install script for directory: /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/arrangements/external/oneTBB

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/arrangements/external/oneTBB/include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TBB/TBBTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TBB/TBBTargets.cmake"
         "/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/CMakeFiles/Export/50bf70e196cec95d4d513cf01ed33e20/TBBTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TBB/TBBTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TBB/TBBTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/TBB" TYPE FILE FILES "/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/CMakeFiles/Export/50bf70e196cec95d4d513cf01ed33e20/TBBTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/TBB" TYPE FILE FILES "/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/CMakeFiles/Export/50bf70e196cec95d4d513cf01ed33e20/TBBTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/TBB" TYPE FILE FILES
    "/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/TBBConfig.cmake"
    "/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/TBBConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/TBB" TYPE FILE FILES "/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/arrangements/external/oneTBB/README.md")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/src/tbb/cmake_install.cmake")
  include("/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/src/tbbmalloc/cmake_install.cmake")
  include("/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/src/tbbmalloc_proxy/cmake_install.cmake")
  include("/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/arrangements/external/oneTBB/cmake/post_install/cmake_install.cmake")

endif()

