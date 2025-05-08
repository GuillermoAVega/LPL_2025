#include "Sucursal.h"



void cargarSucursal(){
	static int codigo = 0;
	int cod_postal = leerEntero("Ingrese el codigo postal de la localidad: \n",1,  0, 10000, -1);	
	obj_Localidad *loc = Localidad_new();
	
	if (loc->findbykey(loc,cod_postal) != NOT_FOUND){
		obj_Sucursal *suc = Sucursal_new();
		
		char *nombre = leerCadena("Ingrese nombre de la sucursal:\n", MAX50);
		char *direccion = leerCadena("Ingrese descripcion de la sucursal:\n",MAX120);
		char *telefono = leerCadena("Ingrese telefono de la sucursal:\n",MAX25);
		
		suc->setCodigo(suc,codigo++);
		suc->setNombre(suc,nombre);
		suc->setDireccion(suc,direccion);
		suc->setTelefono(suc,telefono);
		suc->setCodPostal(suc,cod_postal);
		
		if (suc->saveObj(suc) == true){
			printf("Ingreso exitoso\n");
		}
		else
			printf("Error al ingresar la sucursal\n");
		
		free(nombre);
		free(direccion);
		free(telefono);	
		destroyObj(suc);
	}else
		printf("No existe la localidad ingresada.\n");
	

	destroyObj(loc);
}



void modificarSucursal(){
	
		const char *menuModificarSucursal[] = {"Nombre", "Direccion", "Telefono", "Codigo postal"};
		int codigo = ingresarCodigo((void *) Sucursal_new, "Ingrese el codigo de la sucursal que desea modificar:\n");
		
		obj_Sucursal *suc = Sucursal_new();
		
		if (suc->findbykey(suc,codigo) != NOT_FOUND){
			int opcion = mostrarMenu(menuModificarSucursal, LEN(menuModificarSucursal));
		
			switch (opcion){
				case 1: {
					char *nombre = leerCadena("Ingrese nombre de la sucursal:\n",MAX50);
					suc->setNombre(suc,nombre);
					if(suc->saveObj(suc) == true)
						printf("Modificacion exitosa.\n");
					else
						printf("Error al modificar sucursal.\n");
					free(nombre);
					break;
				}
			
				case 2: {
					char *direccion = leerCadena("Ingrese direccion de la sucursal:\n",MAX120);
					suc->setDireccion(suc,direccion);
					if(suc->saveObj(suc) == true)
						printf("Modificacion exitosa.\n");
					else
						printf("Error al modificar sucursal.\n");
					free(direccion);
					break;
				}
				case 3: {
					char* telefono = leerCadena("Ingrese telefono de la sucursal:\n",MAX25);
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
}


