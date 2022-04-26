/*
NOMBRE DE PROGRAMA: Algoritmo de Huffman - Codificacion
DESCRIPCIÓN: Partiendo de cualquier tipo de archivo, se lee de forma binaria y se guarda cada byte en un arreglo del tamaño del archivo. 
Posteriormente, se hace un análisis del arreglo, para obtener una lista ordenada. Después, se crea un árbol binario de abajo para arriba, usando como hojas, 
los nodos de la lista y como raices, la suma de sus frecuencias. Finalmente, se escribe el archivo intercambiando cada caracter por el camino de unos y ceros 
que se obtiene al recorre el ABB, para obtener el archivo codificacion.txt y frecuencias.txt.
Observación: Se usa como apoyo el archivo auxiliar.txt, pero este es creado a mitad del programa y la decodificacion no requiere de este.
FECHA: noviembre 2021
VERSIÓN: 1.5
AUTOR(ES): 
    González Pérez Vanessa Berenice
    Hurtado Morales Emiliano
    Islas Osorio Enrique
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
#include "tiempo.h"

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

/*Descripción de estructura: huf
Esctructura que simula un nodo, ya sea para la cola o el árbol.
Cada nodo, posee el byte deseado y las veces que se repite dentro del archivo original. Asimismo, tiene los apuntadores siguiente y anterior para crear la lista; y uno y cero para crear el árbol.
*/

