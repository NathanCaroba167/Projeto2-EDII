//
// Created by natha on 15/06/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/grafo.h"

typedef struct {
    Lista vertices; //Pode ser um hash
    int numArestas;
}grafo;

Grafo criarGrafo() {
    grafo* g = (grafo*)malloc(sizeof(grafo));
    if(g == NULL){
        printf("Erro ao alocar memória ao criarGrafo!\n");

        perror("Motivo do erro");
        exit(1);
    }
    g->vertices = iniciarLista();
    g->numArestas = 0;
    return g;
}

void inserirVerticeGrafo(Grafo g, Vertice v) {
    grafo* gf = (grafo*)g;
    if (gf->vertices == NULL) {
        gf->vertices = iniciarLista();
    }

    inserirListaFim(gf->vertices, v);
}

void inserirArestaGrafo(Grafo g, Aresta a) {
    grafo* gf = (grafo*)g;

    Vertice origem = getVerticeV1Aresta(a);
    Vertice destino = getVerticeV2Aresta(a);

    if (origem == NULL || destino == NULL) {
        return;
    }

    setArestaVertice(origem, a);
    gf->numArestas++;

}

Vertice buscaVertice(Grafo g, char* id) {
    grafo* gf = (grafo*)g;
    if (gf->vertices == NULL) {
        return NULL;
    }

    return buscarItemPorId(gf->vertices, id);
}

Lista getVerticesGrafo(Grafo g) {
    return ((grafo*)g)->vertices;
}

int getNumVerticesGrafo(Grafo g) {
    grafo* gf = (grafo*)g;
    return getTamanhoLista(gf->vertices);
}

int getNumArestasGrafo(Grafo g) {
    return ((grafo*)g)->numArestas;
}

void liberarGrafo(Grafo g) {
    grafo* gf = (grafo*)g;
    liberarLista(gf->vertices);
    free(gf);
}