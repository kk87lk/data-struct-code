#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void InsertSort(int PreviousArray[],int n){
    int temp = 0, i = 0,j=0;
    for (i = 1; i < n;i++){
        temp = PreviousArray[i];
        for (j=i; PreviousArray[j - 1] > temp && j > 0;j--){
            PreviousArray[j] = PreviousArray[j - 1];
        }
        PreviousArray[j] = temp;
    }
}
void ShellSort(int PreviousArray[],int n){
    int D = 0, i = 0, j = 0;
    int temp = 0;
    for (D = n; D > 0;D/=2){
        for (i = D; i < n;i++){
            temp = PreviousArray[i];
            for (j = i; PreviousArray[j - D] > temp && j >= D;j-=D){
                PreviousArray[j] = PreviousArray[j - D];
            }
            PreviousArray[j] = temp;
        }
    }
}
void SedgewickShellSort(int PreviousArray[],int n){
    int Si = 0, i = 0, j = 0, temp = 0, D = 0;
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    for (Si = 0; Sedgewick[Si] >= n;Si++);
    for (D = Sedgewick[Si]; D > 0;D=Sedgewick[++Si]){
        for (i = D; i < n;i++){
            temp = PreviousArray[i];
            for (j = i; PreviousArray[j - D] > temp && j >= D;j-=D){
                PreviousArray[j] = PreviousArray[j - D];
            }
            PreviousArray[j] = temp;
        }
    }
}
int main(){
    srand(time(NULL));
    int a[10];
    int b[10];
    int c[10];
    int i = 0;
    for (i = 0; i < 10;i++){
        a[i] = rand() % 100 + 1;
    }
    for (i = 0; i < 10; i++)
    {
        b[i] = rand() % 100 + 1;
    }
    for (i = 0; i < 10; i++)
    {
        c[i] = rand() % 100 + 1;
    }
    printf("Insert sort:\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    InsertSort(a, 10);
    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("Shell sort:\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");
    ShellSort(b, 10);
    for (i = 0; i < 10; i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");
    printf("Sedgewick Shell sort:\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", c[i]);
    }
    printf("\n");
    SedgewickShellSort(c, 10);
    for (i = 0; i < 10; i++)
    {
        printf("%d ", c[i]);
    }
}