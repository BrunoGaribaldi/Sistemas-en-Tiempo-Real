#include <stdio.h>
#include <time.h>
#include <unistd.h> // Para sleep() en sistemas Unix/Linux


int main() {
    while (1) {
        time_t t; 
        struct tm *tm_info; 
        char buffer[9]; //reservamos caracter adicional para el terminador nulo.

        time(&t); //guarda segundos desde epoca.
        tm_info = localtime(&t); //devuelve puntero a una estructura tm que contiene informacion tiempo actual en base a la del sistema
        strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);
        
        printf("\r%s", buffer);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}