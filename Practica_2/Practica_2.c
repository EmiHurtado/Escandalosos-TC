/*
Descripción: Dado un alfabeto {0, 1}, realiza
operaciones con cadenas.
Autores: Hurtado Morales Emiliano
Espinoza León Jaqueline Viridiana
García Zacarías Angel Emmanuel
Fecha de creación: 08/03/22
Versión: 2.0
*/

//////////////////////////////////////// LIBRERÍAS //////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

///////////////////////////////// PROTOTIPOS DE FUNCIONES ///////////////////////////////////
void entradaCadenas(char*);
int verificacionCadenas(char*);
void menuOpciones(char*, char*);
void concatenacionCadenas(char*, char*);
void potenciaCadenas(char*, char*);
void inversoCadenas(char*, char*);
void prefijossufijosCadenas(char*, char*);
void subcadenasCadenas(char*, char*);
void buscarSubcadenas(char*, char*);
void longitudCadenas(char*, char*);
void igualdadCadenas(char*, char*);
void palindromo(char*, char*);
void reemplazoCadenas(char*, char*);
void quitarEspacios(char*, char*);
void complemento1(char*, char*);

//////////////////////////////// DEFINICIÓN DE CONSTANTES ///////////////////////////////////
#define TAM 50

////////////////////////////////// PROGRAMA PRINCIPAL ///////////////////////////////////////
/*
Función: main
Descripción: Declara las cadenas 1 y 2 de tamaño 50 y manda a llamar las 
demás funciones del programa.
Entrada: void
Salida: void
*/
void main(){
	char cadena[TAM], cadena2[TAM];
	entradaCadenas(cadena);
	entradaCadenas(cadena2);
	menuOpciones(cadena, cadena2);
}

////////////////////////////////////// FUNCIONES //////////////////////////////////////////
/*
Función: entradaDatos
Descripción: Imprime el texto de instrucción y recibe la cadena a trabajar.
Entrada: Apuntador a cadena
Salida: void
*/
void entradaCadenas(char * cadena){
	int bandera;
	do{
		bandera = 0;
		printf("\nIngrese una cadena solo con unos y ceros. \n");;
		scanf("%[^\n]", cadena);
		getchar();
		bandera = verificacionCadenas(cadena);
	}while(bandera == 1);
	system("cls");
}

/*
Función: verificacionDatos
Descripción: Revisa que la cadena sea válida para el alfabeto {1, 0}
Entrada: Apuntador a cadena
Salida: int bandera
*/
int verificacionCadenas(char* cadena){
	int i;
	for(i=0 ; cadena[i] != '\0' ; i++){
		if(cadena[i] != '1' && cadena[i] != '0' && cadena[i] != ' '){
			printf("\nCadena rechazada. Ingrese solo una cadena con unos y ceros.\n\n");
			system("pause");
			system("cls");
			return 1;
		}
	}
	return 0;
}

/*
Función: menuOpciones
Descripción: Permite elegir entre las operaciones de cadenas y salir del programa.
Entrada: Apuntadores a cadena 1 y 2.
Salida: void
*/
void menuOpciones(char* cadena, char* cadena2){
	int p;
	do{
		printf("\nEscriba el numero de la operacion que desea realizar.\n");
		printf("1.- Concatenacion.\n");
		printf("2.- Potencia.\n");
		printf("3.- Inverso.\n");
		printf("4.- Prefijos y sufijos.\n");
		printf("5.- Subcadenas.\n");
		printf("6.- Buscar subcadena.\n");
		printf("7.- Longitud de cadenas.\n");
		printf("8.- Igualdad de cadenas.\n");
		printf("9.- Palindromo.\n");
		printf("10.- Reemplazo de cadenas.\n");
		printf("11.- Quitar espacios en blanco.\n");
		printf("12.- Complemento a 1.\n");
		printf("13.- Salir.\n");
		scanf("%i", &p);
		switch(p){
			case 1: concatenacionCadenas(cadena, cadena2);
					break;
			case 2: potenciaCadenas(cadena, cadena2);
					break;
			case 3: inversoCadenas(cadena, cadena2);
					break;
			case 4: prefijossufijosCadenas(cadena, cadena2);
					break;
			case 5: subcadenasCadenas(cadena, cadena2);
					break;
			case 6: buscarSubcadenas(cadena, cadena2);
					break;
			case 7: longitudCadenas(cadena, cadena2);
					break;
			case 8: igualdadCadenas(cadena, cadena2);
					break;
			case 9: palindromo(cadena, cadena2);
					break;
			case 10: reemplazoCadenas(cadena, cadena2);
					break;
			case 11: quitarEspacios(cadena, cadena2);
					break;
			case 12: complemento1(cadena, cadena2);
					break;
			case 13: printf("\nGracias por preferirnos. Hasta la proxima.\n\n");
					system("pause");
					break;
			default: printf("\nNo logro entender. Intente de nuevo.\n\n");
					system("pause");
					getchar();
					break;
		}
		system("cls");
	}while(p != 13);
}

