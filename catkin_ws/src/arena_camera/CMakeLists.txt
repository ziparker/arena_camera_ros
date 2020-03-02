cmake_minimum_required(VERSION 2.8.3)

#
# DEV NOTE
#  - relative path are relative to this file
# 

project(arena_camera)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#  flags for all C++ targets
add_definitions("-std=gnu++11")


# -----------------------------------------------------------------------------
#
# CATKIN
#
# -----------------------------------------------------------------------------
#
set(CATKIN_COMPONENTS
     actionlib
     camera_control_msgs
     camera_info_manager
     cv_bridge
     diagnostic_updater
     image_geometry
     image_transport
     roscpp
     roslint
     roslaunch 
     sensor_msgs
)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(
    catkin REQUIRED
    COMPONENTS 
        ${CATKIN_COMPONENTS}
)

# http://wiki.ros.org/catkin/CMakeLists.txt#catkin_package.28.29
catkin_package(
    INCLUDE_DIRS   include
    LIBRARIES      ${PROJECT_NAME}
    CATKIN_DEPENDS ${CATKIN_COMPONENTS}
)

# -----------------------------------------------------------------------------
#
# ROS
#
# -----------------------------------------------------------------------------
#
set(ROSLINT_CPP_OPTS
   "--extensions=cpp,h,hpp" "--filter=-runtime/references,-readability/todo,-build/include_what_you_use"
)

# check c/c++ static checking. More http://wiki.ros.org/roslint
roslint_cpp() # all .h .cpp files

# closest doc (http://wiki.ros.org/rosbuild/CMakeLists#rosbuild_add_roslaunch_check)
# more https://answers.ros.org/question/200359/purpose-of-roslaunch_add_file_check/
roslaunch_add_file_check(launch)

# -----------------------------------------------------------------------------
#
# ARENA
# TODO
# Make the dirs read from Arena_SDK.conf
#
# -----------------------------------------------------------------------------
#
# ADDS :
# - ${_ARENA_ROOT}
# - ${Arena_INCLUDE_DIRS}
# - ${Arena_LIBRARIES}
# - ${Arena_LIBRARIES_DIRS}
set(_ARENA_ROOT "$ENV{ARENA_ROOT}")
set(Arena_INCLUDE_DIRS 
    "${_ARENA_ROOT}/GenICam/library/CPP/include"
)
set(Arena_LIBRARIES
    "arena"
    "save"
    "gentl"
    "GenApi_gcc421_v3_0"
    "GCBase_gcc421_v3_0"
)
set(Arena_LIBRARIES_DIRS
"${_ARENA_ROOT}/lib64/" 
"${_ARENA_ROOT}/GenICam/library/lib/Linux64_x64/"
)

# -----------------------------------------------------------------------------
#
# GENERAL
#
# -----------------------------------------------------------------------------
#

# headers for compiler
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${catkin_INCLUDE_DIRS}
    ${Arena_INCLUDE_DIRS}
)

link_directories(
     ${Arena_LIBRARIES_DIRS}
)


# -----------------------------------------------------------------------------
#
# ARENA_CAMERA
#
# -----------------------------------------------------------------------------
#

# create a virtual tree for this project
# generates *.o 
# https://cmake.org/cmake/help/latest/command/add_library.html
add_library(
    ${PROJECT_NAME}
        src/${PROJECT_NAME}_node.cpp
        src/${PROJECT_NAME}_parameter.cpp
        src/${PROJECT_NAME}.cpp
        src/encoding_conversions.cpp
)

# catkin first then arena_camera
# the first argument must be created before using add_library
# https://cmake.org/cmake/help/latest/command/add_dependencies.html
add_dependencies(
    ${PROJECT_NAME}
     ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(
    ${PROJECT_NAME}
     ${catkin_LIBRARIES}
     ${Arena_LIBRARIES}
)

# -----------------------------------------------------------------------------
#
# ARENA_CAMERA_NODE
#
# -----------------------------------------------------------------------------
#

# compile the cpp and create an executable
add_executable(
   ${PROJECT_NAME}_node  # runs by rosrun
     src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}_node
     ${catkin_LIBRARIES}
     ${Arena_LIBRARIES}
     ${PROJECT_NAME}
)

# -----------------------------------------------------------------------------
#
# WRITE_DEVICE_USER_ID_TO_CAMERA
#
# -----------------------------------------------------------------------------
#

# compile the cpp and create an executable
add_executable(
    write_device_user_id_to_camera
    src/write_device_user_id_to_camera.cpp
)

target_link_libraries(
    write_device_user_id_to_camera
     ${catkin_LIBRARIES}
     ${Arena_LIBRARIES}
     ${PROJECT_NAME}
)

# This macro ensures modules and global scripts declared therein get installed
# See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
catkin_python_setup()


# -----------------------------------------------------------------------------
#
# INSTALL
#
# -----------------------------------------------------------------------------
#

install(
    DIRECTORY
     launch/
    DESTINATION
     ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
    FILES_MATCHING PATTERN "*.launch"
)

install(
    DIRECTORY
     config/
    DESTINATION
     ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
    FILES_MATCHING PATTERN "*.yaml"
)

install(
    PROGRAMS
     scripts/file_sequencer.py
     scripts/grab_and_save_image_action_server.py
     scripts/result_bag_to_action.py
     scripts/sequence_to_file.py
     scripts/toggle_camera
    DESTINATION
     ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(
    TARGETS
     ${PROJECT_NAME}
     ${PROJECT_NAME}_node
     write_device_user_id_to_camera
    LIBRARY DESTINATION
     ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION
     ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(
    DIRECTORY
     include/${PROJECT_NAME}/
    DESTINATION
     ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
    FILES_MATCHING PATTERN
     "*.h"
    PATTERN "internal" EXCLUDE
)

## Testing ##
# All Jenkins-Tests are now in the arena_camera_tests-pkg
#############

###############
## QtCreator ##
###############
# entry for QtCreator to show all files
file(GLOB children ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(child ${children})
  if(IS_DIRECTORY ${child})
    file(GLOB_RECURSE dir_files "${child}/*")
    list(APPEND ${PROJECT_NAME}_extra_files ${dir_files})
  endif()
endforeach()
#add_custom_target(dummy_${PROJECT_NAME} SOURCES ${${PROJECT_NAME}_extra_files})