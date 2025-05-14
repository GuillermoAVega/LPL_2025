#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/includes.h"

void mostrarAuditoria(){
	
	const char *menuMostrarRegistros[] = {"Cliente", "Producto", "Sucursal"};
	
	int size,i, opcion = 0; 
	void *item, *list;
  		
  	opcion = mostrarMenu(menuMostrarRegistros, LEN(menuMostrarRegistros));  
  	obj_Auditoria *auditoria = Auditoria_new();
  	
	switch (opcion){
  	
  		case 1: 
			size = auditoria->findAll(auditoria,&list,"objeto = 'Cliente'");
  			break;
  	
  		case 2: 
  			size = auditoria->findAll(auditoria,&list,"objeto = 'Producto'");
			break;
  	
  		case 3: 
			size = auditoria->findAll(auditoria,&list,"objeto = 'Sucursal'");
  			break;
  		
  	}	
  	
  	for(i=0;i<size;++i){
    	item = ((Object **)list)[i];    
        char *str = ((Object *)item)->toString(item);
  		printf("%s", str);
		free(item);	
	}
	
	system("PAUSE");
}
