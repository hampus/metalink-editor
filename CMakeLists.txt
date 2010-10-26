CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(metalinkeditor)

#SET(CMAKE_BUILD_TYPE Release)

# Compiler flags
#IF(CMAKE_COMPILER_IS_GNUCXX)
#    list(APPEND CMAKE_EXE_LINKER_FLAGS -s)
#ENDIF()

# Config header
configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# wxWidgets
FIND_PACKAGE(wxWidgets REQUIRED adv html core base )
INCLUDE(${wxWidgets_USE_FILE})

# Expat
FIND_PACKAGE(EXPAT REQUIRED)
INCLUDE_DIRECTORIES(${EXPAT_INCLUDE_DIRS})

# MinGW
if(MINGW)
  # Resource compilation
  set(CMAKE_RC_COMPILER_INIT windres)
  ENABLE_LANGUAGE(RC)
  SET(CMAKE_RC_COMPILE_OBJECT
    "<CMAKE_RC_COMPILER> -O coff <FLAGS> <DEFINES> -o <OBJECT> <SOURCE>")
  # Compiler flags
  SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -Wl,--enable-auto-import)
endif(MINGW)

# Build application
SET(SRCS main.cpp MainFrame.cpp LicenseFrame.cpp StartPanel.cpp SourcePanel.cpp SourceDialog.cpp MetalinkEditor.cpp MetalinkFile.cpp MetalinkSource.cpp Metalink4Writer.cpp Metalink4Reader.cpp util.cpp)
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
