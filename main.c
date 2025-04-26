#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "includes/includes.h"

#define LEN(x) (sizeof(x) / sizeof(x[0]))

const char *menuPrincipal[] = {"Ingresos", "Actualizaciones", "Listados", "Salir"};
const char *menuIngresos[] = {"Localidad", "Marca", "Producto", "Cliente", "Sucursal", "Factura", "Detalle Factura", "Sucursal destino", "Salir"}; //MODIFICAR SUCURSAL DESTINO.
const char *menuActualizaciones[] = {"Localidad", "Marca", "Producto", "Cliente", "Sucursal", "Factura", "Detalle Factura", "Sucursal destino", "Salir"}; //MODIFICAR SUCURSAL DESTINO.
const char *menuListados[] = {"Clientes", "Productos", "Medios de pago mas usados", "Productos mas pedidos", "Salir"};



int main(int argc, char *argv[])
{  
  if(!init_config(argv[POS_CONFIG]))
  	 exit(-1);  

  int respuesta, i = mostrarMenu(menuPrincipal, LEN(menuPrincipal));
  
  switch (i){
  	
  	case 1: 
  		respuesta = mostrarMenu(menuIngresos, LEN(menuIngresos));
		
		if(respuesta == 1){  //DEBERIA SER UN SWITCH, SOLO PARA PROBAR.
			
			ingresarLocalidad();
			
		}
 		
		
  		break;
  	
  	case 2: 
  		respuesta = mostrarMenu(menuActualizaciones, LEN(menuActualizaciones));		
  		break;
  		
  	
  	case 3: 
  		respuesta = mostrarMenu(menuListados, LEN(menuListados));
  		break;
  		
  		
  }
  
  
  // ejemplo para agregar Localidad nueva.
  
  
  //setDebug(true); DESCOMENTAR.
  
  
  // ejemplo para listar todas las localidades en el sistema
  
  /* DESCOMENTAR
  obj_Cliente *cli = Cliente_new();

  obj_Localidad *loc;  
  void *list,*itm;
  int i=0,size=0, sizeEnf=0;
  */
  
  //cli->getLocalidadObj(cli); 
  /*  
  size = cli->findAll(cli,&list,NULL);    
  for(i=0;i<size;++i)
  {
    itm = ((Object **)list)[i];    
    ((Object *)itm)->toString(itm);
  }
  destroyObjList(list,size);
  destroyObj(cli);
  */  
 
  /* DESCOMENTAR.
  loc = Localidad_new();    
  size = loc->findAll(loc,&list,NULL);    
  for(i=0;i<size;++i)
  {
    itm = ((Object **)list)[i];    
    ((Object *)itm)->toString(itm);
  }
  destroyObjList(list,size);
  destroyObj(loc);
  */
  
  
  
  //int i = leerOpcionLoc("Las localidades son:", 0, -1);  EJEMPLO DE GUILLE.
  
  //i=leerEntero("Ingrese edad\n[-1 - corta ingreso]:",true,10,40,-1); DESCOMENTAR.
  
  
  //printf("Nro leido:%d\n",i);
  //i=leerOpcionLoc("ingrese CP:",true, false);
  /*
  loc = Localidad_new();    
  size = loc->findAll(loc,&list,NULL);    
  for(i=0;i<size;++i)
  {
    itm = ((Object **)list)[i];    
    ((Object *)itm)->toString(itm);
  }
  destroyObjList(list,size);
  destroyObj(loc);
  */
  system("PAUSE");
  return 0;
}
