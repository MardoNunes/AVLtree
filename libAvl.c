#include <stdio.h>
#include <stdlib.h>
#include "libAvl.h"
#include "libBst.h"

//essa função irá retornar o fator de balanceamento de um nó
//fator de balanceamento decide qual rotação será feita
//Fb negativo, rotação para a direita
//Fb positivo, rotação para a esquerda
int fb(struct no *no){
    if(no == NULL)
        return -1;
    return no->altura;
}


//Essa função retorna o no com maior valor em uma subarvore
struct no *buscaMax(struct no *no){
    while(no->dir != NULL)  //se nao houver mais nodos a direita, retorna o no
        no = no->dir;
    return no;
}


//Essa função retorna a diferena entre o balanceamento dos filhos
int testaBal(struct no *no){
    int balEsq;
    int balDir;

    //Guarda o balanco dos filhos
    balEsq = fb(no->esq);  //fb é uma função que retorna a altura de um nó
    balDir = fb(no->dir);

    //Testa o balanceamento
    return balEsq - balDir;   //se for positivo, o filho esquerdo é maior
                                //se for negativo, o filho direito é maior
}


//Essa função irá rotacionar a arvore para a esquerda
//antes:
        /*
        //  1
        //    \
        //     2
        //      \
        //       3

    //depois:
    //      2
    //     / \
    //    1   3
    */
struct no *rotEsquerda(struct no *no){
    struct no *aux = no->dir;   //auxiliar recebe o no que irar subir(no do meio)

    //aqui realizo a rotação
    //o nodo aux (do meio sobe)     
    //o no (da esquerda) vira filho do aux
    
    no->dir = aux->esq;
    aux->pai = no->pai;
    no->pai = aux;

    //faço esssa vereficaçao para nao perder o filho da esquerda
    if(aux->esq != NULL)  //se houver filho a esquerda
        aux->esq->pai = no;   //o pai do filho da esquerda será o no
    aux->esq = no;  //agora atualizo o novo filho da esquerda

    //O pai do no ainda tem como filho o no
    //seu filho agora será o aux
    //então atualizo o filho do pai
    if(aux->pai != NULL){
        if(aux->pai->esq == no)
            aux->pai->esq = aux;
        else if(aux->pai->dir == no)
            aux->pai->dir = aux;
    }

    //atualizo a altura dos nos
    no->altura = max(fb(no->esq), fb(no->dir)) + 1;
    aux->altura = max(fb(aux->esq), fb(aux->dir)) + 1;

    return aux; //retorno o novo no que subiu
}

//Essa função irá rotacionar a arvore para a direita
//antes:
        /*
        //       3
        //      /
        //     2
        //    /
        //   1

    //depois:
    //      2
    //     / \
    //    1   3
    */
struct no *rotDireita(struct no *no){
    struct no *aux = no->esq;   //auxiliar recebe o no que irar subir(no do meio)

    //aqui realizo a rotação
    no->esq = aux->dir;
    aux->pai = no->pai;
    no->pai = aux;

    //faço esssa vereficaçao para nao perder o filho da direita
    if(aux->dir != NULL)
        aux->dir->pai = no;
    aux->dir = no;  

    //O pai do no ainda tem como filho o no, atualizo agr
    if(aux->pai != NULL){
        if(aux->pai->esq == no)
            aux->pai->esq = aux;
        else if(aux->pai->dir == no)
            aux->pai->dir = aux;
    }

    //atualizo a altura dos nos
    no->altura = max(fb(no->esq), fb(no->dir)) + 1;
    aux->altura = max(fb(aux->esq), fb(aux->dir)) + 1;

    return aux;
}

//Essa função ajusta o balanceamento da arvore
struct no *balanceamento(struct no *no){
    int bal;
    int balFilho;

    //ajustando o balanceamento
    no->altura = max(fb(no->esq), fb(no->dir)) + 1;

    //testando o balanceamento
    bal = testaBal(no);

    //se o balanceamento for maior que 1, entao o filho esquerdo é maior
    if(bal > 1){
        balFilho = testaBal(no->esq);
        if(balFilho > 0)
            return rotDireita(no);  //zig
        else{
            no->esq = rotEsquerda(no->esq); //zig zag
            return rotDireita(no);  
        }
    }

    //se o balanceamento for menor que -1, entao o filho direito é maior
    if(bal < -1){
        balFilho = testaBal(no->dir);
        if(balFilho < 0)
            return rotEsquerda(no);  //zig
        else{
            no->dir = rotDireita(no->dir); //zig zag
            return rotEsquerda(no);
        }
    }

    return no;
}

//Essa função irá comparar o maior entre duas chaves
int max(int a, int b){
    if(a > b)
        return a;
    return b;
}


