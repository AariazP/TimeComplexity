#!/bin/bash

# Verificar que los programas estén compilados
programas=("bubble_sort" "merge_sort" "quick_sort" "pigeonhole_sort" "bitonic_sort")
compilados_dir="./ordenamiento/compilados"
resultados_dir="./results"

# Crear directorio de resultados si no existe
mkdir -p "$resultados_dir"

for prog in "${programas[@]}"; do
    if [ ! -f "$compilados_dir/$prog" ]; then
        echo "El programa $prog no está compilado. Compílalo antes de ejecutar el script."
        exit 1
    fi
done

# Archivos CSV
archivos=("diezmil.csv" "cienmil.csv" "millon.csv")

for prog in "${programas[@]}"; do
    echo "=== Ejecutando $prog ==="
    # Crear archivo de salida para los tiempos de este programa
    salida="$resultados_dir/${prog}_tiempos.txt"
    echo "Tiempos de ejecución para $prog" > "$salida"
    
    for archivo in "${archivos[@]}"; do
        if [ ! -f "$compilados_dir/$archivo" ]; then
            echo "El archivo $archivo no existe. Skipping..."
            continue
        fi
        echo "--- Archivo: $archivo ---" >> "$salida"
        
        # Ejecutar el programa con el archivo CSV y medir el tiempo
        /usr/bin/time -f "Tiempo: %E" "$compilados_dir/$prog" "$compilados_dir/$archivo" >> "$salida" 2>&1
    done
    echo "" >> "$salida"
done
