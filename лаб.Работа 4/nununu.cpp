#include <iostream>
using namespace std;

void filter(int* A, int size, int T, int* B, int& countB) {
    countB = 0;
    for (int i = 0; i < size; i++) {
        if (A[i] > T) {
            B[countB] = A[i];
            countB++;
        }
    }
}

void input(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "A[" << i << "] = ";
        cin >> arr[i];
    }
}

void print(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    const int SIZE = 10;
    int A[SIZE];
    int B[SIZE];
    int T;
    int countB = 0;

    cout << "Vvedite 10 elementov massiva A:" << endl;
    input(A, SIZE);

    cout << "Vvedite znachenie T: ";
    cin >> T;

    filter(A, SIZE, T, B, countB);

    cout << "\nIshodnyj massiv A: ";
    print(A, SIZE);
    cout << "Znachenie T: " << T << endl;
    cout << "Rezultiruyushchij massiv B: ";
    print(B, countB);

    return 0;
}