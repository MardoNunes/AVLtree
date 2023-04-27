#include <stdio.h>
#include <stdlib.h>

//Essa será a estrutura do nó da árvore
struct no{
    int chave;
    struct no *esq;
    struct no *dir;
    struct no *pai;
    int altura;
};

//essa função irá retornar o fator de balanceamento de um nó
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
        //  1
        //    \
        //     2
        //      \
        //       3

    //depois:
    //      2
    //     / \
    //    1   3
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
        //       3
        //      /
        //     2
        //    /
        //   1

    //depois:
    //      2
    //     / \
    //    1   3
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






//Essa função irá comparar o maior entre duas chaves
int max(int a, int b){
    if(a > b)
        return a;
    return b;
}

//Essa função irá criar um no
//ela retorna esse no criado
struct no *criaNo(int chave){
    //estou apenas criando, ela ainda nao está ligada a ngm da arvore
    struct no *novo = malloc(sizeof(struct no));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    novo->altura = 0;
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
    //raiz = balanceamento(raiz);

    return raiz;
}

//essa função se chama emOrder
//ela irá imprimir a arvore em ordem
//como é um BST, ela imprimi ordenado
void emOrder(struct no *raiz){
    if(raiz != NULL){
        emOrder(raiz->esq);
        printf("%d ", raiz->chave);
        emOrder(raiz->dir);
    }
}


//essa função irá buscar uma chave na arvore
//ela retorna o no que contem a chave
struct no *busca(struct no *raiz, int chave){
    if(raiz == NULL)
        return NULL;
    if(chave == raiz->chave)
        return raiz;
    if(chave < raiz->chave)
        return busca(raiz->esq, chave);
    return busca(raiz->dir, chave);
}

//Essa função irá retornar o sucessor de um no
//Implementado segundo o livro do Cormen
struct no *min(struct no *raiz){
    while(raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

//implementação do transplante
//essa função irá substituir um no por outro(antigo pelo novo)
void transplante(struct no **raiz, struct no *antigo, struct no *atual){
    //se o antigo for a raiz, entao o atual será a nova raiz
    if(antigo->pai == NULL)
        *raiz = atual;
    else if(antigo == antigo->pai->esq) //se o antigo for filho a esquerda, entao o atual será o novo filho a esquerda
        antigo->pai->esq = atual;
    else
        antigo->pai->dir = atual;   //se o antigo for filho a direita, entao o atual será o novo filho a direita
    if(atual != NULL)   //se o atual não for nulo, entao o pai dele será o pai do antigo
        atual->pai = antigo->pai;
}

//implementação do delete
//essa função irá excluir um no da arvore
//usaremos o min e o transplante para a remoção
void delete(struct no **raiz, struct no *z){
    //se o no a ser removido não tiver filhos, entao ele é removido
    if(z->esq == NULL)
        transplante(raiz, z, z->dir);
    else if(z->dir == NULL) //se o no a direita for nulo, entao removemos o no a esquerda
        transplante(raiz, z, z->esq);
    else{
        struct no *y = min(z->dir);
        //se o pai do minimo for diferente do no a ser removido
        //entao o minimo irá para a direita do no a ser removido
        if(y->pai != z){
            transplante(raiz, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplante(raiz, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
    }
    free(z);

    //realizar o balanceamento aqui!!
    //raiz = balanceamento(raiz);
}

int main(){
    struct no *raiz = NULL;
    raiz = insert(raiz, 20);
    raiz = insert(raiz, 30);
    raiz = insert(raiz, 10);
    raiz = insert(raiz, 40);
    raiz = insert(raiz, 50);
    raiz = insert(raiz, 25);
    emOrder(raiz);
    printf("\n");
    struct no *aux = busca(raiz, 20);
    delete(&raiz, aux);
    emOrder(raiz);
    printf("\n");
    struct no *aux2 = busca(raiz, 25);
    delete(&raiz, aux2);
    emOrder(raiz);
    printf("\n");
    return 0;
}