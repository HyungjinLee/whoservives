cmake_minimum_required(VERSION 3.2.0)
set(DB_NAME IronMan)

project(${DB_NAME})
# output path settings
if(MSVC_IDE)

# Visual studio 2010
  if(MSVC_SERSION EQUAL 1600)
	set(DLL_ARCHIVE_DIR_DEBUG "${CMAKE_SOURCE_DIR}/DLL/vc10d")
	set(DLL_ARCHIVE_DIR_RELEASE "${CMAKE_SOURCE_DIR}/DLL/vc10")
	set(MTES_DIR ${CMAKE_SOURCE_DIR}/../../vc10)
	set(VCTOOLS_VER 10.0)
	set(VCBUILD_DIR ${CMAKE_SOURCE_DIR}/buildvc10)
	set(MTES_DEBUG_EXE "MTES_vs2010_debug.exe")
  endif()

  # Visual studio 2013
  if(MSVC_SERSION EQUAL 1800)
	set(DLL_ARCHIVE_DIR_DEBUG "${CMAKE_SOURCE_DIR}/DLL/vc12d")
	set(DLL_ARCHIVE_DIR_RELEASE "${CMAKE_SOURCE_DIR}/DLL/vc12")
	set(MTES_DIR ${CMAKE_SOURCE_DIR}/../../vc12)
	set(VCTOOLS_VER 12.0)
	set(VCBUILD_DIR ${CMAKE_SOURCE_DIR}/buildvc12)
	set(MTES_DEBUG_EXE "MTES_vs2013_debug.exe")
  endif()

  # Visual studio 2015
  if(MSVC_SERSION EQUAL 1900)
	set(DLL_ARCHIVE_DIR_DEBUG "${CMAKE_SOURCE_DIR}/DLL/vc14d")
	set(DLL_ARCHIVE_DIR_RELEASE "${CMAKE_SOURCE_DIR}/DLL/vc14")
	set(MTES_DIR ${CMAKE_SOURCE_DIR}/../../vc14)
	set(VCTOOLS_VER 14.0)
	set(VCBUILD_DIR ${CMAKE_SOURCE_DIR}/buildvc14)
	set(MTES_DEBUG_EXE "MTES_vs2015_debug.exe")
  endif()

  # Visual studio 2017
  if(MSVC_VERSION MATCHES "^191[0-9]$")
	  #if(MSVC15)
	set(DLL_ARCHIVE_DIR_DEBUG "${CMAKE_SOURCE_DIR}/DLL/vc15d")
	set(DLL_ARCHIVE_DIR_RELEASE "${CMAKE_SOURCE_DIR}/DLL/vc15")
	set(MTES_DIR ${CMAKE_SOURCE_DIR}/../../vc15)
	set(VCTOOLS_VER 15.0)
	set(VCBUILD_DIR ${CMAKE_SOURCE_DIR}/buildvc15)
	set(MTES_DEBUG_EXE "MTES_vs2017_debug.exe")
  endif()
else(MSVC_IDE)
  message(FATAL_ERROR "This cmake project of MTES only supports Visual Studio environments") 
endif(MSVC_IDE)
MESSAGE("Output dll debug directory : ${DLL_ARCHIVE_DIR_DEBUG}")
MESSAGE("Output dll release directory : ${DLL_ARCHIVE_DIR_RELEASE}")
MESSAGE("MTES directory : ${MTES_DIR}")

