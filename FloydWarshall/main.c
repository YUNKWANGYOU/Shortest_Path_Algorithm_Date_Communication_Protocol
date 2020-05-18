#include <stdio.h>

#define VERTICES 10
#define inf 50


int G[VERTICES][VERTICES] = {
                {0,4,5,inf,inf,inf,inf},
                {4,0,6,3,10,inf,inf},
                {5,6,0,4,inf,9,inf},
                {inf,3,4,0,6,3,inf},
                {inf,10,inf,6,0,3,2},
                {inf,inf,9,3,3,0,2},
                {inf,inf,inf,inf,2,2,0}
};

int path[VERTICES][VERTICES][2];


void path_method1(int source, int destination,FILE *fp)
{
    if (path[source - 1][destination - 1][0] != -1)
    {
        path_method1(source, path[source - 1][destination - 1][0],fp);
        fprintf(fp," %d ->", path[source - 1][destination - 1][0]);
        path_method1(path[source - 1][destination - 1][0], destination,fp);
    }
}

void path_method2(int source, int destination,FILE *fp)
{
    if (path[source - 1][destination - 1][1] != -1)
    {
        path_method2(source, path[source - 1][destination - 1][1],fp);
        fprintf(fp," %d ->", path[source - 1][destination - 1][1]);
        path_method2(path[source - 1][destination - 1][1], destination,fp);
    }
}

void path_print(int(*graph)[VERTICES], int n,FILE *fp)
{
    for (int source = 1; source <= n; source++)
    {
        fprintf(fp,"<<<--------------- Node %d --------------->>>\n", source);

        for (int destination = 1; destination <= n; destination++)
        {
            if (destination != source)
            {
                fprintf(fp,"[ %d -> %d ], cost : %d\n", source, destination, graph[source - 1][destination - 1]);
                fprintf(fp,"\t\t* %d ->", source);

                path_method1(source, destination,fp);

                fprintf(fp," %d\n", destination);

                if (path[source - 1][destination - 1][0] != path[source - 1][destination - 1][1])
                {
                    fprintf(fp,"\t\t* %d ->", source);
                    path_method2(source, destination,fp);
                    fprintf(fp," %d\n", destination);
                }
            }
        }
    }
}

void floyd(int(*graph)[VERTICES], int n)
{
    int i, j, k;

    for (i = 0; i < VERTICES; i++)
    {
        for (j = 0; j < VERTICES; j++)
        {
            for (k = 0; k < 2; k++)
            {
                path[i][j][k] = -1;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                if (graph[j][k] == graph[j][i] + graph[i][j] && j != i && k != i && path[j][k][0] != i + 1 && path[j][k][1] != i + 1)
                {
                    path[j][k][1] = i + 1;
                }

                if (graph[j][k] > graph[j][i] + graph[i][k])
                {
                    path[j][k][0] = i + 1;
                    path[j][k][1] = i + 1;
                    graph[j][k] = graph[j][i] + graph[i][k];
                }
            }
        }
    }
}


int main() {
    FILE *fp;
    fp = fopen("FloydTest.txt","w");

    floyd(G, 7);
    path_print(G, 7,fp);

    return 0;
}
