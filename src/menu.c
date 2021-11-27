#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

/// @brief Menu que mostrara el programa constantemente y pide ingresar la opcion que usuario quiera
///
/// @param pResultado - puntero que devolvera la opcion que el usuario haya ingresado.

void Menu(int*pOpcion){
	printf("\n=================MENU=================\n");
	printf("||1.Alta Cliente.\n");
	printf("||2.Modificar Datos.\n");
	printf("||3.Baja Cliente.\n"
			"||4.Crear pedido de recoleccion.\n"
			"||5.Procesar Residuos.\n"
			"||6.Informes.\n"
			"||7.Salir.\n"
			"=======================================\n");

	if(GetIntRango(pOpcion,"Ingrese la opcion elegida: ","ERROR! NUMERO INVALIDO!\n",1,7,4)==0){
		printf("Se agotaron los intentos!");
		*pOpcion=-1;
	}
}
/// @brief Menu de modificacion que pide ingresar la opcion que usuario quiera
/// @param pOpcion la opcion elejida por el usuario
void MenuModificacion(int*pOpcion){

	printf("\n============MENU=MODIFICACION===========\n");
	printf("||1.Modificar Direccion del Cliente.\n");
	printf("||2.Modificar Localidad del Cliente.\n");
	printf("=======================================\n");

	if(GetIntRango(pOpcion,"Ingrese el numero de la modificacion deseada: ","ERROR! NUMERO INVALIDO!\n",1,2,4)==0){
		printf("Se agotaron los intentos!");
		*pOpcion=-1;
	}

}
/// @brief Menu de informes que mostrara el programa constantemente y pide ingresar la opcion que usuario quiera
/// @param pOpcion la opcion elejida por el usuario
void MenuInformes(int*pOpcion){

	printf("\n============MENU=LISTADO===========\n");
	printf("||1.Imprimir Clientes.\n");
	printf("||2.Imprimir Pedidos pendientes.\n");
	printf("||3.Imprimir Pedidos procesados.\n");
	printf("||4.Imprimir Pedidos por Localidad.\n");
	printf("||5.Imprimir polipropileno reciclado.\n");
	printf("||6.Imprimir Cliente mas pedidos pendientes.\n");
	printf("||7.Imprimir Cliente mas pedidos completados.\n");
	printf("||8.Imprimir Cliente mas pedidos.\n");
	printf("||9.Volver.\n");
	printf("=======================================\n");

	GetIntRango(pOpcion,"Ingrese el numero de la opcion deseada: ","ERROR! NUMERO INVALIDO!\n",1,9,99);
}

