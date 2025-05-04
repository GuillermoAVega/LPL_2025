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

//Los productos con posibilidad de orden por /categoria 
void listadoProductos(){
	int respuesta = leerEntero("¿Quiere ver todos los productos(1) o ver por categorias(2)?\n", 1, 1, 2, -1);
	if (respuesta == 1){
		printf("Los productos cargados son: \n");
		mostrarObjetos( (void *) Producto_new);
	}else{
		char criterio[100]; // Buffer para el criterio
		int categoria_usuario = ingresarCodigo((void *) Categoria_new ,  "Ingrese el codigo de la categoria que desea listar:\n");
		sprintf(criterio, "cod_categoria = %d", categoria_usuario);
		void *list,*itm; 
		int i,size=0; 
		
		obj_Producto *prod = Producto_new();
		size = prod->findAll(prod,&list,criterio); // se invoca sin criterio - listar todos... 
		
		for(i=0;i<size;++i){ 
			itm = ((Object **)list)[i]; 
			((Object *)itm)->toString(itm); 
		} 
		destroyObjList(list,size);  // liberar listado, cada instancia creada en el listado 
		destroyObj(prod); // liberar Recurso 
		
		getch();
		

	}
	
}
			
void gestionarListados(){
	int opcion = mostrarMenu(menuListados, LEN(menuListados));
	
	switch (opcion){
		case(2):
			 listadoProductos();	
			 break;
	}
	
	return 0;
}

