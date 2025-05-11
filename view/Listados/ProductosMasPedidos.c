#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../includes/includes.h"
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_PRODUCTOS 10

typedef struct{
	
	int posProducto;
	int cantidad;
	
}t_infoProducto;


int cmpInfoProducto(const void *a, const void *b){
	
	t_infoProducto *productoA=(t_infoProducto *)a;
 	t_infoProducto *productoB=(t_infoProducto *)b;
	return (productoA->cantidad - productoB->cantidad ) * -1; //desc 
	
}


void listProdMasPedidos(){
	
	void *list,*listDetFact;
	int size=0, i, j;
	int k, cantDetalles;
	
	t_infoProducto *productos;
	
	
	obj_Producto *producto = Producto_new(), *itemProducto;
	obj_DetFactura *detFactura = DetFactura_new(),*itemDetFact;
	
	char criterio[MAX_SQL];
	
	system("cls");
			
	size = producto->findAll(producto,&list," exists(select 1 from det_factura df where df.cod_producto=producto.codigo)");	
	if(size>0)
	  {	
		productos = malloc(sizeof(t_infoProducto)*size);
		
	  	for(i=0;i<size;++i)
	  	{
	  		itemProducto = ((obj_Producto **)list)[i];
			
			memset(criterio,'\0',MAX_SQL);
			
			sprintf(criterio,"cod_producto = %d",itemProducto->getCodigo(itemProducto));	
			
	  	  	cantDetalles = detFactura->findAll(detFactura,&listDetFact,criterio);
	  	  	productos[i].cantidad = 0;
	  	  	productos[i].posProducto = i;
	  	  	
	  	  	for(j = 0; j < cantDetalles; j++){
	  	  		
	  	  		itemDetFact = ((obj_DetFactura **)listDetFact)[j];		
				productos[i].cantidad += itemDetFact->getCantidad(itemDetFact); 
	  	  	
			}
	  	  	
	  	  	destroyObjList(listDetFact,cantDetalles);
		}
		
		qsort(productos,size,sizeof(t_infoProducto),cmpInfoProducto);
		
		for(k=0;k<size;k++)
		{
			itemProducto = ((obj_Producto **)list)[k];
			if(k < MAX_PRODUCTOS){
				printf("%s  - cant: %d \n",itemProducto->getDescripcion(itemProducto),productos[k].cantidad);	
			}
		}
		destroyObjList(list,size);
	  }	
	  
	  destroyObj(producto);
	  destroyObj(detFactura);
	  free(productos);
	  
	
	system("PAUSE");
}
