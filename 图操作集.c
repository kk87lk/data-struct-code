#include <stdio.h>
#include <stdlib.h>
typedef int Elemtype, Weight, Vertex;
#define INFINITY 1000
#define Max 20
int visited[Max] = {0};
typedef struct
{
    Elemtype *Data;
    int front, rear;
} Queue;
Queue *CreateQueue(int num)
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->Data = (Elemtype *)malloc(sizeof(Elemtype) * num);
    Q->front = Q->rear = 0;
    return Q;
}
int isfull(Queue *Q)
{
    return (((Q->rear + 1) % Max) == Q->front);
}
int isempty(Queue *Q)
{
    return (Q->front == Q->rear);
}
int Add(Queue *Q, Elemtype x)
{
    if (isfull(Q))
        return 0;
    Q->Data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % Max;
    return 1;
}
Elemtype Delete(Queue *Q)
{
    if (isempty(Q))
        return -1;
    Elemtype temp = Q->Data[Q->front];
    Q->front = (Q->front + 1) % Max;
    return temp;
}
typedef struct
{
    int Nv;
    int Ne;
    Weight G[Max][Max];
    Elemtype data[Max];
} MGraph;
typedef struct
{
    Vertex v1, v2;
    Weight weight;
} Edge;
MGraph *CreateGraph(int Vertexnum)
{
    MGraph *G;
    G = (MGraph *)malloc(sizeof(MGraph));
    G->Nv = Vertexnum;
    G->Ne = 0;
    Vertex v, w;
    for (v = 0; v < G->Nv; v++)
    {
        for (w = 0; w < G->Nv; w++)
        {
            G->G[v][w] = INFINITY;
        }
    }
    return G;
}

void InsertEdge(MGraph *G, Edge *E)
{
    G->G[E->v1][E->v2] = E->weight;
    G->G[E->v2][E->v1] = E->weight;
}

