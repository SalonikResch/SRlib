#include <iostream>
using namespace std;

// Following https://www.geeksforgeeks.org/templates-cpp/

// An array that can store different types
template <typename T> class Array{
    private:
        T* ptr; // Pointer to the start
        int size; // Integer for number of items

    public:
        Array(T arr[], int s); // Public way to declare it
        void print(); // It will have a print statement
};

// Define the print function for the Array class
template <typename T> void Array<T>::print(){
    for(int i=0;i<size;i++)
        cout << " " << *(ptr + i);
    cout << endl;
}

// Define class creation
template <typename T> Array<T>::Array(T arr[], int s){
    ptr = new T[s];
    size = s;
    for(int i=0;i<size;i++)
        ptr[i] = arr[i];
}


int main(){
    int *arr1 = new int[5];
    float *arr2 = new float[5];

    for(int i=0;i<5;i++){
        arr1[i] = i;
        arr2[i] = (float)i + 0.5;
    }

    Array<int> a1(arr1, 5);
    Array<float> a2(arr2, 5);

    a1.print();
    a2.print();

    return 0;
}