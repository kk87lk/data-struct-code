#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void Swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void PercDown(int A[],int p,int N){
    int Parent, Child;
    int x;
    x=A[p];
    for (Parent = p; (Parent * 2 + 1) < N;Parent=Child){
        Child = Parent * 2 + 1;
        if((Child!=N-1)&&(A[Child]<A[Child+1]))
            Child++;
        if (x >= A[Child])
            break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = x;
}
void HeapSort(int A[],int N){
    int i;
    for (i = N / 2 - 1; i >= 0;i--){
        PercDown(A, i, N);
    }
    for (i = N - 1; i > 0;i--){
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);
    }
}
int main(){
    int A[10];
    srand(time(NULL));
    int i = 0;
    for (i = 0; i < 10;i++){
        A[i] = rand() % 100 + 1;
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d ", A[i]);
    }
    HeapSort(A, 10);
    printf("\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", A[i]);
    }
}