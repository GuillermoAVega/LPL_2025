#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/includes.h"
#include <sys/types.h>
#include <sys/stat.h>

const char *menuListados[] = {"Clientes", "Productos", "Medios de pago mas usados", "Productos mas pedidos"};


void listadoProductos(){
	char *menuProductos[] = {"Todos los productos", "Productos por categoria","Productos por marca"};
	int opcion = mostrarMenu(menuProductos, LEN(menuProductos));

	switch (opcion){
		case 1:
			printf("Los productos cargados son: \n");
			mostrarObjetos( (void *) Producto_new);
			break;
		case 2:{
			char criterio[100]; // Buffer para el criterio
			int categoria_usuario = ingresarCodigo((void *) Categoria_new ,  "Ingrese el codigo de la categoria que desea listar:\n");
			
			sprintf(criterio, "cod_categoria = %d", categoria_usuario);
			void *list,*itm; 
			int i,size=0; 
			
			obj_Producto *prod = Producto_new();
			size = prod->findAll(prod,&list,criterio); // se invoca sin criterio - listar todos... 
			
			for (i = 0; i < size; ++i) {
			    itm = ((Object **)list)[i];
			    char *str = ((Object *)itm)->toString(itm);
			    printf("%s", str);
			    free(str); 
			}
			
			destroyObjList(list,size);  // liberar listado, cada instancia creada en el listado 
			destroyObj(prod); // liberar Recurso 
			
			system("PAUSE");
			
			break;
		}
		case 3:{
			char criterio[100]; // Buffer para el criterio
			int marca_usuario = ingresarCodigo((void *) Marca_new ,  "Ingrese el codigo de la marca que desea listar:\n");
			
			sprintf(criterio, "cod_marca = %d", marca_usuario);
			void *list,*itm; 
			int i,size=0; 
			
			obj_Producto *prod = Producto_new();
			size = prod->findAll(prod,&list,criterio); // se invoca sin criterio - listar todos... 
			for (i = 0; i < size; ++i) {
			    itm = ((Object **)list)[i];
			    char *str = ((Object *)itm)->toString(itm);
			    printf("%s", str);
			    free(str); 
			}
			
			destroyObjList(list,size);  // liberar listado, cada instancia creada en el listado 
			destroyObj(prod); // liberar Recurso 
			
			system("PAUSE");
			break;
		}
	}
	free(menuProductos);
}
			
void gestionarListados(){
	int opcion = mostrarMenu(menuListados, LEN(menuListados));
	
	switch (opcion){
		case(1):
			break;
		case(2):
			 listadoProductos();	
			 break;
		case(3):
			break;
		case(4):
			break;
	}
	
	return 0;
}

