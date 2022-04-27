/*
NOMBRE DE PROGRAMA: Análisis léxico
DESCRIPCIÓN: Partiendo de cualquier tipo de archivo, se lee de forma binaria y se guarda cada byte
en un arreglo del tamaño del archivo. Posteriormente, se hace un análisis del arreglo, para obtener
una lista ordenada. De esta forma, se consigue la frecuencia de cada byte y se presenta sólo la 
información de los carácteres necesarios.
FECHA: abril 2022
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

#define TAM 100

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

/*Descripción de estructura: huf
Esctructura que simula un nodo.
Cada nodo, posee el byte deseado y las veces que se repite dentro del archivo original. Asimismo, 
tiene los apuntadores siguiente y anterior para crear la lista.
*/

typedef struct nodo{
	char car;
	int f;
	// Apuntadores para la lista
	struct nodo *siguiente;
	struct nodo *anterior;
}huf;

/*Descripción de estructura: ListaDoble
Estructura que tiene los apuntadores al principio y fin de la cola.
*/

typedef struct ListaDoble{
	huf *inicio;
	huf *fin;
	int tam;
}list;

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************

void entradaDatos(char*, char*, struct stat);
void analisisLexico(char*, struct stat);

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
	char *nombreArchivo = argv[1];
	char *arreglo;
	int *numC;
	int alt, i, k;
	list *lista;
	float tamor, tamcom;
	
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
	
	// Inicializa memoria lista
	lista = (list *)malloc(sizeof(list));
	
	// Inicializa estructura
	lista -> inicio = NULL;
	lista -> fin = NULL;
	lista -> tam = 0;
	
	entradaDatos(nombreArchivo, arreglo, sb);
	
	analisisLexico(arreglo, sb);
	
	return EXIT_SUCCESS;
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

//////////////////////////////////////////////////////////////////////////////////////////////

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
	int i=0;
	
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
Funcion creacionLista, se realiza todo el análisis necesario para poder crear una lista ordenada, 
al observar que no se repitan caracteres dentro de ella y que se sepa cuantas veces aparece cada 
byte en el archivo.
Input: Puntero al struct lista, puntero al arreglo y struct stat sb, que habilita saber de que 
tamaño es el archivo.
Output: Lista creada y ordenada.
*/

void analisisLexico(char *arreglo, struct stat sb){
	//Variables
	int frecuencias[TAM];
	int i;
	
	//Estadarización de las frecuencias
	for(i = 0 ; i < TAM ; i++)
		frecuencias[i] = 0;
	
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
		// Agregados de operadores aritméticos
		else if(arreglo[i] == '<' && arreglo[i+1] == '=')
			frecuencias[20]++;
		else if(arreglo[i] == '>' && arreglo[i+1] == '=')
			frecuencias[21]++;
		/////////////////////////////////////////////////
		else if(arreglo[i] == '<')
			frecuencias[6]++;
		else if(arreglo[i] == '>')
			frecuencias[7]++;
		// Operadores lógicos: &&, ||, ! (3)
		else if(arreglo[i] == '&' && arreglo[i+1] == '&')
			frecuencias[8]++;
		else if(arreglo[i] == '|' && arreglo[i+1] == '|')
			frecuencias[9]++;
		else if(arreglo[i] == '!')
			frecuencias[10]++;
		// Operadores aritméticos: (11)
		else if(arreglo[i] == '+' && arreglo[i+1] == '+')
			frecuencias[11]++;
		else if(arreglo[i] == '+')
			frecuencias[12]++;
		else if(arreglo[i] == '-' && arreglo[i+1] == '-')
			frecuencias[13]++;
		else if(arreglo[i] == '-')
			frecuencias[14]++;
		else if(arreglo[i] == '*')
			frecuencias[15]++;
		else if(arreglo[i] == '/')
			frecuencias[16]++;
		else if(arreglo[i] == '%')
			frecuencias[17]++;
		else if(arreglo[i] == '=' && arreglo[i+1] == '=')
			frecuencias[18]++;
		else if(arreglo[i] == '=')
			frecuencias[19]++;
	}
	printf("\nFrecuencia de cada caracter. \n\n");
	printf("Caracteres. \n");
	printf("El caracter ( se repite %i veces \n", frecuencias[0]);
	printf("El caracter ) se repite %i veces \n", frecuencias[1]);
	printf("El caracter [ se repite %i veces \n", frecuencias[2]);
	printf("El caracter ] se repite %i veces \n", frecuencias[3]);
	printf("El caracter { se repite %i veces \n", frecuencias[4]);
	printf("El caracter } se repite %i veces \n", frecuencias[5]);
	printf("El caracter < se repite %i veces \n", frecuencias[6]);
	printf("El caracter > se repite %i veces \n", frecuencias[7]);
	printf("\nOperadores logicos. \n");
	printf("El operador && se repite %i veces \n", frecuencias[8]);
	printf("El operador || se repite %i veces \n", frecuencias[9]);
	printf("El operador ! se repite %i veces \n", frecuencias[10]);
	printf("\nOperadores aritmeticos. \n");
	printf("El operador ++ se repite %i veces \n", frecuencias[11]);
	printf("El operador + se repite %i veces \n", frecuencias[12]);
	printf("El operador -- se repite %i veces \n", frecuencias[13]);
	printf("El operador - se repite %i veces \n", frecuencias[14]);
	printf("El operador * se repite %i veces \n", frecuencias[15]);
	printf("El operador / se repite %i veces \n", frecuencias[16]);
	printf("El operador %c se repite %i veces \n", 37, frecuencias[17]);
	printf("El operador == se repite %i veces \n", frecuencias[18]);
	printf("El operador = se repite %i veces \n", frecuencias[19]);
	printf("El operador <= se repite %i veces \n", frecuencias[20]);
	printf("El operador >= se repite %i veces \n", frecuencias[21]);
	printf("\n\n\nFrecuencia de cada par. \n\n");
	printf("El par de caracteres () aparece %i\n", frecuencias[0] < frecuencias[1] ? frecuencias[0] : frecuencias[1]);
	printf("El par de caracteres {} aparece %i\n", frecuencias[2] < frecuencias[3] ? frecuencias[2] : frecuencias[3]);
	printf("El par de caracteres [] aparece %i\n", frecuencias[4] < frecuencias[5] ? frecuencias[4] : frecuencias[5]);
	printf("El par de caracteres <> aparece %i\n", frecuencias[6] < frecuencias[7] ? frecuencias[6] : frecuencias[7]);
}