#include <points.h>

void quicksort(Point arr[], int lo, int hi, int (*cmp)(Point, Point)) {
    if (lo >= hi) return;
    Point pivot = arr[hi];
    int i = lo;
    for (int j = lo; j < hi; j++) {
        if (cmp(arr[j], pivot) < 0) {
            Point temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            i++;
        }
    }
    Point temp = arr[i]; arr[i] = arr[hi]; arr[hi] = temp;
    quicksort(arr, lo, i - 1, cmp);
    quicksort(arr, i + 1, hi, cmp);
}

void merge(Point arr[], int l, int m, int r, int (*cmp)(Point, Point)) {
    int n1 = m - l + 1, n2 = r - m;
    Point L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (cmp(L[i], R[j]) <= 0) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergesort(Point arr[], int l, int r, int (*cmp)(Point, Point)) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m, cmp);
        mergesort(arr, m + 1, r, cmp);
        merge(arr, l, m, r, cmp);
    }
}