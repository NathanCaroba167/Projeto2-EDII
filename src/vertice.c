//
// Created by natha on 25/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vertice.h"

typedef struct {
    char* id;
    double x;
    double y;
    Lista arestas;
    int indice;
}vertice;

Vertice criarVertice(char* id, double x, double y, int indice) {
    vertice* v = (vertice*) malloc(sizeof(vertice));

    if (v == NULL) {
        printf("Erro ao alocar memória ao criarVertice!\n");

        perror("Motivo do erro");
        exit(1);
    }

    v->id = malloc(strlen(id)+1);
    if (v->id == NULL) {
        printf("Erro ao alocar memória ao definir ID do vértice!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(v->id, id);

    v->x = x;
    v->y = y;
    v->indice = indice;
    v->arestas = iniciarLista();

    return v;
}

char* getIDVertice(Vertice v) {
    return ((vertice*) v)->id;
}

double getXVertice(Vertice v) {
    return ((vertice*) v)->x;
}

double getYVertice(Vertice v) {
    return ((vertice*) v)->y;
}

int getIndiceVertice(Vertice v) {
    return ((vertice*) v)->indice;
}

void setArestaVertice(Vertice v, Aresta a) {
    vertice* v1 = (vertice*) v;
    inserirListaFim(v1->arestas, a);
}

Lista getArestasVertice(Vertice v) {
    return ((vertice*) v)->arestas;
}

void liberarVertice(Vertice v) {
    if (v == NULL) {
        return;
    }
    vertice* v1 = (vertice*)v;

    Nopont noLista = getPrimeiroNoLista(v1->arestas);
    while (noLista != NULL) {
        Aresta a = (Aresta) getItemNoLista(noLista);
        liberarAresta(a);
        noLista = getProximoNoLista(noLista);
    }
    liberarLista(v1->arestas);

    free(v1->id);
    free(v1);
}