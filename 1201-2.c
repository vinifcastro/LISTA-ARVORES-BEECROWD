#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NO {
    int data;
    struct NO* left, * right;
} NO;

void insertBtree(NO ** raiz, int data);

void imprimirpre(NO * raiz, int * i);

void imprimirin(NO * raiz, int * i);

void imprimirpost(NO * raiz, int * i);

void search(NO * raiz, int * i, int x);

void liberar(NO ** raiz);

void remover(NO ** raiz, NO ** raiz2, int x);

void reinserir(NO ** raiz, NO ** raiz2, int x);

int main(){
    int i;
    char input[8];
    NO *raiz = NULL;
    while(scanf("%[^\n]%*c", input) != EOF){
        if(strcmp(input, "INFIXA") == 0){
            i = 0;
            imprimirin(raiz, &i);
            printf("\n");
        }
        else if(strcmp(input, "PREFIXA") == 0){
            i = 0;
            imprimirpre(raiz, &i);
            printf("\n");
        }
        else if(strcmp(input, "POSFIXA") == 0){
            i = 0;
            imprimirpost(raiz, &i);
            printf("\n");
        }
        else{
            if(input[0] == 'I'){
                insertBtree(&raiz, atoi(&input[2]));
            }
            else if(input[0] == 'R'){
                remover(&raiz, &raiz, atoi(&input[2]));
            }
            else{
                i = 0;
                search(raiz, &i, atoi(&input[2]));
                if(i) printf("%d existe\n", atoi(&input[2]));
                else printf("%d nao existe\n", atoi(&input[2]));
            }
        }
    }
    liberar(&raiz);
    return 0;
}

void insertBtree(NO** raiz, int data) {
    NO* novo = NULL, * aux = *raiz;
    if (aux == NULL) {
        novo = (NO*)malloc(sizeof(NO));
        novo->data = data;
        novo->left = NULL;
        novo->right = NULL;
        *raiz = novo;
    }
    else {
        if (data > ((*raiz)->data)) insertBtree(&(aux->right), data);
        else insertBtree(&(aux->left), data);
    }
}

void imprimirpre(NO* raiz, int * i) {
    if (raiz != NULL) {
        if(*i == 0){ 
            *i = *i + 1;
            printf("%d", raiz->data);
        }
        else printf(" %d", raiz->data);
        imprimirpre(raiz->left, i);
        imprimirpre(raiz->right, i);
    }
}

void imprimirin(NO* raiz, int * i) {
    if (raiz != NULL) {
        imprimirin(raiz->left, i);
        if(*i == 0){ 
            *i = *i + 1;
            printf("%d", raiz->data);
        }
        else printf(" %d", raiz->data);
        imprimirin(raiz->right, i);
    }
}

void imprimirpost(NO* raiz, int * i) {
    if (raiz != NULL) {
        imprimirpost(raiz->left, i);
        imprimirpost(raiz->right, i);
        if(*i == 0){ 
            *i = *i + 1;
            printf("%d", raiz->data);
        }
        else printf(" %d", raiz->data);
    }
}

void search(NO * raiz, int * i, int x){
    if(raiz != NULL){
        if(raiz->data == x){
            *i = 1;
            return;
        }
        else{
            if(x>raiz->data) search(raiz->right, i, x);
            else search(raiz->left, i, x);
        }
    }
}

void liberar(NO** raiz) {
    NO* aux = *raiz;
    if (*raiz == NULL)
        return;
    liberar(&(aux->left));
    liberar(&(aux->right));
    free(aux);
    aux = NULL;
}

void remover(NO ** raiz, NO ** raiz2, int x){
    NO *aux = *raiz, *prox;
    if ((*raiz2)->data == x){
        *raiz2 = NULL;
        reinserir(&aux, raiz2, x);
        liberar(&aux);
    }
    else {
        if(x > aux->data){
            prox = aux->right;
            if(prox->data == x){
                aux->right = NULL;
                reinserir(&prox, raiz2, x);
                liberar(&prox);
            }
            else remover(&(aux->right), raiz2, x);
        }
        else {
            prox = aux->left;
            if(prox->data == x){
                aux->left = NULL;
                reinserir(&prox, raiz2, x);
                liberar(&prox);
            }
            else remover(&(aux->left), raiz2, x);
        }
    }
}

void reinserir(NO ** raiz, NO ** raiz2, int x){
    NO *aux = *raiz;
    if(aux == NULL) return;
    if(aux->data != x){
        insertBtree(raiz2, aux->data);
    }
    reinserir(&(aux->left), raiz2, x);
    reinserir(&(aux->right), raiz2, x);
}