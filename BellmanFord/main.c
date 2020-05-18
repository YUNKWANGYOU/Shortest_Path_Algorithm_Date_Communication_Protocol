#include <stdio.h>
#include <stdlib.h>

#define VERTICES 10
#define inf 50

#define TRUE 1
#define FALSE 0

int G[VERTICES][VERTICES] = {
                {0,4,5,inf,inf,inf,inf},
                {4,0,6,3,10,inf,inf},
                {5,6,0,4,inf,9,inf},
                {inf,3,4,0,6,3,inf},
                {inf,10,inf,6,0,3,2},
                {inf,inf,9,3,3,0,2},
                {inf,inf,inf,inf,2,2,0}
};

int distance[VERTICES][VERTICES];
int parent[VERTICES][VERTICES][2];

int path_method1(int source, int destination, int end,FILE* fp)
{
    int flag = FALSE;
    if (parent[source - 1][destination - 1][0] != source - 1)
    {
        flag = path_method1(source, parent[source - 1][destination - 1][0] + 1, end,fp);
    }
    else
    {
        fprintf(fp,"\t\t* ");
    }

    fprintf(fp,"%d -> ", parent[source - 1][destination - 1][0] + 1);

    if (destination == end)
    {
        fprintf(fp,"%d\n", end);
    }

    if (flag || parent[source - 1][destination - 1][0] != parent[source - 1][destination - 1][1])
    {
        return TRUE;
    }

    return FALSE;
}

void path_method2(int source, int destination, int end,FILE* fp)
{
    if (parent[source - 1][destination - 1][1] != source - 1)
    {
        path_method2(source, parent[source - 1][destination - 1][1] + 1, end,fp);
    }
    else
    {
        fprintf(fp,"\t\t* ");
    }

    fprintf(fp,"%d -> ", parent[source - 1][destination - 1][1] + 1);

    if (destination == end)
    {
        fprintf(fp,"%d\n", end);
    }
}

void path_print(int(*graph)[VERTICES], int n,FILE* fp)
{
    int flag;
    for (int source = 1; source <= n; source++)
    {
        fprintf(fp,"<<<—————— Node %d ——————>>>\n", source);
        for (int destination = 1; destination <= n; destination++)
        {
            if (destination != source)
            {
                fprintf(fp,"[ %d -> %d ], cost : %d\n", source, destination, graph[source - 1][destination - 1]);
                flag = path_method1(source, destination, destination,fp);
                if (flag)
                {
                    path_method2(source, destination, destination,fp);
                }
            }
        }
    }
}

void bellman(int(*graph)[VERTICES], int n)
{
    int source;

    for(source = 0 ; source < n ; source++)
    {
        int i;

        for (i = 0; i < n; i++)
        {
            int j;

            distance[source][i] = inf;

            for (j = 0; j < 2; j++)
            {
                parent[source][i][j] = -1;
            }
        }

        distance[source][source] = 0;

        int FLAG = 1;

        while (FLAG)
        {
            FLAG = 0;
            int u, v;

            for (u = 0; u < n; u++)
            {
                for (v = 0; v < n; v++)
                {
                    if (distance[source][v] == distance[source][u] + graph[u][v] && source != u && u != v && parent[source][v][0] != u && parent[source][v][1] != u)
                    {
                        parent[source][v][1] = u;
                    }
                    if (distance[source][v] > distance[source][u] + graph[u][v])
                    {
                        distance[source][v] = distance[source][u] + graph[u][v];
                        parent[source][v][0] = u;
                        parent[source][v][1] = u;
                        FLAG = 1;
                    }
                }
            }
        }
    }
}

int main()
{

    FILE* fp = fopen("BellmanTest.txt", "w");
    bellman(G, 7);
    path_print(distance, 7,fp);

    return 0;
}
