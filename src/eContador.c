#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eContador.h"

int ContadorInit(eContador vector[],int tam){
	int retorno;
	retorno =0;
	for(int i=0;i<tam;i++){
		vector[i].id=-1;
		vector[i].contador=0;
		retorno=1;
	}
	return retorno;
}
