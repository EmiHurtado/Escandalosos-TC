/*
NOMBRE DE PROGRAMA: Analizador de texto (segunda parte)
DESCRIPCIÓN: Partiendo de cualquier tipo de archivo, se lee de forma binaria y se guarda cada byte
en un arreglo del tamaño del archivo. Posteriormente, se hace un análisis del arreglo, para obtener
la información necesaria
FECHA: junio 2022
VERSIÓN: 2.0
AUTOR(ES): 
    Espinoza León Jaqueline Viridiana
	García Zacarías Angel Emmanuel
    Hurtado Morales Emiliano
*/

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************

#include <stdio.h>// Todas las funciones como fread, fwrite, fopen, fclose y printf
#include <stdlib.h>// EXIT_FAILURE y EXIT_SUCCESS
#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "cola.h"

#define TAM 100

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//*******************************************************************************

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************

void entradaDatos(char*, char*, struct stat);
float obtenerPorcentaje(float, struct stat);
void contarRes(char*, char*, struct stat, int);

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************

/*Descripcion de la función:
Funcion main, se ingresa el archivo a analizar y realiza todas las llamadas a funciones que permiten 
su análisis léxico. 
Input: Archivo de entrada.
Output: Ninguno.
*/

int main(int argc, char *argv[]) {

    //******************************************************************	
	//Variables del main
	//******************************************************************	
	
	FILE *archivo;
	char *nombreArchivo;
	char *arreglo;
	int *numC;
	int alt;
	int i;
	int k;
	int *sum;
	float tamor;
	float tamcom;
		char reser[74][17] = {{"asm\0"},{"auto\0"},{"bool\0"},{"catch\0"},{"compl\0"},{"continue\0"},{"do\0"},{"else\0"},{"export\0"},{"float\0"},{"goto\0"},{"int\0"},{"namespace\0"},{"or_eq\0"},{"public\0"},{"return\0"},{"sizeof\0"},{"struct\0"},{"this\0"},{"try\0"},{"typename\0"},{"not_eq\0"},{"using\0"},{"volatile\0"},{"and\0"},{"bitand\0"},{"break\0"},{"char\0"},{"const\0"},{"default\0"},{"double\0"},{"enum\0"},{"extern\0"},{"for\0"},{"if\0"},{"long\0"},{"new\0"},{"operator\0"},{"private\0"},{"register\0"},{"short\0"},{"static\0"},{"switch\0"},{"throw\0"},{"typedef\0"},{"union\0"},{"virtual\0"},{"wchar_t\0"},{"xor\0"},{"and_eq\0"},{"bitor\0"},{"case\0"},{"class\0"},{"const_cast\0"},{"delete\0"},{"dynamic_cast\0"},{"explicit\0"},{"false\0"},{"friend\0"},{"inline\0"},{"mutable\0"},{"not\0"},{"or\0"},{"protected\0"},{"reinterpret_cast\0"},{"signed\0"},{"static_cast\0"},{"template\0"},{"true\0"},{"typeid\0"},{"unsigned\0"},{"void\0"},{"xor_eq\0"},{"while\0"}};

	nombreArchivo = argv[1];
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	
	// Checa el tamaño del archivo y manda un error si no logra realizarlo
	struct stat sb;
	if (stat(nombreArchivo, &sb) == -1){
	    perror("stat");
	    exit(EXIT_FAILURE);
	}
	tamor = sb.st_size;
	
	// Se crea el arreglo dinámico
	arreglo = malloc(sizeof(char)*sb.st_size); 
	
	entradaDatos(nombreArchivo, arreglo, sb);
	
	sum[0] = 0;

	for(i = 0; i<74; i++){
		contarRes(arreglo,reser[i],sb,0);
	}	

	printf("\nHay %d cadenas.",i);
	
	return EXIT_SUCCESS;
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

// ////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion entradaDatos, permite la inserción de cada byte del archivo en el arreglo previamente creado.
Input: Puntero al archivo, puntero al arreglo y struct stat sb, que habilita saber de que tamaño es 
el archivo.
Output: Arreglo llenado completamente.
Observaciones: La inserción es muy rápida y no conlleva
mucho tiempo de procesamiento.
*/

void entradaDatos(char *nombreArchivo, char *arreglo, struct stat sb){
	char bufer[1];
	FILE *archivo;
	size_t bytesLeidos;
	int i;

	i = 0;

	archivo = fopen(nombreArchivo, "rb"); // Abrir en modo read binario
	// Si es NULL, entonces no existe, o no se pudo abrir
	if (!archivo) {
	    printf("¡No se pudo abrir el archivo %s!", nombreArchivo);
	}
	  
	// Mientras no alcancemos el EndOfLine del archivo...
	while (i<sb.st_size) {
	    // Leer dentro del búfer; fread regresa el número de bytes leídos
	    bytesLeidos = fread(bufer, sizeof(char), sizeof(bufer), archivo);
	    arreglo[i] = bufer[0];
	    i++;
	    
	}
	// Al final, se cierra el archivo
	fclose(archivo);
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion obtenerPorcentaje, se obtiene el porcentaje.
Input: un float que representa la frecuencia con la que se repite, struct de tipo stat, 
Output: retorna un porcentaje.
*/

float obtenerPorcentaje(float num, struct stat sb){
	return (num * 100 /sb.st_size);
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion contarRes, Cuenta las palabras reservadas.
Input: un arreglo del texto, la palabra reservada, struct de tipo stat, la posición y la suma total 
Output: void.
*/

void contarRes(char *arreglo, char *res, struct stat sb, int pos){
	// variables
	int i;
	int cont;
	int lon;

	lon = 0;
	cont = 1;
	// recorrido
	for(i = pos; i<sb.st_size;i++){
		//recorremos
		if(lon == strlen(res)){ // Son iguales por su longitud

		    if(arreglo[i] == '	' || arreglo[i] == ' ' || arreglo[i] == '\n' || arreglo[i] == '<' || arreglo[i] == '*' || arreglo[i] == '+' || arreglo[i] == '-'|| arreglo[i] == '['|| arreglo[i] == '{'|| arreglo[i] == '('|| arreglo[i] == ')'|| arreglo[i] == ';'|| arreglo[i] == ',' || arreglo[i] == '"') // revisamos el siguiente valor
		        cont++;
		    else lon = 0; //reseteamos la longitud de la palabra
		} else{
		    if(res[lon] == arreglo[i]){ // Si son iguales, su tamaño coincide
		        lon++;
		    } else lon = 0;
		}
	}
	if(cont > 1)
		printf("%s se repite %d veces, es un %0.4f %% \n", res ,cont, obtenerPorcentaje((float)(strlen(res) * cont),sb));	
	else 
		printf("%s se repite una vez, es un %0.4f %% \n", res , obtenerPorcentaje((float)(strlen(res)),sb));
}
