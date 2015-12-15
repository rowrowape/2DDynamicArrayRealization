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
    } else {
        throw new BadBorderException;
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
    for (int i = 0; i < array.d1Higher - array.d1Lower + 1; i++) {
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

double print(arr array) {
    for (int i = array.d2Lower; i < array.d2Higher; i++) {
        cout << i << "\t";
    }
    cout << "\n";
    for (int i = array.d1Lower; i < array.d1Higher; i++) {
        cout << i;
        for (int j = array.d2Lower; j < array.d2Higher; j++) {
            cout << array.base[i][j] << "\t";
        }
    }
}

int main() {

    arr a;
    cin.get();
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
    cin.get();
    try {
        put(a, 2, 0, get(a, 2, 0) + 10);
    } catch (BadBorderException) {
        cout << "Out of the array" << endl;
        return 0;
    }
    cin.get();
    cout << findMax(a) << endl;
    cin.get();
    print(a);
    cin.get();
    kill(a);

    return 0;
}