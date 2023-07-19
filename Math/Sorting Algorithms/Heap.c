class HeapSort{
    void HeapSort(array<int> arr) {
        for (int i = arr.Count() / 2 - 1; i >= 0; i--) {
            Heapify(arr, arr.Count(), i);
        }

        for (int j = arr.Count() - 1; j >= 0; j--) {
            int temp = arr[0];
            arr[0] = arr[j];
            arr[j] = temp;

            Heapify(arr, j, 0);
        }
    }

    void Heapify(array<int> arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            Heapify(arr, n, largest);
        }
    }
}