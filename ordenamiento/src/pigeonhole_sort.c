#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils.h"

// Función para realizar el Pigeonhole Sort optimizado
void pigeonhole_sort(int arr[], long n) {
    if (n == 0) return; // Si el arreglo está vacío, no hacer nada

    // Encontrar el valor mínimo y máximo en el arreglo
    int min = arr[0], max = arr[0];
    for (long i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    long range = max - min + 1;


    // Si el rango es mayor a un millón, se dividirá el problema
    if (range > 1000) {
        long bucket_size = range / 1000;  // Dividir el rango en 1000 buckets
        long i, j;
        for (i = 0; i < range; i += bucket_size) {
            long start = i + min;
            long end = (i + bucket_size - 1 + min < max) ? i + bucket_size - 1 + min : max;
            long bucket_count = end - start + 1;

            // Crear un arreglo de agujeros basado en el tamaño del bucket
            int *holes = (int *)calloc(bucket_count, sizeof(int));
            if (!holes) {
                perror("Error al asignar memoria para los agujeros");
                exit(EXIT_FAILURE);
            }

            // Contar las ocurrencias de cada número en el bucket
            for (long k = 0; k < n; k++) {
                if (arr[k] >= start && arr[k] <= end) {
                    holes[arr[k] - start]++;
                }
            }

            // Reescribir el arreglo ordenado para el bucket actual
            long index = 0;
            for (long b = 0; b < bucket_count; b++) {
                while (holes[b] > 0) {
                    arr[index++] = b + start;
                    holes[b]--;
                }
            }

            // Liberar la memoria de los agujeros
            free(holes);
        }
    } else {
        // Crear los agujeros (buckets) con el rango calculado
        int *holes = (int *)calloc(range, sizeof(int));
        if (!holes) {
            perror("Error al asignar memoria para los agujeros");
            exit(EXIT_FAILURE);
        }

        // Contar las ocurrencias de cada número en el arreglo
        for (long i = 0; i < n; i++) {
            holes[arr[i] - min]++;
        }

        // Reescribir el arreglo ordenado
        long index = 0;
        for (long i = 0; i < range; i++) {
            while (holes[i] > 0) {
                arr[index++] = i + min;
                holes[i]--;
            }
        }

        // Liberar la memoria de los agujeros
        free(holes);
    }
}

// Función para mostrar el tiempo
void mostrar_tiempo(clock_t inicio, clock_t fin) {
    double tiempo_segundos = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (tiempo_segundos < 1.0) {
        printf("Pigeonhole Sort: %.3f milisegundos\n", tiempo_segundos * 1000.0);
    } else if (tiempo_segundos < 60.0) {
        printf("Pigeonhole Sort: %.3f segundos\n", tiempo_segundos);
    } else {
        printf("Pigeonhole Sort: %.3f minutos\n", tiempo_segundos / 60.0);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return EXIT_FAILURE;
    }

    long size_original;
    int *arr = leer_csv(argv[1], &size_original);
    if (arr == NULL) {
        fprintf(stderr, "Error al leer el archivo CSV\n");
        return EXIT_FAILURE;
    }

    long n = size_original;

    // Medir el tiempo de ejecución
    clock_t inicio = clock();
    pigeonhole_sort(arr, n);
    clock_t fin = clock();

    // Mostrar el tiempo formateado
    mostrar_tiempo(inicio, fin);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "pigeonhole_sort");

    // Agregar la carpeta "results/pigeonhole_sort" al nombre del archivo de salida
    char output_path[512];
    snprintf(output_path, sizeof(output_path), "../results/pigeonhole_sort/%s", output_filename);


    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_path, arr, n);
    printf("Archivo ordenado guardado en: %s\n", output_path);

    free(arr);
    return EXIT_SUCCESS;
}
