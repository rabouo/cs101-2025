#include <stdio.h>
int main()
{
    int i = 20;
    if(i <= 30){
        printf("免費");
    }else if(i >= 240){
        printf("240元");
    }else{
        int n;
        if(i%30 == 0){
            n = i;
        }else{
            n = 30*(i/30)+30;
        }
        printf("%d元",n);
    }
}
