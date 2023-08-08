cmake_minimum_required(VERSION 3.20)

# Global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Project name
project(cppserver)

# CMake module path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler features
include(SetCompilerFeatures)
include(SetCompilerWarnings)
include(SetPlatformFeatures)
include(SystemInformation)

# External packages
if(WIN32)
  find_package(WinSock)
endif()

# Modules
add_subdirectory("modules")

# Link libraries
if(WIN32)
  list(APPEND LINKLIBS ${WINSOCK_LIBRARIES})
endif()
list(APPEND LINKLIBS cppcommon)

# System directories
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Library
file(GLOB_RECURSE LIB_HEADER_FILES "include/*.h" "source/*.h")
file(GLOB_RECURSE LIB_INLINE_FILES "include/*.inl" "source/*.inl")
file(GLOB_RECURSE LIB_SOURCE_FILES "include/*.cpp" "source/*.cpp")
add_library(cppserver ${LIB_HEADER_FILES} ${LIB_INLINE_FILES} ${LIB_SOURCE_FILES})
set_target_properties(cppserver PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "libraries")
target_include_directories(cppserver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(cppserver ${LINKLIBS} asio)
list(APPEND INSTALL_TARGETS cppserver)
list(APPEND LINKLIBS cppserver)

# Additional module components: benchmarks, examples, plugins, tests, tools and install
if(NOT CPPSERVER_MODULE)

  # Install
  install(TARGETS ${INSTALL_TARGETS}
    RUNTIME DESTINATION "${PROJECT_SOURCE_DIR}/bin"
    LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/bin"
    ARCHIVE DESTINATION "${PROJECT_SOURCE_DIR}/bin")

  # Install *.pdb files
  if(MSVC)
    foreach(INSTALL_TARGET_PDB ${INSTALL_TARGETS_PDB})
      install(FILES $<TARGET_PDB_FILE:${INSTALL_TARGET_PDB}> DESTINATION "${PROJECT_SOURCE_DIR}/bin")
    endforeach()
  endif()

endif()
