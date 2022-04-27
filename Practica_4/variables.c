#include <stdio.h>  // Todas las funciones como fread, fwrite, fopen, fclose y printf
#include <stdlib.h> // EXIT_FAILURE y EXIT_SUCCESS
#include <sys/stat.h>
#include <string.h>

//Estructura de Apoyo
typedef struct {
    int pos;
    int modo; 
    /*
        Modos:
            -1 -> identificador incorrecto que no cumple con lo establecido
            0 -> varios identificadores para el mismo tipo de variable
            1 -> un solo identificador para ese tipo de variable
    */
} Elem;


void encontrarTipo(char *, struct stat);
Elem validar(char*, char*, int, int);
void cantidadVar(char *, char *, int, int);

int main(int argc, char const *argv[])
{
    char *arreglo;
    struct stat sb;
    arreglo[0] = ' ';
    strcat(arreglo,"int abcd = 0, ab, a; abcd = ab; ab = 0;");
    sb.st_size = strlen(arreglo);
    printf("%i", sb.st_size);
    //encontrarTipo(arreglo, sb);
    //char arreglo = "int abcd = 0, ab, a; abcd = ab; ab = 0;"
    return 0;
}

void cantidadVar(char *arreglo, char *identificador, int longitud, int pos){
    int i = 0, cont = 1, band = 0;
    for(i = pos; i<longitud; i++){
        char auxC = arreglo[i];
        if(band == strlen(identificador)){
            auxC = arreglo[i+1];
            if(!(auxC >= 48 && auxC <= 57) || (auxC >= 65 && auxC <= 90) || (auxC >= 97 && auxC <= 122) || auxC == 95 )
                cont++;
            else band = 0;
        } else{
            if(identificador[band] == arreglo[i]){
                band++;
            } else band = 0;
        }
    }

    printf("%s se repite %d veces\n",identificador,cont);
    
}

Elem validar(char *arreglo, char *tipo, int pos, int longitud){
    Elem apoyo;
    int band = 0, save = pos, i = 0, j = 0, state = 0, idState = 0, typ = 0;
    char *identificador;
    char auxC = arreglo[pos];

    // La condición del identificador es que su inicial sea minuscula, o 
    // que al inicio tenga un '_' pero después tenga una letra minuscula
    if(auxC == 95 && (arreglo[pos+1] >= 97 && arreglo[pos+1] <= 122)){
        identificador[0] = auxC;
        identificador[1] = arreglo[pos+1];
        state = 1;
        i = pos + 2;
    } else if(auxC >= 97 && auxC <= 122){
        identificador[0] = auxC;
        state = 1;
        i = pos + 1;
    } else state = 0;

    /*
        Significado de valores de idState:
            idState == 0 -> Error
            idState == 1 -> Identificador de variable
            idState == 2 -> Identificador de arreglo abierto
            idState == 3 -> Identificador de arreglo cerrado
            idState == 4 -> Identificador completo
            idState == 5 -> asignacion a variable
            idState == 6 -> fin de identificador
            idState == 7 -> fin de identificador antes del siguiente
        Se obtiene el identificador y se valida al momento.
    */

    if(state == 1){
        idState = 1;
        for(j = i; j<longitud; j++){
            auxC = arreglo[j];
            if(idState == 1 && (auxC >= 48 && auxC <= 57) || (auxC >= 65 && auxC <= 90) || (auxC >= 97 && auxC <= 122)  || auxC == 95 ){
                strcmp(identificador,auxC);
            } else if(auxC == 91) {
                idState = 2;
            } else if(auxC == 93 && idState == 2){
                idState = 3;
            } else if(auxC == 32 && (idState == 1 || idState == 3)){
                idState = 4;
            } else if(auxC == 61 && idState == 4){
                idState = 5;
            } else if(auxC == 59 && idState == 5){
                idState = 6;
                apoyo.modo = 1;
                apoyo.pos = j;
                j = longitud;
            } else if(auxC == 44 && idState == 4){
                idState = 7;
                apoyo.modo = 0;
                apoyo.pos = j;
                j = longitud;
            }else{
                if(!(idState == 2 || idState == 5)){
                    idState = 0;
                    apoyo.modo = -1;
                    apoyo.pos = j;
                    j = longitud;
                }
            }
        }
    }

    if(apoyo.modo >= 0) cantidadVar(arreglo,identificador, longitud, apoyo.pos);

    return apoyo;
}

