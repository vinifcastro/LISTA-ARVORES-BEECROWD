#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int data;
    struct NO* left, * right;
} NO;

void insertBtree(NO** raiz, int data);

void imprimirpre(NO* raiz);

void imprimirin(NO* raiz);

void imprimirpost(NO* raiz);

void imprimir(NO* raiz, int* j);

void liberar(NO** raiz);

int main() {
    NO* raiz = NULL;
    NO* ajuda;
    int c, k, i, data, j = 0;
    scanf("%d", &c);
    while (c--) {
        scanf("%d", &k);
        for (i = 0; i < k; i++) {
            scanf("%d", &data);
            insertBtree(&raiz, data);
        }
        imprimir(raiz, &j);
        ajuda = raiz;
        raiz = NULL;
        liberar(&ajuda);
        printf("\n");
    }
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

void imprimirpre(NO* raiz) {
    if (raiz != NULL) {
        printf(" %d", raiz->data);
        imprimirpre(raiz->left);
        imprimirpre(raiz->right);
    }
}

void imprimirin(NO* raiz) {
    if (raiz != NULL) {
        imprimirin(raiz->left);
        printf(" %d", raiz->data);
        imprimirin(raiz->right);
    }
}

void imprimirpost(NO* raiz) {
    if (raiz != NULL) {
        imprimirpost(raiz->left);
        imprimirpost(raiz->right);
        printf(" %d", raiz->data);
    }
}

void imprimir(NO* raiz, int* j) {
    printf("Case %d:\n", ++(*j));
    printf("Pre.:");
    imprimirpre(raiz);
    printf("\n");
    printf("In..:");
    imprimirin(raiz);
    printf("\n");
    printf("Post:");
    imprimirpost(raiz);
    printf("\n");
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