
#ifndef INFORMES_H_
#define INFORMES_H_
#include "eCliente.h"
#include "ePedidos.h"
#include "eContador.h"

int ContarPedidos(eCliente eCliente,eContador* eContador,ePedidos vPedidos[],int tamP,int estado);
int ImprimirClienteMasPedidos(eCliente vectorC[],int tamC,eContador cPedidos[],int tamP,int masPedidos);
int ImprimirPedidosPendientesPorCliente(ePedidos listP[],int tamP,eCliente cliente);
int ImprimirPedidosCompletados(ePedidos listP[],int tamP,eCliente cliente);
int ContarAcumularPP(ePedidos vectorP[],int tamP,eCliente cliente,int* contador,int* acumulador);
int Contar(eContador* eContador,int idCliente);
int ImprimirContadorMaximo(eCliente cliente,eContador contadores[],int tamCP,int maximo);

//----------INFORMES------------
int InformeClientesYPedidosPendientes(ePedidos listP[],int tamP,eCliente listC[],int tamC,eLocalidad listL[],int tamL);
int InformePedidosPendientes(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int InformePedidosCompletados(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int InformePedidosPendientesPorLocalidad(eCliente listC[],int tamC,ePedidos listP[],int tamP,eLocalidad listL[],int tamL);
int InformePromedioPP(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int InformeClienteMasPedidosGenerico(eCliente vectorC[],int tamC,ePedidos vectorP[],int tamP,int estado);
//-------------------








#endif /* INFORMES_H_ */
