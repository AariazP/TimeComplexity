// pigeonhole_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Implementación de Pigeonhole Sort
void pigeonhole_sort(int arr[], long n) {
    int min = arr[0];
    int max = arr[0];
    for (long i = 1; i < n; i++) {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }

    long range = max - min + 1;
    int *holes = (int*) calloc(range, sizeof(int));
    if (!holes) {
        printf("Error de memoria en Pigeonhole Sort\n");
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < n; i++)
        holes[arr[i] - min]++;

    long index = 0;
    for (long i = 0; i < range; i++) {
        while (holes[i]-- > 0)
            arr[index++] = i + min;
    }

    free(holes);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return EXIT_FAILURE;
    }

    long size;
    int *arr = leer_csv(argv[1], &size);

    clock_t inicio = clock();
    pigeonhole_sort(arr, size);
    clock_t fin = clock();

    double tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Pigeonhole Sort: %.6f segundos\n", tiempo);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "pigeonhole_sort");

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_filename, arr, size);
    printf("Archivo ordenado guardado en: %s\n", output_filename);

    free(arr);
    return EXIT_SUCCESS;
}