typedef struct nodo{
	char car;
	int f;
	// Apuntadores para el árbol binario
	struct nodo *cero;
	struct nodo *uno;
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
void creacionArbol(list*, char*, struct stat);
void preorden(huf*, int);
int altura(huf*);
void codigo(huf*, int*, int, FILE*, char*, int);
void compresion(char*, int inicio, int fin, FILE*);

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************

/*Descripcion de la función:
Funcion main, se ingresa el archivo a codificar y realiza todas las llamadas a funciones que permiten su codificación. Asimismo, toma el tiempo que tarda el proceso en realizarse.
Input: Archivo de entrada.
Output: Tamaños en bytes del archivo original, comprimido, porcentaje de compresión y tiempo de proceso.
*/

int main(int argc, char *argv[]) {

    //******************************************************************	
	//Variables del main
	//******************************************************************	
    
	double utime0, stime0, wtime0,utime1, stime1, wtime1; 
	
	FILE *archivo;
	char *nombreArchivo = argv[1];
	char *nombreArchivo3 = "auxiliar.txt";
	char *arreglo;
	int *numC;
	int alt, i, k;
	list *lista;
	float tamor, tamcom;
	
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	
	uswtime(&utime0, &stime0, &wtime0);
	
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

	creacionArbol(lista, arreglo, sb);
	
	//Mostrar arbol
	//preorden(lista -> inicio,0);
	
	// Altura del árbol
	alt = altura(lista -> inicio);
	
	// Arreglo para guardar  unos y ceros
	numC = malloc(sizeof(int)*alt);
	
	// CODIFICACIÓN
	FILE  *fp = fopen("auxiliar.txt","wb");
	i = 0;
	for(k = 0 ; k < sb.st_size ; k++)	
	{
		codigo(lista -> inicio, numC, i, fp, arreglo, k);
		
	}
		
	fclose(fp);
	
	// Compresion
	if (stat("auxiliar.txt", &sb) == -1){
	    perror("stat");
	    exit(EXIT_FAILURE);
	}

	arreglo = malloc(sizeof(char)*sb.st_size); 
	entradaDatos(nombreArchivo3, arreglo, sb);
	FILE *fp3 = fopen("codificacion.txt","wb");
	
	for(i=0;i<sb.st_size;i+=8)
	{
		compresion(arreglo,i,i+7,fp3);
	}
		
	fclose(fp3);
	
	uswtime(&utime1, &stime1, &wtime1);
	
	if (stat("codificacion.txt", &sb) == -1){
	    perror("stat");
	    exit(EXIT_FAILURE);
	}
	
	tamcom = sb.st_size;
	
	if (stat("auxiliar.txt", &sb) == -1){
	    perror("stat");
	    exit(EXIT_FAILURE);
	}
	
	//******************************************************************	
	//Evaluar información de los archivos y tiempo de ejecución
	//******************************************************************
	
	printf("Archivo: %s\n", argv[1]);
	printf("Tamano del archivo original en bytes: %.0f\n", tamor);
	printf("Tamano del archivo comprimido en bytes: %.0f\n", tamcom);
	printf("Bits necesarios: %i\n", sb.st_size);
	printf("Porcentaje de compresion: %.3f\n", 100 - 100 * tamcom/tamor);
	printf("real (Tiempo total)  %.10f s\n\n",  wtime1 - wtime0);
	
	return EXIT_SUCCESS;
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion entradaDatos, permite la inserción de cada byte del archivo en el arreglo previamente creado.
Input: Puntero al archivo, puntero al arreglo y struct stat sb, que habilita saber de que tamaño es el archivo.
Output: Arreglo llenado completamente.
Observaciones: La inserción es muy rápida y no conlleva
mucho tiempo de procesamiento.
*/

void entradaDatos(char *nombreArchivo, char *arreglo, struct stat sb){
	char bufer[1];
	FILE *archivo;
	size_t bytesLeidos;
	int i=0;
	
	//printf("%i", sb.st_size);
	archivo = fopen(nombreArchivo, "rb"); // Abrir en modo read binario
	// Si es NULL, entonces no existe, o no se pudo abrir
	if (!archivo) {
	    printf("¡No se pudo abrir el archivo %s!", nombreArchivo);
	    //return EXIT_FAILURE;
	}
	  
	// Mientras no alcancemos el EndOfLine del archivo...
	while (i<sb.st_size) {
	    // Leer dentro del búfer; fread regresa el número de bytes leídos
	    bytesLeidos = fread(bufer, sizeof(char), sizeof(bufer), archivo);
	    arreglo[i] = bufer[0];
	    // Para depurar, se imprime la cantidad de bytes leídos (se puede quitar esa parte)
	    //printf("\nSe han leido %lu bytes: %o % c\n", bytesLeidos, arreglo[i], arreglo[i]);
	    i++;
	    
	}
	// Al final, se cierra el archivo
	fclose(archivo);
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion creacionLista, se realiza todo el análisis necesario para poder crear una lista ordenada, al observar que no 
se repitan caracteres dentro de ella y que se sepa cuantas veces aparece cada byte en el archivo.
Input: Puntero al struct lista, puntero al arreglo y struct stat sb, que habilita saber de que tamaño es el archivo.
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
			actual -> cero = NULL;
			actual -> uno = NULL;
			
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
						//si la actual -> f es mas pequeÃ±a que el lista -> inicio  lo manda a la derecha
						actual-> siguiente = NULL;
						actual-> anterior = lista -> inicio ;
						lista -> inicio -> siguiente = actual;
						 lista -> fin = actual;
					}
					else{
						//nodo auxlilar sera el lista -> inicio  y nuestro anterior erior lista -> inicio  el  lista -> fin 
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
						//si la actual -> f es mas pequeña que el lista -> inicio  lo manda a la derecha
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
	
	/*// Mostrar la lista
	actual = lista -> inicio;
	if(actual == NULL)
		printf("\nLa lista esta vacia\n");
	else{
		printf("\n");
		while(actual != lista -> fin){
			printf("[%c %o %i, %i]\n", actual -> car, actual -> car, actual -> car, actual -> f);
			actual = actual -> siguiente;
		}
		printf("[%o, %i]\n", actual -> car, actual -> f);
	}
	printf("\n\n");*/
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion frecuenciaDatos, crea el archivo frecuencias.txt de texto claro que permite saber que bytes están en la lista y cuantas veces se repiten.
Input: Puntero al archivo, puntero a la lista y struct stat sb, que habilita saber de que tamaño es el archivo.
Output: frecuencias.txt de texto claro.
*/

void frecuenciaDatos(FILE* archivo, list* lista, struct stat sb){
	huf *actual;
	
	// Mostrar la lista
		actual = lista -> inicio;
		if(actual == NULL)
			printf("\nLa lista esta vacia\n");
		else{
			archivo = fopen("frecuencias.txt", "wb"); //abre archivo: frecuencias.txt
			fprintf(archivo, "Tamano lista: %i \n", lista -> tam); //Imprimir tamano de lista
			while(actual != lista -> fin){
    			fprintf(archivo, "El caracter %c se repite %i veces \n", actual -> car, actual -> f);
				//printf("El caracter %c se repite %i veces tam lista: %i \n", actual -> car, actual -> f, lista -> tam);
				actual = actual -> siguiente;
			}
			fprintf(archivo, "El caracter %c se repite %i veces \n", actual -> car, actual -> f);
			fprintf(archivo, "Tamano archivo: %i", sb.st_size); //Imprimir tamano del archivo
		}
		fclose(archivo);
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion creacionArbol, crea el arbol partiendo de la lista ordenada, usando los nodos como las hojas y sus raices como la suma de sus frecuencias.
Input: Puntero a la lista, puntero al arreglo y struct stat sb, que habilita saber de que tamaño es el archivo.
Output: Arbol binario creado y llenado.
*/

void creacionArbol(list *lista, char *arreglo, struct stat sb){
	// Variables para árbol
	huf *actual, *aux, *recorrer;
	int a, i, k, p;
	
	// Revisar caso donde ya no haya más nodos a unir
	for(i = 2 ; i < lista -> tam ; i++){
		actual = (huf*)malloc(sizeof(huf));
		actual -> car = 0;
		actual -> cero = lista -> inicio;
		actual -> uno = lista -> inicio -> siguiente;
		actual -> f = lista -> inicio -> f + lista -> inicio -> siguiente -> f;
		lista -> inicio = lista -> inicio -> siguiente -> siguiente;
		//printf("[%i, %i]\n", actual -> cero -> f, actual -> uno -> f);
		if(actual -> f >=  lista -> fin -> f){
			//nodo actual al  lista -> fin  de la lista
			//si la actual -> f es mas pequeña que el lista -> inicio  lo manda a la derecha
			actual -> siguiente = NULL;
			actual -> anterior = lista -> fin ;
			 lista -> fin -> siguiente = actual;
			 lista -> fin = actual;
		}
		else{
			if(actual -> f <= lista -> inicio -> f){
				//nodo actual al incio de la lista
				actual -> siguiente = lista -> inicio;
				lista -> inicio -> anterior = actual;
				actual -> anterior = NULL;
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
		
		// Mostrar la lista
		actual = lista -> inicio;
		if(actual == NULL)
			printf("\nLa lista esta vacia\n");
		else{
			//printf("\n");
			while(actual != lista -> fin){
				//printf("[%c, %i]\n", actual -> car, actual -> f);
				actual = actual -> siguiente;
			}
			//printf("[%c, %i]\n %i", actual -> car, actual -> f, lista -> tam);
		}
	}
	
	actual = (huf*)malloc(sizeof(huf));
	actual -> cero = lista -> inicio;
	actual -> uno = lista -> inicio -> siguiente;
	actual -> f = lista -> inicio -> f + lista -> inicio -> siguiente -> f;
	lista -> inicio = actual;
	actual = lista -> inicio;
	//printf("[%o, %i]\n", actual -> car, actual -> f);
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*void preorden(huf *actual, int cont){
	int i;
	if(actual == NULL){
		return;
	}else{
		preorden(actual->uno,cont+1);
		for(i=0;i<cont;i++)
		{
			printf("   ");
		}
		printf("%d\n", actual -> f);
		preorden(actual -> cero, cont + 1);
	}	
}*/

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion altura, obtiene cual es la altura del ABB, para poder crear un arreglo que pueda guarda, en cualquier caso, el camino de cada caracter.
Input: Puntero a actual, que es el la raiz del árbol.
Output: Altura del ABB.
*/

int altura(huf *actual){
	int alturaizq, alturader;
	if(actual == NULL)
		return 0;
	else
	{
		alturaizq = altura(actual -> cero);
		alturader = altura(actual -> uno);
		if(alturaizq > alturader)
			return (alturaizq + 1);
		else
			return (alturader + 1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion codigo, define los caminos de unos y ceros de cada caracter y los escribe en el archivo auxiliar, de acuerdo al orden en el que aparecen en el archivo original.
Input: Puntero a la raíz del ABB, puntero al arreglo que guarda los caminos, puntero al archivo, puntero al arreglo que tiene cada byte en orden del archivo original y una variable auxiliar que permite el moverse a través del arreglo del archivo.
Output: auxiliar.txt
*/

void codigo(huf *arbol, int *numeros, int i, FILE *fp, char *arreglo, int k){
	if (arbol -> cero!= NULL){
		numeros[i] = 0; //48 es cero es ASCII
		codigo(arbol -> cero, numeros, i + 1, fp, arreglo, k);
	}
	if (arbol -> uno!= NULL){
		numeros[i] = 1; //49 es 1 es ASCII
		codigo(arbol -> uno, numeros, i + 1, fp, arreglo, k);
	}
	if (arbol -> cero == NULL && arbol -> uno == NULL ){ //!(arbol->cero) && !(arbol->uno)
		
		if(arreglo[k] == arbol -> car){
			int j;
	        //printf("  %c   | ", arbol -> car);
	        
		    for(j = 0 ; j < i ; j++){
		  	  //printf("%i", numeros[j]);
		  	  fprintf(fp, "%i", numeros[j]);
		  	  //fprintf(fp, "This is the line %d\n", i + 1);
		    }
		    //printf("\n");
	    }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*Descripción de función:
Funcion compresion, comprime el archivo auxiliar al escribirlo por byte en el archivo codificacion.txt
Input: Puntero al arreglo con todos los unos y ceros de auxiliar, variable inicio y fin que ayudan a determinar donde empieza y termina el archivo; y puntero al archivo codificacion.txt
Output: codificacion.txt
*/

void compresion(char *arreglo, int inicio, int fin, FILE *fp){
	int x=0, i, potencia=1;

	for(i = fin ; i >= inicio ; i--)
	{
		if(arreglo[i] == 49)//49 es 1 en ascii
		{
			x += 1 * potencia;
		}
		potencia *= 2;
	}
	//printf("%c", x);
	fprintf(fp, "%c", x);
}
