#include "Sucursal_det.h"



void cargarSucursalDest(){
	int codSucOrigen = ingresarCodigo((void *) Sucursal_new, "Ingrese el codigo de la sucursal origen:\n");
	if (codSucOrigen == -1)
		return;
	int codSucDestino = ingresarCodigo((void *) Sucursal_new, "Ingrese el codigo de la sucursal destino:\n");
	if (codSucDestino == -1)
		return;
	
	int km = leerEntero("Ingrese los kilometros entre las sucursales \n",0,0,100000,-1);
	
	obj_SucursalDest *camino = SucursalDest_new();
	
	camino->setCodSucO(camino,codSucOrigen);
	camino->setCodSucD(camino,codSucDestino);
	camino->setKm(camino,km);
	
	if (camino->saveObj(camino) == true){
			printf("Ingreso exitoso\n");
		}
	else
		printf("Error al ingresar el camino entre sucursales\n");
			
	destroyObj(camino);
}

