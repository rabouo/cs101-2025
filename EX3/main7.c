#include <stdio.h>
int main()
{
    int i = 1000;
    if(i <= 1500){
        printf("70元");
    }else{
        int n = i-1500;
        int money;
        if(n % 100){
            money = (n/100+1)*10+70;
        }else{
            money = (n/100)*10+70;
        }
        printf("%d元",money);
    }
}
