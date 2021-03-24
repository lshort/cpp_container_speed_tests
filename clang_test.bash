ulimit -s unlimited
clang++-12 -O3 vector_speed_test.cpp -o clang_vector_speed_test
./clang_vector_speed_test 2>&1 | tee ./clang_test_results.txt
