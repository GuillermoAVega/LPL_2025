#include "Detalle_Factura.h"


void cargarDetalleFactura(){
	int codigoFactura = ingresarCodigo ( (void *) Factura_new ,  "Las facturas registrados son: ");
 	obj_Factura *factura = Factura_new();
	
	if(factura->findbykey(factura, codigoFactura) != NOT_FOUND){
		int renglon = 0; //comenzamos en 1 el renglon o en 0?
		do{
			//pido datos	
			int codProducto = ingresarCodigo ( (void *) Producto_new ,  "Los productos registrados son: ");
			if(codProducto == -1)
				return;		
			float precio = leerFloat("Ingrese el precio del producto: \n");
			int cantidad = leerEntero("Ingrese la cantidad del producto: \n",0,0,10000,-1);
			
			//creo el objeto
			obj_DetFactura *detalleFactura = DetFactura_new();
			
			//set
			detalleFactura->setCodFactura(detalleFactura,codigoFactura);
			detalleFactura->setRenglon(detalleFactura,renglon++);
			detalleFactura->setCodProducto(detalleFactura,codProducto);
			detalleFactura->setPrecioUnit(detalleFactura,precio);
			detalleFactura->setCantidad(detalleFactura,cantidad);
			
			//libera
			destroyObj(detalleFactura);
			
		}while(confirma("Desea ingresar otro producto? s/n"));
		destroyObj(factura);
	}else{
		printf("La factura ingresada no esta registrada \n");
		return;
	}
}


void modificarDetalleFactura(){
}
