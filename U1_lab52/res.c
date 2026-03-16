#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>

#define SERVO 24
#define BOTON 17

#define MIN_PULSE 500
#define MAX_PULSE 2500

#define PASO 30
#define DEBOUNCE 200000   // 200 ms en microsegundos

int angulo = 0;
uint32_t ultimo_evento = 0;

// Conversión grados → microsegundos
int angulo_a_pulso(int ang)
{
    return MIN_PULSE + (ang * (MAX_PULSE - MIN_PULSE) / 180);
}

// Interrupción del botón
void boton_callback(int gpio, int level, uint32_t tick)
{
    if(level == 0) // flanco de subida
    {
        if((tick - ultimo_evento) < DEBOUNCE)
            return;

        ultimo_evento = tick;

        angulo += PASO;

        if(angulo > 180)
            angulo = 0;

        int pulso = angulo_a_pulso(angulo);

        gpioServo(SERVO, pulso);

        printf("Posicion servo: %d grados (%d us)\n", angulo, pulso);
    }
}

int main()
{
    if(gpioInitialise() < 0)
    {
        printf("Error inicializando pigpio\n");
        return 1;
    }

    gpioSetMode(SERVO, PI_OUTPUT);

    gpioSetMode(BOTON, PI_INPUT);
    //gpioSetPullUpDown(BOTON, PI_PUD_DOWN);

    gpioServo(SERVO, angulo_a_pulso(0));

    gpioSetAlertFunc(BOTON, boton_callback);

    printf("Sistema listo. Presione el boton para mover el servo.\n");

    while(1)
    {
        sleep(1);
    }

    gpioTerminate();
    return 0;
}