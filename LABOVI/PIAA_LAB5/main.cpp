#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <climits>

using namespace std;
using namespace chrono;

void bubbleSort(vector<int>& arr)
{
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) 
            break;
    }
}

int partitionQS(vector<int>& arr, int low, int high)
{
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partitionQS(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void countingSort(vector<int>& arr, int exp)
{
    int n = arr.size();
    vector<int> output(n);
    int count[10] = { 0 };

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        int digit =(arr[i] / exp)%10;
        output[--count[digit]] = arr[i];
    }

    arr = output;
}

void radixSort(vector<int>& arr)
{
    int mx = *max_element(arr.begin(), arr.end());
    for (int exp = 1; mx / exp > 0; exp *= 10)
        countingSort(arr, exp);
}


int chocDiff(const vector<int>& arr, int M)
{
    int diff = INT_MAX;
    for (int i = 0; i + M - 1 < arr.size(); i++)
        diff = min(diff, arr[i + M - 1] - arr[i]);
    return diff;
}

size_t memoryUsage(const vector<int>& arr, bool radixExtra = false)
{
    size_t mem = arr.size() * sizeof(int);
    if (radixExtra)
        mem += arr.size() * sizeof(int); 
    return mem;
}

void test(int N)
{
    vector<int> original(N);
    for (int i = 0; i < N; i++)
        original[i] = rand() % 10001;

    int M = N * 0.3;
    vector<int> arr;

    cout << "\nN = " << N << ", M = " << M << endl;

    arr = original;
    if (N <= 10000)
    {
        auto start = high_resolution_clock::now();
        bubbleSort(arr);
        auto end = high_resolution_clock::now();

        cout << "bubble sort: "
            << duration_cast<milliseconds>(end - start).count()
            << " ms, mem: "
            << memoryUsage(arr) / 1024 << " KB, diff: "
            << chocDiff(arr, M) << endl;
    }
    else
    {
        cout << "bubble sort: presporo, Mem: "
            << memoryUsage(arr) / 1024 << " KB" << endl;
    }

    arr = original;
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();

    cout << "quick sort:  "
        << duration_cast<milliseconds>(end - start).count()
        << " ms, mem: "
        << memoryUsage(arr) / 1024 << " KB, diff: "
        << chocDiff(arr, M) << endl;

    arr = original;
    start = high_resolution_clock::now();
    radixSort(arr);
    end = high_resolution_clock::now();

    cout << "radix sort:  "
        << duration_cast<milliseconds>(end - start).count()
        << " ms, mem: "
        << memoryUsage(arr, true) / 1024 << " KB, diff: "
        << chocDiff(arr, M) << endl;
}

int main()
{
    srand(time(0));

    int sizes[] = { 100, 1000, 10000, 100000, 1000000, 10000000 };

    for (int n : sizes)
        test(n);

    return 0;
}
