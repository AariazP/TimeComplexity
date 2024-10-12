// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para contar el número de números en el archivo CSV
long contar_numeros(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No se pudo abrir el archivo %s\n", filename);
        exit(EXIT_FAILURE);
    }
    long count = 0;
    int num;
    while (fscanf(file, "%d,", &num) == 1) {
        count++;
    }
    // Manejar el último número si no termina con una coma
    // Verificar si el último carácter es un número sin coma
    fseek(file, -1, SEEK_END);
    int last_char = fgetc(file);
    if (last_char != ',') {
        // Recontar si el último número no fue contado
        fseek(file, 0, SEEK_SET);
        count = 0;
        while (fscanf(file, "%d,", &num) == 1) {
            count++;
        }
        // Intentar leer el último número sin coma
        if (fscanf(file, "%d", &num) == 1) {
            count++;
        }
    }
    fclose(file);
    return count;
}

// Función para leer números desde CSV
int* leer_csv(const char *filename, long *size) {
    *size = contar_numeros(filename);
    if (*size == 0) {
        printf("El archivo %s está vacío o no contiene números válidos.\n", filename);
        exit(EXIT_FAILURE);
    }

    int *arr = (int*) malloc((*size) * sizeof(int));
    if (!arr) {
        printf("Error de memoria\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No se pudo abrir el archivo %s\n", filename);
        free(arr);
        exit(EXIT_FAILURE);
    }

    long index = 0;
    while (fscanf(file, "%d,", &arr[index]) == 1) {
        index++;
        if (index >= *size) break;
    }

    // Leer el último número si no termina con coma
    if (index < *size) {
        if (fscanf(file, "%d", &arr[index]) == 1) {
            index++;
        }
    }

    fclose(file);
    return arr;
}

// Función para escribir números en un archivo CSV
void escribir_csv(const char *filename, int *arr, long size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("No se pudo crear el archivo %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < size; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < size - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");
    fclose(file);
}

// Función para generar el nombre del archivo de salida
// Inserta "_sorted_<algoritmo>" antes de la extensión ".csv"
void generar_nombre_salida(const char *input_filename, char *output_filename, const char *algoritmo) {
    // Encuentra la última aparición de '.'
    const char *dot = strrchr(input_filename, '.');
    if (!dot) {
        // Si no hay punto, simplemente agrega el sufijo
        sprintf(output_filename, "%s_sorted_%s.csv", input_filename, algoritmo);
    } else {
        // Calcula la posición del punto
        size_t basename_length = dot - input_filename;
        // Copia la parte base del nombre
        strncpy(output_filename, input_filename, basename_length);
        output_filename[basename_length] = '\0';
        // Agrega el sufijo y la extensión
        sprintf(output_filename + basename_length, "_sorted_%s.csv", algoritmo);
    }
}

// Función para verificar si el arreglo está ordenado
int verificar_orden(int arr[], long size) {
    for (long i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // No está ordenado
        }
    }
    return 1; // Está ordenado
}

#endif
