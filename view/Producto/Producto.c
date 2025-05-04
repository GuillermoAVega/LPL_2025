#include "Producto.h"


const char *menuModificarProducto[] = {"Descripcion", "Categoria", "Marca", "Precio", "Stock", "Disponibilidad"};


void cargarProducto(){
	static int codigo = 0;
	int codMarca, codCategoria;
	
	codMarca = ingresarCodigo((void *) Marca_new ,  "Las marcas registradas son: ");	
	codCategoria = ingresarCodigo((void *) Categoria_new, "Las categorias registradas son: " );
	

	//Solicito valores para registrar el producto.
	char *descripcion = leerCadena("Ingrese la descripcion \n", MAX80);  //80 CARACTERES	
	float precio = leerFloat("Ingrese el precio del producto \n");
	float stock = leerFloat("Ingrese el stock del producto \n");
	bool disponible = confirma("El producto esta disponible?");
	

	obj_Producto *producto = Producto_new();
	producto->setCodMarca(producto, codMarca);
	producto->setCodCategoria(producto, codCategoria);
	producto->setCodigo(producto, codigo++);
	producto->setDescripcion(producto, descripcion);
	producto->setPrecio(producto, precio);
	producto->setStock(producto, stock);
	producto->setDisponible(producto, disponible);
	
	if(producto->saveObj(producto) == true)
		printf("Ingreso del producto realizado con exito \n");
		
	destroyObj(producto);
	free(descripcion);
	
}


void modificarProducto(){
	
	printf("Los productos cargados son: \n");
	mostrarObjetos( (void *) Producto_new);
		
	int codigo, opcion;
	codigo = ingresarCodigo((void *) Producto_new, "Ingrese el codigo del producto que desea modificar\n");	
	
	if (codigo == -1)
		return;
	
	opcion = mostrarMenu(menuModificarProducto, LEN(menuModificarProducto));

	
}



