/*DANIEL MANRESA 34940336
1) Alta de cliente: Se da de alta un cliente con nombre de la empresa, cuit dirección y
localidad. Se
generará un ID único para este cliente que se imprimirá por pantalla si el alta es correcta.
2) Modificar datos de cliente: Se ingresa el ID de cliente y se permitirá cambiar la dirección
y la localidad.
3) Baja de cliente: Se ingresa el ID del cliente. Luego se preguntará si se quiere confirmar
la eliminación.
4) Crear pedido de recolección: Se imprimirán los clientes por pantalla y se pedirá
que se ingrese el ID de un cliente existente y la cantidad de kilos totales que se
recolectarán del cliente. Se generará un ID para el pedido y el mismo quedará en
estado “Pendiente” hasta que se obtengan los residuos del cliente y se trasladen
a la empresa.
5) Procesar residuos: Se elegirá esta opción cuando los residuos que volvieron a
la empresa se hayan procesado y separado en los diferentes tipos de plástico que
la empresa puede reciclar. Se imprimirán los pedidos por pantalla y se pedirá
seleccionar el ID de uno de ellos. Luego deberán ingresarse la cantidad de kilos
de plástico de cada uno de los 3 tipos que la empresa puede procesar que se
obtuvieron de los kilos totales que se recolectaron. Por último, se marcará
al pedido como “Completado”.
6) Imprimir Clientes: Se imprimirá una lista de clientes con todos sus datos junto
con la cantidad de “pedidos de recolección” que posee en estado “Pendiente”.
7) Imprimir Pedidos pendientes: Se imprimirá una lista de los pedidos que se
encuentren en estado “Pendiente” con la información: Cuit del cliente, dirección
del cliente, cantidad de kilos a recolectar.
8) Imprimir Pedidos procesados: Se imprimirá una lista de los pedidos que se
encuentren en estado “Completado” con la información: Cuit del cliente, dirección
del cliente, cantidad de kilos reciclados de cada tipo de plástico.
9) Ingresar una localidad e indicar la cantidad de pedidos pendientes para dicha
localidad.
10) Cantidad de kilos de polipropileno reciclado promedio por cliente.
(kilos totales / cantidad de clientes)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "biblioteca.h"
#include "eCliente.h"
#include "ePedidos.h"
#include "informes.h"
#include "eLocalidad.h"
#include "menu.h"
#define TAMC 100
#define TAML 100
#define TAMP 1000
#define CARGADO 1
#define DESCARGADO 0
#define PENDIENTE 0
#define COMPLETADO 1
#define TODO 2


int main(void) {
	setbuf(stdout,NULL);
	int opcionMenu;
	int opcionMenuModificacion;
	int opcionMenuInformes;
	int idCliente;
	int idPedido;
	int idLocalidad;
	int auxPos;
	int altas;
	int auxId;
	char sOrN[3];
	eCliente listCliente[TAMC];
	ePedidos listPedidos[TAMP];
	eLocalidad listLocalidad[TAML];
	idCliente=1;
	idPedido=1;
	idLocalidad=1;
	altas=0;


	//INICIALIZACION DE VECTORES: CLIENTE, PEDIDOS Y LOCALIDAD
	if(ClienteInit(listCliente,TAMC)&&
			PedidosInit(listPedidos,TAMP)&&
			LocalidadInit(listLocalidad,TAML)){
		printf("====PROGRAMA=INICIADO====\n");
	}
	else{
		printf("=EL=PROGRAMA=NO=SE=INICIO=CORRECTAMENTE=\n");
	}
	//CARGA DE TESTEO: CLIENTES PEDIDOS Y LOCALIDADES
	if(ClientesTesteo(listCliente,&idCliente,&altas,CARGADO)&&
			PedidosTesteo(listPedidos,&idPedido,CARGADO)&&
			LocalidadesTesteo(listLocalidad,&idLocalidad,CARGADO)){
		printf("===DATOS=DE=TESTEO=CARGADOS===\n");
	}
	else{
		printf("=LOS=DATOS=DE=TESTEO=NO=SE=CARGARON=CORRECTAMENTE=\n");
	}

	do{
		Menu(&opcionMenu);

		switch(opcionMenu){
		case 0:
			MostrarLocalidades(listLocalidad, TAML);
			break;
		case 1://ALTA CLIENTE
			system("cls");
			if(altas==TAMC){//SI HAY 100 CLIENTES CARGADOS
				printf("============PROGRAMA=LLENO============\n");
				break;
			}
			if(AgregarCliente(listCliente,TAMC,&idCliente,listLocalidad,TAML,&idLocalidad)){
				printf("====CLIENTE=AGREGADO====\n");
				altas++;
			}
			else{//ERROR
				printf("=NO=SE=PUDO=CARGAR=EL=CLIENTE=\n");
			}
			break;
		case 2://MODIFICAR DATOS
			system("cls");
			if(altas==0){//ERROR
				printf("=NO=HAY=CLIENTES=EN=ALTA=\n");
				break;
			}
			auxPos=BuscarClientePorId(listCliente,TAMC,&auxId);
			if(auxPos!=-1){
				MenuModificacion(&opcionMenuModificacion);
				switch(opcionMenuModificacion){
				case 1:
					if(ModificarDireccion(&listCliente[auxPos])){
						printf("==DIRECCION=MODIFICADA==\n");
					}
					else{//ERROR
						printf("=ERROR=AL=MODIFICAR=\n");
					}
					break;
				case 2:
					if(ModificarLocalidad(&listCliente[auxPos], listLocalidad, TAML, &idLocalidad)){
						printf("==LOCALIDAD=MODIFICADA==\n");
					}
					else{//ERROR
						printf("=ERROR=AL=MODIFICAR=\n");
					}
					break;
				}
			}
			else{//ERROR
				printf("===NO=EXISTE=EL=CLIENTE===\n");
			}
			break;
		case 3://BAJA DE CLIENTE
			system("cls");
			if(altas==0||idCliente==0){
				printf("==NO=HAY=CLIENTES=DISPONIBLES==\n");
				break;
			}
			auxPos=BuscarClientePorId(listCliente,100,&auxId);
			if(auxPos!=-1){
				do{
					printf("Cliente ==== %s\n", listCliente[auxPos].nombreEmpresa);
					if(GetCharSorN(sOrN,"¿Esta seguro de dar de baja este cliente? <s/n>","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n")){
						if(sOrN[0]=='S'){
							listCliente[auxPos].isEmpty=1;
							altas--;
							printf("=========BAJA=COMPLETADA=========\n");
						}
						else{
							printf("=========BAJA=CANCELADA=========\n");
							break;
						}
					}
				}while(sOrN[0]!='S'&&sOrN[0]!='N');
			}
			else{//ERROR
				printf("===NO=EXISTE=EL=CLIENTE===\n");
			}
			break;
		case 4://CREAR PEDIDO DE RECOLECCION
			system("cls");
			if(altas==0||idCliente==0){
				printf("==NO=HAY=CLIENTES=DISPONIBLES==\n");
				break;
			}
			if(ImprimirClientes(listCliente, TAMC)){
				auxPos=BuscarClientePorId(listCliente,TAMC,&auxId);
				if(auxPos!=-1){
					AgregarPedido(listPedidos,TAMP,&idPedido,auxId);
					printf("=PEDIDO=CARGADO=EXITOSAMENTE=\n");
				}
				else{
					printf("=NO=SE=PUDO=AGREGAR=EL=PEDIDO=\n");
				}
			}
			else{
				printf("=NO=SE=PUDO=MOSTRAR=CLIENTES=\n");
			}
			break;
		case 5://PROCESAR RESIDUOS
			system("cls");
			if(altas==0||idPedido==0){
				printf("==NO=HAY=PEDIDOS=DISPONIBLES==\n");
				break;
			}
			if(ImprimirPedidos(listPedidos,1000)){
				auxPos=BuscarPedidoPorId(listPedidos,1000,&auxId);
				if(listPedidos[auxPos].estado==1){
					printf("=NO=SE=PUDO=PROCESAR=EL=PEDIDO=\n");
					printf("=PEDIDO=YA=PROCESADO=\n");
				}
				else{
					if(auxPos>=0){
						if(ProcesarPedido(&listPedidos[auxPos])){
							printf("====PEDIDO=PROCESADO====\n");
						}
						else{
							printf("=NO=SE=PUDO=PROCESAR=EL=PEDIDO=\n");
						}
					}
				}
			}
			else{
				printf("=NO=SE=PUDO=IMPRIMIR=PEDIDOS=\n");
			}
			break;
		case 6://MENU INFORMES
			system("cls");
			if(altas==0||idPedido==0){
				printf("==NO=HAY=PEDIDOS=DISPONIBLES==\n");
				break;
			}
			do{
				MenuInformes(&opcionMenuInformes);
				switch(opcionMenuInformes){
				case 1://IMPRIMIR CLIENTES Y SUS PEDIDOS
					system("cls");
					printf("==INFORME=CLIENTES=Y=PEDIDOS=PENDIENTES==\n");
					printf("=ID=CLIENTE===============CUIT=========DIRECCION======LOCALIDAD====PENDIENTES======\n");
					if(InformeClientesYPedidosPendientes(listPedidos, TAMP, listCliente, TAMC,listLocalidad,TAML)){
						printf("====================================================================================\n");
					}
					else{
						printf("=ERROR=ERROR=ERROR=ERROR=ERROR=\n");
					}
					break;
				case 2://IMPRIMIR PEDIDOS PENDIENTES
					system("cls");
					printf("==INFORME=PEDIDOS=PENDIENTES==\n");
					printf("======CUIT========DIRECCION========KILOS===\n");
					if(InformePedidosPendientes(listPedidos, TAMP, listCliente, TAMC)){
						printf("===========================================\n");
					}
					else{
						printf("=ERROR=ERROR=ERROR=ERROR=ERROR=\n");
					}
					break;
				case 3://IMPRIMIR PEDIDOS PROCESADOS
					system("cls");
					printf("==INFORME=PEDIDOS=COMPLETADOS==\n");
					printf("======CUIT========DIRECCION=========HDPE====LDPE======PP======DESECHOS==\n");
					if(InformePedidosCompletados(listPedidos, TAMP, listCliente, TAMC)){
						printf("========================================================================\n");
					}
					else{
						printf("=ERROR=ERROR=ERROR=ERROR=ERROR=\n");
					}
					break;
				case 4://IMPRIMIR PEDIDOS PENDIENTES POR LOCALIDAD
					system("cls");
					printf("==INFORME=PEDIDOS=PENDIENTES=POR=LOCALIDAD==\n");
					printf("==LOCALIDAD===PENDIENTES====================\n");
					if(InformePedidosPendientesPorLocalidad(listCliente, TAMC,listPedidos, TAMP,listLocalidad,TAML)){
						printf("============================================\n");
					}
					else{
						printf("=ERROR=ERROR=ERROR=ERROR=ERROR=\n");
					}
					break;
				case 5://IMPRIMIR PROMEDIO DE POLIPROPILENO RECICLADO
					system("cls");
					printf("==INFORME=PROMEDIO=POLIPROPILENO=RECICLADO==\n");
					printf("==EMPRESA==========PROMEDIO==\n");
					if(InformePromedioPP(listPedidos, TAMP,listCliente, TAMC)){
						printf("=============================\n");
					}
					else{
						printf("=ERROR=ERROR=ERROR=ERROR=ERROR=\n");
					}
					break;
				case 6://ClienteMasPedidosPendientes
					system("cls");
					printf("==INFORME=CLIENTE=CON=MAS=PEDIDOS=PENDIENTE=\n");
					printf("==EMPRESA=========PENDIENTE=================\n");
					if(InformeClienteMasPedidosGenerico(listCliente, TAMC,listPedidos, TAMP,PENDIENTE)){
						printf("=============================================\n");
					}
					else{
						printf("=ERROR=ERROR=ERROR=ERROR=ERROR=\n");
					}
					break;
				case 7://ClienteMasPedidosCompletados
					system("cls");
					printf("==INFORME=CLIENTE=CON=MAS=PEDIDOS=COMPLETADOS=\n");
					printf("==EMPRESA========COMPLETADOS==================\n");
					if(InformeClienteMasPedidosGenerico(listCliente, TAMC,listPedidos, TAMP,COMPLETADO)){
						printf("===============================================\n");
					}
					else{
						printf("=ERROR=ERROR=ERROR=ERROR=ERROR=\n");
					}
					break;
				case 8://ClienteMasPedidos
					system("cls");
					printf("==INFORME=CLIENTE=CON=MAS=PEDIDOS=TOTALES=\n");
					printf("==EMPRESA=========TOTALES=================\n");
					if(InformeClienteMasPedidosGenerico(listCliente, TAMC,listPedidos, TAMP,TODO)){
						printf("===============================================\n");
					}
					else{
						printf("=ERROR=ERROR=ERROR=ERROR=ERROR=\n");
					}
					break;
				case 9:
					break;
				}
			}while(opcionMenuInformes!=9);
			break;
		case 7://FIN PROGRAMA
			system("cls");
			Firma();
			break;
		}
	}while(opcionMenu!=7);
	return EXIT_SUCCESS;
}
