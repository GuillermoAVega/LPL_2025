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






void cargarArchivo(FILE *archivo, int size, void *lista){
	
	int i;
	void *item;
	char *cadena;
	
	for(i=0;i<size;++i){
   		item = ((Object **)lista)[i]; 
   		listarClienteEnArchivo(archivo, i, (Object *)item);
		free(cadena);
	}
		
}


void exportarArchivo(void *lista, int size){

		if(confirma("Desea guardar el listado en un archivo? s/n")){
	
			char *nombreArchivo = leerCadena("Ingrese el nombre del archivo: ", 200);
		
			FILE *archivo = fopen(nombreArchivo, "w");
			
			if(archivo != NULL){
				cargarArchivo(archivo, size, lista);
				fclose(archivo);
			}
			else{
				printf("Error al abrir archivo");
			}
			
		free(nombreArchivo);
		//Mostrar que se hizo correctamente.
	}
}


void gestionarListados(){

	const char *menuListados[] = {"Clientes", "Productos", "Medios de pago mas usados", "Productos mas pedidos"};
	
	int opcion = mostrarMenu(menuListados, LEN(menuListados));
  	system("cls");
  	
	switch(opcion){
		case 1:
			listarClientes();
			break;
		
		case 2:
			listarProductos();
			break;
		
		case 3:
			listarMpMasUsados();
			break;
		
		case 4:
			listProdMasPedidos();
			break;
	}
}




