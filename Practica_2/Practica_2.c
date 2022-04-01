/*
Descripción: Dado un alfabeto {0, 1}, realiza
operaciones con cadenas.
Autores: Hurtado Morales Emiliano
Espinoza León Jaqueline Viridiana
García Zacarías Angel Emmanuel
Fecha de creación: 08/03/22
Versión: 4.0
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
#define TAM 200

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
		printf("\nEscriba el numero de la operacion que desea realizar.\n\n");
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
	int e, i, j, k, n, n2, n3, n4;
	char aux[TAM],aux2[TAM];
	system("cls");
	printf("\nIngrese el exponente entero positivo de la potencia.\n");
	scanf("%i", &e);
	n = strlen(cadena);
	n2 = strlen(cadena2);
	n3 = n * e;
	n4 = n2 * e;
	k=0;
	for(i=0 ; i<e ; i++){
		for(j=0 ; cadena[j] != '\0' ; j++, k++){
			aux[k] = cadena[j];
		}
	}
	aux[n3] = '\0';
	k=0;
	for(i=0 ; i<e ; i++){
		for(j=0 ; cadena2[j] != '\0' ; j++, k++){
			aux2[k] = cadena2[j];
		}
	}
	aux2[n4] = '\0';
	printf("\nPotencia.\n");
	printf("\nCadena 1: %s\n", cadena);
	printf("\nCadena potenciada a la %i: %s\n\n", e, aux);
	printf("\nCadena 2: %s\n", cadena2);
	printf("\nCadena potenciada a la %i: %s\n\n", e, aux2);
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
	int i, j, n, n2;
	char aux[TAM], aux2[TAM];
	system("cls");
	n = strlen(cadena);
	j=0;
	for(i=n-1 ; i>=0 ; i--, j++){
		aux[j] = cadena[i];
	}
	aux[n] = '\0';
	n2 = strlen(cadena2);
	j=0;
	for(i=n2-1 ; i>=0 ; i--, j++){
		aux2[j] = cadena2[i];
	}
	aux2[n2] = '\0';
	printf("\nInverso.\n");
	printf("\nCadena 1: %s\n", cadena);
	printf("\nCadena invertida: %s\n\n", aux);
	printf("\nCadena 2: %s\n", cadena2);
	printf("\nCadena invertida: %s\n\n", aux2);
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
	int i, j, n, n2;
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
	printf("\nCadena 2: %s\n", cadena2);
	printf("\nPrefijos:\n");
	n2=strlen(cadena2);
	for(i=0 ; i<n2 ; i++){
		for(j=0 ; j<=i ; j++){
			printf("%c", cadena2[j]);
		}
		printf("\n");
	}
	printf("\n\nSufijos:");
	for(i=n2 ; i>=0 ; i--){
		for(j=i ; j<n2 ; j++){
			printf("%c", cadena2[j]);
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
	int i, j, k, n, n2;
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
	printf("\n");
	printf("\nCadena 2: %s\n\n", cadena2);
	n2=strlen(cadena2);
	for(i=0 ; i<n2 ; i++){
		for(j=n2 ; j>=i ; j--){
			for(k=i ; k<j ; k++){
				printf("%c", cadena2[k]);
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
	char* res2;
	char aux[TAM];
	system("cls");
	printf("\nBuscar una subcadena en %s y %s.\n", cadena, cadena2);
	printf("\nIngrese una subcadena.\n");
	getchar();
	entradaCadenas(aux);
	printf("\nCadena 1: %s\n\n", cadena);
	res = strstr(cadena, aux);
	res2 = strstr(cadena2, aux);
	if(res)
		printf("La subcadena %s SE encuentra dentro de la cadena %s.\n\n", aux, cadena);
	else
		printf("La subcadena %s NO se encuentra dentro de la cadena %s.\n\n", aux, cadena);
	printf("\nCadena 2: %s\n\n", cadena2);
	if(res2)
		printf("La subcadena %s SE encuentra dentro de la cadena %s.\n\n", aux, cadena2);
	else
		printf("La subcadena %s NO se encuentra dentro de la cadena %s.\n\n", aux, cadena2);
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
	system("cls");
	printf("\nLongitud de las cadenas.\n");
	printf("\nLongitud de la cadena %s: %i\n", cadena, strlen(cadena));
	printf("\nLongitud de la cadena %s: %i\n\n", cadena2, strlen(cadena2));
	system("pause");
	system("cls");
}

/*
Función: igualdadCadenas
Descripción: Revisa si las dos cadenas dadas son iguales.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void igualdadCadenas(char* cadena, char* cadena2){
	system("cls");
	int i, n, bandera=0;
	printf("\nIgualdad entre las cadenas.\n\n");
	n = strlen(cadena);
	for(i=0 ; i<n ; i++){
		if(cadena[i] != cadena2[i]){
			bandera = 1;
			break;
		}
	}
	printf("\nCadena 1: %s\n", cadena);
	printf("\nCadena 2: %s\n\n\n", cadena2);
	if(bandera == 1)
		printf("Las cadenas NO son iguales.\n\n");
	else
		printf("Las cadenas SON iguales.\n\n");
	system("pause");
	system("cls");
}

/*
Función: palindromo
Descripción: Revisa que las cadenas sean palíndromos.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void palindromo(char* cadena, char* cadena2){
	int i, j, k, n, n2, bandera=0, bandera2=0;
	char aux[TAM], aux2[TAM];
	system("cls");

	n = strlen(cadena);
	j=0;
	for(i=n-1 ; i>=0 ; i--, j++){
		aux[j] = cadena[i];
	}
	aux[n] = '\0';

	n2 = strlen(cadena2);
	j=0;
	for(i=n2-1 ; i>=0 ; i--, j++){
		aux2[j] = cadena2[i];
	}
	aux2[n2] = '\0';

	printf("\nPalindromo.\n\n");
	printf("\nCadena 1: %s\n", cadena);
	printf("\nCadena 2: %s\n\n\n", cadena2);


	for(k=0 ; k<n ; k++){
		if(cadena[k] != aux[k]){
			bandera=1;
		}
	}
	
	if(bandera == 1)
		printf("La cadena 1 NO es palindromo.\n\n");
	else
		printf("La cadena 1 SI es palindromo.\n\n");

	for(k=0 ; k<n2 ; k++){
		if(cadena2[k] != aux2[k]){
			bandera2=1;
		}
	}
	
	if(bandera2 == 1)
		printf("La cadena 2 NO es palindromo.\n\n");
	else
		printf("La cadena 2 SI es palindromo.\n\n");

	system("pause");
	system("cls");
}

/*
Función: reemplazoCadenas
Descripción: Reemplaza las cadenas originales, por las nuevas otorgadas en la función.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void reemplazoCadenas(char* cadena, char* cadena2){
	system("cls");
	
	printf("\nReemplazo de cadenas.\n\n");
	printf("\nCadena 1.\n");
	getchar();
	
	entradaCadenas(cadena);
	cadena[strlen(cadena)] = '\0';
	
	printf("\nCadena 2.\n");
	entradaCadenas(cadena2);
	cadena2[strlen(cadena2)] = '\0';
	
	system("cls");
}

/*
Función: quitarEspacios
Descripción: Quita los espacios existentes en las cadenas.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void quitarEspacios(char* cadena, char* cadena2){
	system("cls");
	char cadenanueva[TAM] = "", cadenanueva2[TAM] = "";
	int i = 0, j = 0, size = 0, size2 = 0;
	
	printf("\nQuitar espacios.\n");
    while(cadena[size] != '\0') size++;
	
	printf("\nCadena 1: %s.\n", cadena);
	printf("\nCadena sin espacios: ");
    for(i = 0;i<size; i++){
        if(cadena[i] != ' '){
			cadenanueva[j] = cadena[i];
			printf("%c", cadenanueva[j]);
			j++;
		} 
    }
    for(i=0 ; i<size ; i++)
    	cadena[i] = cadenanueva[i];
    cadena[size] = '\0';
    printf("\n\n");
    while(cadena2[size2] != '\0') size2++;
	
	printf("\nCadena 2: %s.\n", cadena2);
	printf("\nCadena sin espacios: ");
	j=0;
    for(i = 0 ; i<size2 ; i++){
        if(cadena2[i] != ' '){
			cadenanueva2[j] = cadena2[i];
			printf("%c", cadenanueva2[j]);
			j++;
		} 
    }
    for(i=0 ; i<size2 ; i++)
    	cadena2[i] = cadenanueva2[i];
    cadena2[size2] = '\0';
    printf("\n\n");
	system("pause");
	system("cls");
}

/*
Función: complemento1
Descripción: Provee el complemnto a 1 de las cadenas dadas.
Entrada: Apuntadores a cadena 1 y 2.
Salida: Impresión de resultados.
*/
void complemento1(char* cadena, char* cadena2){
	system("cls");
	char complemento[TAM] = "",complemento2[TAM] = "";
    int i = 0, size = 0, size2 = 0;
	
	printf("\nComplemento a 1.\n");
    while(cadena[size] != '\0') size++;
	
	printf("\nCadena 1: %s\n", cadena);
	printf("\nComplemento de la cadena: ");
    for(i = 0;i<size; i++){
        if(cadena[i] == '1') 
			complemento[i] = '0';
        else if(cadena[i] == '0')
			complemento[i] = '1';
		else
			complemento[i] = cadena[i];
        printf("%c", complemento[i]);
    }
    printf("\n\n");
    while(cadena2[size2] != '\0') size2++;
	
	printf("\nCadena 2: %s\n", cadena2);
	printf("\nComplemento de la cadena: ");
    for(i = 0 ; i<size2 ; i++){
        if(cadena2[i] == '1') 
			complemento2[i] = '0';
        else if(cadena2[i] == '0')
			complemento2[i] = '1';
		else
			complemento2[i] = cadena2[i];
        printf("%c", complemento2[i]);
    }
    printf("\n\n");
	system("pause");
	system("cls");
}