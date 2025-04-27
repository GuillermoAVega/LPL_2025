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


#define MAX_NOM 90
#define MAX_CLAVE 120
#define MAX_CUIL 20
#define MAX_RAZON_SOCIAL 90
#define MAX_DIR 120
#define MAX_EMAIL 90
#define MAX_CELULAR 25
#define MAX_DESCRIPCION 80


const char *menuIngresos[] = {"Localidad", "Marca", "Producto", "Cliente", "Sucursal", "Factura", "Detalle Factura", "Sucursal destino", "Salir"}; //MODIFICAR SUCURSAL DESTINO.


//Implementado por franco y emi.
void cargarMarcas(){
};
void cargarSucursal(){
};
void cargarFactura(){
};
void cargarDetalleFactura(){
};
void cargarSucursalDest(){
};



	



void cargarLocalidad(){
	
	int codPostal = leerEntero("Ingrese el codigo postal de la localidad \n",1,  0, 10000, -1);	

	obj_Localidad *loc = Localidad_new();
	
	if(loc->findbykey(loc, codPostal) == NOT_FOUND){
		system("cls");
		
		char *nombre = leerCadena("Ingrese el nombre de la localidad \n", 60); //PONER CONSTANTE.

		loc-> setCodpostal(loc, codPostal);
		loc-> setNombre(loc, nombre);

		if(loc->saveObj(loc) == true)
			printf("Ingreso de localidad realizado con exito \n");
			
		free(nombre);
	}
	else{
		printf("Ya existe una localidad con ese codigo postal \n");
	}				
	destroyObj(loc);
}


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


void cargarProducto(){
	
	int codMarca, codCategoria;
	obj_Marca *marca = Marca_new(); 
	
	
	codMarca = ingresarCodigo ( (void *) Marca_new ,  "Las marcas registradas son: ");		
	codCategoria = ingresarCodigo( (void *) Categoria_new, "Las categorias registradas son: " );

	//Solicito valores para registrar el producto.
	char *descripcion = leerCadena("Ingrese la descripcion \n", MAX_DESCRIPCION);  //80 CARACTERES	
	float precio = leerFloat("Ingrese el precio del producto \n");
	float stock = leerFloat("Ingrese el stock del producto \n");
	bool disponible = confirma("El producto esta disponible?");
	
	static int codigo = 0;
	
	obj_Producto *producto = Producto_new();
	
	producto->setCodMarca(producto, codMarca);
	producto->setCodCategoria(producto, codCategoria);
	producto->setCodigo(producto, codigo++);
	producto->setDescripcion(producto, descripcion);
	producto->setPrecio(producto, precio);
	producto->setStock(producto, stock);
	producto->setDisponible(producto, disponible);
	
	if(producto->saveObj(producto) == true)
		printf("Ingreso del producto realizado con exito \n");
		
	destroyObj(producto);

	
	free(descripcion);
	
}

void cargarCliente(){
	static int codigo = 0;
	codigo++;
	
	//Pido los datos.
	char *usuario = leerCadena("Ingrese el nombre del usuario \n", MAX_NOM); // 90 CARACTERES - Definido en Cliente.h
	char *clave = leerCadena("Ingrese la clave \n", MAX_CLAVE);  //120 CARACTERES - Definido en Cliente.h
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
	
	char *cuil = leerCadena("Ingrese el cuil \n", MAX_CUIL); //20 CARACTERES - Definido en Cliente.h	
	char *razonSocial = leerCadena("Ingrese la razon social \n", MAX_RAZON_SOCIAL); //90 CARACTERES - Definido en Cliente.h 
	char *direccion = leerCadena("Ingrese la direccion \n", MAX_DIR); //120 CARACTERES - Definido en Cliente.h
	char *email = leerCadena("Ingrese el mail \n", MAX_EMAIL); //90 CARACTERES - Definido en Cliente.h 
	char *celular = leerCadena("Ingrese el numero de telefono \n", MAX_CELULAR); //25 CARACTERES - Definidos en Cliente.h
	

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
};








void gestionarIngresos(){
	
  	int opcion = mostrarMenu(menuIngresos, LEN(menuIngresos));
  	system("cls");
	switch(opcion){
		case 1:
			cargarLocalidad();
			break;
		
		case 2:
			cargarMarcas();
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
	system("PAUSE");
}



