#include<stdio.h>
#include<stdlib.h>
#include"elemento.h"
#include"pila.h"

int EsMinuscula(char);
int EsMayuscula(char);
int EsDigito(char);
int EsLetra(char);
int EsOperando(char);
int EsOperador(char);
int EsParIzq(char);
int EsParDer(char);
int Precedencia(char);
Pila ProcesarOperador(Pila,Elem[],Elem);
Pila ProcesarParDer(Pila,Elem[]);
void CopiarPilaApos(Pila, Elem[]);
char* inapos(char*,char*);

int main(int argc, char *argv[]){
    char *in=*(argv+1), pos[80]={};

    printf("%s equivale a %s\n",in,inapos(in,pos));

    return 0;
}

int EsMinuscula(char c){return (c>='a')&&(c<='z');};
int EsMayuscula(char c){return (c>='A')&&(c<='Z');};
int EsDigito(char c){return (c>='0')&&(c<='9');};
int EsLetra(char c){return EsMinuscula(c)||EsMayuscula(c);};
int EsOperando(char c){return EsDigito(c)||EsLetra(c);}
int EsOperador(char c){return (c=='+')||(c=='-')||(c=='/')||(c=='*')||(c=='!');};
int EsParIzq(char c){return c=='(';};
int EsParDer(char c){return c==')';};

int Precedencia(char c){
       switch (c){
           case '+': case '-': return 1;
           case '*': case '/': return 2;
           case '!': return 3;
       }
};

Pila ProcesarOperador(Pila ops,Elem pos[],Elem op){
    int i=0;

    if(isempty(ops))
        return push(op,ops);
    else if(EsParIzq(top(ops)))
            return ops=push(op,ops);
         else if(comparar(Precedencia(op),Precedencia(top(ops))))
                return ops=push(op,ops);
              else {while(!isempty(ops)&&!EsParIzq(top(ops))&&!comparar(Precedencia(op),Precedencia(top(ops)))){
                       pos[i++]=top(ops);
                       ops=pop(ops);
                       }
                    return ops=push(op,ops);
                  }
};

Pila ProcesarParDer(Pila ops,Elem pos[]){
        int i=0;
        while(!EsParIzq(top(ops))){
            pos[i++]=top(ops);
            ops=pop(ops);
        }
        ops = pop(ops);
        return ops;
};

void CopiarPilaApos(Pila ops, Elem pos[]){
    int i=0;
    while(!isempty(ops)){
        pos[i++]=top(ops);
        ops=pop(ops);
    }
};

char* inapos(char *in, char *pos){
    Pila ops=empty();
    int i=0,j=0;

    while(in[i]){
        if(EsOperando(in[i]))
            pos[j++]=in[i];
        else if(EsOperador(in[i])){
               ops=ProcesarOperador(ops,pos+j,in[i]);
               while(pos[j]) j++;
             }
             else if(EsParIzq(in[i]))
                     ops=push(in[i],ops);
                  else{
                     ops=ProcesarParDer(ops,pos+j);
                     while(pos[j]) j++;
                  }
        i++;

    }
    CopiarPilaApos(ops, pos+j);
    return pos;
};