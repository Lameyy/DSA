#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Function for Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Function for Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
        k++;
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Binary Search
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Interpolation Search
int interpolationSearch(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));
        if (arr[pos] == target) return pos;
        if (arr[pos] < target) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

void displayTimeComplexity() {
    cout << "\nTime Complexity Analysis:\n";
    cout << "Selection Sort: O(N^2) (All cases)\n";
    cout << "Merge Sort: O(N log N) (Best, Average, Worst)\n";
    cout << "Binary Search: O(log N) (Best/Average), O(log N) (Worst)\n";
    cout << "Interpolation Search: O(log log N) (Best), O(N) (Worst, if elements are unevenly distributed)\n";
}

int main() {
    int N;
    cout << "Enter number of elements: ";
    cin >> N;

    vector<int> arr(N);
    cout << "Enter " << N << " random integers: ";
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    // Sorting (Selection Sort)
    auto start = high_resolution_clock::now();
    selectionSort(arr);
    auto stop = high_resolution_clock::now();
    cout << "Selection Sort Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    // Sorting (Merge Sort)
    start = high_resolution_clock::now();
    mergeSort(arr, 0, N - 1);
    stop = high_resolution_clock::now();
    cout << "Merge Sort Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    // Searching (Binary Search)
    int target;
    cout << "Enter a number to search: ";
    cin >> target;

    start = high_resolution_clock::now();
    int binaryIndex = binarySearch(arr, target);
    stop = high_resolution_clock::now();
    cout << "Binary Search Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";
    if (binaryIndex != -1) cout << "Found at index: " << binaryIndex << "\n";
    else cout << "Not found\n";

    // Searching (Interpolation Search)
    start = high_resolution_clock::now();
    int interpIndex = interpolationSearch(arr, target);
    stop = high_resolution_clock::now();
    cout << "Interpolation Search Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";
    if (interpIndex != -1) cout << "Found at index: " << interpIndex << "\n";
    else cout << "Not found\n";

    // Display Time Complexity Analysis
    displayTimeComplexity();

    return 0;
}
