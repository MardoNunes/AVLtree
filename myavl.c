#include <stdio.h>
#include <stdlib.h>

#include "libBst.h"
#include "libAvl.h"


int main(){

    struct no *raiz = NULL;
    char input;
    int valor;        

    while(scanf("%c %d", &input, &valor) != EOF){

        if (input == 'i'){
            raiz = insert(raiz, valor);

        }
        else if (input == 'r'){
            raiz = delete(raiz, valor);
        }
        else
            fprintf(stderr, "Operação invalida\n");

        getchar();
    }

    emOrder(raiz, 0);
    printf("\n");

    return 0;
}