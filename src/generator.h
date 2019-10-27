#ifndef QSORT_SRC_GENERATOR_H_
#define QSORT_SRC_GENERATOR_H_

namespace generator {
  template <class elementType>
  void simpleGenerate (elementType *array, int32_t size, elementType min, elementType max) {
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_int_distribution<elementType> distribution(min, max);

    for (int32_t i = 0; i < size; i++) {
      array[i] = distribution(mt);
    }
  }
}

#endif //QSORT_SRC_GENERATOR_H_