void encontrarTipo(char *arreglo, struct stat sb)
{
    int i = 0, j = 0, band1 = 0, band2 = 0, state = 0, size = 0;
    char tipos[15][15] = {{"char"},{"unsigned char"},{"signed char"},{"short"},{"unsigned short"},
                            {"signed short"},{"int"},{"unsigned int"},{"signed int"},{"long"},{"signed long"},
                            {"unsigned long"},{"float"},{"double"},{"long double"}};
    char *tipo, *arreglo2;
    Elem elem;
    elem.modo = 1;

    // Las tabulaciones las convertimos en espacios, los saltos de linea se omiten y si tenemos varios espacios seguidos,
    // unicamente usaremos uno.
    for (i = 0; i < sb.st_size; i++){
        if(arreglo[i] == 9){
            *(arreglo2+j) = ' ';
            j++;
        }else if(arreglo[i] != 10 && !(arreglo[i] == 32 && arreglo[i-1] == 32)){
            *(arreglo2+j) = arreglo[i];
            j++;
        }
    }
    size = i;

    // Recorrido de la nueva cadena
    for (i = 0; i < size; i++)
    {
        char auxChar = arreglo2[i];

        // Solamente es posible declarar una variable si antes tenemos un '{', '>', ';' o '(' 
        if(auxChar == 40 || auxChar == 62 || auxChar == 59 || auxChar == 125){
            band1 = 1;
        } // se tiene que haber verificado lo de arriba, además de que tiene que ser una letra minuscula
        else if ((auxChar >= 97 && auxChar <= 122) && band1 == 1 && arreglo2[i-1] != 44){
            // Verificaremos que es la primer letra
            if (band2 == 0){
                tipo[0] = auxChar;
                band2 = 1;
            }else strcat(tipo,auxChar); // Se concatenan las letras que siguen
        } else if (auxChar == 32 || (elem.modo == 0)){ // Encontramos un espacio
            /*
                Tenemos dos opciones si hay un espacio:
                    1.- La variable es de un tipo que se define con dos palabras separadas.
                    2.- Terminamos de definir el tipo de la variable.
            */
            //  verificamos las posibles palabras que pueden ser utilizadas para formar los tipos de 
            //  datos compuestos de dos palabras
            if(!strcmp(tipo,"unsigned") || !strcmp(tipo,"signed") || !strcmp(tipo,"long")){
                // Se concatena el espacio
                strcat(tipo,auxChar);
                j = i;
                auxChar = arreglo[j];
                // Los tipos de datos compuestos de dos palabras, tienen como inicial de su segunda palabra
                // las letras 'c', 'd', 'i', 'l' y 's'
                if(auxChar == 99 || auxChar == 100 || auxChar == 105 || auxChar == 108 || auxChar ==115){
                    // se concatena la inicial
                    strcat(tipo,auxChar);
                    for(j = i+1; j<sb.st_size; j++){
                        // Se realiza el mismo proceso, solo que ahora con la segunda palabra
                        auxChar = arreglo[j];
                        if(auxChar >= 97 && auxChar <= 122){
                            strcat(tipo,auxChar);
                        } else  if (auxChar == 32){ 
                            // Si aparece un espacio entonces ya termina el tipo de dato
                            state = 1;
                            j = sb.st_size;
                        } else{ 
                            // Cualquier otro resultado es algo que invalida la cadena.
                            state = 0;
                            j = sb.st_size;
                        }
                    }
                }
            } else state = 1;

            // Validaremos si el tipo de dato obtenido se encuentra en el arreglo que tenemos
            int val = 1;
            while(state == 1 && j<15 && val == 1){
                val = strcmp(tipo,tipos[j]);
                j++;
            }

            // Almacenamos la posición
            int pos = 0;
            if(i>=j) pos = i;
            else pos = j;

            // En caso de la validación sea correcta, validaremos si el identificador es correcto
            if(val == 0) {
                // Se retorna la posición y el modo.
                elem = validar(arreglo2, tipo, pos, size);
            }else if(state == 0 || val == 1){ 
                // La cadena que obtuvimos no cumplió con alguna caracteristica, entonces reiniciamos
                // los band.
                band1 = 0;
                band2 = 0;
                i =  pos;
                *tipo = ' ';
            }

            // Regresamos a esta parte de la función. Si el modo es 1, entonces reseteamos todo
            // si el modo es 0, unicamente modificamos la posición.
            if(val == 0 && state == 1 && elem.modo == 1){
                band1 = 1;
                band2 = 0;
                i = elem.pos;
                *tipo = ' ';
            }else if(val == 0 && state == 1 && elem.modo == 0){
                i = elem.pos;
            }
        } else band1 = 0;
    }
}