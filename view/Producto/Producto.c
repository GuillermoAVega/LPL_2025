#include "Producto.h"


void cargarProducto(){
	static int codigo = 0;
	int codMarca, codCategoria;
	
	codMarca = ingresarCodigo((void *) Marca_new ,  "Las marcas registradas son: ");	
	
	if(codMarca != -1){
		
		codCategoria = ingresarCodigo((void *) Categoria_new, "Las categorias registradas son: " );

		if(codCategoria != -1){
			
			//Solicito valores para registrar el producto.
			char buffer[MAX560];
			char *descripcion = leerCadena("Ingrese la descripcion \n", MAX80);  //80 CARACTERES	
			system("cls");
			float precio = leerFloat("Ingrese el precio del producto \n",1,1,1000000.00, -1);
			float stock = leerFloat("Ingrese el stock del producto \n", 1,1,1000000.00,-1);
			bool disponible = confirma("El producto esta disponible? s/n");
			
			//Cargo los valores en el objeto.
			obj_Producto *producto = Producto_new();
			producto->setCodMarca(producto, codMarca);
			producto->setCodCategoria(producto, codCategoria);
			producto->setCodigo(producto, codigo++);
			producto->setDescripcion(producto, descripcion);
			producto->setPrecio(producto, precio);
			producto->setStock(producto, stock);
			producto->setDisponible(producto, disponible);
			
			//Cargo el objeto en la BD.
			if(producto->saveObj(producto) == true){
				
				printf("Ingreso del producto realizado con exito \n");
				obj_Marca *marca = producto->getMarcaObj(producto);
				obj_Categoria *categoria = producto->getCategoriaObj(producto);
				
				snprintf(buffer, MAX560, "Crea el producto con codigo = %d, descripcion = %s, marca = %s, categoria = %s"
						,producto->getCodigo(producto)
						,producto->getDescripcion(producto)
						,marca->getDescripcion(marca)
						,categoria->getDescripcion(categoria));
				
				registrarEvento("Producto", buffer);
			}
			
			system("PAUSE");
			producto->destroyInternal(producto);
			destroyObj(producto);
			free(descripcion);
		}
	}
}


void modificarProducto(){
	const char *menuModificarProducto[] = {"Descripcion", "Categoria", "Marca", "Precio", "Stock", "Disponibilidad"};
	int codigo, opcion;

	printf("Los productos cargados son:");
	codigo = ingresarCodigo((void *) Producto_new, "");	
	
	obj_Producto *producto = Producto_new();
	producto->findbykey(producto,codigo);
	
	char buffer[MAX560];
	
	if (codigo != -1){
		
		opcion = mostrarMenu(menuModificarProducto, LEN(menuModificarProducto));
		system("cls");
		
		switch (opcion){	
				case 1:{
					char *descripcion = leerCadena("Ingrese la nueva descripcion del producto \n", MAX80);
					snprintf(buffer, MAX560,"Modifica la descripcion del producto nro %d de %s a %s", producto->getCodigo(producto), producto->getDescripcion(producto), descripcion);
					producto->setDescripcion(producto, descripcion);
					free(descripcion);
					break;
				}
						
				case 2:{
					int codigo = ingresarCodigo((void *) Categoria_new, "");

					if(codigo != -1){
						obj_Categoria *nuevaCategoria, *categoriaAnterior = producto->getCategoriaObj(producto);
						nuevaCategoria->findbykey(nuevaCategoria,codigo);
						snprintf(buffer, MAX560,"Modifica la categoria del producto numero %d de '%s' a '%s'", producto->getCodigo(producto), categoriaAnterior->getDescripcion(categoriaAnterior), nuevaCategoria->getDescripcion(nuevaCategoria));
						producto->setCodCategoria(producto, codigo);
				
						destroyObj(categoriaAnterior);
					}
					else{
						return;
					}
					
					break;
				}
					
				case 3:{
					int codigo = ingresarCodigo((void *) Marca_new, "");
					
					if(codigo != -1){
										
						obj_Marca *nuevaMarca, *marcaAnterior = producto->getMarcaObj(producto);
						nuevaMarca->findbykey(nuevaMarca,codigo);

						snprintf(buffer, MAX560,"Modifica la marca del producto numero %d de '%s' a '%s'", producto->getCodigo(producto), marcaAnterior->getDescripcion(marcaAnterior), nuevaMarca->getDescripcion(nuevaMarca));
						producto->setCodMarca(producto, codigo);
				
						destroyObj(marcaAnterior);
					}
					else{
						return;
					}

					break;
				}
					
				case 4:{
					float nuevoPrecio = leerFloat("Ingrese el nuevo precio del producto \n",1,0,1000000.00,-1);  
					snprintf(buffer, MAX560,"Modifica el precio del producto nro %d de %.2f a %.2f", producto->getCodigo(producto), producto->getPrecio(producto), nuevoPrecio);
					producto->setPrecio(producto, nuevoPrecio);
					break;
				}
					
				case 5:{
					float stock = leerFloat("Ingrese el nuevo stock del producto \n",1,0,1000000.00,-1);  //VALIDAR QUE NO SEA NEGATIVO.
					snprintf(buffer, MAX560,"Modifica el stock del producto nro %d de %.2f a %.2f", producto->getCodigo(producto), producto->getStock(producto), stock);		
					producto->setStock(producto, stock);
					break;
				}
					
				case 6:{
					bool disponibilidad = confirma("El producto esta disponible? s/n \n"); 
					snprintf(buffer, MAX560,"Modifica la disponbilidad del producto nro %d de %s a %s", 
					producto->getCodigo(producto)
					, producto->getDisponible(producto)? "Disponible": "No disponible"
					, disponibilidad? "Disponible": "No Disponible");		
					producto->setDisponible(producto, disponibilidad);
					break;
				}
		}
	
		if(producto->saveObj(producto) == true)
			printf("Modificacion al cliente realizada con exito \n");
			registrarEvento("Producto", buffer);
			system("PAUSE");
	}
	
	producto->destroyInternal(producto);
	destroyObj(producto);	
}



