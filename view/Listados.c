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


void gestionarListados(){

	const char *menuListados[] = {"Clientes", "Productos", "Medios de pago mas usados", "Productos mas pedidos"};
	int opcion;
	
	do{	
		opcion = mostrarMenu(menuListados, LEN(menuListados));
		  	
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
		
	} while(opcion != -1);
}
	




