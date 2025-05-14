#include "Cliente.h"

#define TRUE 1
#define FALSE 0

//Retorna el codigo del cliente con ese cuil. -1 si no existe.
int buscarCliente(char *cuilIngresado){   

	obj_Cliente *cliente = Cliente_new();
	void *list, *item;
	int codigo = -1;
	int i = 0; 
	int size = cliente->findAll(cliente,&list,NULL);    
		
	while (i < size) {
		item = ((Object **)list)[i];    

		if (strcmp(cuilIngresado, ((obj_Cliente *)item)->getCuil(item)) == 0) {
			codigo = ((obj_Cliente *)item)->getCodigo(item);
			break;
		}
		i++;
	}	
	
    destroyObjList(list,size);
    destroyObj(cliente);
	return codigo;
}
	

void cargarCliente(){
	static int codigo = 0;

	//Pido los datos.
	char *cuil = leerCadena("Ingrese el cuil \n", MAX20); //20 CARACTERES - Definido en Cliente.h	
	char buffer[MAX560];
	
	if (buscarCliente(cuil) != -1){
		printf("Ya existe un cliente registrado con ese cuit \n");
	}
	else{
		
		int codPostal = leerEntero("Ingrese el codigo postal \n",0,0,10000,-1); //INT - Definido en Cliente.h	
	
		obj_Localidad *loc = Localidad_new();
		if(loc->findbykey(loc, codPostal) != NOT_FOUND){
			
			char *usuario = leerCadena("Ingrese el nombre del usuario \n", MAX90); // 90 CARACTERES - Definido en Cliente.h
			char *clave = leerCadena("Ingrese la clave \n", MAX120);  //120 CARACTERES - Definido en Cliente.h
			char *razonSocial = leerCadena("Ingrese la razon social \n", MAX90); //90 CARACTERES - Definido en Cliente.h 
			char *direccion = leerCadena("Ingrese la direccion \n", MAX120); //120 CARACTERES - Definido en Cliente.h
			char *email = leerCadena("Ingrese el mail \n", MAX90); //90 CARACTERES - Definido en Cliente.h 
			char *celular = leerCadena("Ingrese el numero de telefono \n", MAX25); //25 CARACTERES - Definidos en Cliente.h
			
			//Creo el objeto cliente.
			obj_Cliente *cliente = Cliente_new();
		
			//Seteo sus atributos.
			cliente->setUsuario(cliente,usuario);
			cliente->setClave(cliente, clave);
			cliente->setCodigo(cliente, codigo++);
			cliente->setCuil(cliente, cuil);
			cliente->setRazonSocial(cliente, razonSocial);
			cliente->setDireccion(cliente, direccion);
			cliente->setCodPostal(cliente, codPostal);
			cliente->setEmail(cliente, email) ;
			cliente->setCelular(cliente, celular);
			
			//Guardo al cliente en la BD.
			if(cliente->saveObj(cliente) == true){
				printf("Ingreso de cliente realizado con exito \n");
				snprintf(buffer, MAX560, "Crea el cliente con codigo = %d, usuario = %s, cuil = %s"
						,cliente->getCodigo(cliente)
						,cliente->getUsuario(cliente)
						,cliente->getCuil(cliente));
				
				registrarEvento("Cliente", buffer);
			}
			else
				printf("Error al ingresar el cliente en la base de datos \n");		
		
		
			//Libero memoria.
			free(usuario);
			free(clave);
			free(usuario);
			free(clave);
			free(razonSocial);
			free(direccion);
			free(email);
			free(celular);	
			destroyObj(loc);
			destroyObj(cliente);
		}
		else{
			printf("No existe la localidad ingresada");
		}			
	}
	free(cuil);
	system("PAUSE");
}


