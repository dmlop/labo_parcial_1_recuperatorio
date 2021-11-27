

#ifndef BIBLIOTECA_H_
#define BIBLIOTECA_H_

int MyGets(char* cadena,int tam);
int GetInt(int* pResultado);
int GetFloat(float* pResultado);
int EsInt(char* cadena);
int EsFloat(char* cadena);
int GetIntRango(int*pResultado,char*mensaje,char*mensajeError,int minimo, int maximo, int reintentos);
int GetFloatRangoR(float* pResultado, char* mensaje,char* mensajeError,int minimo, int maximo, int reintentos);
int EsCharLetra(char cadena);
int EsCharNombre(char cadena[],int tam);
int GetCharNombre(char*,int, char*,char*,int);
int PrimerasLetrasMayuscula(char*mensaje);
int GetCharSorN(char SorN[],char* mensaje,char* mensajeError);
int GetIntR(int*pResultado, char* mensaje,char* mensajeError,int reintentos);
int GetFloatR(float* pResultado, char* mensaje,char* mensajeError,int reintentos);
int EsCuit(char* mensaje, int tam);
int GetCharCuit(char* pResultado,int tam, char* mensaje,char* mensajeError, int reintentos);
int EsCharPuntoComa(char* cadena);
int EsCharDireccion(char cadena[], int tam);
int GetCharLNPC(char*pResultado,int tam, char* mensaje,char* mensajeError, int reintentos);
int GetCharR(char*pResultado,int tam, char* mensaje,char* mensajeError, int reintentos);
//FIRMA
void Firma(void);

#endif /* BIBLIOTECA_H_ */
