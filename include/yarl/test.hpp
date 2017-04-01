#ifndef YARL_TEST_HPP
#define YARL_TEST_HPP

#include <ctime>
#include <random>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>

#include <gtest/gtest.h>

#ifdef TEST_OUTPUT_ON
#define TEST_PRINT(M, ...) fprintf(stdout, M "\n", ##__VA_ARGS__)
#endif

#endif
