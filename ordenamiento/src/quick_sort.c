// quick_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Función para intercambiar dos elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función de partición
long partition(int arr[], long low, long high) {
    int pivot = arr[high];
    long i = low - 1;
    for (long j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Implementación de Quick Sort
void quick_sort_recursive(int arr[], long low, long high) {
    if (low < high) {
        long pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
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
    quick_sort_recursive(arr, 0, size - 1);
    clock_t fin = clock();

    double tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Quick Sort: %.6f segundos\n", tiempo);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "quick_sort");

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_filename, arr, size);
    printf("Archivo ordenado guardado en: %s\n", output_filename);

    free(arr);
    return EXIT_SUCCESS;
}
