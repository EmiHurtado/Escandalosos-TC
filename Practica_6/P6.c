/*
NOMBRE DE PROGRAMA: Analizador de Texto
DESCRIPCIÓN: Partiendo de cualquier tipo de archivo, se lee de forma binaria y se guarda cada byte
en un arreglo del tamaño del archivo. Posteriormente, se hace un análisis del arreglo con el objetivo
de contabilizar el numero de letras, numeros y signos, para que al final muestre la cantidad de
veces que se repite junto con el porcentaje.
FECHA: mayo 2022
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
void analisisLexico(char*, struct stat);
float obtenerPorcentaje(float, struct stat);

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
	float tamor;
	float tamcom;

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
	
	analisisLexico(arreglo, sb);
	
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
Funcion analisisLexico, se realiza todo el análisis del archivo y se contabilizan los caracteres, numeros y
		simbolos.
Input: puntero de char, struct de tipo stat, 
Output: no retorna nada.
*/

void analisisLexico(char *arreglo, struct stat sb){
	//Variables
	int frecuencias[TAM];
	int i;
	// Banderas para enteros y decimales
	int f_dec = 0;
	int sum;

	char dato[94] = {'(',')','[',']','{','}','<','>','&','|','+','-','*','/','%','=',',',';',':','.','#','^','~',34,'?',168,'!',173,'_','$','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',92,39};
	
	//Estadarización de las frecuencias
	for(i = 0 ; i < TAM ; i++)
		frecuencias[i] = 0;
	
	sum  = 0;

	//Análisis
	for(i = 0 ; i < sb.st_size ; i++)
	{
		if(arreglo[i] == '(')
			frecuencias[0]++;
		else if(arreglo[i] == ')')
			frecuencias[1]++;
		else if(arreglo[i] == '[')
			frecuencias[2]++;
		else if(arreglo[i] == ']')
			frecuencias[3]++;
		else if(arreglo[i] == '{')
			frecuencias[4]++;
		else if(arreglo[i] == '}')
			frecuencias[5]++;
		else if(arreglo[i] == '<')
			frecuencias[6]++;
		else if(arreglo[i] == '>')
			frecuencias[7]++;
		else if(arreglo[i] == '&')
			frecuencias[8]++;
		else if(arreglo[i] == '|')
			frecuencias[9]++;
		else if(arreglo[i] == '+')
			frecuencias[10]++;
		else if(arreglo[i] == '-')
			frecuencias[11]++;		
		else if(arreglo[i] == '*')
			frecuencias[12]++;
		else if(arreglo[i] == '/')
			frecuencias[13]++;
		else if(arreglo[i] == '%')
			frecuencias[14]++;
		else if(arreglo[i] == '=')
			frecuencias[15]++;
		else if(arreglo[i] == ',')
			frecuencias[16]++;
		else if(arreglo[i] == ';')
			frecuencias[17]++;
		else if(arreglo[i] == ':')
			frecuencias[18]++;
		else if(arreglo[i] == '.')
			frecuencias[19]++;
		else if(arreglo[i] == '#')
			frecuencias[20]++;
		else if(arreglo[i] == '^')
			frecuencias[21]++;
		else if(arreglo[i] == '~')
			frecuencias[22]++;
		else if(arreglo[i] == '"')
			frecuencias[23]++;
		else if(arreglo[i] == '?')
			frecuencias[24]++;
		else if(arreglo[i] == 168)
			frecuencias[25]++;
		else if(arreglo[i] == '!')
			frecuencias[26]++;
		else if(arreglo[i] == 173)
			frecuencias[27]++;
		else if(arreglo[i] == '_')
			frecuencias[28]++;
		else if(arreglo[i] == '$')
			frecuencias[29]++;
		else if(arreglo[i] == '0')
			frecuencias[30]++;
		else if(arreglo[i] == '1')
			frecuencias[31]++;
		else if(arreglo[i] == '2')
			frecuencias[32]++;
		else if(arreglo[i] == '3')
			frecuencias[33]++;
		else if(arreglo[i] == '4')
			frecuencias[34]++;
		else if(arreglo[i] == '5')
			frecuencias[35]++;
		else if(arreglo[i] == '6')
			frecuencias[36]++;
		else if(arreglo[i] == '7')
			frecuencias[37]++;
		else if(arreglo[i] == '8')
			frecuencias[38]++;
		else if(arreglo[i] == '9')
			frecuencias[39]++;
		else if(arreglo[i] == 'a')
			frecuencias[40]++;
		else if(arreglo[i] == 'b')
			frecuencias[41]++;
		else if(arreglo[i] == 'c')
			frecuencias[42]++;
		else if(arreglo[i] == 'd')
			frecuencias[43]++;
		else if(arreglo[i] == 'e')
			frecuencias[44]++;
		else if(arreglo[i] == 'f')
			frecuencias[45]++;
		else if(arreglo[i] == 'g')
			frecuencias[46]++;
		else if(arreglo[i] == 'h')
			frecuencias[47]++;
		else if(arreglo[i] == 'i')
			frecuencias[48]++;
		else if(arreglo[i] == 'j')
			frecuencias[49]++;
		else if(arreglo[i] == 'k')
			frecuencias[50]++;
		else if(arreglo[i] == 'l')
			frecuencias[51]++;
		else if(arreglo[i] == 'm')
			frecuencias[52]++;
		else if(arreglo[i] == 'n')
			frecuencias[53]++;
		else if(arreglo[i] == 'o')
			frecuencias[54]++;
		else if(arreglo[i] == 'p')
			frecuencias[55]++;
		else if(arreglo[i] == 'q')
			frecuencias[56]++;
		else if(arreglo[i] == 'r')
			frecuencias[57]++;
		else if(arreglo[i] == 's')
			frecuencias[58]++;
		else if(arreglo[i] == 't')
			frecuencias[59]++;
		else if(arreglo[i] == 'u')
			frecuencias[60]++;
		else if(arreglo[i] == 'v')
			frecuencias[61]++;
		else if(arreglo[i] == 'w')
			frecuencias[62]++;
		else if(arreglo[i] == 'x')
			frecuencias[63]++;
		else if(arreglo[i] == 'y')
			frecuencias[64]++;
		else if(arreglo[i] == 'z')
			frecuencias[65]++;
		else if(arreglo[i] == 'A')
			frecuencias[66]++;
		else if(arreglo[i] == 'B')
			frecuencias[67]++;
		else if(arreglo[i] == 'C')
			frecuencias[68]++;
		else if(arreglo[i] == 'D')
			frecuencias[69]++;
		else if(arreglo[i] == 'E')
			frecuencias[70]++;
		else if(arreglo[i] == 'F')
			frecuencias[71]++;
		else if(arreglo[i] == 'G')
			frecuencias[72]++;
		else if(arreglo[i] == 'H')
			frecuencias[73]++;
		else if(arreglo[i] == 'I')
			frecuencias[74]++;
		else if(arreglo[i] == 'J')
			frecuencias[75]++;
		else if(arreglo[i] == 'K')
			frecuencias[76]++;
		else if(arreglo[i] == 'L')
			frecuencias[77]++;
		else if(arreglo[i] == 'M')
			frecuencias[78]++;
		else if(arreglo[i] == 'N')
			frecuencias[79]++;
		else if(arreglo[i] == 'O')
			frecuencias[80]++;
		else if(arreglo[i] == 'P')
			frecuencias[81]++;
		else if(arreglo[i] == 'Q')
			frecuencias[82]++;
		else if(arreglo[i] == 'R')
			frecuencias[83]++;
		else if(arreglo[i] == 'S')
			frecuencias[84]++;
		else if(arreglo[i] == 'T')
			frecuencias[85]++;
		else if(arreglo[i] == 'U')
			frecuencias[86]++;
		else if(arreglo[i] == 'V')
			frecuencias[87]++;
		else if(arreglo[i] == 'W')
			frecuencias[88]++;
		else if(arreglo[i] == 'X')
			frecuencias[89]++;
		else if(arreglo[i] == 'Y')
			frecuencias[90]++;
		else if(arreglo[i] == 'Z')
			frecuencias[91]++;
		else if(arreglo[i] == 92)
			frecuencias[92]++;
		else if(arreglo[i] == 39)
			frecuencias[93]++;

	}

	for(i = 0; i<94; i++){
		sum += frecuencias[i];
	}

	for(i = 0; i<94; i++){
		printf("%c se encuentra %i veces, es un %0.4f %% \n", dato[i], frecuencias[i], obtenerPorcentaje((float)frecuencias[i],sb));
	}
}