#include <iostream>
#include <exception>

using namespace std;

struct BadBorderException : exception {

};
struct MemoryLimitExceded : exception {

};

struct arr {
    double **base;
    int d1Lower, d1Higher, d2Lower, d2Higher;

    arr() {
        this->d1Lower = 0;
        this->d2Lower = 0;
        this->d1Higher = 0;
        this->d2Higher = 0;
        this->base = 0;
    };
};

double put(arr &array, int i, int j, double d) {
    if ((i <= array.d1Higher) &&
        (i >= array.d1Lower) &&
        (j >= array.d2Lower) &&
        (j <= array.d2Higher)) {
        array.base[i - array.d1Lower][j - array.d2Lower] = d;
        return 0 ;
    } else {
        throw new BadBorderException;
        return 0;
    }
}

int init(arr &array, int d1Lower, int d1Higher, int d2Lower, int d2Higher, double initial) {
    if (d1Higher < d1Lower || d2Higher < d2Lower) {
        throw new BadBorderException;
    }
    array.d1Lower = d1Lower;
    array.d1Higher = d1Higher;
    array.d2Lower = d2Lower;
    array.d2Higher = d2Higher;
    int i = 0;
    try {
        array.base = new double *[d1Higher - d1Lower + 1];
        for (i = 0; i < d1Higher - d1Lower + 1; i++) {
            array.base[i] = new double[d2Higher - d2Lower];
        }
    } catch (bad_alloc) {
        for (int j = 0; j < i; j++) {
            delete array.base[i];
        }
        delete[] array.base;
        throw new MemoryLimitExceded;
    }
       for (i = 0;i < d1Higher - d1Lower + 1; i++){
           for (int j = 0; j < d2Higher - d2Lower + 1; j++)
           array.base[i][j] = initial;
    }
    return 0;
}

int kill(arr &array) {
    for (int i = 0; i < array.d1Higher - array.d1Lower; i++) {
        delete [] array.base[i];
    }
    delete[] array.base;
    return 0;
}

double get(arr array, int i, int j) {
    if (array.d1Lower > i || i > array.d1Higher || array.d2Lower > j || j > array.d2Higher) {
        throw new BadBorderException;
    }
    return array.base[i - array.d1Lower][j - array.d2Lower];
}

double findMax(arr array) {
    double maxElement = array.base[0][0];
    for (int i = 0; i < array.d1Higher - array.d1Lower + 1; i++) {
        for (int j = 0; j < array.d1Higher - array.d1Lower + 1; j++) {
            if (maxElement < array.base[i][j]) {
                maxElement = array.base[i][j];
            }
        }
    }
    return maxElement;
}

double print(arr array) {
    cout << "\t";
    for (int i = array.d2Lower; i < array.d2Higher + 1; i++) {
        cout << i << "\t";
    }
    cout << "\n";
    for (int i = 0; i < array.d1Higher - array.d1Lower + 1; i++) {
        cout << array.d1Lower + i << "\t";
        for (int j = 0; j < array.d2Higher - array.d2Lower + 1; j++) {
            cout << array.base[i][j] << "\t";
        }
        cout << "\n";
    }
return 0;
}

int main() {
    arr a;
    try {
        init(a, 2, 5, -2, 2, -1);
    } catch (BadBorderException) {
        cout << "Out of the array" << endl;
        return 0;
    }
    catch (MemoryLimitExceded) {
        cout << "Memory error" << endl;
        return 0;
    }
    try {
        put(a, 2, 0, get(a, 2, 0) + 10);
    } catch (BadBorderException) {
        cout << "Out of the array" << endl;
        return 0;
    }
    cout << findMax(a) << endl;
    print(a);
    kill(a);
    return 0;
}