#include "Detalle_Factura.h"


int ingresarRenglon(int codigoFactura){   
	obj_DetFactura *detalle = DetFactura_new();
	void *list, *item;
	int renglon = -1;
	int i = 0; 
	char criterio[MAX_SQL];
	sprintf(criterio, "exists(select 1 from factura f where det_factura.cod_factura = %d)",codigoFactura);
	
	int size = detalle->findAll(detalle,&list, criterio);    
	
	for(i=0;i<size;++i)
	{
		item = ((Object **)list)[i];
		char *str = ((Object *)item)->toString(item);
		printf("%s \n",str);
		free(str);
	}
		
	renglon= leerEntero("Ingrese el numero del renglon: \n",0,1,1000,-1);
    
	destroyObjList(list,size);
    destroyObj(detalle);
	return renglon;
}


void cargarDetalleFactura(){
	int codigoFactura = ingresarCodigo ( (void *) Factura_new ,  "Las facturas registrados son: ");
	
	if(codigoFactura != -1){
			
	 	obj_Factura *factura = Factura_new();
		factura->findbykey(factura, codigoFactura);
			
		int renglon = ingresarRenglon(codigoFactura);
		
		if(renglon != -1){
			do{
				int reintentar = 1;
				
				int cantidad; //cantidad del producto
				
				obj_Producto *producto = Producto_new();
				
				int codProducto = ingresarCodigo ( (void *) Producto_new ,  "Los productos registrados son: ");
				
				if(codProducto != -1){		
				
					producto->findbykey(producto,codProducto);
				
					if (producto->getStock(producto) == 0){
						printf("No hay stock disponible \n");
						system("PAUSE");
						continue;
					}
					
					int disponible  = 0;
					
					do{ 
						cantidad = leerEntero("Ingrese la cantidad del producto: \n", FALSE , MIN_VAL, MAX_CODIGO, CORTE_INGRESO);
						
						if (cantidad <= producto->getStock(producto) && cantidad > 0){ //se verifica que la cantidad no supere el stock disponible
							disponible = 1;
							producto->setStock(producto,producto->getStock(producto)-cantidad); //actualizamos el stock del producto
							producto->saveObj(producto);
						}
						else{
							printf("La cantidad es invalida \n");
						}
						
					}while(disponible != 1 && (reintentar = confirma("Desea ingresar este producto? s/n")));
					
		
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
			
		}
		
		factura->destroyInternal(factura);
		destroyObj(factura);
	}
}


void modificarDetalleFactura(){
	const char *menuModificarDetalleFactura[] = {"Producto", "Cantidad"};
	
	int codFactura = ingresarCodigo((void *) Factura_new, "Ingrese el codigo de la factura que desea modificar \n");	
	
	if (codFactura != -1){
		
		obj_Factura *factura = Factura_new();
		obj_DetFactura *detalleFactura;
		
		factura->findbykey(factura, codFactura); //QUITAR.
		int opcion;
		
		int renglon = ingresarRenglon(codFactura); 
		
		if (renglon != -1){
			
			detalleFactura = DetFactura_new();
			obj_Producto *producto;
			opcion = mostrarMenu(menuModificarDetalleFactura, LEN(menuModificarDetalleFactura));
			
			if (detalleFactura->findbykey(detalleFactura,renglon) == true){
				switch(opcion){
					case 1:{
						int codProducto = ingresarCodigo((void *) Producto_new, "Ingrese el codigo del producto que desea agregar \n");
					
						if (codProducto != -1){		
							obj_Producto *producto = Producto_new();
							producto->findbykey(producto, codProducto);
							
							//consulta si hay stock del producto, sino termina
							if (producto->getStock(producto) == 0){
								printf("No hay stock disponible \n");
								return;
							}
							
							int disponible, cantidad = 0;
							
							do{
								cantidad = leerEntero("Ingrese la cantidad del producto: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
						
								if (cantidad < producto->getStock(producto)){ //se verifica que la cantidad no supere el stock disponible
									disponible = 1;
									producto->setStock(producto,producto->getStock(producto)-cantidad); //actualizamos el stock del producto
								}
								
							} while(disponible != 1 && confirma("No se posee stock suficiente para la cantidad solicitada. Desea reintentarlo? s/n"));
							
							//set
							detalleFactura->setCantidad(detalleFactura,cantidad);
							detalleFactura->setCodProducto(detalleFactura,codProducto);
							destroyObj(producto);
						}
						else{
							return;
						}
						break;
					}
					case 2:{
						int codProducto = detalleFactura->getCodProducto(detalleFactura);
						
						producto = Producto_new();
						
						const char *menuAgregaQuita[] = {"Agregar productos","Quitar productos"};
						
						int respuesta = mostrarMenu(menuAgregaQuita, LEN(menuAgregaQuita));
						
						producto->findbykey(producto,codProducto);
						
						switch(respuesta){
							
							case -1:
								return;
								break;
			
							case 1:
							{
								int agrega,cantidad = detalleFactura->getCantidad(detalleFactura);		
								do{
									agrega = leerEntero("Ingrese la cantidad que desea agregar: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
								}while(agrega + cantidad < producto->getStock(producto));
								detalleFactura->setCantidad(detalleFactura,cantidad+agrega);
								producto->setStock(producto,producto->getStock(producto)-(cantidad + agrega)); //actualizamos el stock del producto
								break;	
							}
							case 2: 
							{
								int quita, cantidad = detalleFactura->getCantidad(detalleFactura);
								do{
									quita = leerEntero("Ingrese la cantidad que desea quitar: \n",LIMPIAR,MIN_VAL,MAX_CODIGO,CORTE_INGRESO);
								}while(quita < cantidad);
								detalleFactura->setCantidad(detalleFactura,cantidad-quita);
								producto->setStock(producto,producto->getStock(producto)+quita); //actualizamos el stock del producto
								break;
							}
						}
						destroyObj(producto);
						break;
					}
				}
			}	
		}
			
		if(detalleFactura->saveObj(detalleFactura)==true)
			printf("Cambios realizados con exito \n");
		system("PAUSE");
		destroyObj(detalleFactura);
	}
}

