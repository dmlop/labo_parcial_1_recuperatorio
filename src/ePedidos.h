

#ifndef EPEDIDOS_H_
#define EPEDIDOS_H_
#include "eCliente.h"
#include "eLocalidad.h"

typedef struct{
	int id;
	int idC;
	int estado;
	int isEmpty;
	float kilos;
	float HDPE;
	float LDPE;
	float PP;
	float desechos;
}ePedidos;

int PedidosInit(ePedidos vector[],int tam);
int AgregarPedido(ePedidos vector[],int tam,int* idP,int auxId);
int CargarPedido(ePedidos vector[],int tam,ePedidos aux);
int BuscarEmptyPedidos(ePedidos vector[],int tam);
int ImprimirPedidos(ePedidos vector[],int tam);
int BuscarPedidoPorId(ePedidos vector[],int tam,int* auxId);
int ProcesarPedido(ePedidos* pedido);
int PedirPlasticosProcesados(ePedidos* aux);
int CargarPedidoProcesado(ePedidos* pedido,ePedidos aux, int totalPlasticos);



//-------------------
int PedidosTesteo(ePedidos vector[],int *id,int actividad);


#endif /* EPEDIDOS_H_ */
