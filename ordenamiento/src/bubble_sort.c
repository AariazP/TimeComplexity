// bubble_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   // Incluir para mkdir
#include <sys/types.h>  // Incluir para mkdir
#include "utils.h"

// Implementación del algoritmo de ordenamiento por burbuja
void bubble_sort(int a[], long n) {
    int swapped;
    for (long i = 0; i < n-1; i++) {
        swapped = 0;
        for (long j = 0; j < n-i-1; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                swapped = 1;
            }
        }
        // Si no hubo intercambio en la pasada, el arreglo está ordenado
        if (!swapped)
            break;
    }
}

// Función para formatear y mostrar el tiempo
void mostrar_tiempo(clock_t inicio, clock_t fin) {
    double tiempo_segundos = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (tiempo_segundos < 1.0) {
        // Convertir a milisegundos
        double tiempo_milisegundos = tiempo_segundos * 1000.0;
        printf("Bubble Sort: %.3f milisegundos\n", tiempo_milisegundos);
    }
    else if (tiempo_segundos < 60.0) {
        // Mostrar en segundos
        printf("Bubble Sort: %.3f segundos\n", tiempo_segundos);
    }
    else {
        // Convertir a minutos
        double tiempo_minutos = tiempo_segundos / 60.0;
        printf("Bubble Sort: %.3f minutos\n", tiempo_minutos);
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
    bubble_sort(arr, n);
    clock_t fin = clock();

    // Mostrar el tiempo formateado
    mostrar_tiempo(inicio, fin);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "bubble_sort");

    // Agregar la carpeta "results/bubble_sort" al nombre del archivo de salida
    char output_path[512];
    snprintf(output_path, sizeof(output_path), "../results/bubble_sort/%s", output_filename);


    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_path, arr, n);
    printf("Archivo ordenado guardado en: %s\n", output_path);

    free(arr);
    return EXIT_SUCCESS;
}
