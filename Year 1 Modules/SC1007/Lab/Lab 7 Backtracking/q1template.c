#include <stdint.h>
#include <stdio.h>

// Number of vertices in the graph
#define V 4

int graphColoring(int graph[V][V], int, int color[], int);
int isSafe(int, int graph[V][V], int color[], int);
void printSolution(int color[]);

int main()
{
    /* Create following graph and
       test whether it is 3 colorable
      (2)---(3)
       |   / |
       |  /  |
       | /   |
      (1)---(4)
    */
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };
    int m = 3; // Number of colors

    // Initialize all color values as 0.
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (!graphColoring(graph, m, color, 0))
        printf("Solution does not exist");
    else
        printSolution(color);
    return 0;
}

void printSolution(int color[]);

/* A utility function to check if
   the current color assignment
   is safe for vertex v i.e. checks
   whether the edge exists or not
   (i.e, graph[v][i]==1). If exist
   then checks whether the color to
   be filled in the new vertex(c is
   sent in the parameter) is already
   used by its adjacent
   vertices(i-->adj vertices) or
   not (i.e, color[i]==c) */
int isSafe(
    int v, int graph[V][V],
    int color[], int c)
{
    for (int i = 0; i < V; i++)
        if (
            graph[v][i] && c == color[i])
            return 0;
    return 1;
}

/* A backtracking function
to solve m coloring problem */
int graphColoring(
    int graph[V][V], int m,
    int color[], int v)
{
    // base case
    if(v==V) return 1;

    //consider this vertex v and try different colours
    for(int c = 0; c<=m; c++)
    {
        if(isSafe(v,graph,color,c))
        {
            color[v] = c;
            if(graphColoring(graph, m, color, v+1) == 1)
                return 1;
            color[v] = 0;
        }
    }
    // if no color can be assigned
    return 0;

}

/* A utility function to print solution */
void printSolution(int color[])
{
    printf(
        "Solution Exists:"
        " Following are the assigned colors \n");
    for (int i = 0; i < V; i++)
        printf(" %d ", color[i]);
    printf("\n");
}
