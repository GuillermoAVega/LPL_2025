#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../includes/includes.h"
#include <sys/types.h>
#include <sys/stat.h>


void listarProductos(){

	char *menuProductos[] = {"Productos por categoria","Productos por marca"};
	int opcion = mostrarMenu(menuProductos, LEN(menuProductos));
	
	obj_Producto *producto = Producto_new();
	void *lista,*item; 
	int i,size=0; 
	
	if(opcion != -1){
		char criterio[100]; // Buffer para el criterio
		
		if(opcion == 1){
			
			int categoria_usuario = ingresarCodigo((void *) Categoria_new ,  "Ingrese el codigo de la categoria que desea listar:\n");
			sprintf(criterio, "cod_categoria = %d", categoria_usuario);
			
		}
		else{
			
			int marca_usuario = ingresarCodigo((void *) Marca_new ,  "Ingrese el codigo de la marca que desea listar:\n");		
			sprintf(criterio, "cod_marca = %d", marca_usuario);
		
		
		}
		
		size = producto->findAll(producto,&lista,criterio); // se invoca sin criterio - listar todos... 
			
		for (i = 0; i < size; ++i) {
		    item = ((Object **)lista)[i];
		    char *str = ((Object *)item)->toString(item);
		    printf("%s", str);
		    free(str); 
		}
		
		exportarArchivo(lista, size);
	
		destroyObjList(lista,size);  // liberar listado, cada instancia creada en el listado 
		destroyObj(producto); // liberar Recurso 	
	}
	
	

		

		
	
}
