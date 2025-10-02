#include <stdio.h>
void print_sp(int i,int n){
    for(int p = 0;p < n-i;p++){
        printf(" ");
    }
}
void print_num(int n){
    for(int i = 0;i < n;i++){
        printf("%d ",n);
    }
    printf("\n");
}
int main()
{
    int rows=6;
    for(int i = 1;i <= rows;i++){
        print_sp(i,rows);
        print_num(i);
    }
    return 0;
}
