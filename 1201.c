#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NO {
    int data;
    struct NO* left, * right;
} NO;

void imprimirpre(NO* raiz, int* i);

void imprimirin(NO* raiz, int* i);

void imprimirpost(NO* raiz, int* i);

NO* insert(NO** raiz, int x);

NO* remover(NO** raiz, int x);

void search(NO* raiz, int* i, int x);

void liberar(NO** raiz);

int main() {
    int i;
    char input[8];
    NO* raiz = NULL;
    while (scanf("%[^\n]%*c", input) != EOF) {
        if (strcmp(input, "INFIXA") == 0) {
            i = 0;
            imprimirin(raiz, &i);
            printf("\n");
        }
        else if (strcmp(input, "PREFIXA") == 0) {
            i = 0;
            imprimirpre(raiz, &i);
            printf("\n");
        }
        else if (strcmp(input, "POSFIXA") == 0) {
            i = 0;
            imprimirpost(raiz, &i);
            printf("\n");
        }
        else {
            if (input[0] == 'I') {
                raiz = insert(&raiz, atoi(&input[2]));
            }
            else if (input[0] == 'R') {
                raiz = remover(&raiz, atoi(&input[2]));
            }
            else {
                i = 0;
                search(raiz, &i, atoi(&input[2]));
                if (i) printf("%d existe\n", atoi(&input[2]));
                else printf("%d nao existe\n", atoi(&input[2]));
            }
        }
    }
    liberar(&raiz);
    return 0;
}

NO* insert(NO** raiz, int x) {
    NO* novo = NULL;
    if (*raiz == NULL) {
        novo = (NO*)malloc(sizeof(NO));
        novo->left = NULL;
        novo->right = NULL;
        novo->data = x;
        return novo;
    }
    else {
        if (x > (*raiz)->data) (*raiz)->right = insert(&(*raiz)->right, x);
        else (*raiz)->left = insert(&(*raiz)->left, x);
        return *raiz;
    }
}

void imprimirpre(NO* raiz, int* i) {
    if (raiz != NULL) {
        if (*i == 0) {
            *i = *i + 1;
            printf("%d", raiz->data);
        }
        else printf(" %d", raiz->data);
        imprimirpre(raiz->left, i);
        imprimirpre(raiz->right, i);
    }
}

void imprimirin(NO* raiz, int* i) {
    if (raiz != NULL) {
        imprimirin(raiz->left, i);
        if (*i == 0) {
            *i = *i + 1;
            printf("%d", raiz->data);
        }
        else printf(" %d", raiz->data);
        imprimirin(raiz->right, i);
    }
}

void imprimirpost(NO* raiz, int* i) {
    if (raiz != NULL) {
        imprimirpost(raiz->left, i);
        imprimirpost(raiz->right, i);
        if (*i == 0) {
            *i = *i + 1;
            printf("%d", raiz->data);
        }
        else printf(" %d", raiz->data);
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

void search(NO* raiz, int* i, int x) {
    if (raiz != NULL) {
        if (raiz->data == x) {
            *i = 1;
            return;
        }
        else {
            if (x > raiz->data) search(raiz->right, i, x);
            else search(raiz->left, i, x);
        }
    }
}

NO* remover(NO** raiz, int x) {
    NO* aux = *raiz;
    if (*raiz == NULL) {
        return NULL;
    }
    else {
        if (aux->data == x) {
            if (aux->left == NULL && aux->right == NULL) {
                free(aux);
                return NULL;
            }
            else {
                if ((aux->left == NULL && aux->right != NULL) || (aux->left != NULL && aux->right == NULL)) {
                    if (aux->right != NULL) aux = aux->right;
                    else aux = aux->left;
                    free(*raiz);
                    return aux;
                }
                else {
                    aux = (*raiz)->left;
                    while (aux->right != NULL) aux = aux->right;
                    (*raiz)->data = aux->data;
                    aux->data = x;
                    (*raiz)->left = remover(&((*raiz)->left), x);
                    return *raiz;
                }
            }
        }
        else {
            if (x > aux->data) aux->right = remover(&(aux->right), x);
            else aux->left = remover(&(aux->left), x);
            return *raiz;
        }
    }
}