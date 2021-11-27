
#ifndef ECLIENTE_H_
#define ECLIENTE_H_
#include "eLocalidad.h"

typedef struct{
	int id;
	char nombreEmpresa[51];
	char cuit[15];
	char direccion[51];
	int idL;
	int isEmpty;
}eCliente;

int ClienteInit(eCliente vector[], int tam);
int AgregarCliente(eCliente vector[],int tam,int* idC,eLocalidad vectorL[],int tamL,int* idL);
int CargarCliente(eCliente vector[],int tam,eCliente aux);
int BuscarEmptyCliente(eCliente vector[],int tam);
int BuscarClientePorId(eCliente vector[],int tam,int* auxId);
int ImprimirClientes(eCliente vector[],int tam);
int BuscarLocalidadDelCliente(eCliente cliente,eLocalidad vectorL[],int tamL);
int ModificarDireccion(eCliente* cliente);
int ModificarLocalidad(eCliente* cliente,eLocalidad vectorL[],int tamL,int* idL);
int PedirDatosNuevoCliente(eCliente* auxC,int* idC,eLocalidad vectorL[],int tamL,int* idL);


//-----------------HARD CODE TEST-------------------
int ClientesTesteo(eCliente vector[],int* id,int* altas,int actividad);

#endif /* ECLIENTE_H_ */
