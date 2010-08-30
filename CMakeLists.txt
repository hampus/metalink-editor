CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(metalink-editor)

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
SET(SRCS main.cpp MainFrame.cpp MainFrame.hpp util.cpp util.hpp)
IF(WIN32)
    SET(SRCS ${SRCS} windows.rc)
ENDIF()
ADD_EXECUTABLE(metalinkeditor WIN32 ${SRCS})
TARGET_LINK_LIBRARIES(metalinkeditor ${wxWidgets_LIBRARIES})

# Installation
IF(WIN32)
    INSTALL(TARGETS metalinkeditor DESTINATION .)
    INSTALL(FILES resources.xrc DESTINATION .)
ELSE()
    INSTALL(TARGETS metalinkeditor DESTINATION bin)
    INSTALL(FILES resources.xrc DESTINATION share/metalinkeditor)
ENDIF()
