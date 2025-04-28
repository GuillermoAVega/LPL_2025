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
	
	printf("%d\n", codPostal);
	
	if (codPostal == -1)
		return;
	
	obj_Localidad *localidad = Localidad_new();
	localidad->findbykey(localidad, codPostal);
	
	char *nombreLocalidad;
	
	nombreLocalidad = leerCadena("Ingrese el nuevo nombre de la localidad:\n", 60); //Poner constante.
	
	localidad->setNombre(localidad, nombreLocalidad);
	printf("Modificacion exitosa.");
	free(nombreLocalidad);
	destroyObj(localidad);
}

void modificarMarca() {
	
	mostrarObjetos( (void *) Marca_new);
	int cod = ingresarCodigo((void *) Marca_new, "Ingrese el codigo de la marca que desea modificar:\n");	
	
	obj_Marca *marca = Marca_new();
	
	if (marca->findbykey(marca,cod) != NOT_FOUND){
		char *descripcion = leerCadena("Ingrese la nueva descripcion para la marca:\n",50);
		marca->setDescripcion(marca,descripcion);
	
		if(marca->saveObj(marca) == true)
			printf("Modificacion exitosa.\n");
		else
			printf("Error al modificar la marca\n");
		
		free(descripcion);
	}
	
	destroyObj(marca);
};

void modificarProducto(){
};
void modificarCliente(){
};
void modificarSucursal(){
	
		const char *menuModificarSucursal[] = {"Nombre", "Direccion", "Telefono", "Codigo postal"};
		mostrarObjetos( (void *) Sucursal_new);
		int codigo = ingresarCodigo((void *) Sucursal_new, "Ingrese el codigo de la sucursal que desea modificar:\n");
		
		obj_Sucursal *suc = Sucursal_new();
		
		if (suc->findbykey(suc,codigo) != NOT_FOUND){
			int opcion = mostrarMenu(menuModificarSucursal, LEN(menuModificarSucursal));
		
			switch (opcion){
				case 1: {
					char *nombre = leerCadena("Ingrese nombre de la sucursal:\n",50);
					suc->setNombre(suc,nombre);
					if(suc->saveObj(suc) == true)
						printf("Modificacion exitosa.\n");
					else
						printf("Error al modificar sucursal.\n");
					free(nombre);
					break;
				}
			
				case 2: {
					char *direccion = leerCadena("Ingrese direccion de la sucursal:\n",120);
					suc->setDireccion(suc,direccion);
					if(suc->saveObj(suc) == true)
						printf("Modificacion exitosa.\n");
					else
						printf("Error al modificar sucursal.\n");
					free(direccion);
					break;
				}
				case 3: {
					char* telefono = leerCadena("Ingrese telefono de la sucursal:\n",25);
					suc->setTelefono(suc,telefono);
					if(suc->saveObj(suc) == true)
						printf("Modificacion exitosa.\n");
					else
						printf("Error al modificar sucursal.\n");
					free(telefono);
					break;
				}
				case 4:{
					int codpostal = leerEntero("Ingrese el codigo postal de la localidad: \n",1,  0, 10000, -1);
					obj_Localidad *loc = Localidad_new();
					if (loc->findbykey(loc,codpostal) != NOT_FOUND){
						suc->setCodPostal(suc,codpostal);
						if(suc->saveObj(suc) == true)
							printf("Modificacion exitosa.\n");
						else
							printf("Error al modificar sucursal.\n");
					}else
						printf("No existe una localidad con el codigo postal ingresado.\n");
					destroyObj(loc);
					break;
				}
			}
		}
	destroyObj(suc);
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
		
		case 8:
			modificarSucursalDest();
			break;
		
	}
	system("PAUSE");
}
