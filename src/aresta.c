//
// Created by natha on 25/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/aresta.h"

#include <stdlib.h>

typedef struct {
    char* idDestino;
    char* ladoDireito;
    char* ladoEsquerdo;
    double comprimento;
    double velocidadeMedia;
    char* nomeAresta;
}aresta;

static char* copiaString(char* origem) {
    if (origem == NULL) {
        return NULL;
    }

    char* copia = (char*) malloc((strlen(origem) + 1));
    if (copia == NULL) {
        printf("Erro ao alocar memória para string em aresta!\n");

        perror("Motivo do erro");
        exit(1);
    }

    strcpy(copia, origem);
    return copia;
}

Aresta criarAresta(char* IDDestino, char* ldir, char* lesq, double cmp, double vm, char* nome) {
    aresta* a = malloc(sizeof(aresta));

    if (a == NULL) {
        printf("Erro ao alocar memória ao criarAresta!\n");

        perror("Motivo do erro");
        exit(1);
    }

    a->idDestino = copiaString(IDDestino);

    a->ladoDireito = copiaString(ldir);

    a->ladoEsquerdo = copiaString(lesq);

    a->comprimento = cmp;
    a->velocidadeMedia = vm;

    a->nomeAresta = copiaString(nome);

    return a;

}

char* getIDVerticeDestinoAresta(Aresta a) {
    return ((aresta*)a)->idDestino;
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

void setVelocidadeAresta(Aresta a, double velocidadeMedia) {
    ((aresta*) a)->velocidadeMedia = velocidadeMedia;
}

void liberarAresta(Aresta a) {
    if ( a == NULL) {
        return;
    }
    aresta* a1 = ((aresta*)a);
    free(a1->idDestino);
    free(a1->ladoDireito);
    free(a1->ladoEsquerdo);
    free(a1->nomeAresta);
    free(a1);
}


