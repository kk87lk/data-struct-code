#include <stdio.h>
#include <stdlib.h>
typedef int Elemtype;
#define Maxdata 1000
typedef struct HeapNode{
    Elemtype *data;
    int size;
    int capacity;
}Heap;

Heap* CreateHeap(int Maxsize){
    Heap *H = (Heap *)malloc(sizeof(Heap));
    H->size = 0;
    H->data = (Elemtype *)malloc(sizeof(Elemtype) * (Maxsize + 1));
    H->capacity = Maxsize;
    H->data[0] = Maxdata;
    return H;
}
int isfull(Heap*H){
    return (H->capacity == H->size);
}
int isempty(Heap*H){
    return (H->size == 0);
}

int Insert(Heap* H,Elemtype x){                 //MaxHeap
    int i;
    if(isfull(H)){
        printf("The Heap is Full!\n");
        return 0;
    }
    i = ++H->size;
    for (; H->data[i / 2] < x;i/=2){
        H->data[i] = H->data[i / 2];
    }
    H->data[i] = x;
    return 1;
}

Elemtype Delete(Heap*H){
    int parent, child;
    Elemtype Max, x;
    Max = H->data[1];
    x = H->data[H->size--];
    for (parent = 1; parent * 2 <= H->size;parent=child){
        child = parent * 2;
        if((child!=H->size)&&(H->data[child]<H->data[child+1])){
            child++;
        }
        if(x >= H->data[child]) break;
        else    H->data[parent]=H->data[child];
    }
    H->data[parent] = x;
    return Max;
}
void Perdown(Heap* H,int p){
    int parent, child;
    Elemtype x;
    x = H->data[p];
    for (parent = p; parent * 2 <= H->size;parent=child){
        child = parent * 2;
        if((child!=H->size)&&(H->data[child]<H->data[child+1])){
            child++;
        }
        if(x >= H->data[child]) break;
        else    H->data[parent]=H->data[child];
    }
    H->data[parent] = x;
}
void BuildHeap(Heap*H){
    int i;
    for (i = H->size/2; i >0 ; i--){
        Perdown(H, i);
    }
}
