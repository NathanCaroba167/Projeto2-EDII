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

static Vertice buscaVerticePeloID(grafo* g, char* id) {
    Nopont noLista = getPrimeiroNoLista(g->vertices);
    while (noLista != NULL) {
        Vertice v = (Vertice) getItemNoLista(noLista);
        if (strcmp(getIDVertice(v), id) == 0) {
            return v;
        }
        noLista = getProximoNoLista(noLista);
    }

    return NULL;
}

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
    inserirListaFim(gf->vertices, v);
}

bool inserirArestaGrafo(Grafo g, char* IDOrigem, char* IDDestino, char* ldir, char* lesq, double cmp, double vm, char* nome) {
    grafo* gf = (grafo*)g;

    Vertice origem = buscaVerticePeloID(gf, IDOrigem);
    Vertice destino = buscaVerticePeloID(gf, IDDestino);

    if (origem == NULL || destino == NULL) {
        return false;
    }

    Aresta a = criarAresta(IDDestino, ldir, lesq, cmp, vm, nome);
    setArestaVertice(origem, a);
    gf->numArestas++;
    return true;

}

Vertice buscaVertice(Grafo g, char* id) {
    grafo* gf = (grafo*)g;
    if (gf->vertices == NULL) {
        return NULL;
    }

    return buscaVerticePeloID(gf->vertices, id);
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