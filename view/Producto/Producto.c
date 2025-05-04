#include "Producto.h"


void cargarProducto(){
	static int codigo = 0;
	int codMarca, codCategoria;
	
	codMarca = ingresarCodigo((void *) Marca_new ,  "Las marcas registradas son: ");	
	
	if(codMarca != -1){
		
		codCategoria = ingresarCodigo((void *) Categoria_new, "Las categorias registradas son: " );
		
		if(codCategoria != -1){
			
			//Solicito valores para registrar el producto.
			char *descripcion = leerCadena("Ingrese la descripcion \n", MAX80);  //80 CARACTERES	
			float precio = leerFloat("Ingrese el precio del producto \n");
			float stock = leerFloat("Ingrese el stock del producto \n");
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
			if(producto->saveObj(producto) == true)
				printf("Ingreso del producto realizado con exito \n");
				
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
	
	if (codigo != -1){
		
		opcion = mostrarMenu(menuModificarProducto, LEN(menuModificarProducto));
		system("cls");
		
		switch (opcion){	
				case 1:{
					char *descripcion = leerCadena("Ingrese la nueva descripcion del producto \n", MAX80);
					producto->setDescripcion(producto, descripcion);
					free(descripcion);
					break;
				}
						
			
				case 2:{
					int codigo = ingresarCodigo((void *) Categoria_new, "");
					producto->setCodCategoria(producto, codigo);
					break;
				}
					
				case 3:{
					int codigo = ingresarCodigo((void *) Marca_new, "");
					producto->setCodMarca(producto, codigo);	
					break;
				}
					
					
				case 4:{
					float precio = leerFloat("Ingrese el nuevo precio del producto \n");  //VALIDAR QUE NO SEA NEGATIVO.
					producto->setPrecio(producto, precio);
					break;
				}
					
				case 5:{
					float stock = leerFloat("Ingrese el nuevo stock del producto \n");  //VALIDAR QUE NO SEA NEGATIVO.
					producto->setStock(producto, stock);
					break;
				}
					
				case 6:{
					bool disponibilidad = confirma("El producto esta disponible? s/n \n");
					producto->setDisponible(producto, disponibilidad);
					break;
				}
		}
	
		if(producto->saveObj(producto) == true)
			printf("Modificacion al cliente realizada con exito \n");
			system("PAUSE");
	}
	
	destroyObj(producto);	
}



