// stooge_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   // Incluir para mkdir
#include <sys/types.h>  // Incluir para mkdir
#include "utils.h"

// Función para implementar Stooge Sort
void stooge_sort(int arr[], long l, long h) {
    if (l >= h) return;

    // Si el primer elemento es mayor que el último, intercambiarlos
    if (arr[l] > arr[h]) {
        int temp = arr[l];
        arr[l] = arr[h];
        arr[h] = temp;
    }

    // Si hay más de 2 elementos
    if (h - l + 1 > 2) {
        // Si el primer elemento es mayor que el segundo, intercambiarlos
        if (arr[l] > arr[l + 1]) {
            int temp = arr[l];
            arr[l] = arr[l + 1];
            arr[l + 1] = temp;
        }
        // Si el penúltimo elemento es mayor que el último, intercambiarlos
        if (arr[h - 1] > arr[h]) {
            int temp = arr[h - 1];
            arr[h - 1] = arr[h];
            arr[h] = temp;
        }
        // Recursivamente ordenar las primeras dos tercios y las últimas dos tercios
        stooge_sort(arr, l, h - 1);
        stooge_sort(arr, l + 1, h);
        stooge_sort(arr, l, h - 1);
    }
}

// Función para formatear y mostrar el tiempo
void mostrar_tiempo(clock_t inicio, clock_t fin) {
    double tiempo_segundos = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (tiempo_segundos < 1.0) {
        // Convertir a milisegundos
        double tiempo_milisegundos = tiempo_segundos * 1000.0;
        printf("Stooge Sort: %.3f milisegundos\n", tiempo_milisegundos);
    }
    else if (tiempo_segundos < 60.0) {
        // Mostrar en segundos
        printf("Stooge Sort: %.3f segundos\n", tiempo_segundos);
    }
    else {
        // Convertir a minutos
        double tiempo_minutos = tiempo_segundos / 60.0;
        printf("Stooge Sort: %.3f minutos\n", tiempo_minutos);
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
    stooge_sort(arr, 0, n - 1);
    clock_t fin = clock();

    // Mostrar el tiempo formateado
    mostrar_tiempo(inicio, fin);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "stooge_sort");

    // Agregar la carpeta "results/stooge_sort" al nombre del archivo de salida
    char output_path[512];
    snprintf(output_path, sizeof(output_path), "../results/stooge_sort/%s", output_filename);

    // Verificar que el directorio "results/stooge_sort" exista
    if (access("../results/stooge_sort", F_OK) == -1) {
        // Crear directorios intermedios si es necesario
        if (mkdir("../results/stooge_sort", 0777) == -1) {
            perror("Error al crear el directorio results/stooge_sort");
            return EXIT_FAILURE;
        }
    }

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_path, arr, n);
    printf("Archivo ordenado guardado en: %s\n", output_path);

    free(arr);
    return EXIT_SUCCESS;
}
