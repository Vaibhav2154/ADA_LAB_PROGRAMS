#include <stdio.h>
#include <stdlib.h>

int isCycle = 0, components = 0, n, opcount = 0, isTester;

void bfs(int mat[n][n], int *vis, int source)
{
    int queue[n], parent[n];
    int rear = -1, front = -1;
    vis[source] = 1;
    queue[++rear] = source;
    parent[rear] = -1;
    while (rear != front)
    {
        int curr = queue[++front];
        int par = parent[front];
        if (isTester)
            printf("%d ", curr);
        for (int i = 0; i < n; i++)
        {
            opcount++;
            if (i != par && mat[curr][i] && vis[i])
                isCycle = 1;
            if (mat[curr][i] && !vis[i])
            {
                queue[++rear] = i;
                parent[rear] = curr;
                vis[i] = 1;
            }
        }
    }
}

void checkConnectivity(int mat[n][n])
{
    int vis[n], k = 1;
    for (int i = 0; i < n; i++)
    {
        vis[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            components++;
            if (isTester)
                printf("\nConnected component %d: ", k++);
            bfs(mat, vis, i);
        }
    }
}

void tester()
{
    isTester = 1;
    printf("Enter number of vertices :\n");
    scanf("%d", &n);
    int adjMat[n][n];
    printf("Enter the adjacency matrix :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adjMat[i][j]);
        }
    }

    checkConnectivity(adjMat);
    printf("\nNumber of connected components in the graph: %d", components);

    if (isCycle == 1)
    {
        printf("\nCycle exists\n");
    }
    else
    {
        printf("\nCycle doesnot exists\n");
    }
}

void plotter()
{
    isTester = 0;
    FILE *f1 = fopen("bfsadjMatBest.txt", "w");
    FILE *f2 = fopen("bfsadjMatWorst.txt", "w");

    for (int k = 1; k <= 10; k++)
    {
        n = k;
        int adjMat[n][n];

        // BEST CASE: Path graph (0-1-2-3-...-n-1)
        // Minimum edges, single connected component, no cycle
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = 0;

        for (int i = 0; i < n - 1; i++)
        {
            adjMat[i][i + 1] = 1;
            adjMat[i + 1][i] = 1; // Undirected edge
        }

        opcount = 0;
        isCycle = 0;
        components = 0;
        checkConnectivity(adjMat);
        fprintf(f1, "%d\t%d\n", n, opcount);

        // WORST CASE: Complete graph (all vertices connected to all)
        // Maximum edges, single component, has cycles
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                    adjMat[i][j] = 1;
                else
                    adjMat[i][j] = 0;
            }
        }

        opcount = 0;
        isCycle = 0;
        components = 0;
        checkConnectivity(adjMat);
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