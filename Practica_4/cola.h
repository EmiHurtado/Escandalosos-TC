#ifndef cola_h
#define cola_h

typedef struct NodoC{
   char dato;
   struct NodoC *sig;
}*ApNodo;

typedef struct Cnodo{
   ApNodo prim;
   ApNodo ulti;
}*Cola;

Cola nueva(){
   Cola t = (Cola)malloc(sizeof(struct Cnodo));
   t->prim=t->ulti=NULL;
   return t;
}

int esnueva(Cola q){return ((q->prim==NULL)&&(q->ulti==NULL));}

Cola formar(Cola q, char e){
   ApNodo t = (ApNodo)malloc(sizeof(struct NodoC));
   t->dato=e;
   t->sig=NULL;
   if(esnueva(q)){
      q->prim=q->ulti=t;
   } else{
      q->ulti->sig=t;
      q->ulti=t;
   }
   return q;
}

char primero(Cola q){return q->prim->dato;}

Cola desformar(Cola q){
   ApNodo t;
   if(q->prim==q->ulti){
      free(q->prim);
      free(q);
      return nueva();
   } else{
      t = q->prim; 
      q->prim=q->prim->sig;
      free(t);
      return q;
   }
}

int comparar(Cola q, char *cadena, int size, int pos){
   if(esnueva(q) && cadena[pos] == '\0'){
      return 1;
   } else if(esnueva(q) && cadena[pos] != '\0'){
      return 0;
   } else if(!esnueva(q) && cadena[pos] == '\0'){
      return 0;
   } else if(primero(q) != cadena[pos]){
      return 0;
   } else if(primero(q) == cadena[pos]){
      return comparar(desformar(q),cadena,size,pos + 1);
   }
}
#endif