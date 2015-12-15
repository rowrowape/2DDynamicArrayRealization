#include <iostream>
#include "MemoryLimitExceded.h"
#include "BadBorderException.h"
<<<<<<< HEAD
=======

>>>>>>> origin/master

using namespace std;

struct arr {
    double **base;
    int d1Lower, d1Higher, d2Lower, d2Higher;

    arr(int d1Lower, int d1Higher, int d2Lower, int d2Higher, double initial) {
<<<<<<< HEAD
        this->d1Lower = d1Lower;
        this->d1Higher = d1Higher;
        this->d2Lower = d2Lower;
        this->d2Higher = d2Higher;
        int i = 0;
        try {
            base = new double *[d1Higher - d1Lower];
                for (i = 0; i < d1Higher - d1Lower; i++) {
                base[i] = new double[d2Higher - d2Lower];
            }
        } catch (bad_alloc) {
            for (int j = 0; j < i; j++) {
                delete base[i];
            }
            delete[] base;
            throw new bad_alloc;
            }
        for (i = 0; i < d1Higher - d1Lower; i++) {
            for(int j=0; j < d2Higher - d2Lower; j++ ) {
                base[i][j] = initial;
            }
        }
=======

>>>>>>> origin/master
    }
};

double put (arr &array, int i, int j, double d )
{
   if ((i - array.d1Lower <= array.d1Higher) && (i - array.d1Lower >= array.d1Lower) && (j - array.d2Lower >= array.d2Lower) && (j - array.d2Lower <= array.d2Higher))
    {
       array.base[i][j] = d;
    } else {
       throw new BadBorderException;
   }


}

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



int main() {
<<<<<<< HEAD
   return 0;
=======

    return 0;
>>>>>>> origin/master
}