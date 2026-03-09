#include <stdio.h>

int main() {
    int a, b;
    float result = 0;
    char operator;
  
  	
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    printf("Select Operator + - / *");
    scanf(" %c", &operator);

    switch(operator){
        case '/': 
            if(b!=0){
                result = a / b;
                break;
            }else{
                result = 0;
                printf("B es cero");
            }
        case '*':
            result = a * b;
            break;
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
    }

    printf("Sum: %f", result);

    return 0;
}