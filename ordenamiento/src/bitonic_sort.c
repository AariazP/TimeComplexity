// bitonic_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   // Incluir para mkdir
#include <sys/types.h>  // Incluir para mkdir
#include "utils.h"

// Función para intercambiar elementos si están en orden incorrecto
void compare_and_swap(int a[], long i, long j, int dir) {
    if (dir == (a[i] > a[j])) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

// Implementación de Bitonic Sort
void bitonic_merge(int a[], long low, long cnt, int dir) {
    if (cnt > 1) {
        long k = cnt / 2;
        for (long i = low; i < low + k; i++)
            compare_and_swap(a, i, i + k, dir);
        bitonic_merge(a, low, k, dir);
        bitonic_merge(a, low + k, k, dir);
    }
}

void bitonic_sort_recursive(int a[], long low, long cnt, int dir) {
    if (cnt > 1) {
        long k = cnt / 2;
        bitonic_sort_recursive(a, low, k, 1);   // Ascendente
        bitonic_sort_recursive(a, low + k, k, 0); // Descendente
        bitonic_merge(a, low, cnt, dir);
    }
}

// Función para formatear y mostrar el tiempo
void mostrar_tiempo(clock_t inicio, clock_t fin) {
    double tiempo_segundos = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (tiempo_segundos < 1.0) {
        // Convertir a milisegundos
        double tiempo_milisegundos = tiempo_segundos * 1000.0;
        printf("Bitonic Sort: %.3f milisegundos\n", tiempo_milisegundos);
    }
    else if (tiempo_segundos < 60.0) {
        // Mostrar en segundos
        printf("Bitonic Sort: %.3f segundos\n", tiempo_segundos);
    }
    else {
        // Convertir a minutos
        double tiempo_minutos = tiempo_segundos / 60.0;
        printf("Bitonic Sort: %.3f minutos\n", tiempo_minutos);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return EXIT_FAILURE;
    }

    long size_original;
    int *arr = leer_csv(argv[1], &size_original);

    // Asegurarse de que el tamaño sea potencia de dos
    long n = 1;
    while (n < size_original) n <<= 1;
    if (n != size_original) {
        // Rellenar con el valor máximo
        int max = arr[0];
        for (long i = 1; i < size_original; i++) {
            if (arr[i] > max)
                max = arr[i];
        }
        arr = (int*) realloc(arr, n * sizeof(int));
        if (!arr) {
            printf("Error de memoria al redimensionar el arreglo para Bitonic Sort\n");
            exit(EXIT_FAILURE);
        }
        for (long i = size_original; i < n; i++)
            arr[i] = max;
    }

    // Medir el tiempo de ejecución
    clock_t inicio = clock();
    bitonic_sort_recursive(arr, 0, n, 1); // 1 para ascendente
    clock_t fin = clock();

    // Mostrar el tiempo formateado
    mostrar_tiempo(inicio, fin);

    // Si el arreglo fue rellenado, ajusta el tamaño de nuevo
    long size = n;
    if (n != size_original) {
        size = size_original;
    }

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "bitonic_sort");

    // Agregar la carpeta "results" al nombre del archivo de salida
    char output_path[512];
    snprintf(output_path, sizeof(output_path), "../results/bitonic_sort/%s", output_filename);

    // Verificar que el directorio "results" exista
    if (access("results", F_OK) == -1) {
        if (mkdir("results", 0777) == -1) {
            perror("Error al crear el directorio results");
            return EXIT_FAILURE;
        }
    }

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_path, arr, size);
    printf("Archivo ordenado guardado en: %s\n", output_path);

    free(arr);
    return EXIT_SUCCESS;
}

