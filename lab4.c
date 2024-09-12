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

// Función para verificar e ingresar enteros
int verificar(int num, int lim_inf, int lim_sup){
	while (scanf("%d", &num) != 1 || getchar() != '\n') // Mientras no sea un entero el input o sea un salto de linea
        while (getchar() != '\n'); // Limpiar el buffer de entrada
	while ((lim_inf == 0 ? 0 : num < lim_inf) || (lim_sup == 0 ? 0 : num > lim_sup)){
		printf("Ingrese un numero entre %d y %d:\n", lim_inf, lim_sup);
        scanf("%d", &num);
        while (getchar() != '\n'); // Limpiar el buffer de entrada
    }
	return num;
}

// Función para verificar e ingresar flotantes
float verificar_f(float num){
	while (scanf("%f", &num) != 1 || getchar() != '\n')
        while (getchar() != '\n');
	return num;
}

// Función para añadir productos
void add_product(){
	list.first_element = realloc(list.first_element, (list.product_num + 1) * sizeof(product));
	product new;

	if (list.first_element == NULL){
		puts("Error en memoria.");
		exit(1);
	}
	new.name = (char *)malloc(sizeof(char));

	puts("Ingrese el nombre del producto:");
	scanf("%s", new.name);
	puts("Ingrese el precio:");
	new.price = verificar_f(new.price);
	puts("Ingrese la cantidad");
	new.quantity = verificar(new.quantity, 0, 0);

	list.first_element[list.product_num++] = new;
}

// Función para eliminar productos
void delete_product(){
	char *string;
	puts("Que producto desea borrar?");
}

// Función para editar productos
void edit_product(){
	char *string;
	puts("Que producto desea modificar?");

}

// Función para mostrar todos los productos
void show_products(){
	puts("Los productos son:");
	for (int i = 0; i < list.product_num; i++)
		printf("%s ", (list.first_element + i)->name);
    puts("");
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
		puts("\n--- Menu Principal ---\n1 -- Agregar un nuevo producto a la lista\n2 -- Eliminar un producto existente de la lista\n3 -- Editar la informacion de un producto en la lista\n4 -- Mostrar todos los productos presentes en la lista\n5 -- Calcular el costo total de todos los productos en la lista·\n0 -- Salir\n");
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
		else return 0; // Salir del programa
	}
}