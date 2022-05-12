# CMake generated Testfile for 
# Source directory: /work/hw-echen606/hw2/hw2_tests/combiner_tests
# Build directory: /work/hw-echen606/hw2/hw2_tests/combiner_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Combiners.ANDCombiner "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/work/hw-echen606/hw2/hw2_tests/combiner_tests/combiner_tests" "--gtest_filter=Combiners.ANDCombiner")
set_tests_properties(Combiners.ANDCombiner PROPERTIES  _BACKTRACE_TRIPLES "/work/hw-echen606/hw2/hw2_tests/test_cmake_lib/CustomTests.cmake;47;add_test;/work/hw-echen606/hw2/hw2_tests/test_cmake_lib/TestTargets.cmake;123;add_executable_gtests;/work/hw-echen606/hw2/hw2_tests/combiner_tests/CMakeLists.txt;3;add_source_problem;/work/hw-echen606/hw2/hw2_tests/combiner_tests/CMakeLists.txt;0;")
add_test(Combiners.ORCombiner "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/work/hw-echen606/hw2/hw2_tests/combiner_tests/combiner_tests" "--gtest_filter=Combiners.ORCombiner")
set_tests_properties(Combiners.ORCombiner PROPERTIES  _BACKTRACE_TRIPLES "/work/hw-echen606/hw2/hw2_tests/test_cmake_lib/CustomTests.cmake;47;add_test;/work/hw-echen606/hw2/hw2_tests/test_cmake_lib/TestTargets.cmake;123;add_executable_gtests;/work/hw-echen606/hw2/hw2_tests/combiner_tests/CMakeLists.txt;3;add_source_problem;/work/hw-echen606/hw2/hw2_tests/combiner_tests/CMakeLists.txt;0;")
add_test(Combiners.DiffCombiner "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/work/hw-echen606/hw2/hw2_tests/combiner_tests/combiner_tests" "--gtest_filter=Combiners.DiffCombiner")
set_tests_properties(Combiners.DiffCombiner PROPERTIES  _BACKTRACE_TRIPLES "/work/hw-echen606/hw2/hw2_tests/test_cmake_lib/CustomTests.cmake;47;add_test;/work/hw-echen606/hw2/hw2_tests/test_cmake_lib/TestTargets.cmake;123;add_executable_gtests;/work/hw-echen606/hw2/hw2_tests/combiner_tests/CMakeLists.txt;3;add_source_problem;/work/hw-echen606/hw2/hw2_tests/combiner_tests/CMakeLists.txt;0;")
