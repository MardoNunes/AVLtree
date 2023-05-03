#include <stdio.h>
#include <stdlib.h>
#include "libBst.h"
#include "libAvl.h"





//Essa função irá criar um no
//ela retorna esse no criado
struct no *criaNo(int chave){
    //estou apenas criando, ela ainda nao está ligada a ngm da arvore
    struct no *novo = malloc(sizeof(struct no));
    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    novo->altura = 0;

    return novo;
}

//essa função irá inlcuir na BST um novo nó
//essa inserção é feita na folha
struct no *insert(struct no *raiz, int chave){
    //se a raiz for nula, entao o novo no sera a raiz
    if(raiz == NULL){
        struct no *novo = criaNo(chave);
        return novo;
    }
    //se a chave for menor que a raiz, entao ela vai para a esquerda
    if(chave < raiz->chave){
        raiz->esq = insert(raiz->esq, chave);
        raiz->esq->pai = raiz;  
    }
    if(chave > raiz->chave){
        raiz->dir = insert(raiz->dir, chave);
        raiz->dir->pai = raiz;
    }

    //realizar o balanceamento aqui!!
    raiz = balanceamento(raiz);

    return raiz;
}


//implementação do transplante
//faz o transplante de um no para outro
//transplante por antecessor 
struct no *transplante(struct no *raiz, int chave){
    struct no *ant;
    
    ant = buscaMax(raiz->esq);  //busco o antecessor do no que quero remover

    //copia a chave
    raiz->chave = ant->chave;

    //deleta o antecessor, que agr era a antiga raiz, a que eu ja queria deletar
    raiz->esq = delete(raiz->esq, ant->chave);

    return raiz;
}

//implementação do delete
//essa função irá excluir um no da arvore
//usaremos o min e o transplante para a remoção
struct no *delete(struct no *raiz, int chave){

    //se nao encontrar a chave
    if(raiz == NULL){
        printf("Chave não encontrada\n");
        return raiz;
    }

    //se a chave for encontrada
    if(chave == raiz->chave){
        if(raiz->esq && raiz->dir){ //se o no tiver dois filhos
            raiz = transplante(raiz, chave);
        }
        else if(raiz->esq && !raiz->dir){   //se o no tiver apenas o filho esquerdo
            raiz->chave = raiz->esq->chave;
            free(raiz->esq);
            raiz->esq = NULL;
        }
        else if(!raiz->esq && raiz->dir){   //se o no tiver apenas o filho direito
            raiz->chave = raiz->dir->chave;
            free(raiz->dir);
            raiz->dir = NULL;
        }
        else{
            free(raiz); //se o no for uma folha
            return NULL;
        }
    }
    else if(chave < raiz->chave)    //se a chave for menor que a raiz, entao ela vai para a esquerda
        raiz->esq = delete(raiz->esq, chave);
    else
        raiz->dir = delete(raiz->dir, chave);   //se a chave for maior que a raiz, entao ela vai para a direita


    //realizar o balanceamento aqui!!
    raiz = balanceamento(raiz);

    return raiz;
}

//essa função se chama emOrder
//ela irá imprimir a arvore em ordem
//como é um BST, ela imprimi ordenado
void emOrder(struct no *raiz, int h){
    if(raiz != NULL){
        emOrder(raiz->esq, h+1);
        printf("%d,%d\n", raiz->chave, h);
        emOrder(raiz->dir, h+1);
    }
}