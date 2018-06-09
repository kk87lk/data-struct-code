#include <stdio.h>
#include <stdlib.h>
#define INFINITY 1000
#define MAX 20
typedef int vertex,WeightType;
typedef struct
{
    vertex v1, v2;
    WeightType weight;
} Edge;
typedef struct{
    int Nv;
    int Ne;
    WeightType G[MAX][MAX];
} MGraph;
typedef struct node Node;
struct node
{
    vertex Adjv;
    WeightType weight;
    Node *next;
};
typedef struct
{
    Node *FirstEdge;
} Adjlist[MAX];
typedef struct
{
    int Nv;
    int Ne;
    Adjlist G;
} LGraph;
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
LGraph *CreateLGraph(int Vertexnum)
{
    vertex v;
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
vertex FindMinDist(MGraph* Graph,WeightType dist[]){
    vertex MinV, V;
    WeightType MinDist = INFINITY;
    for (V = 0; V < Graph->Nv;V++){
        if(dist[V]!=0&&dist[V]<MinDist){
            MinDist = dist[V];
            MinV = V;
        }
    }
    if(MinDist<INFINITY)
        return MinV;
    else
        return -1;
}
int Prime(MGraph* Graph,LGraph* MST){
    WeightType dist[MAX],Totalweight=0;
    vertex parent[MAX], V, W;
    int Vcount=0;
    Edge* E;
    for (V = 0; V < Graph->Nv;V++){
        dist[V] = Graph->G[0][V];
        parent[V] = 0;              //默认所有结点的父节点都是0
    }
    MST = CreateLGraph(Graph->Nv);
    E = (Edge*)malloc(sizeof(Edge));
    dist[0] = 0;
    Vcount++;
    parent[0] = -1;
    while (1)
    {
        V = FindMinDist(Graph, dist);
        if(V==-1)
            break;
        E->v1 = parent[V];
        E->v2 = V;
        E->weight = dist[V];
        InsertLEdge(MST, E);
        Totalweight += dist[V];
        dist[V] = 0;                //收录
        Vcount++;
        for (W = 0; W < Graph->Nv;W++){                     //更新
            if(dist[W]!=0&&Graph->G[V][W]<INFINITY){
                if(Graph->G[V][W]<dist[W]){
                    dist[W] = Graph->G[V][W];
                    parent[W] = V;
                }
            }
        }
    }
    if(Vcount<Graph->Nv)
        Totalweight = -1;
    return Totalweight;
}