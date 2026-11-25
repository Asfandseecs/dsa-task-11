#include <iostream>
#include <vector>
#include <string>
using namespace std;

int arraySize, depth, maxDepth;
long long comparisons;

void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; ++i)
        cout << (i ? " " : "") << arr[i];
    cout << "]\n";
}

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1, n2 = high - mid;
    vector<int> left(n1), right(n2);
    for (int i = 0; i < n1; ++i) left[i] = arr[low + i];
    for (int j = 0; j < n2; ++j) right[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        ++comparisons;
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
    cout << "Merge [" << low << ".." << high << "]: ";
    printArray(arr, arraySize);
}

void mergeSort(int arr[], int low, int high) {
    if (low > high) return;
    ++depth;
    if (depth > maxDepth) maxDepth = depth;
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
    --depth;
}

void runCase(const string& name, vector<int> values) {
    arraySize = static_cast<int>(values.size());
    comparisons = depth = maxDepth = 0;
    cout << "\n" << name << " (n=" << arraySize << ")\nInput: ";
    printArray(values.data(), arraySize);
    mergeSort(values.data(), 0, arraySize - 1);
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
    cout << "Task 1 - Merge Sort\n";
    runCase("Required array", {35, 12, 43, 8, 51, 27, 19});
    runCase("Already sorted", {1, 2, 4, 5, 8});
    runCase("Reverse sorted", {8, 5, 4, 2, 1});
    runCase("Repeated values", {5, 2, 5, 1, 2});
    runCase("Single element", {42});
    runCase("Empty array", {});
    return 0;
}
