#include "Detalle_Factura.h"

Object *buscarDetalle(int codFactura, int renglon){

	obj_DetFactura *detalle = DetFactura_new();
	void *list, *item;
	char criterio[MAX_SQL];
	
	sprintf(criterio, "exists(select 1 from factura f where (det_factura.cod_factura = %d  ) AND (det_factura.renglon = %d))", codFactura, renglon);
	int size = detalle->findAll(detalle, &list, criterio);    

	return ((Object **)list)[0];
}


int ingresarRenglon(int codigoFactura){   
	obj_DetFactura *detalle = DetFactura_new();
	void *list, *item;
	int renglon = 0;
	int i = 0; 
	char criterio[MAX_SQL];
	
	sprintf(criterio, "exists(select 1 from factura f where %d=det_factura.cod_factura)", codigoFactura);
	int size = detalle->findAll(detalle, &list, criterio);    

	for(i = 0; i < size; ++i) {
		item = ((Object **)list)[i];
		char *str = ((Object *)item)->toString(item);
		printf("%s \n", str);
		free(str);
	}  

	renglon = leerEntero("Ingrese el numero del renglon: \n", LIMPIAR, MIN_VAL,MAX_CODIGO,CORTE_INGRESO);

	int encontrado = 0;
	for(i = 0; i < size; ++i) {
		item = ((Object **)list)[i];
		int renglonActual = ((obj_DetFactura *)item)->getRenglon(item);
		if (renglon == renglonActual) {
			encontrado = 1;
			break;
		}
	}
	if (!encontrado) {
		printf("El numero de renglon ingresado no existe en los detalles de esta factura.\n");
		renglon = -1; 
		system("pause");
	}

	destroyObj(detalle);

	return renglon;
}

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
						cantidad = leerEntero("Ingrese la cantidad del producto: \n", LIMPIAR ,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
						
						if (cantidad <= producto->getStock(producto) && cantidad > 0){ //se verifica que la cantidad no supere el stock disponible
							disponible = 1;
							producto->setStock(producto,producto->getStock(producto)-cantidad); //actualizamos el stock del producto
							producto->saveObj(producto);
						}else{
							printf("La cantidad no es valida \n");
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
					
					if(detalleFactura->saveObj(detalleFactura) != NOT_FOUND)
						printf("Ingreso del detalle realizado con exito \n");
					system("PAUSE");
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
		obj_Producto *producto;
		if(factura->findbykey(factura, codFactura)){
			int opcion = 0;
						
			int renglon = ingresarRenglon(codFactura);	
			
			if (renglon != -1){
				
				system("CLS");
				
				obj_DetFactura *detalleFactura = DetFactura_new();
				void *list, *item;
				char criterio[MAX_SQL];
				
				sprintf(criterio, "exists(select 1 from factura f where (det_factura.cod_factura = %d  ) AND (det_factura.renglon = %d))", codFactura, renglon);
				int size = detalleFactura->findAll(detalleFactura, &list, criterio);    
			
				detalleFactura = ((Object **)list)[0];
				
				opcion=mostrarMenu(menuModificarDetalleFactura, LEN(menuModificarDetalleFactura));
				
				switch(opcion){
					
					case -1:{
						return;
						break;
					}
					
					case 1:{
						producto = Producto_new();
						
						int codProducto = ingresarCodigo((void *) Producto_new, "Ingrese el codigo del producto que desea agregar \n");
						if (codProducto == -1)	
							return;
						
						producto->findbykey(producto,codProducto);
						
						int stockProducto = producto->getStock(producto); 
						
						//consulta si hay stock del producto, sino termina
						if (stockProducto == 0){
							printf("No hay stock disponible \n");
							system("pause");
							return;
						}
						
						int cantidad = leerEntero("Ingrese la cantidad del producto: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
				
						if (cantidad <= stockProducto){ //se verifica que la cantidad no supere el stock disponible
							obj_Producto *productoFactura = detalleFactura->getProductoObj(detalleFactura);//creo este producto para devolver el stock 
							
							int stockProductoAnterior = detalleFactura->getCantidad(detalleFactura) + productoFactura->getStock(productoFactura);
							
							productoFactura->setStock(productoFactura, stockProductoAnterior);
							
							if(productoFactura->saveObj(productoFactura)!= NOT_FOUND)
								printf("Se actualizo el stock del producto anterior \n");
							
							producto->setStock(producto, producto->getStock(producto) - cantidad); //actualizamos el stock del producto
							
							detalleFactura->setCantidad(detalleFactura, cantidad);
							detalleFactura->setCodProducto(detalleFactura, codProducto);
						}
						else{
							printf("No se posee el stock suficiente para realizar la modificacion \n");
							system("pause");
							return;
						}
						break;
					}
		
					case 2:{
						int codProducto = detalleFactura->getCodProducto(detalleFactura);
						
						producto = Producto_new();
						
						const char *menuAgregaQuita[] = {"Agregar mas cantidad","Disminuir cantidad"};
						
						int respuesta = mostrarMenu(menuAgregaQuita, LEN(menuAgregaQuita));
						
						producto->findbykey(producto,codProducto);
						
						switch(respuesta){
							case -1:{
								return;
								break;
							}
							case 1:{
								int agrega = 0,cantidad = detalleFactura->getCantidad(detalleFactura);		
								do{
									agrega = leerEntero("Ingrese la cantidad que desea agregar: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
								}while(agrega <= producto->getStock(producto));
								detalleFactura->setCantidad(detalleFactura,(cantidad+agrega));
								producto->setStock(producto,producto->getStock(producto)-agrega); //actualizamos el stock del producto
								break;	
							}
							case 2: {
								int quita, cantidad = detalleFactura->getCantidad(detalleFactura);
								do{
									quita = leerEntero("Ingrese la cantidad que desea quitar: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
								}while(quita <= cantidad);
								detalleFactura->setCantidad(detalleFactura,cantidad-quita);
								producto->setStock(producto,producto->getStock(producto)+quita); //actualizamos el stock del producto
								break;
							}
						}
						break;
					}
				}
				
				setDebug(1);
				
				system("pause");
				
				if (producto->saveObj(producto)!=NOT_FOUND)
					printf("Cantidad del producto modificada con exito\n");
				destroyObj(producto);

				if(detalleFactura->saveObj(detalleFactura) != NOT_FOUND)
					printf("Cambios realizados con exito \n");
				system("PAUSE");
				destroyObj(detalleFactura);
				destroyObjList(list, size);
			}		
		}	
	}
}

