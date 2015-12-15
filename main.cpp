#include <iostream>
#include "MemoryLimitExceded.h"
#include "BadBorderException.h"


using namespace std;

struct arr {
    double **base;
    int d1Lower, d1Higher, d2Lower, d2Higher;

    arr(int d1Lower, int d1Higher, int d2Lower, int d2Higher, double initial) {

    }
};

int init(arr &array, int d1Lower, int d1Higher, int d2Lower, int d2Higher, double initial) {
    if (d1Higher <= d1Lower || d2Higher <= d2Lower) {
        throw new BadBorderException;
    }
    array.d1Lower = d1Lower;
    array.d1Higher = d1Higher;
    array.d2Lower = d2Lower;
    array.d2Higher = d2Higher;

    try {
        array.base = new double *[d1Higher - d1Lower];
        for (int i = 0; i < d1Higher - d1Lower; i++) {
            array.base[i] = new double[d2Higher - d2Lower];
        }
    } catch (bad_alloc) {
        for (int i = 0; i < d1Higher - d1Lower; i++) {
            delete array.base[i];
        }
        delete[] array.base;
        throw new BadBorderException;
    }
    return 0;
}

int kill(arr &array) {
    for (int i = 0; i < array.d1Higher - array.d1Lower; i++) {
        delete array.base[i];
    }
    delete[] array.base;
}

double get(arr array, int i, int j) {
    if (array.d1Lower > i || i > array.d1Higher || array.d2Lower > j || j > array.d2Higher) {
        throw new BadBorderException;
    }
    return array.base[i - array.d1Lower][j - array.d2Lower];
}

double findMax(arr array) {
    double maxElement = array.base[array.d1Lower][array.d2Lower];
    for (int i = array.d1Lower; i < array.d1Lower; i++) {
        for (int j = array.d2Lower; j < array.d2Higher; j++) {
            if (maxElement < array.base[i - array.d1Lower][j - array.d2Lower]) {
                maxElement = array.base[i - array.d1Lower][j - array.d2Lower];
            }
        }
    }
    return maxElement;
}

int main() {

    return 0;
}