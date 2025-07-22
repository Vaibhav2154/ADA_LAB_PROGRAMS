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

void worst(int arr[], int beg, int end)
{
    if (beg < end)
    {
        // Create two temporary arrays
        int n = end - beg + 1;
        int a[n / 2 + n % 2];
        int b[n / 2];

        // Distribute alternate elements of arr into a and b
        int i_a = 0, i_b = 0;
        for (int i = beg; i <= end; i++)
        {
            if ((i - beg) % 2 == 0)
            {
                a[i_a++] = arr[i];
            }
            else
            {
                b[i_b++] = arr[i];
            }
        }

        // Recurse on the two halves
        worst(a, 0, i_a - 1);
        worst(b, 0, i_b - 1);

        // Copy the rearranged elements from a and b back into arr
        int k = beg;
        for (int i = 0; i < i_a; i++)
        {
            arr[k++] = a[i];
        }
        for (int i = 0; i < i_b; i++)
        {
            arr[k++] = b[i];
        }
    }
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
            fprintf(f4, "%d", *(arr + i));
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