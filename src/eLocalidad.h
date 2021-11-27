

#ifndef ELOCALIDAD_H_
#define ELOCALIDAD_H_

typedef struct{
	int id;
	int isEmpty;
	char localidad[51];
}eLocalidad;

int LocalidadInit(eLocalidad vector[],int tam);
int BuscarEmpty(eLocalidad vector[],int tamL);
int BuscarLocalidad(eLocalidad vector[],int tam,char localidad[]);
int CargarLocalidad(eLocalidad* localidadEmpty,char localidad[],int* idL);
//--------------------------------------------------------------
int NuevaLocalidad(eLocalidad vectorL[], int tamL,char* localidad,int* idL);
int BuscarOAgregarLocalidad(eLocalidad vectorL[],int tamL,char* localidad,int* idL);
//--------------------HARD CODE TEST---------------------------
void MostrarLocalidades(eLocalidad vectorL[],int tam);
int LocalidadesTesteo(eLocalidad vector[],int* id,int actividad);


#endif /* ELOCALIDAD_H_ */
