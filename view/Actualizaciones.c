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

const char *menuActualizaciones[] = {"Localidad", "Marca", "Producto", "Cliente", "Sucursal", "Factura", "Detalle Factura", "Sucursal destino"}; //MODIFICAR SUCURSAL DESTINO.



void modificarLocalidad(){

	mostrarObjetos( (void *) Localidad_new);
	int codPostal = ingresarCodigo((void *) Localidad_new, "Ingrese el codigo postal de la localidad que desea modificar");	
	
	printf("%d", codPostal);
	
	if (codPostal == -1)
		return;
	
	obj_Localidad *localidad = Localidad_new();
	localidad->findbykey(localidad, codPostal);
	
	char *nombreLocalidad;
	
	nombreLocalidad = leerCadena("Ingrese el nuevo nombre de la localidad", 60); //Poner constante.
	
	localidad->setNombre(localidad, nombreLocalidad);
	
	free(nombreLocalidad);
	
}

void modificarMarcas() {
};
void modificarProducto(){
};
void modificarCliente(){
};
void modificarSucursal(){
};
void modificarFactura(){
};
void modificarDetalleFactura(){
};
void modificarSucursalDest(){
};



void gestionarActualizaciones(){
	
  	int opcion = mostrarMenu(menuActualizaciones, LEN(menuActualizaciones));
  	system("cls");
  	
	switch(opcion){
		case 1:
			modificarLocalidad();
			break;
		
		case 2:
			modificarMarcas();
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
		
		case 8:
			modificarSucursalDest();
			break;
		
	}
	system("PAUSE");
}
