#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

FILE *apuntador;

int EsParIzq(char);
int EsParDer(char);
int EsCorIzq(char);
int EsCorDer(char);
int EsLlaIzq(char);
int EsLlaDer(char);
int EsTrnIzq(char);
int EsTrnDer(char);
int EsCaracter(char);
Pila Procesar(Pila, int*, char);
Pila ProcesarParDer(Pila,char[]);
int* General(char*, int*);


int main(int argc, char *argv[])
{
    char direccion[] = "input.txt";
    char texto[100];
    int i = 0;
    int* conts;

    // El apuntador recibe el modo en el que va a trabajar.
    apuntador = fopen(direccion, "r+");
    //printf("%s \n",direccion);
    // Comprobamos que no hay algún error en la dirección
    if (apuntador == NULL) printf("Hay algo mal en la direccion del archivo.\n");
    else{
        while (!feof(apuntador)){
            texto[i] = fgetc(apuntador);
            i++;
        }
        *conts = 0;
        *(conts+1) = 0;
        *(conts+2) = 0;
        *(conts+3) = 0;
        conts = General(texto, conts);
        printf("Hay %d parentesis\n",*conts);
        printf("Hay %d corchetes\n",*(conts+1));
        printf("Hay %d llaves\n",*(conts+2));
        printf("Hay %d parentesis triangulares\n",*(conts+3));
        fclose(apuntador);
    }
    return 1;
}

int EsParIzq(char c){return c=='(';};
int EsParDer(char c){return c==')';};
int EsCorIzq(char c){return c=='[';};
int EsCorDer(char c){return c==']';};
int EsLlaIzq(char c){return c=='{';};
int EsLlaDer(char c){return c=='}';};
int EsTrnIzq(char c){return c=='<';};
int EsTrnDer(char c){return c=='>';};
int EsCaracter(char c){return !(c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='<' || c=='>');};

Pila Procesar(Pila pila, int* conters,char c){
    int i=0;

    if(isempty(pila)) return pila;
    else if(EsParIzq(top(pila)) && EsParDer(c)){
        pila = pop(pila);
        *(conters) = *conters + 1;
    } else if(EsCorIzq(top(pila)) && EsCorDer(c)){
        pila = pop(pila);
        *(conters+1) = *(conters+1) + 1;
    } else if(EsLlaIzq(top(pila)) && EsLlaDer(c)){
        pila = pop(pila);
        *(conters+2) = *(conters+2) + 1;
    } else if(EsTrnIzq(top(pila)) && EsTrnDer(c)){
        pila = pop(pila);
        *(conters+3) = *(conters+3) +1;
    }
    return pila;
};

int* General(char *in, int* conters){
    Pila pila=empty();
    int i=0,j=0;

    while(in[i]){
        if(EsCaracter(in[i])) in[j++]=in[i];
        else if(EsParIzq(in[i])) pila=push(in[i],pila);
        else if(EsCorIzq(in[i])) pila=push(in[i],pila);
        else if(EsLlaIzq(in[i])) pila=push(in[i],pila);
        else if(EsTrnIzq(in[i])) pila=push(in[i],pila);
        else pila = Procesar(pila, conters, in[i]);
        i++;
    }
    return conters;
};