# vcxproj.user
set(VCXPROJ_USER "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n")
set(VCXPROJ_USER "${VCXPROJ_USER}<Project ToolsVersion=\"")
set(VCXPROJ_USER "${VCXPROJ_USER}${VCTOOLS_VER}\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n")
set(VCXPROJ_USER "${VCXPROJ_USER}<PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">\n")
set(VCXPROJ_USER "${VCXPROJ_USER}<LocalDebuggerCommand>")
set(VCXPROJ_USER "${VCXPROJ_USER}${MTES_DIR}/${MTES_DEBUG_EXE}</LocalDebuggerCommand>\n")

set(VCXPROJ_USER "${VCXPROJ_USER}<DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>\n</PropertyGroup>\n</Project>")

 
set(OPENCV_INCLUDE_DIRS "${MTES_DIR}/Lib/OpenCv/include/opencv" "C:/MTEs-light/out/bin/Lib/OpenCv/include/opencv2" "${MTES_DIR}/Lib/OpenCv/include")

MESSAGE("OpenCV include directory : ${OPENCV_INCLUDE_DIRS}")

include_directories(${OPENCV_INCLUDE_DIRS})
set(OPENCV_VER "345")
set(OPENCV_LIB_PATH "${MTES_DIR}/Lib/OpenCv/lib")
set(OPENCV_CMAKE_DEBUG_POSTFIX "d")
MESSAGE("OpenCV LIB PATH : ${OPENCV_LIB_PATH}")

foreach(lib
	calib3d	
	core	
	features2d	
	flann
	highgui
	imgcodecs
	imgproc
	ml
	objdetect
	photo
	shape
	stitching
	superres
	video
	videoio
	videostab
	)
  # Find Release libraries
  find_library(opencv_${lib}_LIBRARY_RELEASE
	NAMES opencv_${lib}${OPENCV_VER}
    PATHS
    HINTS ${OPENCV_LIB_PATH}
    NO_DEFAULT_PATH
    )

  # Find Debug libraries
  find_library(opencv_${lib}_LIBRARY_DEBUG
	NAMES opencv_${lib}${OPENCV_VER}${OPENCV_CMAKE_DEBUG_POSTFIX}
    PATHS
    HINTS ${OPENCV_LIB_PATH}
    NO_DEFAULT_PATH
    )
  message("opencv_${lib}${OPENCV_VER}${OPENCV_CMAKE_DEBUG_POSTFIX}")
  
# Add libraries to variable according to build type
  if(opencv_${lib}_LIBRARY_RELEASE)
    list(APPEND OPENCV_LIBRARIES optimized ${opencv_${lib}_LIBRARY_RELEASE})
  endif()

  if(opencv_${lib}_LIBRARY_DEBUG)
    list(APPEND OPENCV_LIBRARIES debug ${opencv_${lib}_LIBRARY_DEBUG})
  endif()

endforeach()
set(LIBS ${LIBS} ${OPENCV_LIBRARIES})
MESSAGE("LIBS : ${LIBS}")

#######################################################
# KSClass Settings
#######################################################
set(KSCLASS_INCLUDE_DIRS "${MTES_DIR}/Lib/KSClass/include" )
include_directories(${KSCLASS_INCLUDE_DIRS})
set(KSCLASS_LIB_PATH "${MTES_DIR}/Lib/KSClass/Lib")
set(KSCLASS_DEBUG_POSTFIX "d")


# Find Release libraries
find_library(KSCLASS_LIBRARY_RELEASE
  KSClass
  PATHS
  ${KSCLASS_LIB_PATH}
  NO_DEFAULT_PATH
)
# Find Debug libraries
find_library(KSCLASS_LIBRARY_DEBUG
  KSClass${KSCLASS_DEBUG_POSTFIX}
  PATHS
  ${KSCLASS_LIB_PATH}
  NO_DEFAULT_PATH
)

  message("${KSCLASS_LIBRARY_DEBUG}")
  message("${KSCLASS_LIBRARY_RELEASE}")
  
# Add libraries to variable according to build type
  if(KSCLASS_LIBRARY_RELEASE)
    list(APPEND KSCLASS_LIBRARIES optimized ${KSCLASS_LIBRARY_RELEASE})
  endif()

  if(KSCLASS_LIBRARY_DEBUG)
    list(APPEND KSCLASS_LIBRARIES debug ${KSCLASS_LIBRARY_DEBUG})
  endif()

set(LIBS ${LIBS} ${KSCLASS_LIBRARIES})
message("${KSCLASS_LIBRARIES}")

set(CMAKE_SUPPRESS_REGENERATION ON)

file(GLOB_RECURSE CMAKE_FILES CMakelists.txt 
					)

message("${CMAKE_FILES}")
list(REMOVE_AT CMAKE_FILES 0)
message("${CMAKE_FILES}")

foreach(function_each
	${CMAKE_FILES})

  # parse sub dir name
  get_filename_component(FUNC_DIR ${function_each} DIRECTORY)
  message("${FUNC_DIR}")
  
  get_filename_component(func_proj_name ${FUNC_DIR} NAME)
  message("${func_proj_name}")
# parse function name

  set(PROJ_NAME ${func_proj_name})
  add_subdirectory(${FUNC_DIR})

  # debugging settings	
  file(WRITE ${VCBUILD_DIR}/Source/${PROJ_NAME}/${PROJ_NAME}.vcxproj.user "${VCXPROJ_USER}") 
endforeach()

 

