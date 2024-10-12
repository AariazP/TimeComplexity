// merge_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   // Incluir para mkdir
#include <sys/types.h>  // Incluir para mkdir
#include "utils.h"

// Función para fusionar dos subarreglos
void merge(int a[], long left, long mid, long right) {
    long i, j, k;
    long n1 = mid - left + 1;
    long n2 = right - mid;

    // Crear arreglos temporales
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    // Copiar datos a los arreglos temporales
    for (i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    // Fusionar los arreglos temporales de vuelta en el arreglo original
    i = 0; // Índice inicial del primer subarreglo
    j = 0; // Índice inicial del segundo subarreglo
    k = left; // Índice inicial del subarreglo fusionado
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[] si hay alguno
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[] si hay alguno
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }

    // Liberar la memoria de los arreglos temporales
    free(L);
    free(R);
}

// Función recursiva para implementar Merge Sort
void merge_sort_recursive(int a[], long left, long right) {
    if (left < right) {
        long mid = left + (right - left) / 2;

        // Ordenar la primera y la segunda mitad
        merge_sort_recursive(a, left, mid);
        merge_sort_recursive(a, mid + 1, right);

        // Fusionar las mitades ordenadas
        merge(a, left, mid, right);
    }
}

// Función para formatear y mostrar el tiempo
void mostrar_tiempo(clock_t inicio, clock_t fin) {
    double tiempo_segundos = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (tiempo_segundos < 1.0) {
        // Convertir a milisegundos
        double tiempo_milisegundos = tiempo_segundos * 1000.0;
        printf("Merge Sort: %.3f milisegundos\n", tiempo_milisegundos);
    }
    else if (tiempo_segundos < 60.0) {
        // Mostrar en segundos
        printf("Merge Sort: %.3f segundos\n", tiempo_segundos);
    }
    else {
        // Convertir a minutos
        double tiempo_minutos = tiempo_segundos / 60.0;
        printf("Merge Sort: %.3f minutos\n", tiempo_minutos);
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
    merge_sort_recursive(arr, 0, n - 1);
    clock_t fin = clock();

    // Mostrar el tiempo formateado
    mostrar_tiempo(inicio, fin);

    // Generar nombre del archivo de salida
    char output_filename[256];
    generar_nombre_salida(argv[1], output_filename, "merge_sort");

    // Agregar la carpeta "results/merge_sort" al nombre del archivo de salida
    char output_path[512];
    snprintf(output_path, sizeof(output_path), "../results/merge_sort/%s", output_filename);

    // Escribir el arreglo ordenado en el archivo CSV
    escribir_csv(output_path, arr, n);
    printf("Archivo ordenado guardado en: %s\n", output_path);

    free(arr);
    return EXIT_SUCCESS;
}
