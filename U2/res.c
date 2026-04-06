#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

// Variables para contar iteraciones y controlar la ejecución [cite: 21]
long cont_est = 0, cont_nav = 0, cont_tel = 0;
int activo = 1;

// 1. Tarea de Control de Estabilidad (Crítica - Prioridad 80) [cite: 5, 14]
void* task_estabilidad(void* a) {
    while(activo) cont_est++; 
    return NULL;
}

// 2. Tarea de Navegación (Media - Prioridad 40) [cite: 6, 15]
void* task_navegacion(void* a) {
    while(activo) cont_nav++;
    return NULL;
}

// 3. Tarea de Telemetría (Baja - Prioridad 10) [cite: 7, 16, 19]
void* task_telemetria(void* a) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    int s;
    while(activo) {
        sigwait(&set, &s); // Espera al Timer POSIX cada 500ms 
        cont_tel++;
        printf("[Telemetría] Enviando log...\n");
    }
    return NULL;
}

// Función para configurar la política FIFO y la prioridad 
void set_prio(pthread_attr_t *at, int p) {
    struct sched_param sp;
    sp.sched_priority = p;
    pthread_attr_init(at);
    pthread_attr_setschedpolicy(at, SCHED_FIFO); 
    pthread_attr_setschedparam(at, &sp);
    pthread_attr_setinheritsched(at, PTHREAD_EXPLICIT_SCHED);
}

int main() {
    // Bloqueamos SIGALRM en el main para que lo maneje el hilo de Telemetría 
    sigset_t set; sigemptyset(&set); sigaddset(&set, SIGALRM);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    pthread_t h1, h2, h3;
    pthread_attr_t a1, a2, a3;

    // Configuramos las prioridades solicitadas [cite: 14, 15, 16]
    set_prio(&a1, 80); 
    set_prio(&a2, 40);
    set_prio(&a3, 10);

    // Creamos el Timer POSIX para que dispare cada 500ms 
    timer_t tid;
    struct sigevent sev = { .sigev_notify = SIGEV_SIGNAL, .sigev_signo = SIGALRM };
    timer_create(CLOCK_REALTIME, &sev, &tid);
    struct itimerspec ts = { {0, 500000000}, {0, 500000000} }; // {intervalo, valor_inicial}
    timer_settime(tid, 0, &ts, NULL);

    // Lanzamos los hilos [cite: 10]
    pthread_create(&h1, &a1, task_estabilidad, NULL);
    pthread_create(&h2, &a2, task_navegacion, NULL);
    pthread_create(&h3, &a3, task_telemetria, NULL);

    printf("Simulando sistema de vuelo por 10 segundos...\n");
    sleep(10); // Duración del ensayo [cite: 21]
    activo = 0;

    // Imprimimos la tabla de resultados [cite: 22]
    printf("\n--- TABLA COMPARATIVA DE MÉTRICAS ---\n");
    printf("| Tarea          | Prioridad | Iteraciones |\n");
    printf("|----------------|-----------|-------------|\n");
    printf("| Estabilidad    | 80 (Alta) | %ld |\n", cont_est);
    printf("| Navegación     | 40 (Med)  | %ld |\n", cont_nav);
    printf("| Telemetría     | 10 (Baja) | %ld |\n", cont_tel);

    return 0;
}