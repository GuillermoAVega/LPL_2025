#include "Factura.h"

#define LIMPIAR 1
#define MIN_VAL 0
#define MAX_CODIGO 10000
#define CORTE_INGRESO -1

void cargarFactura(){
	
	static int codigoFactura = 0;
	
	
	int codCliente,codmpago;
	
	//foraneas
	codCliente = ingresarCodigo ( (void *) Cliente_new ,  "Los clientes registrados son: ");
	codmpago = ingresarCodigo ( (void *) MedioPago_new ,  "Los medio de pagos registrados son: ");	
	
	//Solicito valores para registrar la factura.
	int nro = leerEntero("Ingrese el numero de la factura \n",LIMPIAR, MIN_VAL, MAX_CODIGO, CORTE_INGRESO);
	int serie = leerEntero("Ingrese la serie de la factura \n",LIMPIAR, MIN_VAL, MAX_CODIGO, CORTE_INGRESO);
	
	char *letra;
	do{
		letra = leerCadena("Ingrese la letra de la factura: A/B/C \n",MAX1);
	}while (!(letra[0] == 'A' || letra[0] == 'B' || letra[0] == 'C'));
	
	
	char *fecha = getFecha();
	
	obj_Factura *factura = Factura_new();
	
	factura->setCodCliente(factura,codCliente);
	factura->setCodMpago(factura,codmpago);
	factura->setCodigo(factura,codigoFactura++);
	factura->setNro(factura,nro);
	factura->setSerie(factura,serie);
	factura->setLetra(factura,letra);
	factura->setFecha(factura,fecha);
	
	system("pause");
	if(factura->saveObj(factura) == true){
		printf("Ingreso de factura realizado con exito \n");
	}else 
		printf("no");
		
	system("pause");
	free(fecha);
	free(letra);
	destroyObj(factura);
	
}

void modificarFactura(){
}
