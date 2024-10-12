import matplotlib.pyplot as plt

# Ruta del archivo de resumen
summary_file = 'ordenamiento/results/summary/summary.txt'

# Diccionario para almacenar los tiempos de ejecución
results = {}

# Leer el archivo de resumen
with open(summary_file, 'r') as file:
    for line in file:
        if "procesado con" in line:
            parts = line.split(':')  # Dividir la línea en dos partes antes y después de los dos puntos.
            if len(parts) < 3:
                print(f"Formato inesperado en la línea: {line.strip()}")
                continue

            algorithm_info = parts[0].strip()
            time_description = parts[2].strip()  # La parte que contiene el tiempo y la unidad.

            # Depuración: imprimir la información de tiempo
            print(f"Procesando línea: {line.strip()}")
            print(f"algorithm_info: {algorithm_info}, time_description: {time_description}")

            try:
                # Dividimos por espacio para obtener el valor numérico y la unidad
                time_value, time_unit = time_description.split()[:2]
                time_value = float(time_value)
            except (ValueError, IndexError):
                print(f"Error al procesar tiempo en la línea: {line.strip()}")
                continue

            # Convertir el tiempo a milisegundos según la unidad
            if time_unit == 'segundos':
                time_value *= 1000  # Convertir segundos a milisegundos.
            elif time_unit == 'minutos':
                time_value *= 1000 * 60  # Convertir minutos a milisegundos.

            algo_name = algorithm_info.split()[0]
            csv_file = algorithm_info.split()[2]
            
            results[f"{algo_name} ({csv_file})"] = time_value

# Verificar si hay datos en el diccionario
if not results:
    print("No se encontraron datos en el archivo.")
else:
    print("Datos leídos correctamente:", results)

# Preparar los datos para el gráfico
algorithms = list(results.keys())
times = list(results.values())

# Crear el gráfico de barras
plt.figure(figsize=(12, 6))
plt.bar(algorithms, times, color='skyblue')
plt.xlabel('Algoritmo (Archivo CSV)')
plt.ylabel('Tiempo (milisegundos)')
plt.title('Tiempos de Ejecución de Algoritmos de Ordenamiento')
plt.xticks(rotation=45, ha='right')

# Ajustar los límites de los ejes (opcional)
plt.ylim(0, max(times) * 1.1)

plt.tight_layout()

# Guardar el gráfico
plt.savefig('ordenamiento/results/summary/times_plot.png')
plt.show()
