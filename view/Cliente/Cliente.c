#include "Cliente.h"




const char *menuModificarCliente[] = {"Usuario", "Clave", "Cuil", "Razon Social", "Direccion", "Codigo Postal", "Email", "Celular"};


void cargarCliente(){
	static int codigo = 0;
	codigo++;
	
	//Pido los datos.
	char *usuario = leerCadena("Ingrese el nombre del usuario \n", MAX90); // 90 CARACTERES - Definido en Cliente.h
	char *clave = leerCadena("Ingrese la clave \n", MAX120);  //120 CARACTERES - Definido en Cliente.h
	int codPostal = leerEntero("Ingrese el codigo postal \n",0,0,10000,-1); //INT - Definido en Cliente.h
	
	obj_Localidad *loc = Localidad_new();
	
	if(loc->findbykey(loc, codPostal) == NOT_FOUND){
		
		if (confirma("La localidad ingresada no se encuentra registrada. Desea cargarla? s/n ")){
			cargarLocalidad();
		}
		else{
			free(usuario);
			free(clave);
			return;
		}
	}
	
	//RESTA VALIDAR QUE NO HAYA OTRA PERSONA CON ESE CUIT.
	
	char *cuil = leerCadena("Ingrese el cuil \n", MAX20); //20 CARACTERES - Definido en Cliente.h	
	char *razonSocial = leerCadena("Ingrese la razon social \n", MAX90); //90 CARACTERES - Definido en Cliente.h 
	char *direccion = leerCadena("Ingrese la direccion \n", MAX120); //120 CARACTERES - Definido en Cliente.h
	char *email = leerCadena("Ingrese el mail \n", MAX90); //90 CARACTERES - Definido en Cliente.h 
	char *celular = leerCadena("Ingrese el numero de telefono \n", MAX25); //25 CARACTERES - Definidos en Cliente.h
	

	//Creo el objeto cliente.
	obj_Cliente *cliente = Cliente_new();

	
	//Seteo sus atributos.
	cliente->setUsuario(cliente,usuario);
	cliente->setClave(cliente, clave);
	cliente->setCodigo(cliente, codigo);
	cliente->setCuil(cliente, cuil);
	cliente->setRazonSocial(cliente, razonSocial);
	cliente->setDireccion(cliente, direccion);
	cliente->setCodPostal(cliente, codPostal);
	cliente->setEmail(cliente, email) ;
	cliente->setCelular(cliente, celular);
	
	//Guardo al cliente en la BD.
	if(cliente->saveObj(cliente) == true)
		printf("Ingreso de cliente realizado con exito \n");
			
	
	//Libero memoria.
	destroyObj(loc);
	destroyObj(cliente);
	free(usuario);
	free(clave);
	free(cuil);
	free(razonSocial);
	free(direccion);
	free(email);
	free(celular);
}




void modificarCliente(){

	printf("Los clientes cargados son: \n");
	mostrarObjetos( (void *) Cliente_new);
		
	int cuil, opcion;
	cuil = ingresarCodigo((void *) Cliente_new, "Ingrese el cuil del cliente que desea modificar");	
	
	if (cuil == -1)
		return;
	
	opcion = mostrarMenu(menuModificarCliente, LEN(menuModificarCliente));

}


