#include <stdio.h>
int main()
{
    int x = -9;
    int y = 9;
    int z = 1;
    int sum;
    if(x<0){
        sum = 100*x*-1+y*10+z;  
        sum *= -1;
    }else{
        sum = 100*x+10*y+z;
    }
    printf("%d",sum);
    return 0;
}
