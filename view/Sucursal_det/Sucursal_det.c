#include "Sucursal_det.h"

void cargarSucursalDet(){
	
	int codSucOrigen = ingresarCodigo((void *) Sucursal_new, "Ingrese el codigo de la sucursal origen: \n");
	
	if (codSucOrigen != -1){
		
		int codSucDestino = ingresarCodigo((void *) Sucursal_new, "Ingrese el codigo de la sucursal destino: \n");
	
		if (codSucDestino != -1){
		
			obj_SucursalDest *camino = SucursalDest_new();
			
			if (codSucOrigen != codSucDestino){
				int km = leerEntero("Ingrese los kilometros entre las sucursales \n", 0, 0, 100000, -1);
		
				camino->setCodSucO(camino,codSucOrigen);
				camino->setCodSucD(camino,codSucDestino);		
				camino->setKm(camino,km);
			
				if (camino->saveObj(camino) == true)
					printf("Ingreso exitoso\n");
				else
				printf("Error al ingresar el camino entre sucursales \n");
			}
			else{
				
				printf("Los codigos de la sucursal destino y la sucursal origen deben ser distintos \n");
				
			}
			destroyObj(camino);
		}
	}
}


