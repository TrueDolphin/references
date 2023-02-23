class InsertionSort{

    void InsertionSortByDistance(TVectorArray arr, vector origin) {
        int n = arr.Count();
        for (int i = 1; i < n; i++) {
            vector key = arr[i];
            float keyDist = vector.Distance(key, origin);
            int j = i - 1;
            while (j >= 0 && vector.Distance(arr[j], origin) > keyDist) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }


    void InsertionSort(array<int> arr) {
        int n = arr.Count();
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
}