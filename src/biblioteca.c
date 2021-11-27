
#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"
#include <string.h>
#include <ctype.h>
#include <windows.h>

/// @brief pide al usuario ingresar caracteres y de forma segura se guardan en una variable.
///
/// @param cadena - es el vector char en la cual se guarda lo que el usuario ingreso
/// @param tam - es el tamaño del vector char, usado para que no desborde el vector
/// @return
int MyGets(char* cadena,int tam){
	int retorno;
	retorno=1;
	fflush(stdin);
	fgets(cadena,tam,stdin);
	cadena[strlen(cadena)-1]='\0';
	if(strlen(cadena)==0){
		retorno=0;
	}
	return retorno;
}
/// @brief toma una cadena de caracteres y checkea que sea numerica del tipo Int
///
/// @param cadena - la cadena de caracteres a checkear
/// @return - retorna 1 si la cadena es numerica del tipo int y 0 si algun caracter no es valido para una variable int.
int EsInt(char* cadena){
	int retorno= 1;
	int i=0;
	if(cadena[0]=='-'){
		i=1;
	}
	for(;cadena[i]!='\0';i++){
		if(cadena[i]<'0'||cadena[i]>'9'){
			retorno=0;
			break;
		}
	}
	return retorno;
}
/// @brief toma una cadena de caracteres y checkea que sea numerica del tipo float
///
/// @param cadena - la cadena de caracteres a checkear
/// @return - retorna 1 si la cadena es numerica del tipo float y 0 si algun caracter no es valido para una variable float.
int EsFloat(char* cadena){
	int retorno= 1;
	int i=0;//inicializo la variable i aca para modificarla en el if de abajo, y no le meto nada en ese sector del for
	int contadorPunto=0;
	int esNegativo=0;
	if(cadena[0]=='-'){//checkeo si la poss 0 es un "-", si es asi, el for comienza desde 1 y no desde 0
		i=1;			//ya que la unica posicion valida para un menos en el la poss 0
		esNegativo=1;//pongo una vandera de que el numero es negativo
	}
	for(;cadena[i]!='\0';i++){//dejo vacio el primer argumento, por q ya esta definido arriba

		if(cadena[i]<'.'||(cadena[i]>'.'&&cadena[i]<'0')||cadena[i]>'9'){//ya descartado el "-" solo filtro numeros y punto
			//para entender el if este tenes q mirar el ascii
			retorno=0;//devuelve 0 si se encontro algo que no va y rompe
			break;
		}
		else{//si no es caracter invalido va a saltear el if y entrar aca

			if(cadena[i]=='.'){//aca le pregunto espesificamente si es un punto, y si es q lo cuente
				contadorPunto++;
				if(contadorPunto>1||(esNegativo==0&&i==0)||(esNegativo==1&&i==1)){//aca filtro el punto si hay mas de uno
					retorno=0;//y tambien la posicion que tiene en la cadena, no puede estar adelante de todo
					break;//si esta adelante de todo o hay mas de un punto retorno 0(error) y break.
				}
			}
		}
	}
	return retorno;
}
/// @brief checkea si es "texto basico", aceptando solo: ESPACIOS, a-z,A-Z,ñ-Ñ.
///
/// @param cadena - la cadena de caracteres a checkear
/// @return retorna 1 si la cadena es denominada como "texto basico" sino retorna 0.
int EsCharLetra(char caracter){
	int retorno= 1;

	if(caracter<65||(caracter>90&&caracter<97)||(caracter>122&&caracter<164)||caracter>165){
	retorno=0;
	}

	return retorno;
}
/// @brief verifica si es letras y espacios
///
/// @param cadena texto a verificar
/// @param tam tamaño de la cadena
/// @return
int EsCharNombre(char cadena[],int tam){
	int retorno;
	retorno=1;
	for(int i=0;cadena[i]!='\0';i++){
		if(EsCharLetra(cadena[i])==0&&cadena[i]!=32){
			retorno=0;
			break;
		}
	}
	return retorno;
}
/// @brief pide al usuario ingresar caracteres, los lee y checkea que que tenga un formato numero ENTERO
///
/// @param pResultado - el puntero por el cual devuelve el entero ingresado y validado.
/// @return - retorna 1 si el si lo que ingreso el usuario es convertible a int, sino retorna 0
int GetInt(int* pResultado){
	int retorno=0;
	char buffer[4096];

	if(MyGets(buffer,sizeof(buffer))&&EsInt(buffer)){
		retorno=1;
		*pResultado=atoi(buffer);
	}
	return retorno;
}
/// @brief pide al usuario ingresar caracteres, los lee y checkea que que tenga un formato de numero FLOAT
///
/// @param pResultado - el puntero por el cual devuelve el float ingresado y validado.
/// @return - retorna 1 si el si lo que ingreso el usuario es convertible a float, sino retorna 0
int GetFloat(float* pResultado){
	int retorno=0;
	char buffer[4096];
	if(MyGets(buffer,sizeof(buffer))&&EsFloat(buffer)){
		retorno=1;
		*pResultado=atof(buffer);
	}
	return retorno;
}
/// @brief funcion final para pedir un entero, utilizando varias funciones que le dan seguridad y otros agregando parametros
/// como Rango y Reintentos.
///
/// @param pResultado - puntero donde se guardara el numero ingresado por el usuario
/// @param mensaje	- mensaje en pantalla antes de pedir al usuario ingresar el numero.
/// @param mensajeError - mensaje de error por si el usuario no ingresa un numero valido.
/// @param minimo - el minimo valor aceptado.
/// @param maximo - el maximo valor aceptado
/// @param reintentos - la cantidad de reintentos por si falla constantemente.
/// @param retorno - 1 para okey - 0 si se le acavo los reintentos.
int GetIntRango(int* pResultado, char* mensaje,char* mensajeError,int minimo, int maximo, int reintentos){
	int retorno;
	int buffer;
	retorno=1;
	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&minimo<=maximo&&reintentos>=0){
		do{
			printf("%s",mensaje);
			if(GetInt(&buffer)==1&&buffer>=minimo&&buffer<=maximo){
				*pResultado=buffer;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;

		}while(reintentos>0);
	}
	if(reintentos==0){
		retorno=0;
	}
	return retorno;
}
/// @brief Pide al usuario que ingrese un dato del tipo float dentro de un rango, lo valida
/// 		, si pasa la validacion tiene un limite de reintentos pasados por parametro.
///
/// @param pResultado	puntero donde retornara el resultado
/// @param mensaje	mensaje que mostrara al usuario
/// @param mensajeError mensaje de error
/// @param minimo valor minimo permitido, incluyente
/// @param maximo valor maximo permitido, incluyente
/// @param reintentos - cantidad de reintentos que tiene el usuario
/// @return
int GetFloatRangoR(float* pResultado, char* mensaje,char* mensajeError,int minimo, int maximo, int reintentos){
	int retorno;
	float buffer;
	retorno=1;
	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&minimo<=maximo&&reintentos>=0){
		do{
			printf("%s",mensaje);
			if(GetFloat(&buffer)==1&&buffer>=minimo&&buffer<=maximo){
				*pResultado=buffer;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;

		}while(reintentos>0);
	}
	if(reintentos==0){
		retorno=0;
	}
	return retorno;
}
/// @brief funcion final para pedir un Nombre o Apellido, utilizando varias funciones que le dan seguridad y otros agregando parametros como mensaje, mensaje de error y Reintentos.
///
/// @param pResultado - el puntero donde se guarde lo ingresado por el usuario
/// @param tam - tamaño del puntero, para asegurarnos de no desbordar el vector.
/// @param mensaje	mensaje que vera el usuario antes de pedirle que ingrese datos
/// @param mensajeError - el mensaje que se mostrara si el usuario no ingresa datos validos.
/// @param reintentos - la cantidad de reintentos por si falla constantemente.
/// @param retorno - 1 para okey - 0 si se le acavo los reintentos.
///
int GetCharNombre(char*pResultado,int tam, char* mensaje,char* mensajeError, int reintentos){
	char buffer[4096];
	int retorno;
	retorno=1;
	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&reintentos>=0){
		do{
			printf("%s",mensaje);
			if(MyGets(buffer,tam)==1&&EsCharNombre(buffer,tam)==1){
				PrimerasLetrasMayuscula(buffer);
				strncpy(pResultado,buffer,tam);
				break;
			}
			printf("%s",mensajeError);
			reintentos--;

		}while(reintentos>0);
	}
	if(reintentos==0){
		retorno=0;
	}
	return retorno;
}
/// @brief toma una cadena de caracteres y devuelve la misma cadena con la primer letra de cada palabra mayuscula
///
/// @param mensaje - el vector char que se modificara
/// @return
int PrimerasLetrasMayuscula(char*mensaje){
	int i;
	mensaje[0]=toupper(mensaje[0]);
	for(i=1;mensaje[i]!='\0';i++){
		mensaje[i]=tolower(mensaje[i]);
		if(mensaje[i-1]==32){
			mensaje[i]=toupper(mensaje[i]);
		}
	}
	return 1;
}
/// @brief funcion final para pedir un numero int, utilizando varias funciones que le dan seguridad y otros agregando parametros como mensaje, mensaje de error y Reintentos.
///
///
/// @param pResultado - puntero que devuelve el numero ingresado
/// @param mensaje - mensaje que se le muestra al usuario antes de pedirle un numero
/// @param mensajeError - mensaje de error que se le muestra al usuario si ingresa algun caracter fuera de los permitidos
/// @param reintentos - cuantos intentos tiene el usuario de poder llegar a ingresar un numero correctamente
/// @param retorno - 1 para okey - 0 si se le acavo los reintentos.
int GetIntR(int*pResultado, char*mensaje,char*mensajeError, int reintentos){
	int retorno;
	int buffer;
	retorno=1;
	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&reintentos>=0){
		do{
			printf("%s",mensaje);
			if(GetInt(&buffer)==1){
				*pResultado=buffer;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;
		}while(reintentos>0);
	}
	if(reintentos==0){
		retorno=0;
	}
	return retorno;
}
/// @brief funcion final para pedir un numero float, utilizando varias funciones que le dan seguridad y otros agregando parametros como mensaje, mensaje de error y Reintentos.
/// @param pResultado - puntero que devuelve el numero ingresado
/// @param mensaje - mensaje que se le muestra al usuario antes de pedirle un numero
/// @param mensajeError - mensaje de error que se le muestra al usuario si ingresa algun caracter fuera de los permitidos
/// @param reintentos - cuantos intentos tiene el usuario de poder llegar a ingresar un numero correctamente
/// @param retorno - 1 para okey - 0 si se le acavo los reintentos.

