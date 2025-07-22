#include <stdio.h>
#include <stdlib.h>

int n, indeg[20], opcount = 0, queue[20], front = -1, rear = -1;

int bfs(int mat[n][n])
{
    int count = 0;
    front = rear = -1;

    // Add all vertices with 0 indegree to queue
    for (int i = 0; i < n; i++)
    {
        if (indeg[i] == 0)
        {
            queue[++rear] = i;
        }
    }

    // Process queue
    while (front != rear)
    {
        int curr = queue[++front];
        count++; // Count processed vertices

        // For each adjacent vertex, reduce indegree
        for (int i = 0; i < n; i++)
        {
            opcount++;
            if (mat[curr][i])
            {
                indeg[i]--;
                if (!indeg[i])
                    queue[++rear] = i;
            }
        }
    }

    // Check if cycle exists
    if (count < n)
        return 1; // Cycle exists (not all vertices processed)
    else
        return 0; // No cycle (all vertices processed)
}

void tester()
{
    printf("Enter number of vertices :\n");
    scanf("%d", &n);
    int adjMat[n][n];

    for (int i = 0; i < n; i++)
        indeg[i] = 0;

    printf("Enter the adjacency matrix :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adjMat[i][j]);
            if (adjMat[i][j])
                indeg[j]++;
        }
    }

    if (bfs(adjMat))
    {
        printf("Cycle exists..Cannot perform topological sorting!!!");
        exit(0);
    }
    else
    {
        printf("Topological sorting order : \n");

        for (int i = 0; i <= rear; i++)
        {
            printf("%d ", queue[i]);
        }
    }
}

void plotter()
{
    FILE *f1 = fopen("srcrmMatTopSortBest.txt", "w");
    FILE *f2 = fopen("srcrmMatTopSortWorst.txt", "w");

    for (int k = 1; k <= 10; k++)
    {
        n = k;
        int adjMat[n][n];

        // BEST CASE: Linear DAG (0->1->2->3->...->n-1)
        // Each vertex has only one outgoing edge, minimal queue operations
        for (int i = 0; i < n; i++)
        {
            indeg[i] = 0;
            for (int j = 0; j < n; j++)
                adjMat[i][j] = 0;
        }

        for (int i = 0; i < n - 1; i++)
        {
            adjMat[i][i + 1] = 1;
            indeg[i + 1] = 1;
        }

        opcount = 0;
        bfs(adjMat);
        fprintf(f1, "%d\t%d\n", n, opcount);

        // WORST CASE: Complete DAG (every i->j where i<j)
        // Maximum possible edges, maximum adjacency matrix checks
        for (int i = 0; i < n; i++)
            indeg[i] = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i < j)
                {
                    adjMat[i][j] = 1;
                    indeg[j]++;
                }
                else
                {
                    adjMat[i][j] = 0;
                }
            }
        }

        opcount = 0;
        bfs(adjMat);
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