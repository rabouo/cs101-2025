#include <stdio.h>
int main()
{
    int i = 1;
    if(i & (i-1)){
        printf("false");
    }else if(i == 1){
        printf("false");
    }else{
        printf("true");
    }
}
