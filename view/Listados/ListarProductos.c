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

void listarProductoEnArchivo(FILE *archivo, int numeroProducto, Object *obj){
	
	obj_Producto *producto = (obj_Producto *) obj;
	obj_Marca *marca = producto->getMarcaObj(producto);
	obj_Categoria *categoria = producto->getCategoriaObj(producto);

    fprintf(archivo, "---------------------------------\n");
    fprintf(archivo, "Producto %d \n", numeroProducto);
    fprintf(archivo, "Descripcion: %s \n", producto->getDescripcion(producto));
    fprintf(archivo, "Categoria: %s \n", categoria->getDescripcion(categoria));
    fprintf(archivo, "Marca: %s \n", marca->getDescripcion(marca));
    fprintf(archivo, "Precio: $%.2f \n", producto->getPrecio(producto));
    fprintf(archivo, "Stock: %.2f \n", producto->getStock(producto));
    fprintf(archivo, "--------------------------------- \n");
	
	producto->destroyInternal(producto);
}

void mostrarProducto(int numeroProducto, Object *obj){
	
	obj_Producto *producto = (obj_Producto *) obj;
	obj_Marca *marca = producto->getMarcaObj(producto);
	obj_Categoria *categoria = producto->getCategoriaObj(producto);

    printf("---------------------------------\n");
	printf("Producto %d \n", numeroProducto);
    printf("Descripcion: %s \n", producto->getDescripcion(producto));
    printf("Categoria: %s \n", categoria->getDescripcion(categoria));
    printf("Marca: %s \n", marca->getDescripcion(marca));
    printf("Precio: $%.2f \n", producto->getPrecio(producto));
    printf("Stock: %.2f \n", producto->getStock(producto));
    printf("--------------------------------- \n");
	
	producto->destroyInternal(producto);
}



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
		}
		
		if(confirma("Desea guardar el listado en un archivo? s/n")){

			char *nombreArchivo = leerCadena("Ingrese el nombre del archivo: ", 200);
		
			FILE *archivo = fopen(nombreArchivo, "w");
			
			if(archivo != NULL){
				
				for(i=0;i<size;++i){
			   		item = ((Object **)lista)[i]; 
					listarProductoEnArchivo(archivo, i, (Object *)item);
				}
				
				fclose(archivo);
			}
			else{
				printf("Error al abrir archivo");
			}
		
			free(nombreArchivo);
		}
	
		destroyObjList(lista,size);  // liberar listado, cada instancia creada en el listado 
		destroyObj(producto); // liberar Recurso 	
	}
	
	

		

		
	
}
