#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

void merge(int *arr, int beg, int mid, int end)
{
    int i, j, k;
    int n1 = (mid - beg) + 1;
    int n2 = end - mid;
    int left[n1], right[n2];
    for (int i = 0; i < n1; i++)
        left[i] = arr[beg + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + j + 1];
    i = 0;
    j = 0;
    k = beg;
    while (i < n1 && j < n2)
    {
        count++;
        if (left[i] <= right[j])
            arr[k] = left[i++];
        else
            arr[k] = right[j++];
        k++;
    }
    while (i < n1)
    {
        arr[k++] = left[i++];
    }
    while (j < n2)
    {
        arr[k++] = right[j++];
    }
}

void mergeSort(int *arr, int beg, int end)
{
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        mergeSort(arr, beg, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, beg, mid, end);
    }
}

// void worst(int arr[], int beg, int end)
// {
//     int n = end - beg + 1;
//     int idx = 0;
//     // Fill odds first
//     for (int i = beg + 1; i <= end + 1; i++) {
//         if (i % 2 != 0) {
//             arr[idx++] = i;
//         }
//     }
//     // Then fill evens
//     for (int i = beg + 1; i <= end + 1; i++) {
//         if (i % 2 == 0) {
//             arr[idx++] = i;
//         }
//     }
// }
void worst(int *arr,int l, int r) {
    if (l >= r)
        return;

    int m = (l + r) / 2;
    int n1 = m - l + 1;
    int n2 = r - m;

    int a[n1], b[n2];

    // Split even and odd indices
    for (int i = 0; i < r - l + 1; i++) {
        if (i % 2 == 0)
            a[i / 2] = arr[l + i];
        else
            b[i / 2] = arr[l + i];
    }

    //Recursively split subarrays
    worst( a,0, n1 - 1);
    worst(b,0, n2- 1);

    // Copy back into original array
    for (int i = 0; i < n1; i++)
        arr[l + i] = a[i];
    for (int i = 0; i < n2; i++)
        arr[l + n1 + i] = b[i];
}

void tester()
{
    int *arr, n;
    printf("Enter the number of elements\n");
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    printf("Enter the array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("The elments of array before sorting :\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    mergeSort(arr, 0, n - 1);
    printf("The elements of the array after sorting :\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void plotter()
{
    int *arr, n;
    srand(time(NULL));
    FILE *f1, *f2, *f3, *f4;
    f1 = fopen("Mergebest.txt", "w");
    f2 = fopen("Mergeworst.txt", "w");
    f3 = fopen("Mergeavg.txt", "w");
    f4 = fopen("Worstdata.txt", "w");
    for (n = 2; n <= 1024; n = n * 2)
    {
        arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            *(arr + i) = i + 1;
        count = 0;
        mergeSort(arr, 0, n - 1); // best case
        fprintf(f1, "%d\t%d\n", n, count);
        count = 0;
        worst(arr, 0, n - 1);
        for (int i = 0; i < n; i++)
            fprintf(f4, "%d ", *(arr + i));
        fprintf(f4, "\n");
        mergeSort(arr, 0, n - 1); // worst case
        fprintf(f2, "%d\t%d\n", n, count);
        for (int i = 0; i < n; i++)
            *(arr + i) = rand() % n;
        count = 0;
        mergeSort(arr, 0, n - 1);
        fprintf(f3, "%d\t%d\n", n, count);
        free(arr);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    printf("Data is entered into file\n");
}

void main()
{
    int ch;
    printf("Enter your choice: \n\n1.Tester\n2.Plotter\n\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice!!!\n\n");
    }
}