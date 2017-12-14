# project name
PROJECT(QFullScreenTest)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_DEBUG_POSTFIX D)
cmake_policy(SET CMP0003 OLD)   # full path for libs vs. searching for libs

# option settings ........................
OPTION(USE_QT5 "..." ON)

message("----- COMPILE RELEASE -----")
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")

# set some compiler options .... you can also set this command "/Zc:wchar_t-" into the comand line of the compiler
# /MP - parallel build in VS
#add_definitions(/Zc:wchar_t-) # DONT ADD compiler flags using definitions
#set(CMAKE_EXTRA_CXX_FLAGS "/MP /Zc:wchar_t- /nologo /wd4996 /wd4290" CACHE STRING "Extra CXX options")
set(CMAKE_EXTRA_CXX_FLAGS "/Zc:wchar_t- /nologo /wd4996 /wd4290 /DNDEBUG /MP" CACHE STRING "Extra CXX options")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_EXTRA_CXX_FLAGS}")

# find QT 4/5
IF(USE_QT5)

	ADD_DEFINITIONS(-DUSE_QT5)
	set(CMAKE_PREFIX_PATH "$ENV{QTDIR}/qtbase/lib/cmake")
	MESSAGE(${CMAKE_PREFIX_PATH})
	# Tell CMake to run moc when necessary:
	set(CMAKE_AUTOMOC ON)
	# As moc files are generated in the binary dir, tell CMake
	# to always look for includes there:
	set(CMAKE_INCLUDE_CURRENT_DIR ON)

	find_package(Qt5Core REQUIRED)
	find_package(Qt5Widgets REQUIRED)
	
	IF(Qt5Widgets_FOUND)
		message("----- USE QT 5-----")
	ELSE(Qt5Widgets_FOUND)
		message("ERROR: No QT 5 found")
	ENDIF(Qt5Widgets_FOUND)
	
	MESSAGE(${Qt5Widgets_VERSION_STRING})
	MESSAGE(${Qt5Widgets_INCLUDE_DIRS})
	include_directories(${Qt5Widgets_INCLUDE_DIRS})
	add_definitions(${Qt5Widgets_DEFINITIONS})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
	
ELSE(USE_QT5)

FIND_PACKAGE(Qt4 REQUIRED)
ADD_DEFINITIONS(${QT_DEFINITIONS})
set(LINK_FLAGS "${LINK_FLAGS} -mwindows -mconsole")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} ${PointCab_SOURCE_DIR} ${PointCab_BINARY_DIR} ${CMAKE_BINARY_DIR})

IF(WIN32)
	message("----- USE QT -----")  
	# add Qt modules here, the include will setup QT_LIBRARIES
	SET( QT_USE_QTMAIN TRUE)
	SET (QT_USE_QTOPENGL TRUE)
	SET (QT_USE_QTNETWORK TRUE)
	SET (QT_USE_QTXML TRUE)
	SET (QT_USE_QTDECLARATIVE TRUE)
	#SET (QT_DONT_USE_QTCORE TRUE)
	#SET (QT_DONT_USE_QTGUI TRUE)
	#SET (QT_USE_QT3SUPPORT TRUE)
	#SET (QT_USE_QTASSISTANT TRUE)
	#SET (QT_USE_QAXCONTAINER TRUE)
	#SET (QT_USE_QAXSERVER TRUE)
	#SET (QT_USE_QTDESIGNER TRUE)
	#SET (QT_USE_QTMOTIF TRUE)
	#SET (QT_USE_QTNSPLUGIN TRUE)
	#SET (QT_USE_QTSQL TRUE)
	#SET (QT_USE_QTSVG TRUE)
	#SET (QT_USE_QTTEST TRUE)
	SET (QT_USE_QTUITOOLS TRUE)
	#SET (QT_USE_QTDBUS TRUE)
	SET (QT_USE_QTSCRIPT TRUE)
	#SET (QT_USE_QTASSISTANTCLIENT TRUE)
	#SET (QT_USE_QTHELP TRUE)
	#SET (QT_USE_QTWEBKIT TRUE)
	#SET (QT_USE_QTXMLPATTERNS TRUE)
	#SET (QT_USE_PHONON TRUE)
  ADD_DEFINITIONS(-DNODEFAULTLIB:library)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
  SET (${QT_LIBRARIES} qtmain ${QT_LIBRARIES})

  # for static QT
  #FIND_LIBRARY(QT_GIF_PLUGIN qgif PATHS ${QT_PLUGINS_DIR} PATH_SUFFIXES imageformats)
  #FIND_LIBRARY(QT_JPEG_PLUGIN qjpeg PATHS ${QT_PLUGINS_DIR} PATH_SUFFIXES imageformats)
  # for dynamic QT
  FIND_LIBRARY(QT_GIF_PLUGIN qgif4 PATHS ${QT_PLUGINS_DIR} PATH_SUFFIXES imageformats)
  FIND_LIBRARY(QT_JPEG_PLUGIN qjpeg4 PATHS ${QT_PLUGINS_DIR} PATH_SUFFIXES imageformats)

  #MESSAGE(${QT_GIF_PLUGIN})
  #MESSAGE(${QT_JPEG_PLUGIN})

	ENDIF(WIN32)
	INCLUDE(${QT_USE_FILE})

ENDIF(USE_QT5)

# -----------------------------------------------------------------------
# -----------------------------------------------------------------------
# -----------------------------------------------------------------------

FILE(GLOB HDR_LIST *.h)
FILE(GLOB UI_LIST *.ui)
FILE(GLOB SRC_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

IF(NOT USE_QT5)
QT4_WRAP_UI(MOC_LIST ${UI_LIST})
QT4_WRAP_CPP(MOC_LIST ${HDR_LIST})
ENDIF()

# -----------------------------------------------------------------------
# -----------------------------------------------------------------------
# -----------------------------------------------------------------------

ADD_EXECUTABLE(QFullScreenTest
	${SRC_LIST}
	${HDR_LIST}
	${MOC_LIST}		
)

TARGET_LINK_LIBRARIES(QFullScreenTest
	${QT_LIBRARIES}
	${Qt5Widgets_LIBRARIES}
	${QT_GIF_PLUGIN}
	${QT_JPEG_PLUGIN}
)
