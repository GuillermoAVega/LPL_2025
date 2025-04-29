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

const char *menuIngresos[] = {"Localidad", "Marca", "Producto", "Cliente", "Sucursal", "Factura", "Detalle Factura", "Sucursal destino"}; //MODIFICAR SUCURSAL DESTINO.

void mostrarObjetos( void *(*constructor)() ){
	
	Object *obj;
	
	obj = constructor();
	
	void *list,*itm;
	int i,size=0;
	size = obj->findAll(obj,&list,NULL); // se invoca sin criterio - listar todos...
	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];
		((Object *)itm)->toString(itm);
	}
	destroyObjList(list,size); // liberar listado, cada instancia creada en el listado
	destroyObj(obj);
	
}


int ingresarCodigo (void *(*constructor)(), char *msj_pant){
	
	int codigo, reintentar;
	Object *obj = constructor();
			
	do{
		system("cls");
		printf("%s\n", msj_pant);
		mostrarObjetos( (void *) constructor); //Muestra todas las marcas.
		codigo = leerEntero("Ingrese el codigo asociado segun corresponda \n", 0, 0, 10000, -1);
	
	} while ((obj->findbykey(obj,codigo) == NOT_FOUND) && (reintentar = confirma("El codigo ingresado no se encuentra registrado. Desea reintentarlo? s/n")));
	
	destroyObj(obj);
	
	if(!reintentar)
		return -1;
	else
		return codigo;
}


void gestionarIngresos(){
	
  	int opcion = mostrarMenu(menuIngresos, LEN(menuIngresos));
  	system("cls");
	switch(opcion){
		case 1:
			cargarLocalidad();
			break;
		
		case 2:
			cargarMarca();
			break;
		
		case 3:
			cargarProducto();
			break;
		
		case 4:
			cargarCliente();
			break;
			
		case 5:
			cargarSucursal();
			break;
		
		case 6:
			cargarFactura();
			break;
		
		case 7:
			cargarDetalleFactura();
			break;
		
		case 8:
			cargarSucursalDest();
			break;
		
	}
}



