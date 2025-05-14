#include "Marca.h"


void cargarMarca(){
	static int cod = 0;
	char *descripcion = leerCadena("Ingrese una descripcion para la marca:\n",MAX50);
	
	obj_Marca *marca = Marca_new();
	marca->setCodigo(marca,cod++);
	marca->setDescripcion(marca,descripcion);
	
	if(marca->saveObj(marca) == true){
		printf("Ingreso exitoso.\n");
	}
	else
		printf("Error al ingresar la marca\n");
	
	
	system("PAUSE");
	destroyObj(marca);
	free(descripcion);
}


void modificarMarca() {

	int cod = ingresarCodigo((void *) Marca_new, "Ingrese el codigo de la marca que desea modificar:\n");	
	
	obj_Marca *marca = Marca_new();
	
	if (marca->findbykey(marca,cod) != NOT_FOUND){
		char *descripcion = leerCadena("Ingrese la nueva descripcion para la marca:\n", MAX50);
		marca->setDescripcion(marca,descripcion);
	
		if(marca->saveObj(marca) == true)
			printf("Modificacion exitosa.\n");
		else
			printf("Error al modificar la marca\n");
		
		free(descripcion);
	}
	
	destroyObj(marca);
}
