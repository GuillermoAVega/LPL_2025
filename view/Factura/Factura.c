#include "Factura.h"


void cargarFactura(){
	static int codigoFactura = 0;
	
	
	int codCliente,codmpago;
	
	//foraneas
	codCliente = ingresarCodigo ( (void *) Cliente_new ,  "Los clientes registrados son: ");
	codmpago = ingresarCodigo ( (void *) MedioPago_new ,  "Los medio de pagos registrados son: ");	
	
	//Solicito valores para registrar la factura.
	int nro = leerEntero("Ingrese el numero de la factura \n",0,0,10000,-1);
	int serie = leerEntero("Ingrese la serie de la factura \n",0,0,10000,-1);
	
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

	if(factura->saveObj(factura) == true){
		printf("Ingreso de factura realizado con exito \n");
	}else 
		printf("no");
		
	system("PAUSE");
	free(fecha);
	free(letra);
	destroyObj(factura);

}

void modificarFactura(){
	const char *menuModificarFactura[] = {"Nro", "Serie", "Letra", "Fecha", "Codigo del cliente", "Codigo del medio de pago"};
	int opcion;
	int codFactura = ingresarCodigo((void *) Factura_new, "Ingrese el codigo de la factura que desea modificar \n");	
	if (codFactura == -1)
		return;
	
	opcion=mostrarMenu(menuModificarFactura, LEN(menuModificarFactura));
	obj_Factura *factura = Factura_new();
	factura->findbykey(factura, codFactura);
	
	switch (opcion){
		case 1:{
			int nro = leerEntero("Ingrese el nuevo numero de la factura \n",0,0,10000,-1);
			factura->setNro(factura,nro);
			break;
		}
		case 2:{
			int serie = leerEntero("Ingrese la nueva serie de la factura \n",0,0,10000,-1);
			factura->setSerie(factura,serie);
			break;
		}
		case 3:{
			char *letra;
			do{
				letra = leerCadena("Ingrese la letra de la factura: A/B/C \n",MAX1);
			}while (!(letra[0] == 'A' || letra[0] == 'B' || letra[0] == 'C'));
			factura->setLetra(factura,letra);
			break;
		}
		case 4:{
			char *fecha=getFecha();
			factura->setFecha(factura,fecha);
			free(fecha);
			break;
		}
		case 5:{
			int codCliente = ingresarCodigo(*(*Cliente_new),"Los clientes registrados son: ");
			if (codCliente == -1)
				return;
			factura->setCodCliente(factura,codCliente);
			break;
		}
		case 6:{
			int codMpago = ingresarCodigo(*(*MedioPago_new),"Los clientes registrados son: ");
			if (codMpago == -1)
				return;
			factura->setCodMpago(factura,codMpago);
			break;
		}	
	}
	
	if(factura->saveObj(factura) == true)
		printf("Modificacion al cliente realizada con exito \n");
	destroyObj(factura);
	system("PAUSE");
	
}

