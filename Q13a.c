#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0, t[25][25], w[25], v[25];

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int knapsackMemo(int n, int m)
{
    if (t[n][m] != -1)
        return t[n][m];

    count++;
    if (w[n - 1] <= m)
        return t[n][m] = max(knapsackMemo(n - 1, m), v[n - 1] + knapsackMemo(n - 1, m - w[n - 1]));
    else
        return t[n][m] = knapsackMemo(n - 1, m);
}

void init(int n, int m)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            if (i == 0 || j == 0)
                t[i][j] = 0;
            else
                t[i][j] = -1;
    }
}

void tester()
{
    int n, m;
    printf("Number of items: ");
    scanf("%d", &n);
    printf("Sack capacity: ");
    scanf("%d", &m);

    printf("Weight\tValue\n");
    for (int i = 0; i < n; i++)
        scanf("%d%d", &w[i], &v[i]);

    init(n, m);
    printf("Max value is %d\n", knapsackMemo(n, m));

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            printf("%d\t", t[i][j]);
        printf("\n");
    }

    printf("Composition:\n");
    int k = m;
    for (int i = n; i > 0; i--)
    {
        if (t[i][k] != t[i - 1][k])
        {
            printf("%d\t", i);
            k -= w[i - 1];
        }
    }
    printf("\nOpcount: %d\n", count);
}

void plotter()
{
    FILE *fp = fopen("KnapMemo.txt", "w");
    for (int i = 5; i <= 10; i++)
    {
        int m = i * 2;
        for (int j = 0; j < i; j++)
        {
            w[j] = rand() % 10 + 1;
            v[j] = rand() % 50 + 1;
        }
        init(i, m);
        count = 0;
        knapsackMemo(i, m);
        fprintf(fp, "%d\t%d\n", i, count);
    }
    fclose(fp);
}

int main()
{
    int ch;
    printf("Enter\n1.Tester\n2.Plotter\n");
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
        printf("Invalid choice.\n");
    }
    return 0;
}
