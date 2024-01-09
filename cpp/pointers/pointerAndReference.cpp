#include <iostream>
using namespace std;

void incrementReference(int& ref) {
    ref++;  // Incrementing the value of the reference affects the original variable
}

void incrementPointer(int *pointer){
    (*pointer)++;
}

int main() {
    int a = 10;
    incrementReference(a);  // Passing a by reference
    cout << a << endl;
    incrementPointer(&a);  // Passing a by pointer
    cout << a << endl;
    return 0;
}