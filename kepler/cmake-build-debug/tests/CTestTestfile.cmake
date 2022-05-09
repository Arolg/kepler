# CMake generated Testfile for 
# Source directory: C:/Users/ismat/Desktop/repo/kepler/kepler/tests
# Build directory: C:/Users/ismat/Desktop/repo/kepler/kepler/cmake-build-debug/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[run_test_kepler]=] "C:/Users/ismat/Desktop/repo/kepler/kepler/cmake-build-debug/tests/run_test_kepler.exe")
set_tests_properties([=[run_test_kepler]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ismat/Desktop/repo/kepler/kepler/tests/CMakeLists.txt;22;add_test;C:/Users/ismat/Desktop/repo/kepler/kepler/tests/CMakeLists.txt;0;")
subdirs("googletest-master")
