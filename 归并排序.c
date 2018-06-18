#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void Merge(int A[],int Temp[],int L,int R,int RightEnd){
    int LeftEnd, Num, Tmp;
    int i;
    LeftEnd = R - 1;
    Tmp = L;
    Num = RightEnd - L + 1;
    while (L<=LeftEnd&&R<=RightEnd){   
        if(A[L]<A[R])
            Temp[Tmp++] = A[L++];
        else
            Temp[Tmp++] = A[R++];
    }
    while (L<=LeftEnd){
        Temp[Tmp++] = A[L++];
    }
    while (R <= RightEnd){
        Temp[Tmp++] = A[R++];
    }
    for (i = 0; i < Num;i++,RightEnd--){
        A[RightEnd] = Temp[RightEnd];
    }
}
void Msort(int A[],int Temp[],int L,int RightEnd){
    int Center;
    if(L<RightEnd){
        Center = (L + RightEnd) / 2;
        Msort(A, Temp, L, Center);
        Msort(A, Temp, Center + 1, RightEnd);
        Merge(A, Temp, L, Center + 1, RightEnd);
    }
}
void MergeSort(int A[],int N){
    int *Temp;
    Temp = (int *)malloc(sizeof(int) * N);
    if(Temp){
        Msort(A, Temp, 0, N - 1);
        free(Temp);
    }else{
        printf("Over Flow!\n");
    }
}
void MergePass(int A[],int Temp[],int N,int Length){
    int i, j;
    for (i = 0; i <= N - 2 * Length;i+=2*Length){
        Merge(A, Temp, i, i + Length, i + 2 * Length - 1);
    }
    if(i+Length<N){
        Merge(A, Temp, i, i + Length, N - 1);
    }else{
        for (j = i; j < N;j++){
            Temp[j] = A[j];
        }
    }
}
void Merge_Sort(int A[],int N){
    int Length;
    int *Temp;
    Length = 1;
    Temp = (int *)malloc(sizeof(int) * N);
    if(Temp){
        while (Length<N){
            MergePass(A, Temp, N, Length);
            Length *= 2;
            MergePass(Temp, A, N, Length);
            Length *= 2;
        }
        free(Temp);
    }else{
        printf("Over flow!\n");
    }
}
int main(){
    int a[10];
    int b[10];
    int i;
    srand(time(NULL));
    for (i = 0; i < 10;i++){
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
    }
    printf("MergeSort:\n");
    for (i = 0; i < 10;i++){
        printf("%d ", a[i]);
    }
    MergeSort(a, 10);
    printf("\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("MergeSort2:\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", b[i]);
    }
    Merge_Sort(b, 10);
    printf("\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", b[i]);
    }
}