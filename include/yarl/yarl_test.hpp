#ifndef yarl_TEST_HPP
#define yarl_TEST_HPP

#include <fstream>
#include <iostream>
#include <random>

#include <gtest/gtest.h>

#ifdef TEST_OUTPUT_ON
#define TEST_PRINT(M, ...) fprintf(stdout, M "\n", ##__VA_ARGS__)
#endif

#endif
