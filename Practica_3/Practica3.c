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
void creacionLista(list*, char*, struct stat);
void frecuenciaDatos(FILE*, list*, struct stat);

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
	
	creacionLista(lista, arreglo, sb);

	frecuenciaDatos(archivo, lista, sb);
	
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

void creacionLista(list *lista, char *arreglo, struct stat sb){
	//Variables lista
	int i=0, j, f, a;
	int bandera;
	huf *actual;
	huf *recorrer;
	huf *aux;
	
	// Crea la lista a partir del análisis del arreglo
	while(i<sb.st_size){
		bandera = 0;
		
		// Se revisa que no se repita el caracter en la lista
		actual = lista -> inicio;
		while(actual != NULL){
				if(actual -> car == arreglo[i]){
					bandera = 1;
					break;
				}
				actual = actual -> siguiente;
		}
		
		// Revisa que no esté repetido un caracter en la lista
		if(bandera != 1){
			
			// Se mide la frecuencia del caracter dentro del arreglo
			f=0;
			for(j=i ; j<sb.st_size ; j++)
				if(arreglo[i] == arreglo[j])
					f++;
			
			// Se crea el nodo y se insertan los valores
			actual = (huf*)malloc(sizeof(huf));
			actual -> car = arreglo[i];
			actual -> f = f;
			
			// Se aumenta el tamaño de la lista
			lista -> tam = lista -> tam + 1;
			
			// Creando nodo lista -> inicio 
        	if(lista -> inicio == NULL){   
				actual -> siguiente = NULL;
				actual-> anterior = NULL;
				lista -> inicio = actual;
			}
			else{
				if( lista -> fin == NULL){
					//creando nodo  lista -> fin 
					if(actual -> f >= lista -> inicio -> f){
						//nodo actual sera nuestro  lista -> fin 
						//si la actual -> f es mas pequeÃ±a que el lista -> inicio  lo manda a la 
						//derecha
						actual-> siguiente = NULL;
						actual-> anterior = lista -> inicio ;
						lista -> inicio -> siguiente = actual;
						 lista -> fin = actual;
					}
					else{
						//nodo auxlilar sera el lista -> inicio  y nuestro anterior erior lista -> 
						//inicio  el  lista -> fin 
						actual-> siguiente = lista -> inicio ;
						actual-> anterior = NULL;
						lista -> inicio -> anterior = actual;
						 lista -> fin = lista -> inicio ;
						lista -> inicio = actual;
					}
				}
				else{
					if(actual -> f >=  lista -> fin -> f){
						//nodo actual al  lista -> fin  de la lista
						//si la actual -> f es mas pequeña que el lista -> inicio  lo manda a la 
						//derecha
						actual -> siguiente = NULL;
						actual -> anterior = lista -> fin ;
						 lista -> fin -> siguiente = actual;
						 lista -> fin = actual;
					}
					else{
						if(actual -> f <= lista -> inicio -> f){
							//nodo actual al incio de la lista
							actual-> siguiente = lista -> inicio ;
							lista -> inicio -> anterior = actual;
							actual-> anterior = NULL;
							lista -> inicio = actual;	
						}
						else{
							//acomodar el actual en medio de nuestra lista recorriendo
							//nuestra lista desde el lista -> inicio 
							recorrer = lista -> inicio ;
							a = 0;
							while(a!=1)
							{
								//aux sera nuestro nodo anterior al que esta nuestro nodo recorrer
								aux = recorrer;
								recorrer = recorrer -> siguiente ;
								if(actual -> f < recorrer -> f)
								{
									actual -> siguiente = recorrer;
									recorrer -> anterior = actual;
									actual -> anterior = aux ;
									aux -> siguiente = actual;
									a = 1;
								}	
							}
						}
					}
				}
			}		
		}
		i++;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion frecuenciaDatos, Imprime los caracteres requeridos, su frecuencia y el número de pares.
Input: Puntero al archivo, puntero a la lista y struct stat sb, que habilita saber de que tamaño 
es el archivo.
Output: Impresión de información.
*/

void frecuenciaDatos(FILE* archivo, list* lista, struct stat sb)
{
	huf *actual;
	int aux1 = 0, aux2 = 0, aux3 = 0, aux4 = 0;
	
	// Mostrar la lista
	actual = lista -> inicio;
	if(actual == NULL)
		printf("\nLa lista esta vacia\n");
	else
	{
		printf("\nFrecuencia de cada caracter. \n\n");
		while(actual != lista -> fin)
		{
			if(actual -> car == '(' || actual -> car == ')')
			{
				if(actual -> car == '(')
				{
					aux1 = actual -> f;
				}
				else if(actual -> car == ')' && actual -> f < aux1)
				{
					aux1 = actual -> f;
				}
				printf("El caracter %c se repite %i veces \n", actual -> car, actual -> f);
				
			}
			else if(actual -> car == '{' || actual -> car == '}')
			{
				if(actual -> car == '{')
				{
					aux2 = actual -> f;
				}
				else if(actual -> car == '}' && actual -> f < aux2)
				{
					aux2 = actual -> f;
				}
				printf("El caracter %c se repite %i veces \n", actual -> car, actual -> f);
			}
			else if(actual -> car == '[' || actual -> car == ']')
			{
				if(actual -> car == '[')
				{
					aux3 = actual -> f;
				}
				else if(actual -> car == ']' && actual -> f < aux3)
				{
					aux3 = actual -> f;
				}
				printf("El caracter %c se repite %i veces \n", actual -> car, actual -> f);
				
			}
			else if(actual -> car == '<' || actual -> car == '>')
			{
				if(actual -> car == '<')
				{
					aux4 = actual -> f;
				}
				else if(actual -> car == '>' && actual -> f < aux4)
				{
					aux4 = actual -> f;
				}
				printf("El caracter %c se repite %i veces \n", actual -> car, actual -> f);
			}
			actual = actual -> siguiente;
		}
		printf("\n\nFrecuencia de cada par. \n\n");
		printf("El par de caracteres () aparece %i\n", aux1);
		printf("El par de caracteres {} aparece %i\n", aux2);
		printf("El par de caracteres [] aparece %i\n", aux3);
		printf("El par de caracteres <> aparece %i\n", aux4);
	}
}
