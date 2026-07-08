//
// Created by natha on 15/06/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <string.h>
#include <error.h>

#include "../include/filaPrioridade.h"
#include "../include/vertice.h"
#include "../include/dijkstra.h"

typedef struct {
    bool encontrou;
    double custo;
    Lista caminho;
}resultadoDijkstra;

static int encontraIndice(Vertice* vertices, int nVertices, char* id) {
    for (int i = 0; i < nVertices; i++) {
        if (strcmp(getIDVertice(vertices[i]), id) == 0) {
            return i;
        }
    }
    return -1;
}

static int encontraIndicePonteiro(Vertice* vertices, int nVertices, Vertice v) {
    for (int i = 0; i < nVertices; i++) {
        if (vertices[i] == v) {
            return i;
        }
    }
    return -1;
}

double pesoCurtoDijkstra(Aresta a) {
    return getComprimentoAresta(a);
}

double pesoRapidoDijkstra(Aresta a) {
    return getComprimentoAresta(a) / getVelocidadeAresta(a);
}

ResultadoDijkstra executarDijkstra(Grafo g, char* IDOrigem, char* IDDestino, double (*funcaoPesoCusto)(Aresta a)) {
    resultadoDijkstra* r = (resultadoDijkstra*) malloc(sizeof(resultadoDijkstra));
    if (r == NULL) {
        printf("Erro ao alocar memória ao executarDijkstra!\n");

        perror("Motivo do erro");
        exit(1);
    }

    r->encontrou = false;
    r->custo = 0.0;
    r->caminho = iniciarLista();
    int nVertices = getNumVerticesGrafo(g);
    if (nVertices == 0) {
        return r;
    }

    Vertice* vertices = (Vertice*) malloc(nVertices * sizeof(Vertice));
    double* distancia = (double*) malloc(nVertices * sizeof(double));
    Aresta* predArestas = (Aresta*) malloc(nVertices * sizeof(Aresta));
    int* predIndice = (int*) malloc(nVertices * sizeof(int));

    if (!vertices || !distancia || !predArestas || !predIndice) {
        printf("Erro ao alocar memória dos vetores ao executarDijkstra!\n");

        perror("Motivo do erro");
        exit(1);
    }

    Lista listaVertices = getVerticesGrafo(g);
    Nopont noLista = getPrimeiroNoLista(listaVertices);
    for (int i = 0; i < nVertices; i++) {
        vertices[i] = (Vertice) getItemNoLista(noLista);
        distancia[i] = DBL_MAX;
        predArestas[i] = NULL;
        predIndice[i] = -1;
        noLista = getProximoNoLista(noLista);
    }

    int origemIndice = encontraIndice(vertices, nVertices, IDOrigem);
    int destinoIndice = encontraIndice(vertices, nVertices, IDDestino);

    if (origemIndice == -1 || destinoIndice == -1) {
        free(vertices);
        free(distancia);
        free(predArestas);
        free(predIndice);
        return r;
    }

    distancia[origemIndice] = 0.0;

    FilaPrioridade fP = criarFilaPrioridade();
    inserirFilaPrioridade(fP, vertices[origemIndice], 0.0);

    while (!filaPrioridadeVazia(fP)) {
        double menorPrioridade = consultarPrioridadeMinima(fP);
        Vertice v = (Vertice) extrairFilaPrioridadeMinima(fP);

        int indice = encontraIndicePonteiro(vertices, nVertices, v);
        if (indice == -1) {
            continue;
        }
        if (menorPrioridade > distancia[indice]) {
            continue;
        }
        if (indice == destinoIndice) {
            break;
        }

        Lista arestas = getArestasVertice(v);
        Nopont noListaArestas = getPrimeiroNoLista(arestas);
        while (noListaArestas != NULL) {
            Aresta a = (Aresta) getItemNoLista(noListaArestas);
            Vertice viz = buscaVertice(g, getIDVerticeDestinoAresta(a));
            int vizIndice = (viz != NULL) ? encontraIndicePonteiro(vertices, nVertices, viz) : -1;

            if (vizIndice != -1) {
                double novaDistancia = distancia[indice] + funcaoPesoCusto(a);
                if (novaDistancia < distancia[vizIndice]) {
                    distancia[vizIndice] = novaDistancia;
                    predArestas[vizIndice] = a;
                    predIndice[vizIndice] = indice;
                    inserirFilaPrioridade(fP, viz, novaDistancia);
                }
            }

            noListaArestas = getProximoNoLista(noListaArestas);
        }
    }

    liberarFilaPrioridade(fP);

    if (distancia[destinoIndice] < DBL_MAX) {
        r->encontrou = true;
        r->custo = distancia[destinoIndice];

        int atual = destinoIndice;
        while (predIndice[atual] != -1) {
            inserirListaInicio(r->caminho, predArestas[atual]);
            atual = predIndice[atual];
        }
    }

    free(vertices);
    free(distancia);
    free(predArestas);
    free(predIndice);

    return r;
}

bool encontrouCaminhoDijkstra(ResultadoDijkstra resultado) {
    resultadoDijkstra* r = (resultadoDijkstra*) resultado;
    return r->encontrou;
}

double getCustoDijkstra(ResultadoDijkstra resultado) {
    resultadoDijkstra* r = (resultadoDijkstra*) resultado;
    return r->custo;
}

Lista getCaminhoDijkstra(ResultadoDijkstra resultado) {
    resultadoDijkstra* r = (resultadoDijkstra*) resultado;
    return r->caminho;
}

void liberarResultadoDijkstra(ResultadoDijkstra resultado) {
    resultadoDijkstra* r = (resultadoDijkstra*) resultado;
    liberarLista(r->caminho);
    free(r);

}