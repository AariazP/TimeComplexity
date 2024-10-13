// merge_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   // Incluir para mkdir
#include <sys/types.h>  // Incluir para mkdir
#include "utils.h"

// Función para realizar la búsqueda lineal limitada
int busqueda_lineal_limitada(int arr[], int n, int x, int limite) {
    for (int i = 0; i < n && i < limite; i++) {
        if (arr[i] == x) {
            return i;  // Retorna la posición donde se encuentra el elemento
        }
    }
    return -1;  // Retorna -1 si el elemento no se encuentra dentro del límite
}


// Función para formatear y mostrar el tiempo
void mostrar_tiempo(clock_t inicio, clock_t fin) {
    double tiempo_segundos = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (tiempo_segundos < 1.0) {
        // Convertir a milisegundos
        double tiempo_milisegundos = tiempo_segundos * 1000.0;
        printf("Limited Linear Search: %.3f milisegundos\n", tiempo_milisegundos);
    }
    else if (tiempo_segundos < 60.0) {
        // Mostrar en segundos
        printf("Limited Linear Search: %.3f segundos\n", tiempo_segundos);
    }
    else {
        // Convertir a minutos
        double tiempo_minutos = tiempo_segundos / 60.0;
        printf("Limited Linear Search: %.3f minutos\n", tiempo_minutos);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return EXIT_FAILURE;
    }

    long size_original;
    int *arr = leer_csv(argv[1], &size_original);

    long n = size_original;

    // Medir el tiempo de ejecución
    clock_t inicio = clock();
    busqueda_lineal_limitada(arr, n, arr[n-1], 10);
    clock_t fin = clock();

    // Mostrar el tiempo formateado
    mostrar_tiempo(inicio, fin);

}
