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

typedef struct {
	
	int posMedioPago;
	int cantidad;
	
} t_infoMedio;

int cmpInfoMedio(const void *a, const void *b){
	
	t_infoMedio *MedioPagoA=(t_infoMedio *)a;
	t_infoMedio *MedioPagoB=(t_infoMedio *)b;
	return(MedioPagoA->cantidad - MedioPagoB->cantidad) * -1; //Orden descendente. 

}


void listarMpMasUsados(){

	void *lista,*listaFacturas;
	int size = 0, i , j;
	t_infoMedio *mediosPago;
	obj_MedioPago *medio = MedioPago_new(), *itemMedio;
	obj_Factura *factura = Factura_new(), *itemFactura;
	char criterio[MAX_SQL];
	system("cls");
	size = medio->findAll(medio, &lista, "exists(select 1 from factura f where f.cod_mpago = medio_pago.codigo)");
	if (size>0){

		mediosPago = malloc(sizeof(t_infoMedio)*size);
		for (i=0; i<size; ++i){
			itemMedio = ((obj_MedioPago **)lista)[i];
			memset(criterio,'\0',MAX_SQL);//limpiar cadena
			sprintf(criterio,"cod_mpago = %d",itemMedio->getCodigo(itemMedio));
			mediosPago[i].cantidad = factura->findAll(factura,&listaFacturas,criterio);
			mediosPago[i].posMedioPago = i;
			destroyObjList(listaFacturas,mediosPago[i].cantidad); //libera listado de facturas pagadas con ese medio de pago
			}
		qsort(mediosPago,size,sizeof(t_infoMedio),cmpInfoMedio); 
		for (i = 0; i < size && i < 3;++i){
			itemMedio = ((obj_MedioPago **)lista)[mediosPago[i].posMedioPago];
			printf("%s - cant: %d \n",itemMedio->getDescripcion(itemMedio),mediosPago[i].cantidad);
			
		}	
		
		destroyObjList(lista,size); //liberar listado de clientes
	
	}
	
	system("pause");
		
	//libero recursos
	destroyObj(medio);	
	destroyObj(factura);
	free(mediosPago);
}