MGraph *BuildMGraph()
{
    MGraph *G;
    Edge *E;
    Vertex v;
    int Nv, i;
    printf("please input the V num:");
    scanf("%d", &Nv);
    G = CreateGraph(Nv);
    printf("please input the Edge num:");
    scanf("%d", &(G->Ne));
    if (G->Ne != 0)
    {
        E = (Edge *)malloc(sizeof(Edge));
        for (i = 0; i < G->Ne; i++)
        {
            printf("please input v1 v2 and weight:");
            scanf("%d%d%d", &(E->v1), &(E->v2), &(E->weight));
            InsertEdge(G, E);
        }
    }
    // for (v = 0; v < G->Nv;v++){
    //     scanf("%d", &(G->data[v]));
    // }
    return G;
}
int IsEdge(MGraph *G, Vertex v, Vertex w)
{
    return (G->G[v][w] != INFINITY);
}
void visit(Vertex V)
{
    printf("%d ", V);
}
void BFS(MGraph *G, Vertex S, void (*visit)(Vertex))
{
    Queue *Q = CreateQueue(Max);
    Vertex V, W;
    visit(S);
    visited[S] = 1;
    Add(Q, S);
    while (!isempty(Q))
    {
        V = Delete(Q);
        for (W = 0; W < G->Nv; W++)
        {
            if (!visited[W] && IsEdge(G, V, W))
            {
                visit(W);
                visited[W] = 1;
                Add(Q, W);
            }
        }
    }
}
void PrintMGraph(MGraph *G)
{
    Vertex v, w;
    for (v = 0; v < G->Nv; v++)
    {
        for (w = 0; w < G->Nv; w++)
        {
            if (G->G[v][w] != INFINITY)
                printf("<%d,%d> ", v, w);
            else
                printf(" 0 ");
        }
        printf("\n");
    }
}
typedef struct node Node;
struct node
{
    Vertex Adjv;
    Weight weight;
    Node *next;
};
typedef struct
{
    Node *FirstEdge;
    Elemtype data;
} Adjlist[Max];
typedef struct
{
    int Nv;
    int Ne;
    Adjlist G;
} LGraph;
LGraph *CreateLGraph(int Vertexnum)
{
    Vertex v;
    LGraph *G;
    G = (LGraph *)malloc(sizeof(LGraph));
    G->Nv = Vertexnum;
    G->Ne = 0;
    for (v = 0; v < G->Nv; v++)
    {
        G->G[v].FirstEdge = NULL;
    }
    return G;
}
void InsertLEdge(LGraph *G, Edge *E)
{
    Node *NewNode;
    NewNode = (Node *)malloc(sizeof(NewNode));
    NewNode->Adjv = E->v2;
    NewNode->weight = E->weight;
    NewNode->next = G->G[E->v1].FirstEdge;
    G->G[E->v1].FirstEdge = NewNode;

    NewNode = (Node *)malloc(sizeof(NewNode));
    NewNode->Adjv = E->v1;
    NewNode->weight = E->weight;
    NewNode->next = G->G[E->v2].FirstEdge;
    G->G[E->v2].FirstEdge = NewNode;
}
LGraph *BuildLGraph()
{
    LGraph *G;
    Edge *E;
    Vertex v, i;
    int Nv;
    printf("please input the V num:");
    scanf("%d", &Nv);
    G = (LGraph *)malloc(sizeof(LGraph));
    G = CreateLGraph(Nv);
    printf("please input the Edge num:");
    scanf("%d", &(G->Ne));
    if (G->Ne != 0)
    {
        E = (Edge *)malloc(sizeof(Edge));
        for (i = 0; i < G->Ne; i++)
        {
            printf("please input v1 v2 and weight:");
            scanf("%d%d%d", &(E->v1), &(E->v2), &(E->weight));
            InsertLEdge(G, E);
        }
    }
    // for (v = 0; v < G->Nv;v++){
    //     printf("input the %d's data:",v);
    //     scanf("%d", &(G->G[v].data));
    // }
    return G;
}
void DFS(LGraph *G, Vertex V, void (*visit)(Vertex))
{
    Node *W;
    visit(V);
    visited[V] = 1;
    for (W = G->G[V].FirstEdge; W; W = W->next)
    {
        if (!visited[W->Adjv])
            DFS(G, W->Adjv, visit);
    }
}
void PrintLGraph(LGraph *G)
{
    Vertex i = 0;
    Node *W;
    for (i = 0; i < G->Nv; i++)
    {
        for (W = G->G[i].FirstEdge; W; W = W->next)
        {
            printf("<%d,%d> ", i, W->Adjv);
            if(!(W->next))
                printf("\n");
        }
        
    }
}
int main(){
    int x,i;
    int Mmark = 0, Lmark = 0;
    MGraph *MGRAPH;
    LGraph *LGRAPH;
    do{
        printf("1.Build MGraph\n");
        printf("2.Build LGraph\n");
        printf("3.BFS(MGraph)\n");
        printf("4.DFS(LGraph)\n");
        printf("0.Exit\n");
        scanf("%d", &x);
        switch(x){
            case 1:
                Mmark++;
                MGRAPH = BuildMGraph();
                PrintMGraph(MGRAPH);
                break;
            case 2:
                Lmark++;
                LGRAPH = BuildLGraph();
                PrintLGraph(LGRAPH);
                break;
            case 3:
                if(Mmark){
                    Vertex S;
                    printf("Please input the Place you want to start:");
                    scanf("%d", &S);
                    BFS(MGRAPH, S, visit);
                    printf("\n");
                    for (i = 0; i < Max; i++)
                    {
                        visited[i] = 0;
                    }
                }else{
                    printf("There is no MGraph in memory!\n");
                    continue;
                }
                break;
            case 4:
                if(Lmark){
                    Vertex V;
                    printf("Please input the Place you want to start:");
                    scanf("%d", &V);
                    DFS(LGRAPH, V, visit);
                    printf("\n");
                    for (i = 0; i < Max;i++)
                    {
                        visited[i] = 0;
                    }
                }else{
                    printf("There is no LGraph in memory!\n");
                    continue;
                }
                break;
            case 0:
                printf("Thanks to use!\n");
                exit(1);
        }
    } while (1);
    return 1;
}