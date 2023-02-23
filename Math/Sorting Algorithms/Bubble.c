class BubbleSort{

    //vector by distance
    void BubbleSortByDistance(TVectorArray arr, vector origin) {
        int n = arr.Count();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (vector.Distance(arr[j], origin) > vector.Distance(arr[j + 1], origin)) {
                    Swap(arr, j, j + 1);
                }
            }
        }
    }
    void Swap(TVectorArray arr, int i, int j) {
        vector temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }


    //int by size
    void BubbleSort(array<int> arr) {
        int n = arr.Count();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}