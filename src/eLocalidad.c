#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eCliente.h"
#include "eLocalidad.h"
#include "biblioteca.h"


int LocalidadInit(eLocalidad vector[],int tam){
	int retorno;
	retorno=0;

	for(int i=0;i<tam;i++){
		vector[i].isEmpty=1;
		retorno=1;
	}
	return retorno;
}
int BuscarEmpty(eLocalidad vector[],int tamL){
	int retorno;
	retorno=-1;

	for(int i=0;i<tamL;i++){
		if(vector[i].isEmpty==1){
			retorno=i;
			break;
		}
	}
	return retorno;
}

int BuscarLocalidad(eLocalidad vector[],int tam,char* localidad){
	int retorno;
	retorno=0;

	for(int i=0;i<tam;i++){
		if(strcmp(vector[i].localidad,localidad)==0){
			retorno=vector[i].id;
			break;
		}
	}
	return retorno;
}

int CargarLocalidad(eLocalidad* localidadEmpty,char localidad[],int* idL) {
	int retorno;
	retorno=0;
	if(localidadEmpty->isEmpty==1){
		localidadEmpty->isEmpty=0;
		strcpy(localidadEmpty->localidad,localidad);
		localidadEmpty->id=*idL;
		*idL=*idL+1;
		retorno=1;
	}
	return retorno;
}
int BuscarOAgregarLocalidad(eLocalidad vectorL[],int tamL,char* localidad,int* idL){
	int retorno;
	int idLocalidad;
	retorno=-1;
	PrimerasLetrasMayuscula(localidad);
	idLocalidad=BuscarLocalidad(vectorL, tamL, localidad);

	if(idLocalidad==0){
		idLocalidad=NuevaLocalidad(vectorL, tamL, localidad, idL);

		if(idLocalidad!=-1){
			retorno=idLocalidad;
		}
	}
	return retorno;
}
int NuevaLocalidad(eLocalidad vectorL[], int tamL,char* localidad,int* idL){
	int retorno;
	int posicion;
	retorno=-1;
	posicion=BuscarEmpty(vectorL, tamL);
	if(posicion!=-1){
		if(CargarLocalidad(&vectorL[posicion], localidad, idL)){
			retorno=vectorL[posicion].id;
		}
	}
	return retorno;
}
//--------------------HARD CODE TEST---------------------------
void MostrarLocalidades(eLocalidad vectorL[],int tam){
	for(int i=0;i<tam;i++){
		printf("%d--%d--%s\n",vectorL[i].id,vectorL[i].isEmpty,vectorL[i].localidad);
	}
}
int LocalidadesTesteo(eLocalidad vector[],int* id,int actividad){
	int retorno;
	retorno=0;

	if(actividad==1){
		retorno=1;

		vector[0].id=*id;
		vector[0].isEmpty=0;
		strncpy(vector[0].localidad,"Avellaneda",51);
		*id=*id+1;

		vector[1].id=*id;
		vector[1].isEmpty=0;
		strncpy(vector[1].localidad,"Sarandi",51);
		*id=*id+1;

		vector[2].id=*id;
		vector[2].isEmpty=0;
		strncpy(vector[2].localidad,"Gerli",51);
		*id=*id+1;

		vector[3].id=*id;
		vector[3].isEmpty=0;
		strncpy(vector[3].localidad,"Dominico",51);
		*id=*id+1;
	}
	return retorno;
}
