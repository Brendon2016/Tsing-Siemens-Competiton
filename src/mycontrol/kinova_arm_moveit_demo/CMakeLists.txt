cmake_minimum_required(VERSION 2.8.3)
project(kinova_arm_moveit_demo)

add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
             COMPONENTS
             moveit_core
             moveit_ros_planning
             moveit_ros_planning_interface
             pluginlib
             cmake_modules
             geometric_shapes
			 object_recognition_ros 
			 object_recognition_msgs
)

find_package(Boost REQUIRED system filesystem date_time thread)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS 
    moveit_core
    moveit_ros_planning_interface
    interactive_markers
)
find_package(Eigen REQUIRED)

find_package(kinova_driver REQUIRED)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

include_directories(SYSTEM ${Boost_INCLUDE_DIR} ${EIGEN_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

include_directories(${kinova_driver_INCLUDE_DIRS})

add_executable(objectplan src/objectplan.cpp)
target_link_libraries(objectplan ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS objectplan DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(pick_test src/pick_test.cpp)
target_link_libraries(pick_test ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS pick_test DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(pick_realrobot src/pick_realrobot.cpp)
target_link_libraries(pick_realrobot ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS pick_realrobot DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(pick_realrobot2 src/pick_realrobot2.cpp)
target_link_libraries(pick_realrobot2 ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS pick_realrobot2 DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(objectplan1 src/objectplan1.cpp)
target_link_libraries(objectplan1 ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS objectplan1 DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(mymotion src/mymotion.cpp)
target_link_libraries(mymotion ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS mymotion DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(motion_plan src/motion_plan.cpp)
target_link_libraries(motion_plan ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS motion_plan DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(work_scene src/work_scene.cpp)
target_link_libraries(work_scene ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS work_scene DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(pick_place src/pick_place.cpp include/pick_place.h)
target_link_libraries(pick_place ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS pick_place DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(test_accuracy src/test_accuracy.cpp include/test_accuracy.h)
target_link_libraries(test_accuracy ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${kinova_driver_LIBRARIES})
install(TARGETS test_accuracy DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
