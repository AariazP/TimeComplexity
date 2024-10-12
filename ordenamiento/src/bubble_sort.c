// bubble_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Implementación de Bubble Sort
void bubble_sort(int arr[], long n) {
    long i, j;
    int swapped;
    for (i = 0; i < n-1; i++) {
        swapped = 0;
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Intercambiar
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
            }
        }
        // Si no se realizaron intercambios, el arreglo está ordenado
        if (!swapped)
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return EXIT_FAILURE;
    }

    long size;
    int *arr = leer_csv(argv[1], &size);

    clock_t inicio = clock();
    bubble_sort(arr, size);
    clock_t fin = clock();

    double tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Bubble Sort: %.6f segundos\n", tiempo);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "bubble_sort");

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_filename, arr, size);
    printf("Archivo ordenado guardado en: %s\n", output_filename);

    free(arr);
    return EXIT_SUCCESS;
}
