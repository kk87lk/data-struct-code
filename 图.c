#include <stdio.h>
#include <stdlib.h>
typedef int Elemtype,Weight,Vertex;
#define Max 20
int visited[Max] = {0};
typedef struct{
    Elemtype *Data;
    int front, rear;
} Queue;
Queue* CreateQueue(int num){
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->Data = (Elemtype *)malloc(sizeof(Elemtype) * num);
    Q->front = Q->rear = 0;
    return Q;
}
int isfull(Queue* Q){
    return (((Q->rear+1)%Max)==Q->front);
}
int isempty(Queue *Q){
    return (Q->front == Q->rear);
}
int Add(Queue* Q,Elemtype x){
    if(isfull(Q))
        return 0;
    Q->Data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % Max;
    return 1;
}
Elemtype Delete(Queue* Q){
    if(isempty(Q))
        return -1;
    Elemtype temp = Q->Data[Q->front];
    Q->front = (Q->front + 1) % Max;
    return temp;
}
typedef struct{
    int Nv;
    int Ne;
    Weight G[Max][Max];
    Elemtype data[Max];
} MGraph;
typedef struct{
    Vertex v1, v2;
    Weight weight;
} Edge;
MGraph* CreateGraph(int Vertexnum){
    MGraph *G;
    G = (MGraph *)malloc(sizeof(MGraph));
    G->Nv = Vertexnum;
    G->Ne = 0;
    Vertex v, w;
    for (v = 0; v < G->Nv; v++)
    {
        for (w = 0; w < G->Nv;w++){
            G->G[v][w] = 0;
        }
    }
    return G;
}

void InsertEdge(MGraph* G,Edge* E){
    G->G[E->v1][E->v2] = E->weight;
    G->G[E->v2][E->v1] = E->weight;
}

MGraph* BuildGraph(){
    MGraph *G;
    Edge *E;
    Vertex v;
    int Nv, i;
    printf("please input the V num:");
    scanf("%d", &Nv);
    G = CreateGraph(Nv);
    printf("please input the Edge num:");
    scanf("%d", &(G->Ne));
    if(G->Ne!=0){
        E = (Edge *)malloc(sizeof(Edge));
        for (i = 0; i < G->Ne;i++){
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
int IsEdge(MGraph* G,Vertex v,Vertex w){
    return (G->G[v][w] != 0);
}
void visit(Vertex V){
    printf("%d ", V);
}
void BFS(MGraph* G,Vertex S,void(*visit)(Vertex)){
    Queue *Q = CreateQueue(Max);
    Vertex V, W;
    visit(S);
    visited[S] = 1;
    Add(Q, S);
    while (!isempty(Q))
    {
        V = Delete(Q);
        for (W = 0; W < G->Nv;W++){
            if(!visited[W]&&IsEdge(G,V,W)){
                visit(W);
                visited[W] = 1;
                Add(Q, W);
            }
        }
    }
}
void PrintMGraph(MGraph* G){
    Vertex v, w;
    for (v = 0; v < G->Nv;v++){
        for (w = 0; w < G->Nv;w++){
            if(G->G[v][w]!=0)
                printf("<%d,%d> ", v, w);
            else
                printf(" 0 ");
        }
        printf("\n");
    }
}
int main(){
    MGraph *G = BuildGraph();
    //BFS(G, 1, visit);
    PrintMGraph(G);
}
