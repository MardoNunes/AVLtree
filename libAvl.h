

#ifndef __LIBAVL__
#define __LIBAVL__
#include "libBst.h"

//essa função irá retornar o fator de balanceamento de um nó
int fb(struct no *no);

//Essa função retorna o no com maior valor em uma subarvore
struct no *buscaMax(struct no *no);

///Essa função retorna a diferena entre o balanceamento dos filhos
int testaBal(struct no *no);

//Essa função faz a rotação a esquerda
struct no *rotEsquerda(struct no *no);

//Essa função faz a rotação a direita
struct no *rotDireita(struct no *no);

//Essa função faz o balanceamento da arvore
struct no *balanceamento(struct no *no);

//Essa função irá comparar o maior entre duas chaves
int max(int a, int b);

#endif