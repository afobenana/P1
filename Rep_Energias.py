import matplotlib.pyplot as plt
import csv

# Nombre del archivo de datos
file_name = "Energias.txt"

# Crear una figura y ejes para los subgráficos
fig, axs = plt.subplots(2, 1, figsize=(10, 8))

# Leer los datos del archivo y trazar los subgráficos
with open(file_name, 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        # Extraer datos de x e y del archivo
        x_data = [float(val) for val in row[::2]]
        y_data = [float(val) for val in row[1::2]]

        # Trazar los datos en el primer subgráfico
        axs[0].plot(x_data, y_data, label='Datos')

# Configuración del primer subgráfico
axs[0].set_xlabel('X')
axs[0].set_ylabel('Y')
axs[0].set_title('Gráfico 1')
axs[0].legend()

# Leer los datos del archivo nuevamente (puntero al inicio)
file.seek(0)

# Leer los datos del archivo y trazar los subgráficos
with open(file_name, 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        # Extraer datos de x e y del archivo
        x_data = [float(val) for val in row[::2]]
        y_data = [float(val) for val in row[1::2]]

        # Trazar los datos en el segundo subgráfico
        axs[1].plot(x_data, y_data, label='Datos')

# Configuración del segundo subgráfico
axs[1].set_xlabel('X')
axs[1].set_ylabel('Y')
axs[1].set_title('Gráfico 2')
axs[1].legend()

# Ajustar el diseño de los subgráficos
plt.tight_layout()

# Mostrar el gráfico
plt.show()
