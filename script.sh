#!/bin/bash

# Directorios
COMPILADOS_DIR="ordenamiento/compilados"
RESULTS_DIR="ordenamiento/results/summary"

# Archivo de resumen
SUMMARY_FILE="$RESULTS_DIR/summary.txt"
echo "Resumen de ejecución de algoritmos de ordenamiento" >"$SUMMARY_FILE"
echo "===================================" >>"$SUMMARY_FILE"

# Archivos CSV a procesar
CSV_FILES=("diezmil.csv" "cienmil.csv" "millon.csv")

# Ejecutar cada algoritmo
for algo in "$COMPILADOS_DIR"/*; do
	# Verificar que sea un archivo ejecutable
	if [[ -x "$algo" ]]; then
		algo_name=$(basename "$algo")

		for csv in "${CSV_FILES[@]}"; do
			# Ignorar el caso de bubble_sort y millon.csv
			if [[ "$algo_name" == "bubble_sort" && "$csv" == "millon.csv" ]]; then
				echo "Ignorando bubble_sort con $csv"
				continue
			fi

			#ignorar el pigeonhole_sort
			if [[ "$algo_name" == "pigeonhole_sort" ]]; then
				echo "Ignorando pigeonhole_sort"
				continue
			fi

			#ignorar el stooge_sort
			if [[ "$algo_name" == "stooge_sort" ]]; then
				echo "Ignorando stooge_sort"
				continue
			fi
			# Ejecutar el algoritmo con el archivo CSV
			output=$("$algo" "$COMPILADOS_DIR/$csv" 2>&1) # Capturar la salida

			# Tomar la primera línea de salida
			first_line=$(echo "$output" | head -n 1)

			# Escribir la salida en el archivo de resumen
			echo "$algo_name procesado con $csv: $first_line" >>"$SUMMARY_FILE"
		done
	fi
done

echo "Ejecuciones completadas. Revisa el resumen en $SUMMARY_FILE."

#Ejeceutar script.py

echo "Se ejecutará el script.py"

python3 -m venv env
source env/bin/activate
python3 -m pip install matplotlib
python3 script.py
