#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include "ePedidos.h"
#include "eCliente.h"
#include "eLocalidad.h"
#include "eContador.h"
/// @brief Cuenta los pedidos de un cliente bajo un estado espesifico
///
/// @param eCliente cliente
/// @param eContador puntero que devuelve la cantidad de pedidos que se conto
/// @param vPedidos vector de pedidos a recorrer
/// @param tamP tamaño del vector pedido
/// @param estado -0 para pedidos en estado PENDIENTE -1 para pedidos en estado COMPLETADO -2 para contar TODOS
/// @return
int ContarPedidos(eCliente eCliente,eContador* eContador,ePedidos vPedidos[],int tamP,int estado){
	int retorno;
	retorno=0;

	for(int i=0;i<tamP;i++){
		if(vPedidos[i].isEmpty==0&&eCliente.id==vPedidos[i].idC&&(estado>-1||estado<3)){
			if((estado==0||estado==1)&&vPedidos[i].estado==estado){
				Contar(eContador, eCliente.id);
			}
			else{
				if(estado==2){
					Contar(eContador, eCliente.id);
				}
			}
			retorno=1;
		}
	}
	return retorno;
}
int Contar(eContador* eContador,int idCliente){
	int retorno;
	retorno=0;
	eContador->contador=eContador->contador+1;
	eContador->id=idCliente;

	return retorno;
}
int ImprimirPromedio(int contador,float acumulador,char* nombreEmpresa){
	int retorno;
	float promedio;
	promedio=0;
	retorno=0;
	if(contador>0){
		promedio=acumulador/contador;
	}
	else{
		promedio=0;
	}
	printf("  %-15s  %-5.2f\n",nombreEmpresa,promedio);
	return retorno;
}
/// @brief Imprime en pantalla los clientes con mas pedidos
///
/// @param vectorC vector de Clientes a recorrer
/// @param tamC tamaño del vector de clientes
/// @param cPedidos vector de contadores
/// @param tamCP tamaño del vector de contadores
/// @param masPedidos la cantidad de pedidos maximos entre los clientes
/// @return
int ImprimirClienteMasPedidos(eCliente vectorC[],int tamC,eContador cPedidos[],int tamCP,int masPedidos ){
	int retorno;
	retorno=0;
	for(int i=0;i<tamC;i++){
		if(vectorC[i].isEmpty==0){
			ImprimirContadorMaximo(vectorC[i], cPedidos, tamCP, masPedidos);
			retorno=1;
		}
	}
	return retorno;
}
int ImprimirContadorMaximo(eCliente cliente,eContador contadores[],int tamCP,int maximo){
	int retorno;
	retorno=0;
	for(int i=0;i<tamCP;i++){
		if(cliente.id==contadores[i].id&&contadores[i].contador==maximo){
			printf(" %-16s      %-2d\n",cliente.nombreEmpresa,contadores[i].contador);
			retorno=1;
			break;
		}
	}
	return retorno;
}
/// @brief Imprime en pantalla los pedidos en estado pendiente
///
/// @param listP	vector de pedidos
/// @param tamP		tamaño del vector pedidos
/// @param cliente	cliente para matchear los pedidos
/// @return
int ImprimirPedidosPendientesPorCliente(ePedidos listP[],int tamP,eCliente cliente){
	int retorno;
	retorno=0;
	for(int i=0;i<tamP;i++){
		if(cliente.id==listP[i].idC&&listP[i].estado==0){
			printf("%-15s %-17s %-7.2f\n",cliente.cuit,cliente.direccion,listP[i].kilos);
			retorno=1;
		}
	}
	return retorno;
}
/// @brief Imprime en pantalla los pedidos en estado Completado
///
/// @param listP 	vector de pedidos
/// @param tamP		tamaño del vector pedidos
/// @param cliente	cliente para matchear los pedidos
/// @return
int ImprimirPedidosCompletados(ePedidos listP[],int tamP,eCliente cliente){
	int retorno;
	retorno=0;
	for(int i=0;i<tamP;i++){
		if(cliente.id==listP[i].idC&&listP[i].estado==1){
			printf(" %-15s %-17s %-7.2f  %-7.2f  %-7.2f  %-7.2f\n",
					cliente.cuit,cliente.direccion,listP[i].HDPE,
					listP[i].LDPE,listP[i].PP,listP[i].desechos);
			retorno=1;
		}
	}
	return retorno;
}
/// @brief Cuenta los pedidos completados y acumula el PP procesado
///
/// @param vectorP	vector de Pedidos
/// @param tamP		tamaño del vector pedidos
/// @param cliente	cliente para recorrer sus pedidos
/// @param contador	contador de pedidos
/// @param acumulador	acumulador de PP
/// @return
int ContarAcumularPP(ePedidos vectorP[],int tamP,eCliente cliente,int* contador,float* acumulador){
	int retorno;
	retorno=0;
	for(int i=0;i<tamP;i++){
		if(cliente.id==vectorP[i].idC&&vectorP[i].estado==1){
			retorno=1;
			*contador=*contador+1;
			*acumulador=*acumulador+vectorP[i].PP;
		}
	}
	return retorno;
}
//------------------------INFORMES--------------------------
/// @brief imprime los datos de los clientes con pedidos
/// 		pendientes y la cantidad de pedidos pendientes
///
/// @param listP vector de pedidos
/// @param tamP	tamaño del vector pedidos
/// @param listC vector de clientes
/// @param tamC tamaño del vector clientes
/// @return
int InformeClientesYPedidosPendientes(ePedidos listP[],int tamP,eCliente listC[],int tamC,eLocalidad listL[],int tamL){
	int retorno;
	int posicionL;
	eContador contador[1];
	retorno=0;
	ContadorInit(contador, 1);

	for(int i=0;i<tamC;i++){
		if(listC[i].isEmpty==0){
			posicionL=BuscarLocalidadDelCliente(listC[i], listL, tamL);
			if(posicionL>-1){
				ContarPedidos(listC[i], &contador[0], listP, tamP, 0);
				printf(" %-2d %-16s %-15s %-16s %-16s %-2d\n",listC[i].id,
						listC[i].nombreEmpresa,listC[i].cuit,listC[i].direccion,
						listL[posicionL].localidad,contador[0].contador);
				contador[0].contador=0;
			}
			retorno=1;
		}
	}
	return retorno;
}
/// @brief imprime el cuit y direccion del cliente y los kilos a procesar en cada pedido
///
/// @param listP	vector de pedidos
/// @param tamP		tamaño dle vector pedidos
/// @param listC	vector cliente
/// @param tamC		tamaño del vector cliente
/// @return
int InformePedidosPendientes(ePedidos listP[],int tamP,eCliente listC[],int tamC){
	int retorno;
	retorno=0;
	for(int i=0;i<tamC;i++){
		if(listC[i].isEmpty==0){
			if(ImprimirPedidosPendientesPorCliente(listP, tamP, listC[i])){
				retorno=1;
			}
		}
	}
	return retorno;
}
/// @brief Informe de pedidos completados
///
/// @param listP 	vector de pedidos
/// @param tamP		tamaño del vector pedidos
/// @param listC	vector de clientes
/// @param tamC		tamaño del vector clientes
/// @return
int InformePedidosCompletados(ePedidos listP[],int tamP,eCliente listC[],int tamC){
	int retorno;
	retorno=0;
	for(int i=0;i<tamC;i++){
		if(listC[i].isEmpty==0){
			if(ImprimirPedidosCompletados(listP, tamP, listC[i])){
				retorno=1;
			}
		}
	}
	return retorno;
}
/// @brief pide al usuario que ingrese una localidad y
/// luego muestra cuantos pedidos pendientes tiene esa dicha localidad
///
/// @param listC	vector de clientes
/// @param tamC		tamaño del vector cliente
/// @param listP	vector de pedidos
/// @param tamP		tamaño del vector pedidos
/// @return
int InformePedidosPendientesPorLocalidad(eCliente listC[],int tamC,ePedidos listP[],int tamP,eLocalidad listL[],int tamL){
	int retorno;
	char localidad[20];
	eContador contador[1];
	int idL;

	ContadorInit(contador, 1);
	retorno=0;

	if(GetCharLNPC(localidad, 20, "ingrese una Localidad: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 4)){
		idL=BuscarLocalidad(listL, tamL, localidad);
		if(idL>0){
			for(int i=0;i<tamC;i++){
				if(listC[i].isEmpty==0&&listC[i].idL==idL){
					ContarPedidos(listC[i], &contador[0], listP, tamP, 0);
					retorno=1;
				}
			}
			printf("  %-16s %-2d\n",localidad, contador[0].contador);
		}
	}
	return retorno;
}
/// @brief 	informa el promedio de PP reciclado por cliente
///
/// @param listP	vector de Pedidos
/// @param tamP		tamaño del vector pedidos
/// @param listC	vector de Clientes
/// @param tamC		tamaño del vector Cliente
/// @return
int InformePromedioPP(ePedidos listP[],int tamP,eCliente listC[],int tamC){
	int retorno;
	int contador;
	float acumulador;

	retorno=0;

	for(int i=0;i<tamC;i++){
		if(listC[i].isEmpty==0){
			acumulador=0;
			contador=0;
			ContarAcumularPP(listP, tamP, listC[i], &contador, &acumulador);
			ImprimirPromedio(contador, acumulador, listC[i].nombreEmpresa);
			retorno=1;
		}
	}
	return retorno;
}
/// @brief 	informe de clientes con mas pedidos en un estado determinado
///
/// @param vectorC vector de cliente
/// @param tamC		tamaño del vector cliente
/// @param vectorP	vector de pedidos
/// @param tamP		tamaño del vector pedidos
/// @param estado	0- para pedidos pendientes 1- para pedidos completados 2- para pedidos pendientes y copletados
/// @return
int InformeClienteMasPedidosGenerico(eCliente vectorC[],int tamC,ePedidos vectorP[],int tamP,int estado){
	int retorno;
	eContador cPedidos[100];
	int flagMayor;
	int masPedidos;
	retorno=0;
	flagMayor=0;

	ContadorInit(cPedidos,100);

	for(int i=0;i<tamC;i++){
		if(vectorC[i].isEmpty==0&&(estado>-1&&estado<3)){
			ContarPedidos(vectorC[i], &cPedidos[i], vectorP, tamP, estado);
			if(flagMayor==0||cPedidos[i].contador>masPedidos){
				masPedidos=cPedidos[i].contador;
				flagMayor=1;
			}
		}
	}
	if(ImprimirClienteMasPedidos(vectorC, tamC, cPedidos, tamC, masPedidos)){
		retorno=1;
	}
	return retorno;
}
