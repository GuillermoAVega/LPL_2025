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
	
	printf("%s \n", msj_pant);
	
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


/// otras funciones para interaccionar con el usuario.



