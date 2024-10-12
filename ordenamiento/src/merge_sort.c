// merge_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Función para fusionar dos subarreglos
void merge(int arr[], long l, long m, long r) {
    long i, j, k;
    long n1 = m - l + 1;
    long n2 = r - m;

    // Crear arreglos temporales
    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Fusionar los arreglos temporales
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    // Copiar los elementos restantes
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

// Implementación de Merge Sort
void merge_sort_recursive(int arr[], long l, long r) {
    if (l < r) {
        long m = l + (r - l) / 2;
        merge_sort_recursive(arr, l, m);
        merge_sort_recursive(arr, m + 1, r);
        merge(arr, l, m, r);
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
    merge_sort_recursive(arr, 0, size - 1);
    clock_t fin = clock();

    double tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Merge Sort: %.6f segundos\n", tiempo);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "merge_sort");

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_filename, arr, size);
    printf("Archivo ordenado guardado en: %s\n", output_filename);

    free(arr);
    return EXIT_SUCCESS;
}
