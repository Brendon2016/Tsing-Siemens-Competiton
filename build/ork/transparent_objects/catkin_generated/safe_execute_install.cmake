execute_process(COMMAND "/home/h/catkin_ws/build/ork/transparent_objects/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/h/catkin_ws/build/ork/transparent_objects/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
