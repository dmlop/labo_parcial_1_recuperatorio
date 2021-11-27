#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include "ePedidos.h"
#include "eCliente.h"

/// @brief inicializa un vector ePedidos con el campo isEmpty=1;
///
/// @param vector - vector ePedidos
/// @param tam - tamaño del vector
int PedidosInit(ePedidos vector[],int tam){
	int retorno;
	retorno=0;
	for(int i=0;i<tam;i++){
		vector[i].isEmpty=1;
		retorno=1;
	}
	return retorno;
}
/// @brief Pide al usuario la cantidad de kilos  y agrega el pedido al vector ePedidos
///
/// @param vector - vecor de pedidos
/// @param tam - tamaños del vector
/// @param aux - auxialiar del tipo ePedidos que contiene los datos a copiar en el nuevo pedido
/// @param id - puntero del id que se le asigna al nuevo pedido
/// @param auxId - el id del cliente para guardarlo en FK de ePedidos
int AgregarPedido(ePedidos vector[],int tam,int* idP,int auxId){
	int retorno;
	ePedidos auxP;
	retorno=0;
	if(GetFloatRangoR(&auxP.kilos, "Ingrese la cantidad de kilos: ",
			"ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 100, 5000, 4)){
		auxP.id=*idP;
		auxP.idC=auxId;
		if(CargarPedido(vector,tam,auxP)>-1){
			*idP=*idP+1;
			retorno=1;
		}
	}
	return retorno;
}
/// @brief busca lugar disponible en el vector ePedidos y Carga los
///			datos guardados en el auxiliar
///
/// @param vector- vector de pedidos
/// @param tam - tamaño del vector
/// @param aux - auxiliar del tipo ePedidos con los datos necesarios
/// 		para agregar un nuevo pedido
/// @return
int CargarPedido(ePedidos vector[],int tam,ePedidos aux){

	int posicion;

	posicion=BuscarEmptyPedidos(vector,tam);
	if(posicion!=-1){
		vector[posicion].id=aux.id;
		vector[posicion].estado=0;
		vector[posicion].idC=aux.idC;
		vector[posicion].isEmpty=0;
		vector[posicion].kilos=aux.kilos;
	}
	return posicion;
}
/// @brief Busca un lugar disponible en el vector
///
/// @param vector - vector de pedidos
/// @param tam - tamaño del vector
/// @return
int BuscarEmptyPedidos(ePedidos vector[],int tam){
	int retorno;
	retorno=-1;
	for(int i=0;i<tam;i++){
		if(vector[i].isEmpty==1){
			retorno=i;
			break;
		}
	}
	return retorno;
}
/// @brief imprime los pedidos, su id estado y kilos a procesar
///
/// @param vector - vector de pedidos
/// @param tam - tamaño del vector
/// @return
int ImprimirPedidos(ePedidos vector[],int tam){
	int retorno;
	char estado[15];
	retorno=0;
	for(int i=0;i<tam;i++){
		if(vector[i].isEmpty==0){
			if(vector[i].estado==0){
				strncpy(estado,"Pendiente",12);
			}
			else{
				if(vector[i].estado==1){
					strncpy(estado,"Completado",12);
				}
			}
			printf(" %-2d  %-10s  %-7.2f\n",vector[i].id,estado,vector[i].kilos);
			retorno=1;
		}
	}
	return retorno;
}
/// @brief  pide al usuario un id y busca un pedido con dicho id
///
/// @param vector - vector de pedidos
/// @param tam - tamaño del vector
/// @param auxId - puntero que recive el ID ingresado por el usuario
/// @return - devuelvo -1 si no se encontro un pedido con el id ingresado
/// 		si no devuelve la posicion en el vector que matchea con el id ingresado en el vector.
int BuscarPedidoPorId(ePedidos vector[],int tam,int* auxId){
	int retorno;
	int id;
	retorno=-1;
	GetIntR(&id, "Ingrese el ID del Pedido: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",4);

	for(int i=0;i<tam;i++){
		if(vector[i].id==id&&vector[i].isEmpty==0){
			retorno=i;
			*auxId=vector[i].id;
			break;
		}
	}
	return retorno;
}
/// @brief procesa un pedido espesifico
///
/// @param pedido	- puntero del pedido a procesar
/// @return devuelve 0 si no se pudo procesar o 1 si logro procesarlo
int ProcesarPedido(ePedidos* pedido){
	int retorno;
	ePedidos aux;
	float totalPlasticos;
	retorno=0;

	PedirPlasticosProcesados(&aux);

	totalPlasticos=aux.HDPE + aux.LDPE + aux.PP;
	if(pedido->kilos>=totalPlasticos){
		CargarPedidoProcesado(pedido, aux, totalPlasticos);
		retorno=1;
	}

	return retorno;
}
int PedirPlasticosProcesados(ePedidos* aux){
	int retorno;
	retorno=0;

	GetFloatRangoR(&aux->HDPE, "Ingrese la cantidad de HDPE procesado: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 1, 5000, 99);
	GetFloatRangoR(&aux->LDPE, "Ingrese la cantidad de LDPE procesado: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 1, 5000, 99);
	GetFloatRangoR(&aux->PP, "Ingrese la cantidad de PP procesado: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 1, 5000, 99);

	return retorno;
}
int CargarPedidoProcesado(ePedidos* pedido,ePedidos aux, int totalPlasticos){
	int retorno;
	retorno=1;

	pedido->HDPE=aux.HDPE;
	pedido->LDPE=aux.LDPE;
	pedido->PP=aux.PP;
	pedido->desechos=pedido->kilos - totalPlasticos;
	pedido->estado=1;

	return retorno;
}

//-------------------------HARD CODE TEST------------------------
int PedidosTesteo(ePedidos vector[],int *id,int actividad){
	int retorno;
	retorno=0;
	if(actividad==1){
		retorno=1;

		vector[0].id=*id;
		vector[0].isEmpty=0;
		vector[0].idC=3;
		vector[0].estado=1;
		vector[0].kilos=1510;
		vector[0].HDPE=300;
		vector[0].LDPE=400;
		vector[0].PP=500;
		vector[0].desechos=310;
		*id=*id+1;

		vector[1].id=*id;
		vector[1].isEmpty=0;
		vector[1].idC=1;
		vector[1].estado=0;
		vector[1].kilos=230;
		*id=*id+1;

		vector[2].id=*id;
		vector[2].isEmpty=0;
		vector[2].idC=7;
		vector[2].estado=0;
		vector[2].kilos=1000;
		*id=*id+1;

		vector[3].id=*id;
		vector[3].isEmpty=0;
		vector[3].idC=8;
		vector[3].estado=0;
		vector[3].kilos=900;
		*id=*id+1;

		vector[4].id=*id;
		vector[4].isEmpty=0;
		vector[4].idC=9;
		vector[4].estado=0;
		vector[4].kilos=1500;
		*id=*id+1;

		vector[5].id=*id;
		vector[5].isEmpty=0;
		vector[5].idC=10;
		vector[5].estado=0;
		vector[5].kilos=2000;
		*id=*id+1;

		vector[6].id=*id;
		vector[6].isEmpty=0;
		vector[6].idC=11;
		vector[6].estado=0;
		vector[6].kilos=4500;
		*id=*id+1;


		vector[7].id=*id;
		vector[7].isEmpty=0;
		vector[7].idC=12;
		vector[7].estado=0;
		vector[7].kilos=800;
		*id=*id+1;


		vector[8].id=*id;
		vector[8].isEmpty=0;
		vector[8].idC=1;
		vector[8].estado=0;
		vector[8].kilos=100;
		*id=*id+1;

		vector[9].id=*id;
		vector[9].isEmpty=0;
		vector[9].idC=2;
		vector[9].estado=0;
		vector[9].kilos=800;
		*id=*id+1;

		vector[10].id=*id;
		vector[10].isEmpty=0;
		vector[10].idC=3;
		vector[10].estado=1;
		vector[10].kilos=900;
		vector[10].HDPE=200;
		vector[10].LDPE=200;
		vector[10].PP=250;
		vector[10].desechos=250;
		*id=*id+1;

		vector[11].id=*id;
		vector[11].isEmpty=0;
		vector[11].idC=4;
		vector[11].estado=0;
		vector[11].kilos=150;
		*id=*id+1;

		vector[12].id=*id;
		vector[12].isEmpty=0;
		vector[12].idC=5;
		vector[12].estado=1;
		vector[12].kilos=850;
		vector[12].HDPE=100;
		vector[12].LDPE=100;
		vector[12].PP=400;
		vector[12].desechos=250;
		*id=*id+1;

		vector[13].id=*id;
		vector[13].isEmpty=0;
		vector[13].idC=6;
		vector[13].estado=1;
		vector[13].kilos=3500;
		vector[13].HDPE=800;
		vector[13].LDPE=1200;
		vector[13].PP=1000;
		vector[13].desechos=500;
		*id=*id+1;

		vector[14].id=*id;
		vector[14].isEmpty=0;
		vector[14].idC=7;
		vector[14].estado=1;
		vector[14].kilos=2800;
		vector[14].HDPE=500;
		vector[14].LDPE=500;
		vector[14].PP=1000;
		vector[14].desechos=800;
		*id=*id+1;

		vector[15].id=*id;
		vector[15].isEmpty=0;
		vector[15].idC=3;
		vector[15].estado=1;
		vector[15].kilos=2000;
		vector[15].HDPE=250;
		vector[15].LDPE=750;
		vector[15].PP=800;
		vector[15].desechos=200;
		*id=*id+1;

		vector[16].id=*id;
		vector[16].isEmpty=0;
		vector[16].idC=1;
		vector[16].estado=1;
		vector[16].kilos=2120;
		vector[16].HDPE=350;
		vector[16].LDPE=650;
		vector[16].PP=620;
		vector[16].desechos=500;
		*id=*id+1;
	}
	return retorno;
}
