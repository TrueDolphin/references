class SelectionSort {
    void SelectionSort(array<int> arr) {
        for (int i = 0; i < arr.Count() - 1; i++) {
            int min_index = i;
            for (int j = i + 1; j < arr.Count(); j++) {
                if (arr[j] < arr[min_index]) {
                    min_index = j;
                }
            }
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
    }
}