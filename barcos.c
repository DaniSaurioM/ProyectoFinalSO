#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N_THREADS 2

// Coordenadas iniciales de los barcos
int boat1_x = 0, boat1_y = 0;
int boat2_x = 0, boat2_y = 10;

// Semáforo para controlar el acceso a la zona crítica
sem_t crossing_semaphore;

// Función para mover el barco 1
void* move_boat1(void* arg) {
    while (1) {
        // Mover el barco 1 en el eje x
        boat1_x++;

        // Verificar si el barco 1 está en la zona crítica
        if (boat1_x >= 5 && boat1_x <= 10 && boat1_y >= 5 && boat1_y <= 15) {
            // Esperar a que el semáforo esté disponible
            sem_wait(&crossing_semaphore);

            // Entrar a la zona crítica
            printf("Barco 1 entrando en la zona crítica.\n");

            // Salir de la zona crítica después de un tiempo simulado
            sleep(2);

            // Salir de la zona crítica
            printf("Barco 1 saliendo de la zona crítica.\n");

            // Liberar el semáforo
            sem_post(&crossing_semaphore);
        }

        // Simular el movimiento en el eje y
        boat1_y++;

        // Simular el tiempo de espera entre movimientos
        usleep(500000);
    }
}

// Función para mover el barco 2
void* move_boat2(void* arg) {
    while (1) {
        // Mover el barco 2 en el eje y
        boat2_y--;

        // Verificar si el barco 2 está en la zona crítica
        if (boat2_x >= 5 && boat2_x <= 10 && boat2_y >= 5 && boat2_y <= 15) {
            // Esperar a que el semáforo esté disponible
            sem_wait(&crossing_semaphore);

            // Entrar a la zona crítica
            printf("Barco 2 entrando en la zona crítica.\n");

            // Salir de la zona crítica después de un tiempo simulado
            sleep(2);

            // Salir de la zona crítica
            printf("Barco 2 saliendo de la zona crítica.\n");

            // Liberar el semáforo
            sem_post(&crossing_semaphore);
        }

        // Simular el movimiento en el eje x
        boat2_x++;

        // Simular el tiempo de espera entre movimientos
        usleep(500000);
    }
}

int main() {
    // Inicializar el semáforo
    sem_init(&crossing_semaphore, 0, 1);

    // Crear los hilos para los barcos
    pthread_t threads[N_THREADS];
    pthread_create(&threads[0], NULL, move_boat1, NULL);
    pthread_create(&threads[1], NULL, move_boat2, NULL);

    // Esperar a que los hilos terminen (esto no debería ocurrir en este ejemplo)
    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruir el semáforo
    sem_destroy(&crossing_semaphore);

    return 0;
}
