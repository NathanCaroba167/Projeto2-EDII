//
// Created by natha on 25/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/aresta.h"

#include <stdlib.h>

typedef struct {
    Vertice v1;
    Vertice v2;
    char* ladoDireito;
    char* ladoEsquerdo;
    double comprimento;
    double velocidadeMedia;
    char* nomeAresta;
}aresta;

Aresta criarAresta(Vertice v1, Vertice v2, char* ldir, char* lesq, double cmp, double vm, char* nome) {
    aresta* a = malloc(sizeof(aresta));

    if (a == NULL) {
        printf("Erro ao alocar memória ao criarAresta!\n");

        perror("Motivo do erro");
        exit(1);
    }

    a->v1 = v1;
    a->v2 = v2;
    a->ladoDireito = malloc(sizeof(ldir)+1);
    if (a->ladoDireito == NULL) {
        printf("Erro ao alocar memória ao definir ladoDireito!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(a->ladoDireito, ldir);

    a->ladoEsquerdo = malloc(sizeof(lesq)+1);
    if (a->ladoEsquerdo == NULL) {
        printf("Erro ao alocar memória ao definir ladoEsquerdo!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(a->ladoEsquerdo, lesq);

    a->comprimento = cmp;
    a->velocidadeMedia = vm;

    a->nomeAresta = malloc(sizeof(nome)+1);
    if (a->nomeAresta == NULL) {
        printf("Erro ao alocar memória ao definir nomeAresta!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(a->nomeAresta, nome);

    return a;

}

Vertice getVerticeV1Aresta(Aresta a) {
    return ((aresta*)a)->v1;
}

Vertice getVerticeV2Aresta(Aresta a) {
    return ((aresta*)a)->v2;
}

char* getQuadraLadoDireitoAresta(Aresta a) {
    return ((aresta*)a)->ladoDireito;
}

char* getQuadraLadoEsquerdoAresta(Aresta a) {
    return ((aresta*)a)->ladoEsquerdo;
}

double getComprimentoAresta(Aresta a) {
    return ((aresta*)a)->comprimento;
}

double getVelocidadeAresta(Aresta a) {
    return ((aresta*)a)->velocidadeMedia;
}

char* getNomeAresta(Aresta a) {
    return ((aresta*)a)->nomeAresta;
}

void setQuadraLadoDireitoAresta(Aresta a, char* ladoDireito) {
    aresta* auxiliar = (aresta*)a;
    realloc(auxiliar->ladoEsquerdo, strlen(ladoDireito)+1);
    strcpy(auxiliar->ladoEsquerdo, ladoDireito);
}

void setQuadraLadoEsquerdoAresta(Aresta a, char* ladoEsquerdo) {
    aresta* auxiliar = (aresta*)a;
    realloc(auxiliar->ladoEsquerdo, strlen(ladoEsquerdo)+1);
    strcpy(auxiliar->ladoEsquerdo, ladoEsquerdo);
}

void setComprimentoAresta(Aresta a, double comprimento) {
    ((aresta*) a)->comprimento = comprimento;
}

void setVelocidadeAresta(Aresta a, double velocidadeMedia) {
    ((aresta*) a)->velocidadeMedia = velocidadeMedia;
}

void liberarAresta(Aresta a) {
    if ( a == NULL) {
        return;
    }
    aresta* a1 = ((aresta*)a);
    free(a1->nomeAresta);
    free(a1->ladoDireito);
    free(a1->ladoEsquerdo);
    free(a1);
}


