#ifndef QSORT_SRC_SORT_H_
#define QSORT_SRC_SORT_H_

namespace quickSort {
  namespace partitions {
    namespace pivot {
      template <class ElementType>
      ElementType middlePivot(ElementType *array, int32_t start, int32_t end) {
        assert(start != end);
        return array[(start + end) / 2];
      }

      template <class ElementType>
      ElementType lastPivot(ElementType *array, int32_t start, int32_t end) {
        assert(start != end);
        return array[end - 1];
      }

      template <class ElementType>
      ElementType randomPivot(ElementType *array, int32_t start, int32_t end) {
        return array[start + (rand() % static_cast<int32_t >(end - start+ 1))];
      }

      template <class ElementType>
      ElementType medianPivot(ElementType *array, int32_t start, int32_t end) {
        ElementType first = array[start];
        ElementType last = array[end - 1];
        ElementType middle = array[(start + end)/2];

        if (first < last) {
          if (first < middle) {
            if (middle < last) {
              return middle;
            } else {
              return last;
            }
          } else {
            return first;
          }
        } else {
          if (last < middle) {
            if (middle < first) {
              return middle;
            } else {
              return first;
            }
          } else {
            return last;
          }
        }
      }

    }

    template <class ElementType, class Comparator>
    int32_t partitionLomuto(ElementType *array, int32_t start, int32_t end,
                                    Comparator comparator,
                                    ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)) {
      debug::debug(array, start, end, "Before partition");
      ElementType pivot = getPivot(array, start, end);
      int32_t indexForSwap = start;

      for (int32_t index = start; index < end - 1; index++) {
        if (!comparator(pivot, array[index])) {
          std::swap(array[index], array[indexForSwap]);
          indexForSwap++;
        }
      }
      std::swap(array[indexForSwap], array[end - 1]);

      debug::debug(array, start, end, "After partition");
      return indexForSwap;
    }

