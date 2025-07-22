#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int n, opcount = 0;
int stack[MAX], top = -1;

// Returns 1 if cycle exists, 0 otherwise
int dfs(int mat[n][n], int vis[n], int track[n], int source)
{
    vis[source] = 1;
    track[source] = 1;

    for (int i = 0; i < n; i++)
    {
        opcount++;
        if (mat[source][i] && track[i]) // Cycle detection
        {
            return 1;
        }

        if (mat[source][i] && !vis[i] && dfs(mat, vis, track, i))
        {
            return 1;
        }
    }

    stack[++top] = source; // Add to topological sort order
    track[source] = 0;
    return 0;
}

// Returns 1 if cycle exists, 0 otherwise
int checkTopologicalSort(int mat[n][n])
{
    int vis[n], track[n];
    top = -1; // Reset the stack

    for (int i = 0; i < n; i++)
    {
        vis[i] = 0;
        track[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            if (dfs(mat, vis, track, i))
            {
                return 1; // Cycle exists
            }
        }
    }

    return 0; // No cycle
}

void tester()
{
    printf("Enter number of vertices:\n");
    scanf("%d", &n);
    int adjMat[n][n];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);

    if (checkTopologicalSort(adjMat))
    {
        printf("Cycle exists... Cannot perform topological sorting!\n");
    }
    else
    {
        printf("Topological sorting order:\n");
        while (top >= 0)
        {
            printf("%d ", stack[top--]);
        }
        printf("\n");
    }
}

void plotter()
{
    FILE *f1 = fopen("dfsMatTopSortBest.txt", "w");
    FILE *f2 = fopen("dfsMatTopSortWorst.txt", "w");

    for (int k = 1; k <= 10; k++)
    {
        n = k;
        int adjMat[n][n];

        // BEST CASE: Linear DAG (0->1->2->3->...->n-1)
        // Each vertex has only one outgoing edge, minimal comparisons
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = 0;

        for (int i = 0; i < n - 1; i++)
            adjMat[i][i + 1] = 1;

        opcount = 0;
        checkTopologicalSort(adjMat);
        fprintf(f1, "%d\t%d\n", n, opcount);

        // WORST CASE: Complete DAG (every i->j where i<j)
        // Maximum possible edges, maximum comparisons
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = (i < j) ? 1 : 0;

        opcount = 0;
        checkTopologicalSort(adjMat);
        fprintf(f2, "%d\t%d\n", n, opcount);
    }

    fclose(f1);
    fclose(f2);
    printf("Best and worst case data generated successfully.\n");
}

void main()
{
    int choice;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice");
    }
}