/*
Función: concatenacionCadenas
Descripción: Concatena la cadena 1 y 2 en aux e imprime resultados.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void concatenacionCadenas(char* cadena, char* cadena2){
	int i, n, n2, n3;
	char aux[TAM];
	system("cls");
	n = strlen(cadena);
	n2 = strlen(cadena2);
	n3 = n + n2;
	for(i=0 ; cadena[i] != '\0' ; i++){
		aux[i] = cadena[i];
	}
	for(i=n ; cadena2[i-n] != '\0' ; i++){
		aux[i] = cadena2[i-n];
	}
	aux[n3] = '\0';
	printf("\nConcatenacion.\n");
	printf("\nCadena 1: %s\n", cadena);
	printf("\nCadena 2: %s\n", cadena2);
	printf("\nCadena concatenada: %s\n\n", aux);
	system("pause");
	system("cls");
}

/*
Función: potenciaCadenas
Descripción: Eleva la cadena a la potencia indicada por el usuario. 
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void potenciaCadenas(char* cadena, char* cadena2){
	int e, i, j, k, n, n3;
	char aux[TAM];
	system("cls");
	printf("\nIngrese el exponente entero positivo de la potencia.\n");
	scanf("%i", &e);
	n = strlen(cadena);
	n3 = n * e;
	k=0;
	for(i=0 ; i<e ; i++){
		for(j=0 ; cadena[j] != '\0' ; j++, k++){
			aux[k] = cadena[j];
		}
	}
	aux[n3] = '\0';
	printf("\nPotencia.\n");
	printf("\nCadena 1: %s\n", cadena);
	printf("\nCadena potenciada a la %i: %s\n\n", e, aux);
	system("pause");
	system("cls");
}

/*
Función: inversoCadenas
Descripción: Invierte la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void inversoCadenas(char* cadena, char* cadena2){
	int i, j, n;
	char aux[TAM];
	system("cls");
	n = strlen(cadena);
	j=0;
	for(i=n-1 ; i>=0 ; i--, j++){
		aux[j] = cadena[i];
	}
	aux[n] = '\0';
	printf("\nInverso.\n");
	printf("\nCadena 1: %s\n", cadena);
	printf("\nCadena invertida: %s\n\n", aux);
	system("pause");
	system("cls");
}

/*
Función: prefijossufijosCadenas
Descripción: Muestra los prefijos y sufijos de la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void prefijossufijosCadenas(char* cadena, char* cadena2){
	int i, j, n;
	system("cls");
	printf("\nPrefijos y Sufijos.\n");
	printf("\nCadena 1: %s\n", cadena);
	printf("\nPrefijos:\n");
	n=strlen(cadena);
	for(i=0 ; i<n ; i++){
		for(j=0 ; j<=i ; j++){
			printf("%c", cadena[j]);
		}
		printf("\n");
	}
	printf("\n\nSufijos:");
	for(i=n ; i>=0 ; i--){
		for(j=i ; j<n ; j++){
			printf("%c", cadena[j]);
		}
		printf("\n");
	}
	printf("\n");
	system("pause");
	system("cls");
}

/*
Función: subcadenasCadenas
Descripción: Muestra las subcadenas.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void subcadenasCadenas(char* cadena, char* cadena2){
	int i, j, k, n;
	system("cls");
	printf("\nSubcadenas.\n");
	printf("\nCadena 1: %s\n\n", cadena);
	n=strlen(cadena);
	for(i=0 ; i<n ; i++){
		for(j=n ; j>=i ; j--){
			for(k=i ; k<j ; k++){
				printf("%c", cadena[k]);
			}
			printf("\n");
		}
	}
	system("pause");
	system("cls");
}

/*
Función: buscarSubcadenas
Descripción: Encuentra una subcadena dada en la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void buscarSubcadenas(char* cadena, char* cadena2){
	char* res;
	char aux[TAM];
	system("cls");
	printf("\nBuscar una subcadena en %s.\n", cadena);
	printf("\nIngrese una subcadena.\n");
	getchar();
	entradaCadenas(aux);
	/*getchar();
	scanf("%[^\n]", aux);
	getchar();
	printf("\n");*/
	printf("\nCadena 1: %s\n\n", cadena);
	res = strstr(cadena, aux);
	if(res)
		printf("La subcadena %s se encuentra dentro de la cadena %s.\n\n", aux, cadena);
	else
		printf("La subcadena %s no se encuentra dentro de la cadena %s.\n\n", aux, cadena);
	system("pause");
	system("cls");
}

/*
Función: longitudCadenas
Descripción: Regresa el número de símbolos que tiene la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void longitudCadenas(char* cadena, char* cadena2){
	int n1, n2;
	system("cls");
	printf("\nLongitud de las cadenas.\n");
	printf("\nLongitud de la cadena %s: %i\n", cadena, strlen(cadena));
	printf("\nLongitud de la cadena %s: %i\n\n", cadena2, strlen(cadena2));
	system("pause");
	system("cls");
}

/*
Función: igualdadCadenas
Descripción: Encuentra una subcadena dada en la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void igualdadCadenas(char* cadena, char* cadena2){
	system("cls");

	system("pause");
	system("cls");
}

/*
Función: palindromo
Descripción: Encuentra una subcadena dada en la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void palindromo(char* cadena, char* cadena2){
	system("cls");

	system("pause");
	system("cls");
}

/*
Función: reemplazoCadenas
Descripción: Encuentra una subcadena dada en la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void reemplazoCadenas(char* cadena, char* cadena2){
	system("cls");

	system("pause");
	system("cls");
}

/*
Función: quitarEspacios
Descripción: Encuentra una subcadena dada en la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void quitarEspacios(char* cadena, char* cadena2){
	system("cls");

	system("pause");
	system("cls");
}

/*
Función: complemento1
Descripción: Encuentra una subcadena dada en la cadena.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void complemento1(char* cadena, char* cadena2){
	system("cls");

	system("pause");
	system("cls");
}