#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

// Función para leer un carácter sin esperar Enter en Linux
int getch_linux() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Desactiva el modo canónico y el eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura la configuración original
    return ch;
}


void bubbleSort(int *arr, int n) {
    
    bool swapped;
  
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
      
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}


int main(){

    printf("Ingrese un numero que quisiera ordenar");
    int numero = 0;
    scanf("%d",numero);



    int arr[10];
    int counter = 0;

    for( int i=0; numero!=0; i++ )
    {
        arr[i] = numero % 10;
        numero /= 10;
        counter ++;

        printf("%d ", arr[i]);
    }


    int c = getch_linux();
    printf("Ingrese A para ordenar ascendente o D para descendente");
    
    if(c == 'A' || c == 'a'){
        //ascendente bublesort
        bubbleSort(&arr, counter);
        
    }else{
        //descendente bublesort
    }

    for (int i = 0; i < counter - 1; i++) {
        printf("%d ", arr[i]); 
    }

    return 0;
}