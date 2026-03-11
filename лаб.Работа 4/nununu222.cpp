#include <iostream>
#include <set>
#include <string>

using namespace std;

bool startsOne(int number) {
    if (number == 0) return false;

    int absNumber = abs(number);
    while (absNumber >= 10) {
        absNumber /= 10;
    }
    return absNumber == 1;
}

set<int> Filter(const set<int>& A, const set<int>& B) {
    set<int> result;

    for (int element : A) {
        if (B.count(element) && startsOne(element)) {
            result.insert(element);
        }
    }

    return result;
}

set<int> input(const string& setName) {
    set<int> result;
    int size, element;

    cout << "Enter the number of elements in the set " << setName << ": ";
    cin >> size;

    cout << "Enter " << size << " element " << setName << ":\n";
    for (int i = 0; i < size; i++) {
        cout << "Element " << (i + 1) << ": ";
        cin >> element;
        result.insert(element);
    }

    return result;
}

int main() {
    set<int> A = input("A");
    set<int> B = input("B");

    set<int> result = Filter(A, B);

    cout << "mnojestvo A: ";
    for (int elem : A) cout << elem << " ";

    cout << "\nmnojestvo B: ";
    for (int elem : B) cout << elem << " ";

    cout << "\nResult (intersection + start from 1): ";
    for (int elem : result) cout << elem << " ";
    cout << endl;
    system("pause");
    return 0;

}
