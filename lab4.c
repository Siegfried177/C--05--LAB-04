#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *name;
	float price;
	int quantity;
} product;

typedef struct {
	product *first_element;
	int product_num;
} product_list;

product_list list;

// Función para ingresar y verificar enteros
// Parametros: El entero que se busca ingresar y los limites de su rango
// Retorno: El entero ingresado y verificado correctamente
int verificar(int num, int lim_inf, int lim_sup){
	while (scanf("%d", &num) != 1 || getchar() != '\n') // Mientras no sea un entero el input o sea un salto de linea
        while (getchar() != '\n'); // Limpiar el buffer de entrada
	while ((lim_inf == -1 ? 0 : num < lim_inf) || (lim_sup == -1 ? 0 : num > lim_sup)){
		if (lim_inf != -1 && lim_sup == -1) printf("Ingrese un numero a partir de %d:\n", lim_inf);
		if (lim_inf == -1 && lim_sup != -1) printf("Ingrese un numero hasta %d:\n", lim_sup);
		if (lim_inf != -1 && lim_sup != -1) printf("Ingrese un numero entre %d y %d:\n", lim_inf, lim_sup);
        scanf("%d", &num);
        while (getchar() != '\n'); // Limpiar el buffer de entrada
    }
	return num;
}

// Función para ingresar y verificar floats
// Parametros: El float que se busca ingresar y los limites de su rango
// Retorno: El float ingresado y verificado correctamente
float verificar_f(float num){
	while (scanf("%f", &num) != 1 || getchar() != '\n' || num < 0)
        while (getchar() != '\n');
	return num;
}

// Función para añadir productos
void add_product(){
	char ch;
	int size; // Un entero que representa la cantidad de elementos del nombre
	product new;
	list.first_element = realloc(list.first_element, (list.product_num + 1) * sizeof(product));

	new.name = (char *)malloc(1); // Reservar memoria para el nombre
	puts("Ingrese el nombre del producto:");
	for (size = 1; (ch = getchar()) != '\n'; size++) {
        new.name = (char *)realloc(new.name, size * sizeof(char));
        new.name[size - 1] = ch;
    }
	new.name[size - 1] = '\0';
	puts("Ingrese el precio:");
	new.price = verificar_f(new.price);
	puts("Ingrese la cantidad:");
	new.quantity = verificar(new.quantity, 1, -1);

	list.first_element[list.product_num++] = new;
}

// Función para eliminar productos
void delete_product(){
	int index = 0;
	product aux; // Variable auxiliar para ir cambiando el orden de los elementos
	puts("Ingrese el indice del producto a borrar");
	index = verificar(index, 0, list.product_num - 1);
	for (int i = index; i < list.product_num - 1; i++){ // Bubble Sort
		aux = list.first_element[i];
		list.first_element[i] = list.first_element[i + 1];
		list.first_element[i + 1] = aux;
	}
	list.first_element = realloc(list.first_element, --list.product_num * sizeof(product)); // Realloc para acortar el array
}

// Función para editar productos
void edit_product(){
	int index = 0, size;
	char ch;
	puts("Ingrese el indice del producto a modificar");
	index = verificar(index, 0, list.product_num - 1);
	(list.first_element + index)->name = (char *)malloc(1);
	puts("Ingrese el nombre del producto:");
	for (size = 1; (ch = getchar()) != '\n'; size++) {
		(list.first_element + index)->name = (char *)realloc((list.first_element + index)->name, size * sizeof(char));
		(list.first_element + index)->name[size - 1] = ch;
	}
	(list.first_element + index)->name[size - 1] = '\0';
	puts("Ingrese el nuevo precio:");
	(list.first_element + index)->price = verificar_f((list.first_element + index)->price);
	puts("Ingrese la nueva cantidad:");
	(list.first_element + index)->quantity = verificar((list.first_element + index)->quantity, 1, -1);
}

// Función para mostrar todos los productos
void show_products(){
	puts("Los productos son:");
	for (int i = 0; i < list.product_num; i++, puts(""))
		printf("Producto: %s -- Precio: %.2f -- Cantidad: %d", (list.first_element + i)->name, (list.first_element + i)->price, (list.first_element + i)->quantity);
}

// Función para calcular y mostrar el costo total
void total_cost(){
	float total;
	for (int i = 0; i < list.product_num; i++)
        total += (list.first_element + i)->price * (list.first_element + i)->quantity;
	printf("El costo total es: %.2f\n", total);
}

int main(void) {
	int option = 0;
	while(1){
		puts("\n--- Menu Principal ---\n1 -- Agregar un nuevo producto a la lista\n2 -- Eliminar un producto de la lista\n3 -- Editar la informacion de un producto en la lista");
		puts("4 -- Mostrar todos los productos en la lista\n5 -- Calcular el costo total de todos los productos en la lista\n0 -- Salir\n");
		option = verificar(option, 0, 5);
		if (option == 1)
			add_product();
		else if (option == 2)
			delete_product();
		else if (option == 3)
			edit_product();
		else if (option == 4)
			show_products();
		else if (option == 5)
			total_cost();
		else{
			free(list.first_element); // Liberar memoria
			return 0; // Salir del programa
		}
	}
}