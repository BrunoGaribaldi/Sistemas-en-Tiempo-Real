#include <stdio.h>

//Intercambiar 2 elementos.
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort
void bubbleSort(int *arr, int n, int modo) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (modo ? (arr[j] > arr[j + 1]) : (arr[j] < arr[j + 1])) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    int numero;
    printf("Ingrese un numero que quisiera ordenar: ");
    scanf("%d", &numero);

    int arr[10], counter = 0;

    // Convertir numero a arreglo
    while (numero != 0) {
        arr[counter++] = numero % 10; // Usamos mod para separar los caracteres.
        numero /= 10;
    }

    char orden;
    printf("Ingrese A para ordenar ascendente o D para descendente: ");
    scanf(" %c", &orden);

    int modo = (orden == 'A' || orden == 'a') ? 1 : 0;

    bubbleSort(arr, counter, modo);

    // Imprimir el número ordenado
    printf("Número ordenado: ");
    for (int i = 0; i < counter; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}