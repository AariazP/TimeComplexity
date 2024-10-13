#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   // Incluir para mkdir
#include <sys/types.h>  // Incluir para mkdir
#include "utils.h"

// Función para realizar la busqueda por saltos
int busqueda_saltos(int arr[], int n, int x) {
    // Encontrar el bloque a saltar
    int salto = sqrt(n);
    int anterior = 0;

    // Saltar bloques hasta encontrar un bloque donde el valor podría estar
    int index = fmin(salto, n);
    while ( index - 1 < x) {
        anterior = salto;
        salto += sqrt(n);
        if (anterior >= n) {
            return -1; // Si se sale del arreglo, no se encontró el elemento
        }
    }

    // Realizar una búsqueda lineal dentro del bloque
    while (arr[anterior] < x) {
        anterior++;
        if (anterior == fmin(salto, n)) {
            return -1; // Si se llega al final del bloque sin encontrar el elemento
        }
    }

    // Si el elemento es encontrado
    if (arr[anterior] == x) {
        return anterior;
    }

    return -1; // Si no se encuentra el elemento
}


// Función para formatear y mostrar el tiempo
void mostrar_tiempo(clock_t inicio, clock_t fin) {
    double tiempo_segundos = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (tiempo_segundos < 1.0) {
        // Convertir a milisegundos
        double tiempo_milisegundos = tiempo_segundos * 1000.0;
        printf("Jump Search: %.3f milisegundos\n", tiempo_milisegundos);
    }
    else if (tiempo_segundos < 60.0) {
        // Mostrar en segundos
        printf("Jump Search: %.3f segundos\n", tiempo_segundos);
    }
    else {
        // Convertir a minutos
        double tiempo_minutos = tiempo_segundos / 60.0;
        printf("Jump Search: %.3f minutos\n", tiempo_minutos);
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
    busqueda_saltos(arr, n-1, arr[n-1]);
    clock_t fin = clock();

    // Mostrar el tiempo formateado
    mostrar_tiempo(inicio, fin);

}
