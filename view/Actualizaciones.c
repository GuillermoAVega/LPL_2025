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


const char *menuActualizaciones[] = {"Localidad", "Marca", "Producto", "Cliente", "Sucursal", "Factura", "Detalle Factura"};


void gestionarActualizaciones(){
	
  	int opcion = mostrarMenu(menuActualizaciones, LEN(menuActualizaciones));
  	system("cls");
  	
	switch(opcion){
		case 1:
			modificarLocalidad();
			break;
		
		case 2:
			modificarMarca();
			break;
		
		case 3:
			modificarProducto();
			break;
		
		case 4:
			modificarCliente();
			break;
		
		case 5:
			modificarSucursal();
			break;
		
		case 6:
			modificarFactura();
			break;
		
		case 7:
			modificarDetalleFactura();
			break;
	}
}
