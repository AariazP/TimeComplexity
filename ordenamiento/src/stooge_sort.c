// stooge_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Implementación de Stooge Sort
void stooge_sort(int arr[], long l, long h) {
    if (arr[l] > arr[h]) {
        // Intercambiar
        int temp = arr[l];
        arr[l] = arr[h];
        arr[h] = temp;
    }
    if (h - l + 1 > 2) {
        long t = (h - l + 1) / 3;
        stooge_sort(arr, l, h - t);
        stooge_sort(arr, l + t, h);
        stooge_sort(arr, l, h - t);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return EXIT_FAILURE;
    }

    long size;
    int *arr = leer_csv(argv[1], &size);

    // Recomendar al usuario si el tamaño es muy grande
    if (size > 100000) {
        printf("Advertencia: Stooge Sort es extremadamente ineficiente para tamaños de datos grandes. Se recomienda usar tamaños <= 100,000.\n");
        return EXIT_FAILURE;
    }

    clock_t inicio = clock();
    stooge_sort(arr, 0, size - 1);
    clock_t fin = clock();

    double tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Stooge Sort: %.6f segundos\n", tiempo);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "stooge_sort");

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_filename, arr, size);
    printf("Archivo ordenado guardado en: %s\n", output_filename);

    free(arr);
    return EXIT_SUCCESS;
}

