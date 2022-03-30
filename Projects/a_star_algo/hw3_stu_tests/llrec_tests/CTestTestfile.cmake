# CMake generated Testfile for 
# Source directory: /work/hw-echen606/hw3/hw3_stu_tests/llrec_tests
# Build directory: /work/hw-echen606/hw3/hw3_stu_tests/llrec_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Pivot.Nominal "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/work/hw-echen606/hw3/hw3_stu_tests/llrec_tests/llrec_tests" "--gtest_filter=Pivot.Nominal")
set_tests_properties(Pivot.Nominal PROPERTIES  _BACKTRACE_TRIPLES "/work/hw-echen606/hw3/hw3_stu_tests/test_cmake_lib/CustomTests.cmake;47;add_test;/work/hw-echen606/hw3/hw3_stu_tests/test_cmake_lib/TestTargets.cmake;123;add_executable_gtests;/work/hw-echen606/hw3/hw3_stu_tests/llrec_tests/CMakeLists.txt;2;add_source_problem;/work/hw-echen606/hw3/hw3_stu_tests/llrec_tests/CMakeLists.txt;0;")
add_test(Filter.Size3_nF_F_nF "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/work/hw-echen606/hw3/hw3_stu_tests/llrec_tests/llrec_tests" "--gtest_filter=Filter.Size3_nF_F_nF")
set_tests_properties(Filter.Size3_nF_F_nF PROPERTIES  _BACKTRACE_TRIPLES "/work/hw-echen606/hw3/hw3_stu_tests/test_cmake_lib/CustomTests.cmake;47;add_test;/work/hw-echen606/hw3/hw3_stu_tests/test_cmake_lib/TestTargets.cmake;123;add_executable_gtests;/work/hw-echen606/hw3/hw3_stu_tests/llrec_tests/CMakeLists.txt;2;add_source_problem;/work/hw-echen606/hw3/hw3_stu_tests/llrec_tests/CMakeLists.txt;0;")
