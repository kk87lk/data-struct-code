#include <stdio.h>
#include <stdlib.h>
typedef int Elemtype, Weight, Vertex;
#define Max 20
int visited[Max] = {0};
typedef struct node Node;
struct node{
    Vertex Adjv;
    Weight weight;
    Node *next;
};
typedef struct{
    Node* FirstEdge;
    Elemtype data;
} Adjlist[Max];
typedef struct{
    int Nv;
    int Ne;
    Adjlist G;
} LGraph;
typedef struct
{
    Vertex v1, v2;
    Weight weight;
} Edge;
LGraph* CreateGraph(int Vertexnum){
    Vertex v;
    LGraph* G;
    G = (LGraph *)malloc(sizeof(LGraph));
    G->Nv = Vertexnum;
    G->Ne = 0;
    for (v = 0; v < G->Nv;v++){
        G->G[v].FirstEdge = NULL;
    }
    return G;
}
void InsertEdge(LGraph*G,Edge* E){
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
LGraph* BuildGraph(){
    LGraph *G;
    Edge *E;
    Vertex v,i;
    int Nv;
    printf("please input the V num:");
    scanf("%d", &Nv);
    G = (LGraph *)malloc(sizeof(LGraph));
    G = CreateGraph(Nv);
    printf("please input the Edge num:");
    scanf("%d" ,&(G->Ne));
    if(G->Ne!=0){
        E = (Edge *)malloc(sizeof(Edge));
        for (i = 0; i < G->Ne;i++){
            printf("please input v1 v2 and weight:");
            scanf("%d%d%d", &(E->v1), &(E->v2), &(E->weight));
            InsertEdge(G, E);
        }
    }
    // for (v = 0; v < G->Nv;v++){
    //     printf("input the %d's data:",v);
    //     scanf("%d", &(G->G[v].data));
    // }
         return G;
}
void visit(Vertex V)
{
    printf("%d ", V);
}
void DFS(LGraph* G,Vertex V,void (*visit)(Vertex)){
    Node *W;
    visit(V);
    visited[V] = 1;
    for (W = G->G[V].FirstEdge; W;W=W->next){
        if(!visited[W->Adjv])
            DFS(G, W->Adjv, visit);
    }
}
void PrintLGraph(LGraph* G){
    Vertex i = 0;
    Node *W;
    for (i = 0; i < G->Nv; i++)
    {
        for (W = G->G[i].FirstEdge; W; W = W->next)
        {
            printf("<%d,%d> ", i, W->Adjv);
        }
        printf("\n");
    }
}
int main(){
    LGraph *G;
    G = BuildGraph();
   // DFS(G, 1, visit);
    PrintLGraph(G);
}