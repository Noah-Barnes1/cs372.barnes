#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <chrono>
#include <random>
using namespace std;
//O(n^2) Sorts
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//Quicksort
int partitionQS(int a[], int start, int end) {
    int pivot = a[end];
    int pIndex = start;
    for (int i = start; i < end; i++) {
        if (a[i] <= pivot) {
            swap(a[i], a[pIndex]);
            pIndex++;
        }
    }
    swap(a[pIndex], a[end]);
    return pIndex;
}

void iterativeQuickSort(int a[], int n) {
    stack<pair<int, int>> s;
    s.push({ 0, n - 1 });

    while (!s.empty()) {
        int start = s.top().first;
        int end = s.top().second;
        s.pop();

        if (start >= end) continue;

        int pivot = partitionQS(a, start, end);

        if (pivot - 1 > start) {
            s.push({ start, pivot - 1 });
        }
        if (pivot + 1 < end) {
            s.push({ pivot + 1, end });
        }
    }
}

//Timing Helper
template <typename Func>
long long timeSort(Func sortFunc, vector<int> data) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Wrapper for quicksort (works on vector<int>)
long long timeQuickSort(vector<int> data) {
    int n = data.size();
    int* arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = data[i];

    auto start = chrono::high_resolution_clock::now();
    iterativeQuickSort(arr, n);
    auto end = chrono::high_resolution_clock::now();

    delete[] arr;
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

//Main
int main() {
    vector<int> sizes = { 10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 250000 };

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);

    for (int n : sizes) {
        vector<int> data(n);
        for (int& x : data) x = dist(gen);

        cout << "\nArray Size: " << n << endl;

        cout << "Bubble Sort:    " << timeSort(bubbleSort, data) << " ms" << endl;
        cout << "Selection Sort: " << timeSort(selectionSort, data) << " ms" << endl;
        cout << "Insertion Sort: " << timeSort(insertionSort, data) << " ms" << endl;
        cout << "QuickSort:      " << timeQuickSort(data) << " ms" << endl;
    }

    return 0;
}

