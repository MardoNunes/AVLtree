



#ifndef __LIBBST__
#define __LIBBST__
//Essa será a estrutura do nó da árvore
struct no{
    int chave;
    struct no *esq;
    struct no *dir;
    struct no *pai;
    int altura;
};

//Cria un no para a arvore
struct no *criaNo(int chave);

//Insere um no na arvore
struct no *insert(struct no *raiz, int chave);

//faz a troca de um no por outro
struct no *transplante(struct no *raiz, int chave);

//Faz exclusao de um no da arvore
struct no *delete(struct no *raiz, int chave);

//Faz a travessia em ordem da arvore
void emOrder(struct no *raiz, int h);

#endif