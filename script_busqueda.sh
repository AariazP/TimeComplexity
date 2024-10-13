#!/bin/bash

# Directorios
COMPILADOS_DIR="busqueda/compilados"
RESULTS_DIR="busqueda/summary"

# Archivo de resumen
SUMMARY_FILE="$RESULTS_DIR/summary.txt"
echo "Resumen de ejecución de algoritmos de ordenamiento" >"$SUMMARY_FILE"
echo "===================================" >>"$SUMMARY_FILE"

# Archivos CSV a procesar
CSV_FILES=("cienmil_sorted.csv" "diezmil_sorted.csv" "millon_sorted.csv")
ARRAYS_DIR="busqueda/arrays"

# Ejecutar cada algoritmo
for algo in "$COMPILADOS_DIR"/*; do
	# Verificar que sea un archivo ejecutable
	if [[ -x "$algo" ]]; then
		algo_name=$(basename "$algo")

		for csv in "${CSV_FILES[@]}"; do
			# Ejecutar el algoritmo con el archivo CSV
			output=$("$algo" "$ARRAYS_DIR/$csv" 2>&1) # Capturar la salida

			# Tomar la primera línea de salida
			first_line=$(echo "$output" | head -n 1)

			# Escribir la salida en el archivo de resumen
			echo "$algo_name procesado con $csv: $first_line" >>"$SUMMARY_FILE"
		done
	fi
done

echo "Ejecuciones completadas. Revisa el resumen en $SUMMARY_FILE."

#Ejecutar script.py

echo "Se ejecutará el script.py"

python3 -m venv env
source env/bin/activate
python3 -m pip install matplotlib
python3 script_busqueda.py
