import matplotlib.pyplot as plt

# Ruta del archivo de resumen
summary_file = 'ordenamiento/results/summary/summary.txt'

# Diccionarios para almacenar los tiempos de ejecución por archivo CSV
results_diezmil = {}
results_cienmil = {}
results_millon = {}

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
            csv_file = algorithm_info.split()[-1]  # Cambiar para detectar el archivo correctamente
            
            # Depuración para verificar el archivo CSV detectado
            print(f"Archivo CSV detectado: {csv_file}")

            # Almacenar los tiempos en el diccionario correspondiente
            if 'diezmil.csv' in csv_file:
                results_diezmil[f"{algo_name} (diezmil)"] = time_value
            elif 'cienmil.csv' in csv_file:
                results_cienmil[f"{algo_name} (cienmil)"] = time_value
            elif 'millon.csv' in csv_file:
                results_millon[f"{algo_name} (millon)"] = time_value

# Función para crear gráficos ordenados
def generar_grafico(resultados, titulo, nombre_archivo):
    if not resultados:
        print(f"No se encontraron datos para {titulo}.")
        return
    
    # Ordenar los resultados por tiempo de ejecución (valores)
    sorted_results = sorted(resultados.items(), key=lambda x: x[1])

    # Separar algoritmos y tiempos ordenados
    algorithms, times = zip(*sorted_results)

    # Crear el gráfico de barras
    plt.figure(figsize=(12, 6))
    plt.bar(algorithms, times, color='skyblue')
    plt.xlabel('Algoritmo')
    plt.ylabel('Tiempo (milisegundos)')
    plt.title(titulo)
    plt.xticks(rotation=45, ha='right')

    # Cambiar la escala del eje y a logarítmica
    plt.yscale('log')

    # Ajustar los límites de los ejes (opcional)
    plt.ylim(min(times) * 0.9, max(times) * 1.1)

    plt.tight_layout()

    # Guardar el gráfico
    plt.savefig(f'ordenamiento/results/summary/{nombre_archivo}.png')
    plt.show()

# Generar gráficos para cada conjunto de datos
generar_grafico(results_diezmil, 'Tiempos de Ejecución con 10,000 Elementos', 'times_plot_diezmil')
generar_grafico(results_cienmil, 'Tiempos de Ejecución con 100,000 Elementos', 'times_plot_cienmil')
generar_grafico(results_millon, 'Tiempos de Ejecución con 1,000,000 Elementos', 'times_plot_millon')