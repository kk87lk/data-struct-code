//利用最小堆和并查集优化，复杂度：O(eloge)
#include <stdio.h>
#include <stdlib.h>
int Totalweight = 0;
#define MAX 20
#define INFINITY 1000
typedef int vertex, WeightType;
typedef vertex Elemtype,SetName;
typedef Elemtype SetType[MAX];
typedef struct
{
    vertex v1, v2;
    WeightType weight;
} Edge;
typedef struct
{
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
    NewNode = (Node *)malloc(sizeof(Node));
    NewNode->Adjv = E->v2;
    NewNode->weight = E->weight;
    NewNode->next = G->G[E->v1].FirstEdge;
    G->G[E->v1].FirstEdge = NewNode;

    NewNode = (Node *)malloc(sizeof(Node));
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
vertex FindMinDist(MGraph *Graph, WeightType dist[])
{
    vertex MinV, V;
    WeightType MinDist = INFINITY;
    for (V = 0; V < Graph->Nv; V++)
    {
        if (dist[V] != 0 && dist[V] < MinDist)
        {
            MinDist = dist[V];
            MinV = V;
        }
    }
    if (MinDist < INFINITY)
        return MinV;
    else
        return -1;
}
void PrintLGraph(LGraph *G)
{
    vertex i = 0;
    Node *W;
    for (i = 0; i < G->Nv; i++)
    {
        for (W = G->G[i].FirstEdge; W; W = W->next)
        {
            printf("<%d,%d> ", i, W->Adjv);
            if (!(W->next))
                printf("\n");
        }
    }
}
void InsertEdge(MGraph *G, Edge *E)
{
    G->G[E->v1][E->v2] = E->weight;
    G->G[E->v2][E->v1] = E->weight;
}
MGraph *CreateGraph(int Vertexnum)
{
    MGraph *G;
    G = (MGraph *)malloc(sizeof(MGraph));
    G->Nv = Vertexnum;
    G->Ne = 0;
    vertex v, w;
    for (v = 0; v < G->Nv; v++)
    {
        for (w = 0; w < G->Nv; w++)
        {
            G->G[v][w] = INFINITY;
        }
    }
    return G;
}
LGraph *BuildLGraph()
{
    LGraph *G;
    Edge *E;
    vertex i; //v;
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
MGraph *BuildMGraph()
{
    MGraph *G;
    Edge *E;
    //vertex v;
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
void InitializeVSET(SetType S,int N){
    Elemtype x;
    for (x = 0; x < N;x++){
        S[x] = -1;
    }
}
void Union(SetType S,SetName Root1,SetName Root2){
    if(S[Root1]>S[Root2]){
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }else{
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}
SetName Find(SetType S,Elemtype x){
    if(S[x]<0)
        return x;
    else
        return S[x] = Find(S, S[x]);
}
int CheckCycle(SetType VSet,vertex v1,vertex v2){
    vertex root1, root2;
    root1 = Find(VSet, v1);
    root2 = Find(VSet, v2);
    if(root1==root2)
        return -1;
    else{
        Union(VSet, root1, root2);
        return 1;
    }
}
void PercDown(Edge *ESet, int p, int N)
{
    int Parent, Child;
    Edge x;
    x = ESet[p];
    for (Parent = p; (Parent * 2 + 1) < N;Parent=Child){
        Child = Parent * 2 + 1;
        if ((Child != N - 1)&&(ESet[Child].weight>ESet[Child+1].weight)){
            Child++;
        }
        if(x.weight<=ESet[Child].weight)
            break;
        else{
            ESet[Parent] = ESet[Child];
        }
    }
    ESet[Parent] = x;
}
void InitializeESET(LGraph*Graph,Edge* ESet){
    vertex v;
    Node *w;
    int Ecount = 0;
    for (v = 0; v < Graph->Nv;v++){
        for (w = Graph->G[v].FirstEdge; w;w=w->next){
            if(v<w->Adjv){
                ESet[Ecount].v1 = v;
                ESet[Ecount].v2 = w->Adjv;
                ESet[Ecount++].weight = w->weight;
            }
        }
    }
    for (Ecount = Graph->Nv / 2; Ecount >= 0;Ecount--){
        PercDown(ESet, Ecount, Graph->Ne);
    }
}
void Swap(Edge* a,Edge* b){
    Edge temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int GetEdge(Edge* ESet,int CurrentSize){
    Swap(&ESet[0], &ESet[CurrentSize - 1]);
    PercDown(ESet, 0, CurrentSize - 1);
    return CurrentSize - 1;
}
LGraph* Kruskal(LGraph*Graph,LGraph* MST){
    int Ecount=0, NextEdge=0;
    SetType VSet;
    Edge *ESet;
    InitializeVSET(VSet, Graph->Nv);
    ESet = (Edge *)malloc(sizeof(Edge) * (Graph->Ne));
    InitializeESET(Graph, ESet);
    MST = CreateLGraph(Graph->Nv);
    NextEdge = Graph->Ne;
    while(Ecount<Graph->Nv-1){
        NextEdge = GetEdge(ESet, NextEdge);
        if(NextEdge<0)
            break;
        if (CheckCycle(VSet, ESet[NextEdge].v1, ESet[NextEdge].v2)==1){
            InsertLEdge(MST, ESet + NextEdge);
            Totalweight += ESet[NextEdge].weight;
            Ecount++;
        }
    }
    if(Ecount<Graph->Nv-1)
        Totalweight = -1;
    return MST;
}
int main(){
    LGraph *Graph=NULL, *MST=NULL;
    Graph = BuildLGraph();
    MST=Kruskal(Graph,MST);
    printf("\nTotalweight= %d \n", Totalweight);
    PrintLGraph(MST);
}