int GetFloatR(float*pResultado,char*mensaje,char*mensajeError, int reintentos){
	int retorno;
	float buffer;

	retorno=1;
	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&reintentos>=0){
		do{
			printf("%s",mensaje);
			if(GetFloat(&buffer)==1){
				*pResultado=buffer;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;
		}while(reintentos>0);
	}
	if(reintentos==0){
			retorno=0;
		}
		return retorno;
}
/// @brief muestra el mensaje que hace una pregunta y pide como respuesta <s/n>
///
/// @param SorN - vector char donde guardara la respuesta, debe ser un vector[3]
/// @param mensaje - mensaje que se mostrara
/// @param mensajeError - mensaje de error si el usuario no ingresa s o n
/// @return

int GetCharSorN(char SorN[],char* mensaje,char* mensajeError){
	char buffer[3];
	int bandera=0;

	if(mensaje!=NULL&&mensajeError!=NULL){
		do{
			printf("%s",mensaje);
			if(MyGets(buffer,3)==1){
				buffer[0]=toupper(buffer[0]);
			}
			if(buffer[0]=='S'|| buffer[0]=='N'){
				bandera=1;
				strncpy(SorN,buffer,3);
				break;
			}
			printf("%s",mensajeError);
		}while(bandera==0);
	}
	return bandera;
}
/// @brief verifica si lo ingresado por el usuario es un cuit con el formato 00-00000000-0
///
/// @param cadena - la cadena que va a verificar
/// @param tam - el tamaño de la cadena
/// @return devuelve 1 si la verificacion es positiva y 0 si es negativa.
int EsCuit(char* cadena, int tam){
	int retorno;
	retorno=1;
	for(int i=0;cadena[i]!='\0';i++){
		if(strlen(cadena)==13){
			if((i==2&&cadena[i]!='-')||(i==11&&cadena[i]!='-')){
				retorno=0;
				break;
			}
			else{
				if((i!=2&&i!=11)&&!isdigit(cadena[i])){
					retorno=0;
					break;
				}
			}
		}
		else{
			retorno=0;
			break;
		}
	}
	return retorno;
}
/// @brief muestra un mensaje y pide al usuario que ingrese un cuit y verifica que sea correcto.
///
/// @param pResultado - donde enviara el resultado si el cuit es de formato valido
/// @param tam - tamaño del vector pResultado
/// @param mensaje - mensaje a mostrar
/// @param mensajeError - mensaje que se mostrara si el usuario no ingresa un cuit valido
/// @param reintentos - cantidad de reintentos que tendra el usuario
/// @return - devuelve 0 si se le acaban los reintentos y 1 si logra ingresar un cuit de formato valido
int GetCharCuit(char* pResultado,int tam, char* mensaje,char* mensajeError, int reintentos){
	char buffer[4096];
	int retorno;
	retorno=1;
	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&reintentos>=0){
		do{
			printf("%s",mensaje);
			if(MyGets(buffer,tam)==1&&EsCuit(buffer, tam)==1){
				strncpy(pResultado,buffer,tam);
				break;
			}
			printf("%s",mensajeError);
			reintentos--;

		}while(reintentos>0);
	}
	if(reintentos==0){
		retorno=0;
	}

	return retorno;
}
/// @brief verifica si el char es punto o coma '.' ','
///
/// @param cadena - char a verificar
/// @return retorna 0 si la verificacion no es correcta y 1 si es correcta
int EsCharPuntoComa(char* cadena){
	int retorno;
	retorno=0;
	if(*cadena=='.'||*cadena==','){
		retorno=1;
	}
	return retorno;
}
/// @brief verifica si la cadena de texto tiene un formato valido para una Direccion
///
/// @param cadena - la cadena a verificar
/// @param tam - tamaño de la cadena
/// @return devuelve 1 si pasa la verificacion y 0 si no la pasa.
int EsCharDireccion(char cadena[], int tam){
	int retorno;
	retorno=1;

	for(int i=0;cadena[i]!='\0';i++){
		if(!EsCharPuntoComa(&cadena[i])&&!isdigit(cadena[i])&&!EsCharLetra(cadena[i])&&cadena[i]!=32){
			retorno=0;
			break;
		}
	}
	return retorno;
}
/// @brief muestra un mensaje en pantalla y pide al usuario que ingrese un texto y valida que solo contenga
/// Letras Numeros Puntos y Comas LNPC
///
/// @param pResultado - Puntero donde se enviara el resultado si la validacion es exitosa
/// @param tam - tamaño del puntero
/// @param mensaje - mensaje que mostrara antes de pedirle al usuario el ingreso de datos
/// @param mensajeError - mensaje de error si no pasa la validacion
/// @param reintentos - cantiddad de reintentos que tiene el usuario si ingresa un dato invalido
/// @return devuelve 1 si sale todo ok y 0 si sale algo mal
int GetCharLNPC(char*pResultado,int tam, char* mensaje,char* mensajeError, int reintentos){
	char buffer[4096];
		int retorno;
		retorno=1;
		if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&reintentos>=0){
			do{
				printf("%s",mensaje);
				if(MyGets(buffer,tam)&&EsCharDireccion(buffer, tam)){
					strncpy(pResultado,buffer,tam);
					break;
				}
				printf("%s",mensajeError);
				reintentos--;

			}while(reintentos>0);
		}
		if(reintentos==0){
			retorno=0;
		}
		return retorno;
}
/// @brief pide texto sin verificacion con reintentos
///
/// @param pResultado cadena que el usuario ingreso
/// @param tam	 tamaño de la cadena
/// @param mensaje	 mensaje
/// @param mensajeError  mensaje de error si lo ingresado no es correcto
/// @param reintentos cantidad de reintentos por si falla el ingreso el usuario
/// @return
int GetCharR(char*pResultado,int tam, char* mensaje,char* mensajeError, int reintentos){
	char buffer[4096];
	int retorno;
	retorno=1;
	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&reintentos>=0){
		do{
			printf("%s",mensaje);
			if(MyGets(buffer,tam)==1){
				PrimerasLetrasMayuscula(buffer);
				strncpy(pResultado,buffer,tam);
				break;
			}
			printf("%s",mensajeError);
			reintentos--;

		}while(reintentos>0);
	}
	if(reintentos==0){
		retorno=0;
	}
	return retorno;
}

//FIRMA
void Firma(void){

	printf("========================================DANIEL MANRESA========================================\n");
	printf("||  ::::::::  :::::::::: ::::::::::   :::::::::  :::::::::: :::::::::   ::::::::  :::   ::: ||\n");
	printf("|| :+:    :+: :+:        :+:          :+:    :+: :+:        :+:    :+: :+:    :+: :+:   :+: ||\n");
	printf("|| +:+    +:+ +:+        +:+          +:+    +:+ +:+        +:+    +:+ +:+         +:+ +:+  ||\n");
	printf("|| +#+    +:+ :#::+::#   :#::+::#     +#++:++#+  +#++:++#   +#++:++#:  +#+          +#++:   ||\n");
	printf("|| +#+    +#+ +#+        +#+          +#+        +#+        +#+    +#+ +#+           +#+    ||\n");
	printf("|| #+#    #+# #+#        #+#          #+#        #+#        #+#    #+# #+#    #+#    #+#    ||\n");
	printf("||  ########  ###        ###          ###        ########## ###    ###  ########     ###    ||\n");
	printf("========================================DANIEL MANRESA========================================\n");
	Sleep(5000);
}
