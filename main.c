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

const char *menuPrincipal[] = {"Ingresos", "Actualizaciones", "Listados"};

int main(int argc, char *argv[])
{  
  if(!init_config(argv[POS_CONFIG]))
  	 exit(-1);  

  int opcion = 0; 
  
  do{
  	
	opcion = mostrarMenu(menuPrincipal, LEN(menuPrincipal));
	  
	  switch (opcion){
	  	
	  	case 1: 
			gestionarIngresos();
			
	  		break;
	  	
	  	case 2: 
	  		gestionarActualizaciones(); //VA DENTRO - opcion = mostrarMenu(menuActualizaciones, LEN(menuActualizaciones));		
	  		break;
	  		
	  	
	  	case 3: 
	  		gestionarListados(); //VA DENTRO - opcion = mostrarMenu(menuListados, LEN(menuListados));

	  		break;
	  		
	  	}	
	  	
  } while(opcion != -1);
  
  
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
  //system("PAUSE");
  return 0;
}
