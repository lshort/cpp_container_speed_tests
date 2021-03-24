ulimit -s unlimited
g++-10 vector_speed_test.cpp -o gcc_vector_speed_test
./gcc_vector_speed_test 2>&1 | tee ./gcc_test_results.txt
