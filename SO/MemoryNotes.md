# Memoria

## Secciones por defecto de un ejecutable ELF (Executable and Linkable Format)

1. **.text**	- código
2. **.data**	- datos globales inicializados
3. **.bss**		- datos globales sin valor inicial
4. **.debug** 	- información de debug
5. **.dynamic**	- información para el enlace dinámico (direcciones de memoria de librerías de C)
6. **.init**	- código de inicialización del proceso


La zona de .dynamic puede estar vacía si compilamos con la opción *-static*, que copia el código de las librerías dentro de nuestro ejecutable.


### Reserva/Liberar memoria dinámica

Si queremos reservar regiones de memoria en tiempo de ejecución, usamos el **heap** del espacio lógico de direcciones.

Normalmente reservamos una zona de memoria dinámica (heap) y/o ampliamos el heap.

### sbrk(n)

Amplia o reduce el heap por el número de bytes *n* pasado como argumento. Si se amplia el heap, sbrk es un puntero al inicio de la zona ampliada. Si escribimos sbrk(0) se nos devolverá el límite actual del heap.
Para liberar la memoria ampliada, escribimos sbrk(n) donde n es el número de bytes a liberar **en negativo**.

```c

	int *s;
	s = sbrk(8 * sizeof(int));		// s apunta al inicio de la zona ampliada

	int num = sbrk(0)			// guardamos el límite actual del heap

	sbrk(-8 * sizeof(int));			// liberamos los 64 bytes anteriores


```

### malloc(n)

A diferencia de sbrk, malloc no siempre amplia el espacio de memoria dinámica. Si tiene espacio suficiente, simplemente reserva una zona de la memoria para la variable específicada. En el momento en que se pide una cantidad de memoria superior a la disponible, malloc ampliará la memoria dinámica por una cantidad superior a la que hemos pedido, para asegurar que en llamadas posteriores se podrá ahorrar la ampliación.

malloc devuelve la dirección de inicio de la memoria reservada, independientemente de si el heap ha sido ampliado o no. Para liberarla, usamos **free()**.

```c

	int *s;
	s = malloc(1000 * sizeof(int));		// reservamos el tamaño equivalente a 1000 enteros

	free(s);				// pasamos como argumento el puntero anterior

```



### Paginación (partición fija)

El espacio de direcciones lógicas de memoria está dividido en **páginas**, con una tabla de páginas por proceso.

Normalmente, cada página referencia una de las regiones de memoria (código, datos, heap, etc.).



### Segmentanción (partición variable)

Espacio de direcciones lógicas dividido en particiones de tamaño variable (ajustadas a lo que necesite). 

Como mínimo, habrá un segmento para el código, pila y datos.

La asignación funciona mediante la búsqueda de una particioón disponible donde quepa el segmento (first fit, best fit, worst fit).



## Esquema mixto (paginación & segmentación)

Dividimos el espacio lógico en segmentos y dividimos esos segmentos en páginas (dónde el segmento es un múltiplo del tamaño de página).

La unidad de trabajo del SO es la página.




## Servicios para la optimización del uso de memoria


### COW (Copy on Write)

Solo se reservan/inicializan zonas de la memoria física cuando es necesario. Ahorramos tiempo y espacio de memoria.

En el fork, solo es necesario copiar el código, datos, etc. cuándo ya no estamos accediendo en modo lectura (es decir, si se accede a una posición distinta del padre o entramos en una espera de input, por ejemplo).

Aplicable al pedir memoria dinámica, entre procesos, o siempre que se aumenta/modifica el espacio de direcciones.