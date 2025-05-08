#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/includes.h"

#define LEN(x) (sizeof(x) / sizeof(x[0]))


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
		fflush(stdin);
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
			int size = strlen(cadena);
			//cadena[size - 1] = '\0';
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

int confirma(char *msj_pant){
	
	char c;
	
	do{
		printf("%s \n", msj_pant);
		fflush(stdin);
		c = getchar();
		
	} while ( c != 's' && c != 'S' && c != 'n' && c != 'N');
	
	
	return (c == 's' || c == 'S');
}


int mostrarMenu(char *opciones[], int cantidadOpciones){
	
	int i, respuesta;
	
	system("cls");	
	printf("---------------------------------\n");
	printf("Ingrese segun desee: \n");
		
	for (i = 0; i < cantidadOpciones; i++){
	
		printf("%d - %s \n", i + 1, opciones[i]);
	
	}
	printf("---------------------------------\n");
	printf("Ingrese -1 para salir \n");	
	printf("---------------------------------\n");
	respuesta = leerEntero("", 0, 1, cantidadOpciones, -1);
	
	return (respuesta);
}


	



/// otras funciones para interaccionar con el usuario.



