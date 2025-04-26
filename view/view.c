#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/includes.h"


int leerEntero(char *msj_pant,bool clear, int minVal, int maxVal, int corteIngreso )
{
	int valor;
	while (true)
	{
		if(clear) 
		  system("cls");
		printf(msj_pant);
		fflush(stdin);
		scanf("%d",&valor);
		if(valor>=minVal && valor<=maxVal)
			return valor;
		if(valor == corteIngreso)
			return corteIngreso;		
	}
	return corteIngreso;// devuelve si no se leyo nada valor de corte
}


char *leerCadena(char *msj_pant,int max_cad){
	
	printf("%s", msj_pant);
	fflush(stdin);
	
	char *cadena = (char *) malloc(sizeof(char) * max_cad);
	
	if(cadena == NULL){
		
		printf("Error al asignar memoria \n");
	}
	else{
		if(fgets(cadena, max_cad, stdin) != NULL){
			return cadena;
		}
	}
	
	return NULL;
}


float leerFloat(char *msj_pant ){
	
	float n;
	
	printf("%s",msj_pant);
	fflush(stdin);
	scanf("%f", &n);
	fflush(stdin);
	
	return n;
	
}


int mostrarMenu(char *opciones[], int cantidadOpciones){
	
	int i, respuesta;
	
	system("cls");	
	
	printf("Ingrese segun desee: \n");
		
	for (i = 0; i < cantidadOpciones; i++){
	
		printf("%d - %s \n", i + 1, opciones[i]);
	
	}
	
	respuesta = leerEntero("", 0, 1, cantidadOpciones, -1);
		
		
	return (respuesta);
}

void ingresarLocalidad(){
	
	int codPostal = leerEntero("Ingrese el codigo postal de la localidad \n",1,  0, 10000, -1);	
	char *nombre;
	obj_Localidad *loc = Localidad_new();
	
	if(loc->findbykey(loc, codPostal) == NOT_FOUND){
		system("cls");
		nombre = leerCadena("Ingrese el nombre de la localidad \n", 50);

		loc-> setCodpostal(loc, codPostal);
		loc-> setNombre(loc, nombre);

		if(loc->saveObj(loc) == true)
			printf("Ingreso exitoso");
			
		destroyObj(loc);			
	}
	else{
		printf("Ya existe una localidad con ese codigo postal \n");
	}
	
	free(nombre);
}


/// otras funciones para interaccionar con el usuario.



