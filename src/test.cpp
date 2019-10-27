#include <algorithm>
#include "qsort.h"
#include "generator.h"

#define RANDOM_TEST_SIZE 1000
#define RANDOM_TEST_MIN -500
#define RANDOM_TEST_MAX 500
#define RANDOM_TEST_COUNT 10

template <class elementType>
class Comparator {
 public:
  bool operator() (elementType &left, elementType &right) {
    return left < right;
  }
};

template <class elementType>
class ComparatorReverse {
 public:
  bool operator() (elementType &left, elementType &right) {
    return left > right;
  }
};

template <class elementType>
bool compare(elementType *left, elementType *right, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    if (left[i] != right[i]) {
      return false;
    }
  }
  return true;
}


void randomTest() {
  auto *arrayReal = new int32_t[RANDOM_TEST_SIZE];
  auto *arrayRealReverse = new int32_t[RANDOM_TEST_SIZE];

  auto *arrayLomuto = new int32_t[RANDOM_TEST_SIZE];
  auto *arrayHoar = new int32_t[RANDOM_TEST_SIZE];

  auto *arrayLomutoReverse = new int32_t[RANDOM_TEST_SIZE];
  auto *arrayHoarReverse = new int32_t[RANDOM_TEST_SIZE];

  auto *arrayHoarRandom = new int32_t[RANDOM_TEST_SIZE];
  auto *arrayHoarMedian = new int32_t[RANDOM_TEST_SIZE];

  auto *arrayPartitionOptimize = new int32_t[RANDOM_TEST_SIZE];
  auto *arrayPartitionOptimizeReverse = new int32_t[RANDOM_TEST_SIZE];

  auto *arrayWithOneRecursiveBranch = new int32_t[RANDOM_TEST_SIZE];
  auto *arrayWithOneRecursiveBranchReverse = new int32_t[RANDOM_TEST_SIZE];

  auto *arrayWithoutRecursion = new int32_t[RANDOM_TEST_SIZE];
  auto *arrayWithoutRecursionReverse = new int32_t[RANDOM_TEST_SIZE];

  auto *arrayWithInsertion = new int32_t[RANDOM_TEST_SIZE];
  auto *arrayWithInsertionReverse = new int32_t[RANDOM_TEST_SIZE];


  generator::simpleGenerate(arrayReal, RANDOM_TEST_SIZE, RANDOM_TEST_MIN, RANDOM_TEST_MAX);

  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayRealReverse);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayLomuto);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayLomutoReverse);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayHoar);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayHoarReverse);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayHoarRandom);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayHoarMedian);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayPartitionOptimize);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayPartitionOptimizeReverse);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayWithOneRecursiveBranch);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayWithOneRecursiveBranchReverse);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayWithoutRecursion);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayWithoutRecursionReverse);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayWithInsertion);
  std::copy(arrayReal, arrayReal + RANDOM_TEST_SIZE, arrayWithInsertionReverse);



  Comparator<int32_t> comparator;
  ComparatorReverse<int32_t> comparatorReverse;

  debug::debug("Start Lomuto");
  quickSort::simpleSort(arrayLomuto, 0, RANDOM_TEST_SIZE, comparator, quickSort::partitions::partitionLomuto, quickSort::partitions::pivot::lastPivot);
  quickSort::simpleSort(arrayLomutoReverse, 0, RANDOM_TEST_SIZE, comparatorReverse, quickSort::partitions::partitionLomuto, quickSort::partitions::pivot::lastPivot);

  debug::debug("Start Hoar");
  quickSort::simpleSort(arrayHoar, 0, RANDOM_TEST_SIZE - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::middlePivot);
  quickSort::simpleSort(arrayHoarReverse, 0, RANDOM_TEST_SIZE - 1, comparatorReverse, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::middlePivot);
  quickSort::simpleSort(arrayHoarRandom, 0, RANDOM_TEST_SIZE - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::randomPivot);
  quickSort::simpleSort(arrayHoarMedian, 0, RANDOM_TEST_SIZE - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);

  debug::debug("Start optimize partition");
  quickSort::sortWithPartitionOptimization(arrayPartitionOptimize, 0, RANDOM_TEST_SIZE - 1, comparator);
  quickSort::sortWithPartitionOptimization(arrayPartitionOptimizeReverse, 0, RANDOM_TEST_SIZE - 1, comparatorReverse);

  debug::debug("Start qsort with one recursive branch");
  quickSort::simpleSortWithOneRecursiveBranch(arrayWithOneRecursiveBranch, 0, RANDOM_TEST_SIZE - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);
  quickSort::simpleSortWithOneRecursiveBranch(arrayWithOneRecursiveBranchReverse, 0, RANDOM_TEST_SIZE - 1, comparatorReverse, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);

  debug::debug("Start qsort without recursion");
  quickSort::simpleSortWithoutRecursion(arrayWithoutRecursion, 0, RANDOM_TEST_SIZE - 1, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);
  quickSort::simpleSortWithoutRecursion(arrayWithoutRecursionReverse, 0, RANDOM_TEST_SIZE - 1, comparatorReverse, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);

  debug::debug("Start qsort with insertion");
  quickSort::simpleSortWithInsertion(arrayWithInsertion, 0, RANDOM_TEST_SIZE - 1, 11, comparator, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);
  quickSort::simpleSortWithInsertion(arrayWithInsertionReverse, 0, RANDOM_TEST_SIZE - 1, 11, comparatorReverse, quickSort::partitions::partitionHoar, quickSort::partitions::pivot::medianPivot);


  std::sort(arrayReal, arrayReal + RANDOM_TEST_SIZE, comparator);
  std::sort(arrayRealReverse, arrayRealReverse + RANDOM_TEST_SIZE, comparatorReverse);

  bool lomutoResult = compare(arrayReal, arrayLomuto, RANDOM_TEST_SIZE);
  bool lomutoReverseResult = compare(arrayRealReverse, arrayLomutoReverse, RANDOM_TEST_SIZE);
  bool hoarResult = compare(arrayReal, arrayHoar, RANDOM_TEST_SIZE);
  bool hoarReverseResult = compare(arrayRealReverse, arrayHoarReverse, RANDOM_TEST_SIZE);
  bool hoarRandomResult = compare(arrayReal, arrayHoarRandom, RANDOM_TEST_SIZE);
  bool hoarMedianResult = compare(arrayReal, arrayHoarMedian, RANDOM_TEST_SIZE);
  bool optimizePartResult = compare(arrayReal, arrayPartitionOptimize, RANDOM_TEST_SIZE);
  bool optimizePartReverseResult = compare(arrayReal, arrayPartitionOptimizeReverse, RANDOM_TEST_SIZE);
  bool withOneRecursiveBranch = compare(arrayReal, arrayWithOneRecursiveBranch, RANDOM_TEST_SIZE);
  bool withOneRecursiveBranchReverse = compare(arrayRealReverse, arrayWithOneRecursiveBranchReverse, RANDOM_TEST_SIZE);
  bool withoutRecursion = compare(arrayReal, arrayWithoutRecursion, RANDOM_TEST_SIZE);
  bool withoutRecursionReverse = compare(arrayRealReverse, arrayWithoutRecursionReverse, RANDOM_TEST_SIZE);
  bool withInsertion = compare(arrayReal, arrayWithInsertion, RANDOM_TEST_SIZE);
  bool withInsertionReverse = compare(arrayRealReverse, arrayWithInsertionReverse, RANDOM_TEST_SIZE);


  debug::test("Lomuto", lomutoResult);
  debug::test("LomutoReverse", lomutoReverseResult);
  debug::test("Hoar", hoarResult);
  debug::test("HoarReverse", hoarReverseResult);
  debug::test("HoarRandom", hoarRandomResult);
  debug::test("HoarMedian", hoarMedianResult);
  debug::test("OptimizePartition", optimizePartResult);
  debug::test("OptimizePartitionReverse", optimizePartReverseResult);
  debug::test("WithOneRecursiveBranch", withOneRecursiveBranch);
  debug::test("WithOneRecursiveBranch", withOneRecursiveBranchReverse);
  debug::test("WithoutRecursion", withoutRecursion);
  debug::test("WithoutRecursionReverse", withoutRecursionReverse);
  debug::test("WithInsertion", withInsertion);
  debug::test("WithInsertionReverse", withInsertionReverse);


  assert(lomutoResult);
  assert(lomutoReverseResult);
  assert(hoarResult);
  assert(hoarReverseResult);
  assert(hoarRandomResult);
  assert(hoarMedianResult);
  assert(optimizePartResult);
  assert(optimizePartReverseResult);
  assert(withOneRecursiveBranch);
  assert(withOneRecursiveBranchReverse);
  assert(withoutRecursion);
  assert(withoutRecursionReverse);
  assert(withInsertion);
  assert(withInsertionReverse);


  delete []arrayReal;
  delete []arrayRealReverse;
  delete []arrayLomuto;
  delete []arrayLomutoReverse;
  delete []arrayHoar;
  delete []arrayHoarReverse;
  delete []arrayHoarRandom;
  delete []arrayHoarMedian;
  delete []arrayPartitionOptimize;
  delete []arrayWithOneRecursiveBranch;
  delete []arrayWithOneRecursiveBranchReverse;
  delete []arrayWithoutRecursion;
  delete []arrayWithoutRecursionReverse;
  delete []arrayWithInsertion;
  delete []arrayWithInsertionReverse;
}

int main() {
  srand(time(nullptr));
  for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
    randomTest();
  }
  return 0;
}

