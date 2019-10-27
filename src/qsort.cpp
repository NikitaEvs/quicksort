#include "qsort.h"
#include "generator.h"

template <class elementType>
class Comparator {
 public:
  bool operator() (elementType &left, elementType &right) {
    return left < right;
  }
};

void allTest() {
  Comparator<int32_t> comparator;
  for (int32_t numbers = STEP; numbers <= MAX_COUNT; numbers += STEP) {
    std::cout << numbers << ',';
    auto *testArray = new int32_t[numbers];
    generator::simpleGenerate(testArray, numbers, MIN_NUMBER, MAX_NUMBER);

    /* With Lomuto partition */
    auto *test1 = new int32_t[numbers];
    std::copy(testArray, testArray + numbers, test1);
    auto tStart1 = std::chrono::high_resolution_clock::now();
    quickSort::simpleSort(test1, 0, numbers, comparator, quickSort::partitions::partitionLomuto, quickSort::partitions::pivot::lastPivot);
    auto tFinish1 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tFinish1 - tStart1).count() << ',';
    delete []test1;

    /* With Hoar partition and last pivot */
    auto *test2 = new int32_t[numbers];
    std::copy(testArray, testArray + numbers, test2);
    auto tStart2 = std::chrono::high_resolution_clock::now();
    quickSort::simpleSort(test2, 0, numbers - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::lastPivot);
    auto tFinish2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tFinish2 - tStart2).count() << ',';
    delete []test2;

    /* With Hoar partition and random pivot */
    auto *test3 = new int32_t[numbers];
    std::copy(testArray, testArray + numbers, test3);
    auto tStart3 = std::chrono::high_resolution_clock::now();
    quickSort::simpleSort(test3, 0, numbers - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::randomPivot);
    auto tFinish3 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tFinish3 - tStart3).count() << ',';
    delete []test3;

    /* With Hoar partition and median pivot */
    auto *test4 = new int32_t[numbers];
    std::copy(testArray, testArray + numbers, test4);
    auto tStart4 = std::chrono::high_resolution_clock::now();
    quickSort::simpleSort(test4, 0, numbers - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);
    auto tFinish4 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tFinish4 - tStart4).count() << ',';
    delete []test4;

    /* With partition optimization */
    auto *test5 = new int32_t[numbers];
    std::copy(testArray, testArray + numbers, test5);
    auto tStart5 = std::chrono::high_resolution_clock::now();
    quickSort::sortWithPartitionOptimization(test5, 0, numbers - 1, comparator);
    auto tFinish5 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tFinish5 - tStart5).count() << ',';
    delete []test5;

    /* With one recursive branch */
    auto *test6 = new int32_t[numbers];
    std::copy(testArray, testArray + numbers, test6);
    auto tStart6 = std::chrono::high_resolution_clock::now();
    quickSort::simpleSortWithOneRecursiveBranch(test6, 0, numbers - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);
    auto tFinish6 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tFinish6 - tStart6).count() << ',';
    delete []test6;

    /* Without recursion */
    auto *test7 = new int32_t[numbers];
    std::copy(testArray, testArray + numbers, test7);
    auto tStart7 = std::chrono::high_resolution_clock::now();
    quickSort::simpleSortWithoutRecursion(test7, 0, numbers - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);
    auto tFinish7 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tFinish7 - tStart7).count() << ',';
    delete []test7;

    /* With recursion optimization */
    auto *test8 = new int32_t[numbers];
    std::copy(testArray, testArray + numbers, test8);
    auto tStart8 = std::chrono::high_resolution_clock::now();
    quickSort::simpleSortWithInsertion(test8, 0, numbers - 1, 11, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);
    auto tFinish8 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tFinish8 - tStart8).count() << ',';
    delete []test8;

    std::cout << std::endl;
  }
}

void makeHat() {
  std::cout << "Количество элементов," << "С разбиением Ломуто,"
            << "С разбиением Хоара/pivot – последний," << "С разбиением Хоара/pivot – случайный,"
            << "С разбиением Хоара/pivot – медиана," << "С оптимизацией partition,"
            << "С одной рекурсивной веткой," << "Без рекурсии," << "С опимизации концевой рекурсии" << std::endl;
}

int main() {
  srand(time(nullptr));
  freopen("../out/result.csv", "w", stdout);
  makeHat();
  allTest();
  return 0;
}