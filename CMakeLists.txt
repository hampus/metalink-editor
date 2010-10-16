CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(metalinkeditor)

set(CMAKE_BUILD_TYPE Release)

# Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    list(APPEND CMAKE_EXE_LINKER_FLAGS -s)
endif()

# Config header
configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# wxWidgets
FIND_PACKAGE(wxWidgets REQUIRED xrc xml adv html core base )
INCLUDE(${wxWidgets_USE_FILE})

# Build application
SET(SRCS main.cpp MainFrame.cpp LicenseFrame.cpp MetalinkEditor.cpp MetalinkFile.cpp util.cpp)
IF(WIN32)
    SET(SRCS ${SRCS} windows.rc)
ENDIF()
ADD_EXECUTABLE(metalinkeditor WIN32 ${SRCS})
TARGET_LINK_LIBRARIES(metalinkeditor ${wxWidgets_LIBRARIES})

# Install
IF(WIN32)
    INSTALL(TARGETS metalinkeditor DESTINATION .)
    INSTALL(FILES LICENSE.txt DESTINATION .)
ELSE()
    INSTALL(TARGETS metalinkeditor DESTINATION bin)
    INSTALL(FILES LICENSE.txt DESTINATION share/metalinkeditor)
ENDIF()

# Uninstall
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY
)
ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
