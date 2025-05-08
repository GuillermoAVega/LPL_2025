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


enum OrdenCliente{
	DNI = 1,
	APELLIDO = 2
};

enum OrdenCliente tipoOrden; //Variable global que tiene el criterio para ordenar al cliente.


void mostrarCliente(int numero, Object *obj){
	
	obj_Cliente *cliente = (obj_Cliente *) obj;
	obj_Localidad *localidad = cliente->getLocalidadObj(cliente); 
	
	printf("---------------------------------\n");
	printf("Cliente %d \n", numero);
	printf("Usuario: %s \n", cliente->getUsuario(cliente) );
	printf("Cuil: %s \n", cliente->getCuil(cliente));
	printf("Localidad: %s \n", localidad->getNombre(localidad));
	printf("---------------------------------\n");
}


void listarClienteEnArchivo(FILE *archivo, int numeroCliente, Object *obj){
	
	obj_Cliente *cliente = (obj_Cliente *) obj;
    obj_Localidad *localidad = cliente->getLocalidadObj(cliente); 

    fprintf(archivo, "---------------------------------\n");
    fprintf(archivo, "Cliente %d \n", numeroCliente);
    fprintf(archivo, "Usuario: %s \n", cliente->getUsuario(cliente));
    fprintf(archivo, "Cuil: %s \n", cliente->getCuil(cliente));
    fprintf(archivo, "Localidad: %s \n", localidad->getNombre(localidad));
    fprintf(archivo, "--------------------------------- \n \n");
	
}


int comparaCliente(const void *a, const void *b){
	
	obj_Cliente *objA = *(obj_Cliente **) a;
	obj_Cliente *objB = *(obj_Cliente **) b;
	
	obj_Cliente *clienteA = (obj_Cliente *)objA;
    obj_Cliente *clienteB = (obj_Cliente *)objB;
    
    if(tipoOrden == APELLIDO){
    	char *nombreA = clienteA->getUsuario(clienteA);
		char *nombreB = clienteB->getUsuario(clienteB);
		
		return (stricmp(nombreA, nombreB));
	}
	else{
		char *cuilA = clienteA->getCuil(clienteA);
		char *cuilB = clienteB->getCuil(clienteB);
		return (strcmp(cuilA, cuilB));
	}


}


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


void listarClientes() {
	
	const char *menuListarClientes[] = {"Ordenados por DNI", "Ordenados por Nombre"};
	int opcion = mostrarMenu(menuListarClientes, LEN(menuListarClientes));


	if(opcion != -1){
		
		system("cls");
		obj_Cliente *cliente = Cliente_new();
		void *lista, *item;
		int i, size;
		
		tipoOrden = (enum OrdenCliente) opcion;

		size = cliente->findAll(cliente,&lista,NULL);  
		qsort(lista,size,sizeof(void *),comparaCliente);	
				
		for(i=0; i < size ; i++){
	   		item = ((Object **)lista)[i];    
		 	mostrarCliente(i, (Object *) item);
		}

		if(confirma("Desea guardar el listado en un archivo? s/n")){
		
			char *nombreArchivo = leerCadena("Ingrese el nombre del archivo: ", 200);

			FILE *archivo = fopen(nombreArchivo, "w");
			
			if(archivo != NULL){
				cargarArchivo(archivo, size, lista);
				fclose(archivo);
				free(nombreArchivo);
			}
			else{
				printf("Error al abrir archivo");
			}
			
			//Mostrar que se hizo correctamente.
		}
		
		destroyObj(cliente);
		destroyObjList(lista,size);
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
			//listarProductos();
			break;
		
		case 3:
			//listarMediosPago;
			break;
		
		case 4:
			//modificarCliente();
			break;
	}
}
