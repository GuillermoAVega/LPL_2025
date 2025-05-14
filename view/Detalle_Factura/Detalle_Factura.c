#include "Detalle_Factura.h"


void cargarDetalleFactura(){
	int codigoFactura = ingresarCodigo ( (void *) Factura_new ,  "Las facturas registrados son: ");
 	obj_Factura *factura = Factura_new();
	
	if(factura->findbykey(factura, codigoFactura) != NOT_FOUND){
		
		//Enumera el renglon.
		void *list;
		char criterio[MAX_SQL];
		snprintf(criterio, MAX_SQL, "cod_factura = %d", codigoFactura);
		int renglon = (factura->findAll(factura,&list, criterio)) + 1;
		
		do{
			int reintentar = 1;
			int cantidad; //cantidad del producto
			obj_Producto *producto = Producto_new();
			int codProducto = ingresarCodigo ( (void *) Producto_new ,  "Los productos registrados son: ");
			
			if(codProducto != -1){		
			
				if (producto->findbykey(producto,codProducto)!= NOT_FOUND){
			
					if (producto->getStock(producto) == 0){
						printf("No hay stock disponible \n");
						system("PAUSE");
						continue;
					}
					
					int disponible  = 0;
					
					do{ 
						cantidad = leerEntero("Ingrese la cantidad del producto: \n", 1 ,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
						
						if (cantidad <= producto->getStock(producto)){ //se verifica que la cantidad no supere el stock disponible
							disponible = 1;
							producto->setStock(producto,producto->getStock(producto)-cantidad); //actualizamos el stock del producto
							producto->saveObj(producto);
						}
					}while(disponible != 1 && (reintentar = confirma("Desea ingresar este producto? s/n")));
				}
	
				if(reintentar == 1){
					
					//creo el objeto
					obj_DetFactura *detalleFactura = DetFactura_new();
					
					//set
					detalleFactura->setPrecioUnit(detalleFactura,producto->getPrecio(producto));
					detalleFactura->setCantidad(detalleFactura,cantidad);
					detalleFactura->setCodFactura(detalleFactura,codigoFactura);
					detalleFactura->setRenglon(detalleFactura,renglon++);
					detalleFactura->setCodProducto(detalleFactura,codProducto);
					
					if(detalleFactura->saveObj(detalleFactura) == true)
						printf("Ingreso del detalle realizado con exito \n");
									
				}
			}
			
		}while(confirma("Desea ingresar otro producto? s/n"));
		
		factura->destroyInternal(factura);
		destroyObj(factura);
	}

}


void modificarDetalleFactura(){
	const char *menuModificarDetalleFactura[] = {"Producto", "Cantidad"};
	
	int codFactura = ingresarCodigo((void *) Factura_new, "Ingrese el codigo de la factura que desea modificar \n");	
	
	if (codFactura != -1){
		
		obj_Factura *factura = Factura_new();
		
		if(factura->findbykey(factura, codFactura)){
			int opcion;
			
			//No usar ingresarCodigo sino que implementar algo para poder ver los detalle factura asociados a la factura.
						
			int renglon = ingresarCodigo((void *)  DetFactura_new, "Ingrese el numero del renglon que desea modificar \n");	
			
			if (renglon == -1)
				return;
			obj_DetFactura *detalleFactura = DetFactura_new();
			opcion=mostrarMenu(menuModificarDetalleFactura, LEN(menuModificarDetalleFactura));
			
			if (detalleFactura->findbykey(detalleFactura,renglon) == true){
				switch(opcion){
					case 1:{
						int codProducto = ingresarCodigo((void *) Producto_new, "Ingrese el codigo del producto que desea agregar \n");
						if (codProducto == -1)
							return;
						obj_Producto *producto = Producto_new();
						if(producto->findbykey(producto,codProducto)){
						//consulta si hay stock del producto, sino termina
							if (producto->getStock(producto) == 0){
								printf("No hay stock disponible \n");
								return;
							}
							int disponible,cantidad = 0;
							do{
								cantidad = leerEntero("Ingrese la cantidad del producto: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
						
								if (cantidad < producto->getStock(producto)){ //se verifica que la cantidad no supere el stock disponible
									disponible = 1;
									producto->setStock(producto,producto->getStock(producto)-cantidad); //actualizamos el stock del producto
								}
							}while(disponible == 1 || confirma("Desea ingresar este producto? s/n"));
							//set
							detalleFactura->setCantidad(detalleFactura,cantidad);
							detalleFactura->setCodProducto(detalleFactura,codProducto);
						}
						destroyObj(producto);
						break;
					}
					case 2:{
						int codProducto = detalleFactura->getCodProducto(detalleFactura);
						obj_Producto *producto = Producto_new();
						const char *menuAgregaQuita[] = {"Agregar productos","Quitar productos"};
						int respuesta = mostrarMenu(menuAgregaQuita, LEN(menuAgregaQuita));
						if (producto->findbykey(producto,codProducto)){
							switch(respuesta){
								case 1:{
									int agrega,cantidad = detalleFactura->getCantidad(detalleFactura);		
									do{
										agrega = leerEntero("Ingrese la cantidad que desea agregar: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
									}while(agrega + cantidad < producto->getStock(producto));
									detalleFactura->setCantidad(detalleFactura,cantidad+agrega);
									producto->setStock(producto,producto->getStock(producto)-(cantidad + agrega)); //actualizamos el stock del producto
									break;	
								}
								case 2: {
									int quita, cantidad = detalleFactura->getCantidad(detalleFactura);
									do{
										quita = leerEntero("Ingrese la cantidad que desea quitar: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
									}while(quita < cantidad);
									detalleFactura->setCantidad(detalleFactura,cantidad-quita);
									producto->setStock(producto,producto->getStock(producto)+quita); //actualizamos el stock del producto
									break;
								}
							}
						}
						destroyObj(producto);
						break;
					}
				}
			}
			if(detalleFactura->saveObj(detalleFactura)==true)
				printf("Cambios realizados con exito \n");
			system("PAUSE");
			destroyObj(detalleFactura);
	}

	
	
	}
}

