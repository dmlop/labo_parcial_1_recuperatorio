#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eCliente.h"
#include "eLocalidad.h"
#include "biblioteca.h"
/// @brief inicializa toda el vector con isEmpty=1
///
/// @param vector- vector de cliente a iniciar
/// @param tam - tamaño del vector
int ClienteInit(eCliente vector[],int tam){
	int retorno;
	retorno=0;
	for(int i=0;i<tam;i++){
		vector[i].isEmpty=1;
		retorno=1;
	}
	return retorno;

}
/// @brief Pide datos y agrega un cliente a la lista
///
/// @param vector - vector de clientes
/// @param tam - tamaño del vector de clientes
/// @param aux - auxiliar que guardara los datos ingresados por el usuario de forma momentanea
/// @param id - puntero del contador de id que se le asignara al nuevo cliente.
int AgregarCliente(eCliente vectorC[],int tam,int* idC,eLocalidad vectorL[],int tamL,int* idL){
	int retorno;
	eCliente auxC;

	retorno=0;

	if(PedirDatosNuevoCliente(&auxC,idC, vectorL,tamL,idL)){
		if(CargarCliente(vectorC,tam,auxC)>-1){
			*idC=*idC+1;
			retorno=1;
		}
	}
	return retorno;
}
/// @brief  buscara un lugar libre en la lista y copiara los datos guardados en la variable eCliente auxiliar
///   		a la lista de cliente en la posicion disponible.
///
/// @param vector - vector de clientes
/// @param tam - tamaño del vector de clientes
/// @param aux - variable eCliente auxiliar que contiene la informacion del nuevo cliente
/// @return devuelve -1 si hay algun problema. retorna la posicion encontrada libre en el vector de cliente
int CargarCliente(eCliente vector[],int tam,eCliente aux){
	int posicion;

	posicion=BuscarEmptyCliente(vector,tam);
	if(posicion!=-1){
		vector[posicion]=aux;
	}
	return posicion;
}
/// @brief Busca en un vector eCliente un lugar disponible para cargar un nuevo cliente.
///
/// @param vector - vector eCliente
/// @param tam - tamaño del vector eCliente
/// @return - devuelve -1 si hay algun problema. retorna la posicion libre encontrada en el vector cliente
int BuscarEmptyCliente(eCliente vector[],int tam){
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
/// @brief  Pide al usuario un id de un cliente activo, busca en el vector eCliente
/// 		un cliente con el mismo id y devuelve el id y la posicion del cliente
/// @param vector - vector eCliente
/// @param tam - tamaño del vector
/// @param auxId - puntero auxiliar del id ingresado por el usuario si es que se encontro un cliente con ese id
/// @return - devuelve -1 si no encontro ningun cliente con ese id y si encontro un cliente con la id ingresada
/// 		devuelve la posicion del cliente en el vector.
int BuscarClientePorId(eCliente vector[],int tam,int* auxId){
	int retorno;
	int id;
	retorno=-1;
	GetIntR(&id,"Ingrese el ID del cliente: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",4);

	for(int i=0;i<tam;i++){
		if(vector[i].id==id&&vector[i].isEmpty==0){
			retorno=i;
			*auxId=vector[i].id;
			break;
		}
	}
	return retorno;
}
/// @brief imprime una lista de clientes, mostrando su id y su nombre
///
/// @param vector - vector eCliente
/// @param tam - tamaño del vector
/// @return devuelve 0 si hay algun problema y 1 si no.
int ImprimirClientes(eCliente vector[],int tam){
	int retorno;
	retorno=0;
	for(int i=0;i<tam;i++){
		if(vector[i].isEmpty==0){
			printf("%d -- %s\n",vector[i].id,vector[i].nombreEmpresa);
			retorno=1;
		}
	}
	return retorno;
}
/// @brief Se le pasa como parametro un cliente y busca la localidad del cliente y
/// 		devuelve la posicion en el array de localidad que esta
///
/// @param cliente	Cliente elegido para la tarea
/// @param vectorL	vector de Localidad
/// @param tamL 	Tamaño del vector localidad
/// @return retorna la posicion del array de localidad
int BuscarLocalidadDelCliente(eCliente cliente,eLocalidad vectorL[],int tamL){
	int retorno;
	int i;
	retorno=-1;
	for(i=0;i<tamL;i++){
		if(vectorL[i].isEmpty==0&&vectorL[i].id==cliente.idL){
			retorno=i;
			break;
		}
	}
	return retorno;
}
/// @brief Modifica la direccion de un cliente,
///
/// @param cliente  Cliente que se le modificara su direccion.
/// @return
int ModificarDireccion(eCliente* cliente){
	int retorno;
	eCliente auxCliente;
	retorno=0;
	if(GetCharLNPC(auxCliente.direccion, 51, "Ingrese la Nueva Direccion de la Empresa: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",4)){
		strncpy(cliente->direccion,auxCliente.direccion,sizeof(cliente->direccion));
		retorno=1;
	}
	return retorno;
}
/// @brief Modifica la localidad de un cliente, verifica previamente si la nueva localidad
/// 		ya existe en el vector localidad y si no es asi se crea una nueva localidad
///
/// @param cliente	-Cliente que se le modificara su localidad
/// @param vectorL	-Vector de localidad
/// @param tamL		-Tamaño del vector de localidad
/// @param idL		-puntero al id de localidad por si es necesario crear una nueva localidad
/// @return
int ModificarLocalidad(eCliente* cliente,eLocalidad vectorL[],int tamL,int* idL){
	int retorno;
	int idLocalidad;
	eLocalidad auxLocalidad;
	retorno=0;

	GetCharLNPC(auxLocalidad.localidad, 51, "Ingrese la Nueva Localidad de la Empresa: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",99);

	idLocalidad=BuscarOAgregarLocalidad(vectorL, tamL, auxLocalidad.localidad, idL);
	if(idLocalidad>-1){
		cliente->idL=idLocalidad;
		retorno=1;
	}

	return retorno;
}
int PedirDatosNuevoCliente(eCliente* auxC,int* idC,eLocalidad vectorL[],int tamL,int* idL){
	int retorno;
	char localidad[51];
	int idLocalidad;
	retorno=0;

	GetCharR(auxC->nombreEmpresa, 51, "Ingrese el Nombre de la Empresa: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",99);
	GetCharCuit(auxC->cuit, 15, "Ingrese su CUIT: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 99);
	GetCharLNPC(auxC->direccion, 51, "Ingrese la Direccion: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 99);
	GetCharLNPC(localidad, 51, "Ingrese la Localidad: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 99);

	idLocalidad=BuscarOAgregarLocalidad(vectorL, tamL, localidad, idL);
	auxC->id=*idC;
	auxC->isEmpty=0;

	if(idLocalidad>-1){
		auxC->idL=idLocalidad;
		retorno=1;
	}

	return retorno;
}
//-----------------HARD CODE TEST-------------------
int ClientesTesteo(eCliente vector[],int *id,int* altas,int actividad){
	int retorno;
	retorno=0;
	if(actividad==1){
		retorno=1;
		vector[0].id=*id;
		vector[0].isEmpty=0;
		strncpy(vector[0].nombreEmpresa,"Marolio",51);
		strncpy(vector[0].cuit,"12-34940336-8",15);
		strncpy(vector[0].direccion,"Cantinfla 220",51);
		vector[0].idL=1;
		*id=*id+1;
		*altas=*altas+1;

		vector[1].id=*id;
		vector[1].isEmpty=0;
		strncpy(vector[1].nombreEmpresa,"HellsMans",51);
		strncpy(vector[1].cuit,"12-34231336-8",15);
		strncpy(vector[1].direccion,"cervantes 1220",51);
		vector[1].idL=1;
		*id=*id+1;
		*altas=*altas+1;

		vector[2].id=*id;
		vector[2].isEmpty=0;
		strncpy(vector[2].nombreEmpresa,"Danica",51);
		strncpy(vector[2].cuit,"12-33240336-8",15);
		strncpy(vector[2].direccion,"Lafayette 720",51);
		vector[2].idL=2;
		*id=*id+1;
		*altas=*altas+1;

		vector[3].id=*id;
		vector[3].isEmpty=0;
		strncpy(vector[3].nombreEmpresa,"CocaCola",51);
		strncpy(vector[3].cuit,"12-34979826-8",15);
		strncpy(vector[3].direccion,"Lagos 1997",51);
		vector[3].idL=3;
		*id=*id+1;
		*altas=*altas+1;

		vector[4].id=*id;
		vector[4].isEmpty=0;
		strncpy(vector[4].nombreEmpresa,"Pepsi",51);
		strncpy(vector[4].cuit,"12-11140336-8",15);
		strncpy(vector[4].direccion,"Burruchaga 220",51);
		vector[4].idL=3;
		*id=*id+1;
		*altas=*altas+1;

		vector[5].id=*id;
		vector[5].isEmpty=0;
		strncpy(vector[5].nombreEmpresa,"Manaos",51);
		strncpy(vector[5].cuit,"12-10940336-8",15);
		strncpy(vector[5].direccion,"La Carra 220",51);
		vector[5].idL=3;
		*id=*id+1;
		*altas=*altas+1;

		vector[6].id=*id;
		vector[6].isEmpty=0;
		strncpy(vector[6].nombreEmpresa,"Felizia",51);
		strncpy(vector[6].cuit,"12-34232136-8",15);
		strncpy(vector[6].direccion,"Italia 20",51);
		vector[6].idL=4;
		*id=*id+1;
		*altas=*altas+1;

		vector[7].id=*id;
		vector[7].isEmpty=0;
		strncpy(vector[7].nombreEmpresa,"La Compostela",51);
		strncpy(vector[7].cuit,"22-76543336-8",15);
		strncpy(vector[7].direccion,"La Trota 1098",51);
		vector[7].idL=4;
		*id=*id+1;
		*altas=*altas+1;

		vector[8].id=*id;
		vector[8].isEmpty=0;
		strncpy(vector[8].nombreEmpresa,"Cunninton",51);
		strncpy(vector[8].cuit,"12-34978954-1",15);
		strncpy(vector[8].direccion,"Puerredon 501",51);
		vector[8].idL=3;
		*id=*id+1;
		*altas=*altas+1;

		vector[9].id=*id;
		vector[9].isEmpty=0;
		strncpy(vector[9].nombreEmpresa,"Paladini",51);
		strncpy(vector[9].cuit,"12-34999886-8",15);
		strncpy(vector[9].direccion,"San Martin 1235",51);
		vector[9].idL=4;
		*id=*id+1;
		*altas=*altas+1;

		vector[10].id=*id;
		vector[10].isEmpty=0;
		strncpy(vector[10].nombreEmpresa,"Calchaqui",51);
		strncpy(vector[10].cuit,"14-34440336-8",15);
		strncpy(vector[10].direccion,"Sarmiento 9281",51);
		vector[10].idL=2;
		*id=*id+1;

		*altas=*altas+1;

		vector[11].id=*id;
		vector[11].isEmpty=0;
		strncpy(vector[11].nombreEmpresa,"Vienisima",51);
		strncpy(vector[11].cuit,"12-34123336-8",15);
		strncpy(vector[11].direccion,"Rotta 9478",51);
		vector[11].idL=1;
		*id=*id+1;
		*altas=*altas+1;
	}
	return retorno;
}