void modificarCliente(){
	
	const char *menuModificarCliente[] = {"Usuario", "Clave", "Cuil", "Razon Social", "Direccion", "Codigo Postal", "Email", "Celular"};

	printf("Los clientes cargados son: \n");
	mostrarObjetos((void *) Cliente_new);

	char *cuil = leerCadena("Ingrese el cuil \n", MAX20); //20 CARACTERES - Definido en Cliente.h					
	int opcion, codigo = buscarCliente(cuil);

	if(codigo != -1){
		
		obj_Cliente *cliente = Cliente_new();
		cliente->findbykey(cliente, codigo);
		char buffer[MAX560];
		opcion = mostrarMenu(menuModificarCliente, LEN(menuModificarCliente));
		
		switch (opcion){
			
			case 1: {
				char *usuario = leerCadena("Ingrese el nuevo nombre de usuario \n", MAX90);	
				snprintf(buffer, MAX560,"Modifica el nombre del usuario con cuil numero %s a %s", cliente->getCuil(cliente), usuario);
				cliente->setUsuario(cliente, usuario);
				free(usuario);
				break;
			}
				
			case 2:{
				char *clave = leerCadena("Ingrese la nueva clave del usuario \n", MAX120);	
				snprintf(buffer, MAX560,"Modifica la clave del usuario con cuil numero %s de '%s' a '%s' %s", cliente->getCuil(cliente),cliente->getClave(cliente), clave);
				cliente->setClave(cliente, clave);
				
				free(clave);	
				break;
			}
			
			case 3: {
				char *nuevoCuil = leerCadena("Ingrese el nuevo cuil del usuario \n", MAX20);	
				if(buscarCliente(nuevoCuil) == -1){
					snprintf(buffer, MAX560,"Modifica el cuil de '%s' a '%s' %s", cliente->getCuil(cliente), nuevoCuil);
					cliente->setCuil(cliente, nuevoCuil);
					free(nuevoCuil);
				}
				else{
					printf("Ya existe un cliente con ese cuil \n");
					free(nuevoCuil);	
					system("PAUSE");
					return;
				}
				break;
			}
			
			case 4: {
				char *razonSocial = leerCadena("Ingrese la nueva razon social del usuario \n", MAX90);	
				snprintf(buffer, MAX560,"Modifica la razon social del usuario con cuil numero %s de '%s' a '%s' %s", cliente->getCuil(cliente), cliente->getRazonSocial(cliente), razonSocial);
				cliente->setRazonSocial(cliente, razonSocial);
				free(razonSocial);	
				break;	
			}
		
			case 5: {
				char *direccion = leerCadena("Ingrese la nueva direccion del usuario \n", MAX120);	
				snprintf(buffer, MAX560,"Modifica la direccion del usuario con cuil numero %s de '%s' a '%s' %s", cliente->getCuil(cliente), cliente->getDireccion(cliente), direccion);
				cliente->setDireccion(cliente, direccion);
				free(direccion);		
				break;
			} 
			
		
			case 6: {
	
				int codPostal = ingresarCodigo((void *) Localidad_new, "Las localidades registradas son: " );
					
				if(codigo != -1){						
						obj_Localidad *nuevaLocalidad, *localidadAnterior = cliente->getLocalidadObj(cliente);
						nuevaLocalidad->findbykey(nuevaLocalidad,codigo);
						snprintf(buffer, MAX560,"Modifica la localidad del usuario con cuil numero %s de '%s' a '%s'", cliente->getCuil(cliente), localidadAnterior->getNombre(localidadAnterior), nuevaLocalidad->getNombre(nuevaLocalidad));
						cliente->setCodPostal(cliente, codigo);
						destroyObj(localidadAnterior);
				}
				else{
						return;
				}		
				
				break;
			}
			
			case 7: {
				char *email = leerCadena("Ingrese el nuevo mail del usuario \n", MAX90);	
				snprintf(buffer, MAX560,"Modifica el email del usuario con cuil numero %s de '%s' a '%s' %s", cliente->getCuil(cliente), cliente->getEmail(cliente), email);
				cliente->setEmail(cliente, email);
				free(email);	
				break;
			}
			
			case 8: {
				char *celular = leerCadena("Ingrese el nuevo celular del usuario \n", MAX25);	
				cliente->setCelular(cliente, celular);
				snprintf(buffer, MAX560,"Modifica el celular del usuario con cuil numero %s de '%s' a '%s' %s", cliente->getCuil(cliente), cliente->getCelular(cliente), celular);
				free(celular);	
				break;
			}
		
		}
		
		if(cliente->saveObj(cliente) == true){
			printf("Modificacion al cliente realizada con exito \n");
			registrarEvento("Cliente", buffer);
		}
		
		destroyObj(cliente);
	}
	else{
		printf("No existe un cliente con ese numero de cuil \n");
	}
	free(cuil);
	system("PAUSE");
		
}