    template <class ElementType, class Comparator>
    int32_t partitionHoar(ElementType *array, int32_t start, int32_t end,
                                 Comparator comparator,
                                 ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)) {
      debug::debug(array, start, end, "Before partition");
      ElementType pivot = getPivot(array, start, end);
      debug::debug(pivot, "Pivot");

      int32_t startIndex = start;
      int32_t endIndex = end;

      while (startIndex <= endIndex) {
        while (comparator(array[startIndex], pivot)) {
          startIndex++;
        }

        while (comparator(pivot, array[endIndex])) {
          endIndex--;
        }

        if (startIndex >= endIndex) {
          break;
        }
        std::swap(array[startIndex], array[endIndex]);
        startIndex++;
        endIndex--;
      }

      return endIndex;
    }

    template <class ElementType, class Comparator>
    std::pair<int32_t, int32_t> optimizePartition(ElementType *array, int32_t start, int32_t end,
                              Comparator comparator) {
      debug::debug(array, start, end, "Before partition");
      ElementType pivot = array[end];
      debug::debug(pivot, "Pivot");
      int32_t endEquals = start;
      int32_t startEquals = end - 1;
      int32_t indexLess = start - 1;
      int32_t indexGreat = end;

      while (endEquals <= startEquals) {
        while (array[endEquals] < pivot) {
          endEquals++;
        }

        while (array[startEquals] > pivot) {
          startEquals--;
        }

        if (endEquals >= startEquals) {
          break;
        }

        std::swap(array[endEquals], array[startEquals]);

        if (array[startEquals] == pivot) {
          std::swap(array[--indexGreat], array[startEquals]);
        }
        startEquals--;

        if (array[endEquals] == pivot) {
          std::swap(array[++indexLess], array[endEquals]);
        }
        endEquals++;
      }
      std::swap(array[endEquals], array[end]);
      startEquals = endEquals - 1;
      endEquals++;

      for (int32_t index = start; index <= indexLess; index++) {
        std::swap(array[index], array[startEquals--]);
      }

      for (int32_t index = end - 1; index >= indexGreat; index--) {
        std::swap(array[index], array[endEquals++]);
      }

      std::pair<int32_t, int32_t> result = std::make_pair(startEquals, endEquals);
      debug::debug(array, start, end, "After partition");
      return result;
    }
  }

  template <class ElementType, class Comparator>
  void simpleSort(ElementType *array, int32_t start, int32_t end,
                    Comparator comparator,
                    ElementType (*partition)(ElementType *array, int32_t start, int32_t end,
                                                Comparator comparator,
                                                ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)),
                    ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)) {
    if (start < end) {
      int32_t partitionElement = partition(array, start, end, comparator, getPivot);
      simpleSort(array, start, partitionElement, comparator, partition, getPivot);
      simpleSort(array, partitionElement + 1, end, comparator, partition, getPivot);
    }
  }

  /* Include end */
  template <class ElementType, class Comparator>
  void sortWithPartitionOptimization(ElementType *array, int32_t start, int32_t end,
                                        Comparator comparator) {
    if (start < end) {
      std::pair<int32_t, int32_t> partitions = partitions::optimizePartition(array, start, end, comparator);
      sortWithPartitionOptimization(array, start, partitions.first, comparator);
      sortWithPartitionOptimization(array, partitions.second, end, comparator);
    }
  }

  template <class ElementType, class Comparator>
  void simpleSortWithOneRecursiveBranch(ElementType *array, int32_t start, int32_t end,
                  Comparator comparator,
                  ElementType (*partition)(ElementType *array, int32_t start, int32_t end,
                                           Comparator comparator,
                                           ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)),
                  ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)) {
    while (start < end) {
      int32_t partiotionElement = partition(array, start, end, comparator, getPivot);
      simpleSortWithOneRecursiveBranch(array, start, partiotionElement, comparator, partition, getPivot);
      start = partiotionElement + 1;
    }
  }

  template <class ElementType, class Comparator>
  void simpleSortWithoutRecursion(ElementType *array, int32_t start, int32_t end,
                  Comparator comparator,
                  ElementType (*partition)(ElementType *array, int32_t start, int32_t end,
                                           Comparator comparator,
                                           ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)),
                  ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)) {
    std::stack<std::pair<int32_t, int32_t> > borders;
    borders.push(std::make_pair(start, end));

    while(!borders.empty()) {
      std::pair<int32_t, int32_t> currentBorders = borders.top();
      borders.pop();

      if (currentBorders.first < currentBorders.second) {
        int32_t partitionElement = partition(array, currentBorders.first, currentBorders.second, comparator, getPivot);

        /* Push bigger array for sort first */
        if (partitionElement - currentBorders.first > currentBorders.second - partitionElement) {
          borders.push(std::make_pair(currentBorders.first, partitionElement));
          borders.push(std::make_pair(partitionElement + 1, currentBorders.second));
        } else {
          borders.push(std::make_pair(partitionElement + 1, currentBorders.second));
          borders.push(std::make_pair(currentBorders.first, partitionElement));
        }
      }
    }
  }

  template <class T, class Comp>
  void insertionSort(T *array, int size, Comp comp) {
    for (int i = 1; i < size; i++) {
      T item = array[i];
      int j = i - 1;
      while ((j >= 0) && (!comp(array[j], item))) {
        array[j + 1] = array[j];
        j--;
      }
      array[j + 1] = item;
    }
  }

  template <class ElementType, class Comparator>
  void simpleSortWithInsertion(ElementType *array, int32_t start, int32_t end, int32_t maxDepth,
                                  Comparator comparator,
                                  ElementType (*partition)(ElementType *array, int32_t start, int32_t end,
                                                           Comparator comparator,
                                                           ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)),
                                  ElementType (*getPivot)(ElementType *array, int32_t start, int32_t end)) {
    if (start < end) {
      if (end - start < maxDepth) {
        insertionSort(array + start, end - start + 1, comparator);
      } else {
        int32_t partitionElement = partition(array, start, end, comparator, getPivot);
        simpleSortWithInsertion(array, start, partitionElement, maxDepth, comparator, partition, getPivot);
        simpleSortWithInsertion(array, partitionElement + 1, end, maxDepth, comparator, partition, getPivot);
      }
    }
  }
}

#endif //QSORT_SRC_SORT_H_
