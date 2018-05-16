#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void prefix_table(char pattern[],int prefix[],int n){
    prefix[0] = 0;
    int len = 0;
    int i = 1;
    while(i<n){
        if(pattern[i]==pattern[len]){
            len++;
            prefix[i] = len;
            i++;
        }else{
            if(len>0)
            len = prefix[len - 1];
            else
            {
                prefix[i] = len;    //len==0;
                i++;
            }   
        }
    }
}
void move_prefix(int prefix[],int n){
    int i;
    for (i = n - 1; i > 0;i--){
        prefix[i] = prefix[i - 1];
    }
    prefix[0] = -1;
}
void KMP(char text[],char pattern[]){
    int n = strlen(pattern);
    int m = strlen(text);
    int *prefix = malloc(sizeof(int) * n);
    int i=0, j=0;
    prefix_table(pattern, prefix, n);
    move_prefix(prefix, n);
    while(i<m){
        if(j==n-1&&text[i]==pattern[j]){
            printf("First appear at %d\n", i - j);
            j = prefix[j];
        }
        if(text[i]==pattern[j]){
            i++;
            j++;
        }else{
            j = prefix[j];
            if(j==-1){
                i++;
                j++;
            }
        }
    }
}
int main(){
    char pattern[] = "abaa";
    char text[] = "abaabaabaa";
    KMP(text, pattern);
}
