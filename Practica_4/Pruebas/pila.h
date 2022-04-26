typedef struct Nodo{
                Elem dato;
                struct Nodo *sig;
              }*Pila;

Pila empty(){return NULL;}

Pila push(Elem e, Pila l){
    Pila t=(Pila)malloc(sizeof(struct Nodo));
    t->dato=e;
    t->sig=l;
    return t;
}

int isempty(Pila l){return l==NULL;}

Elem top(Pila l){return l->dato;}

Pila pop(Pila l){return l->sig;}


/*
Espec Pila
     empty:->Pila;
     push:Elem, Pila->Pila;
     isempty:Pila->Bool;
     top:Pila->Elem;
     pop:Pila->Pila;
   Axiomas: Elem e, Pila p;
   [p1] isempty(empty())=cierto;
   [p2] isempty(push(e,p))=falso;
   [p3] top(empty())=ERROR;
   [p4] top(push(e,p))=e;
   [p5] pop(empty())=ERROR;
   [p6] pop(push(e,p))=p;
Fin Pila.
*/
