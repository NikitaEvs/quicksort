#ifndef QSORT_SRC_QSORT_H_
#define QSORT_SRC_QSORT_H_

#define DEBUG 0
#define LOG 0
#define TEST 1
#define ALL_TEST 1

#define MAX_COUNT 1500000
#define STEP 100000
#define MAX_NUMBER 1000000
#define MIN_NUMBER -1000000
#define TEST_COUNT 3

#include <iostream>
#include <cassert>
#include <utility>
#include <string>
#include <random>
#include <stack>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>


namespace debug {
  template <class elementType>
  void debug(elementType *array, int32_t start, int32_t end) {
    if (LOG) {
      freopen("out/log", "w", stdout);
    }
    if (DEBUG) {
      for (int32_t i = start; i < end; i++) {
        std::cout << array[i] << " ";
      }
      std::cout << std::endl;
    }
  }

  template <class elementType>
  void debug(elementType *array, int32_t start, int32_t end, char const *message) {
    if (LOG) {
      freopen("out/log", "w", stdout);
    }
    if (DEBUG) {
      std::cout << message << std::endl;
      for (int32_t i = start; i < end; i++) {
        std::cout << array[i] << " ";
      }
      std::cout << std::endl;
    }
  }

  void debug(char const *message) {
    if (LOG) {
      freopen("out/log", "w", stdout);
    }
    if (DEBUG) {
      std::cout << message << std::endl;
    }
  }

  void test(char const *message, bool result) {
    if (LOG) {
      freopen("out/testResult", "w", stdout);
    }
    if (TEST) {
      std::cout << "TEST: " << message << " | RESULT: " << result << std::endl;
    }
  }


  template <class elementType>
  void debug(elementType item, char const *message) {
    if (LOG) {
      freopen("out/log", "w", stdout);
    }
    if (DEBUG) {
      std::cout << message << std::endl;
      std::cout << item << std::endl;
    }
  }
}

#include "sort.h"


#endif //QSORT_SRC_QSORT_H_
