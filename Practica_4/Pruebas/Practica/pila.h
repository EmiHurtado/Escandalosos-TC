typedef struct Nodo{
                char dato;
                struct Nodo *sig;
              }*Pila;

Pila empty(){return NULL;}

Pila push(char e, Pila l){
    Pila t=(Pila)malloc(sizeof(struct Nodo));
    t->dato=e;
    t->sig=l;
    return t;
}

int isempty(Pila l){return l==NULL;}

char top(Pila l){return l->dato;}

Pila pop(Pila l){return l->sig;}