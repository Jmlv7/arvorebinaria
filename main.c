#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

No* encontrarMinimo(No* raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

No* remover(No* raiz, int valor) {
    if (raiz == NULL) return raiz;
    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No* temp = encontrarMinimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover(raiz->direita, temp->valor);
    }
    return raiz;
}

int buscar(No* raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;
    if (valor < raiz->valor) return buscar(raiz->esquerda, valor);
    return buscar(raiz->direita, valor);
}

void imprimirArvore(No* raiz) {
    if (raiz != NULL) {
        imprimirArvore(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimirArvore(raiz->direita);
    }
}

int altura(No* raiz) {
    if (raiz == NULL) return 0;
    int alturaEsquerda = altura(raiz->esquerda);
    int alturaDireita = altura(raiz->direita);
    return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
}

int contarNos(No* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

int contarFolhas(No* raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esquerda == NULL && raiz->direita == NULL) return 1;
    return contarFolhas(raiz->esquerda) + contarFolhas(raiz->direita);
}

int fatorial(int n) {
    if (n <= 1) return 1;
    return n * fatorial(n - 1);
}

int combinatoria(int n, int p) {
    return fatorial(n) / (fatorial(p) * fatorial(n - p));
}

void menu() {
    No* raiz = NULL;
    int opcao, n, p, valor;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserir resultado da análise combinatória na árvore\n");
        printf("2. Remover elemento da árvore\n");
        printf("3. Buscar elemento na árvore\n");
        printf("4. Imprimir a árvore\n");
        printf("5. Altura da árvore\n");
        printf("6. Número de nós e folhas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite n e p para calcular C(n, p): ");
                scanf("%d %d", &n, &p);
                if (n >= p && n >= 0 && p >= 0) {
                    valor = combinatoria(n, p);
                    raiz = inserir(raiz, valor);
                    printf("Valor %d inserido na árvore.\n", valor);
                } else {
                    printf("Valores inválidos para n e p.\n");
                }
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                printf("Elemento %d removido da árvore.\n", valor);
                break;
            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor)) {
                    printf("Elemento %d encontrado na árvore.\n", valor);
                } else {
                    printf("Elemento %d não encontrado.\n", valor);
                }
                break;
            case 4:
                printf("Árvore em ordem: ");
                imprimirArvore(raiz);
                printf("\n");
                break;
            case 5:
                printf("Altura da árvore: %d\n", altura(raiz));
                break;
            case 6:
                printf("Número total de nós: %d\n", contarNos(raiz));
                printf("Número de folhas: %d\n", contarFolhas(raiz));
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
