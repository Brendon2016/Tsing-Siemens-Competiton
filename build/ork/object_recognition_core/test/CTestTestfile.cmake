# CMake generated Testfile for 
# Source directory: /home/h/catkin_ws/src/ork/object_recognition_core/test
# Build directory: /home/h/catkin_ws/build/ork/object_recognition_core/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(object_recognition_core_test_import.py "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/run_test.sh" "/home/h/catkin_ws/devel/setup.sh" "/home/h/catkin_ws/src/ork/object_recognition_core/test/test_import.py")
ADD_TEST(object_recognition_core_test_config.py "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/run_test.sh" "/home/h/catkin_ws/devel/setup.sh" "/home/h/catkin_ws/src/ork/object_recognition_core/test/test_config.py")
ADD_TEST(object_recognition_core_help_/home/h/catkin_ws/src/ork/object_recognition_core/test/../apps/detection "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/run_test.sh" "/home/h/catkin_ws/devel/setup.sh" "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/test_help.py /home/h/catkin_ws/src/ork/object_recognition_core/test/../apps/detection")
ADD_TEST(object_recognition_core_help_/home/h/catkin_ws/src/ork/object_recognition_core/test/../apps/training "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/run_test.sh" "/home/h/catkin_ws/devel/setup.sh" "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/test_help.py /home/h/catkin_ws/src/ork/object_recognition_core/test/../apps/training")
ADD_TEST(object_recognition_core_source_OpenNI "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/run_test.sh" "/home/h/catkin_ws/devel/setup.sh" "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/test_source.py OpenNI object_recognition_core.io {}")
ADD_TEST(object_recognition_core_sink_GuessCsvWriter "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/run_test.sh" "/home/h/catkin_ws/devel/setup.sh" "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/test_sink.py GuessCsvWriter object_recognition_core.io {}")
ADD_TEST(object_recognition_core_/home/h/catkin_ws/src/ork/object_recognition_core/test/detection.test.ork "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/run_test.sh" "/home/h/catkin_ws/devel/setup.sh" "/home/h/catkin_ws/devel/share/object_recognition_core/cmake/../test/test_config.py -c /home/h/catkin_ws/src/ork/object_recognition_core/test/detection.test.ork")
SUBDIRS(db)
