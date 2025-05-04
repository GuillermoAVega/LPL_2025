#include "Localidad.h"


void cargarLocalidad(){
	
	int codPostal = leerEntero("Ingrese el codigo postal de la localidad \n",1,  0, 10000, -1);	

	obj_Localidad *loc = Localidad_new();
	
	if(loc->findbykey(loc, codPostal) == NOT_FOUND){
		system("cls");
		
		char *nombre = leerCadena("Ingrese el nombre de la localidad \n", MAX60); 

		loc->setCodpostal(loc, codPostal);
		loc->setNombre(loc, nombre);

		if(loc->saveObj(loc) == true)
			printf("Ingreso de localidad realizado con exito \n");
			
		free(nombre);
	}
	else{
		printf("Ya existe una localidad con ese codigo postal \n");
	}				
	destroyObj(loc);
}


void modificarLocalidad(){

	mostrarObjetos( (void *) Localidad_new);
	int codPostal = ingresarCodigo((void *) Localidad_new, "Ingrese el codigo postal de la localidad que desea modificar \n");	
	
	if (codPostal == -1)
		return;
	
	obj_Localidad *localidad = Localidad_new();
	localidad->findbykey(localidad, codPostal);
	
	char *nombreLocalidad = leerCadena("Ingrese el nuevo nombre de la localidad \n", MAX60); 
	
	localidad->setNombre(localidad, nombreLocalidad);
	
	if(localidad->saveObj(localidad) == true)
		printf("Actualizacion de la localidad realizada con exito \n");
			
	
	free(nombreLocalidad);
	destroyObj(localidad);
	
}



