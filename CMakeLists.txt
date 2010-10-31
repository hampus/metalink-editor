CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(metalinkeditor)

SET(METALINKEDITOR_VERSION "2.0dev")

IF(NOT METALINKEDITOR_CUSTOM_VERSION)
    SET(METALINKEDITOR_CUSTOM_VERSION CACHE STRING "Custom Metalink Editor version string. Empty = default version string." FORCE)
ELSE()
    SET(METALINKEDITOR_VERSION ${METALINKEDITOR_CUSTOM_VERSION})
ENDIF()

# Config header
configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

# Build settings
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF()
IF(CMAKE_COMPILER_IS_GNUCXX AND NOT CMAKE_EXE_LINKER_FLAGS_RELEASE)
    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE -s CACHE STRING "Flags used by the linker." FORCE)
ENDIF()

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

# wxWidgets
FIND_PACKAGE(wxWidgets REQUIRED adv html core base )
INCLUDE(${wxWidgets_USE_FILE})

# Expat
FIND_PACKAGE(EXPAT REQUIRED)
INCLUDE_DIRECTORIES(${EXPAT_INCLUDE_DIRS})

# MinGW
IF(MINGW)
  # Resource compilation
  SET(CMAKE_RC_COMPILER_INIT windres)
  ENABLE_LANGUAGE(RC)
  SET(CMAKE_RC_COMPILE_OBJECT
    "<CMAKE_RC_COMPILER> -O coff <FLAGS> <DEFINES> -o <OBJECT> <SOURCE>")
  # Compiler flags
  SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -Wl,--enable-auto-import)
ENDIF()

# Build application
SET(SRCS main.cpp MainFrame.cpp LicenseFrame.cpp StartPanel.cpp SourcePanel.cpp
    SourceDialog.cpp MetalinkEditor.cpp MetalinkFile.cpp MetalinkSource.cpp
    Metalink4Writer.cpp Metalink3Writer.cpp Metalink4Reader.cpp
    Metalink3Reader.cpp XmlParser.cpp util.cpp)
IF(WIN32)
    SET(SRCS ${SRCS} windows.rc)
ENDIF()
ADD_EXECUTABLE(metalinkeditor WIN32 ${SRCS})
TARGET_LINK_LIBRARIES(metalinkeditor ${wxWidgets_LIBRARIES} ${EXPAT_LIBRARIES})

# Install
IF(WIN32)
    INSTALL(TARGETS metalinkeditor DESTINATION .)
    INSTALL(FILES LICENSE.txt legal.htm start.htm DESTINATION .)
ELSE()
    INSTALL(TARGETS metalinkeditor DESTINATION bin)
    INSTALL(FILES LICENSE.txt legal.htm start.htm metalink.png DESTINATION share/metalinkeditor)
ENDIF()

# Uninstall
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY
)
ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
