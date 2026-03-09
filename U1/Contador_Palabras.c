#include <stdio.h>

#define IN  1  // Estado: dentro de una palabra
#define OUT 0  // Estado: fuera de una palabra

int main() {
    int c;             // Variable para almacenar el carácter actual
    int estado = OUT;  // Empezamos fuera de una palabra
    int palabras = 0;  // Contador de palabras

    printf("Escribe un texto (presiona Ctrl+D --> Fin de Archivo (EOF)):\n");

    // Leemos carácter por carácter hasta llegar al fin del archivo (EOF)
    while ((c = getchar()) != EOF) {
        
        // Si el carácter es un espacio, salto de línea o tabulación
        if (c == ' ' || c == '\n' || c == '\t') {
            estado = OUT;
        } 
        // Si no es un espacio y el estado era OUT, encontramos una palabra
        else if (estado == OUT) {
            estado = IN;
            palabras++;
        }
    }

    printf("\nNumero total de palabras: %d\n", palabras);

    return 0;
}