// quick_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   // Incluir para mkdir
#include <sys/types.h>  // Incluir para mkdir
#include "utils.h"

// Función para intercambiar dos elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función de partición para QuickSort
long partition(int a[], long low, long high) {
    int pivot = a[high];
    long i = low - 1;
    for (long j = low; j <= high - 1; j++) {
        if (a[j] < pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return (i + 1);
}

// Implementación recursiva de QuickSort
void quick_sort_recursive(int a[], long low, long high) {
    if (low < high) {
        long pi = partition(a, low, high);
        quick_sort_recursive(a, low, pi - 1);
        quick_sort_recursive(a, pi + 1, high);
    }
}

// Función para formatear y mostrar el tiempo
void mostrar_tiempo(clock_t inicio, clock_t fin) {
    double tiempo_segundos = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (tiempo_segundos < 1.0) {
        // Convertir a milisegundos
        double tiempo_milisegundos = tiempo_segundos * 1000.0;
        printf("QuickSort: %.3f milisegundos\n", tiempo_milisegundos);
    }
    else if (tiempo_segundos < 60.0) {
        // Mostrar en segundos
        printf("QuickSort: %.3f segundos\n", tiempo_segundos);
    }
    else {
        // Convertir a minutos
        double tiempo_minutos = tiempo_segundos / 60.0;
        printf("QuickSort: %.3f minutos\n", tiempo_minutos);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return EXIT_FAILURE;
    }

    long size_original;
    int *arr = leer_csv(argv[1], &size_original);

    // No es necesario ajustar el tamaño a una potencia de dos para QuickSort
    long n = size_original;

    // Medir el tiempo de ejecución
    clock_t inicio = clock();
    quick_sort_recursive(arr, 0, n - 1);
    clock_t fin = clock();

    // Mostrar el tiempo formateado
    mostrar_tiempo(inicio, fin);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "quick_sort");

    // Agregar la carpeta "results/quick_sort" al nombre del archivo de salida
    char output_path[512];
    snprintf(output_path, sizeof(output_path), "../results/quick_sort/%s", output_filename);

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_path, arr, n);
    printf("Archivo ordenado guardado en: %s\n", output_path);

    free(arr);
    return EXIT_SUCCESS;
}
