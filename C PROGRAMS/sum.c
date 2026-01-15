


#include<stdio.h>
int main()
{
    /*declaration of int variables*/
    int num1,num2,sum;
    printf("enter 2 numbers for sum:");
    scanf("%d,%d", &num1, &num2);
    
    /*sum of 2 numbers*/
    sum = num1+num2;
    printf("sum of %d and %d is %d", num1,num2,sum);
    return 0;
}