#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int cutoff = 20;
typedef int ElementType;
int compare(const void*a,const void*b){
    return (*(int *)a - *(int *)b);
}
void swap(int *a,int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
void InsertionSort(ElementType A[], int N)
{ /* 插入排序 */
    int P, i;
    ElementType Tmp;

    for (P = 1; P < N; P++)
    {
        Tmp = A[P]; /* 取出未排序序列中的第一个元素*/
        for (i = P; i > 0 && A[i - 1] > Tmp; i--)
            A[i] = A[i - 1]; /*依次与已排序序列中元素比较并右移*/
        A[i] = Tmp;          /* 放进合适的位置 */
    }
}
int Medium3(int A[],int left,int right){
    int center = (left + right) / 2;
    if(A[left]>A[center])
        swap(&A[left], &A[center]);
    if(A[left]>A[right])
        swap(&A[left], &A[right]);
    if(A[center]>A[right])
        swap(&A[center], &A[right]);
    swap(&A[center], &A[right-1]);
    return A[right - 1];
}
void Qsort(int A[],int left,int right){
    int pivot, low, high;
    if(cutoff<=right-left){
    pivot = Medium3(A, left, right);
    low = left;
    high = right - 1;
    while (1)
    {
        while(A[++low]<pivot);
        while(A[--high]>pivot);
        if(low<high)
            swap(&A[low], &A[high]);
        else
            break;
    }
    swap(&A[low], &A[right - 1]);
    Qsort(A, left, low - 1);
    Qsort(A, low + 1, right);
    }else
    {
        InsertionSort(A + left, right - left);
    }
}
void QuickSort(int A[],int N){
    Qsort(A, 0, N - 1);
}
int main(){
    srand((unsigned)time(NULL));
    int a[20],b[20];
    int i = 0;
    for (i = 0; i < 20;i++){
        a[i] = rand() % 100;
    }
    printf("Previous arrary:\n");
    for (i = 0; i < 20;i++){
        printf("%d  ", a[i]);
    }
    qsort(a, 20, sizeof(int), compare);
    printf("\nCurrent arrary:\n");
    for (i = 0; i < 20; i++)
    {
        printf("%d  ", a[i]);
    }
    for (i = 0; i < 5; i++)
    {
        b[i] = rand() % 100;
    }
    printf("\nPrevious arrary:\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d  ", b[i]);
    }
    QuickSort(b, 5);
    printf("\nCrevious arrary:\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d  ", b[i]);
    }
    return 0;
}
