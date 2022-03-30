#include <stdlib.h>
#include <stdio.h>

void complemento(char[]);

int main(int argc, char const *argv[])
{
	complemento("100                  01");
	espacios("10  00  1");
    return 0;
}

void complemento(char* cadena){
    char complemento[100] = "";
    int i = 0, size = 0;

    while(cadena[size] != '\0') size++;

    for(i = 0;i<size; i++){
        if(cadena[i] == '1') complemento[i] = '0';
        else if(cadena[i] == '0') complemento[i] = '1';
        printf("%c", complemento[i]);
    }
    printf("\n");
}

void espacios(char* cadena){
	char cadenanueva[100] = "";
	int i = 0, j = 0, size = 0;

    while(cadena[size] != '\0') size++;

    for(i = 0;i<size; i++){
        if(cadena[i] != ' '){
			cadenanueva[j] = cadena[i];
			printf("%c", cadenanueva[j]);
			j++;
		} 
    }
    printf("\n");
}

