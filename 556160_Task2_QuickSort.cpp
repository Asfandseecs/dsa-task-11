#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

int arraySize, depth, maxDepth;
long long comparisons;

void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; ++i)
        cout << (i ? " " : "") << arr[i];
    cout << "]\n";
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; ++j) {
        ++comparisons;
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    cout << "Partition [" << low << ".." << high
         << "] pivot=" << pivot << ", pi=" << i + 1 << ": ";
    printArray(arr, arraySize);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low > high) return;
    ++depth;
    if (depth > maxDepth) maxDepth = depth;
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
    --depth;
}

void runCase(const string& name, vector<int> values) {
    arraySize = static_cast<int>(values.size());
    comparisons = depth = maxDepth = 0;
    cout << "\n" << name << " (n=" << arraySize << ")\nInput: ";
    printArray(values.data(), arraySize);
    quickSort(values.data(), 0, arraySize - 1);
    cout << "Sorted: ";
    printArray(values.data(), arraySize);
    bool correct = true;
    for (int i = 1; i < arraySize; ++i)
        if (values[i - 1] > values[i]) correct = false;
    cout << "Comparisons: " << comparisons
         << ", max depth: " << maxDepth
         << ", result: " << (correct ? "PASS" : "FAIL") << "\n";
}

int main() {
    cout << "Asfandyar Kamran | CMS 556160 | BSAI 2A\n";
    cout << "Task 2 - Quick Sort (last element pivot)\n";
    runCase("First trace array", {2, 1, 5, 4, 6, 3});
    runCase("Second trace array", {35, 12, 43, 8, 51, 27, 19});
    runCase("Random order", {5, 1, 4, 2, 8});
    runCase("Already sorted", {1, 2, 4, 5, 8});
    runCase("Reverse sorted", {8, 5, 4, 2, 1});
    runCase("Repeated values", {7, 7, 7, 7, 7});
    runCase("Single element", {42});
    runCase("Empty array", {});
    return 0;
}
