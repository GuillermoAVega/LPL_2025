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


int comparaClienteNombre(const void *a, const void *b){
	
	obj_Cliente *objA = *(obj_Cliente **) a;
	obj_Cliente *objB = *(obj_Cliente **) b;
	
	obj_Cliente *clienteA = (obj_Cliente *)objA;
    obj_Cliente *clienteB = (obj_Cliente *)objB;
	
	char *nombreA = clienteA->getUsuario(clienteA);
	char *nombreB = clienteB->getUsuario(clienteB);
	
	return (stricmp(nombreA, nombreB));
}

int comparaClienteDNI(const void *a, const void *b){
	
	obj_Cliente *objA = *(obj_Cliente **) a;
	obj_Cliente *objB = *(obj_Cliente **) b;
	
	obj_Cliente *clienteA = (obj_Cliente *)objA;
    obj_Cliente *clienteB = (obj_Cliente *)objB;
	
	char *cuilA = clienteA->getCuil(clienteA);
	char *cuilB = clienteB->getCuil(clienteB);
	
	return ( strcmp(cuilA, cuilB));
}




void listarClientes() {
	
	const char *menuListarClientes[] = {"Ordenados por DNI", "Ordenados por Nombre"};
	int opcion = mostrarMenu(menuListarClientes, LEN(menuListarClientes));
	if(opcion != -1){
		
		system("cls");
		obj_Cliente *cliente = Cliente_new();
		void *lista, *item;
		int size = cliente->findAll(cliente,&lista,NULL);  
		
		if(opcion == 1){
			qsort(lista,size,sizeof(void *),comparaClienteDNI);	
		}
		else{
			qsort(lista,size,sizeof(void *),comparaClienteNombre);	
		}
			
		int i;
	    for(i=0;i<size;++i){
	       item = ((Object **)lista)[i];    
		   mostrarCliente(i, (Object *) item);
	    }
		
		system("PAUSE");
		
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
			//modificarMarca();
			break;
		
		case 3:
			//modificarProducto();
			break;
		
		case 4:
			//modificarCliente();
			break;
	}
}
