//
// Created by natha on 15/06/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <error.h>

#include "../include/vertice.h"
#include "../include/aresta.h"
#include "../include/componentes.h"

typedef struct {
    int numComponentes;
    Lista* componentes;
}resultadoComponentes;

static int procurar(int* pai, int i) {
    if (pai[i] != i) {
        pai[i] = procurar(pai, pai[i]);
    }
    return pai[i];
}

static void unir(int* pai, int* peso, int i, int j) {
    int ri = procurar(pai, i);
    int rj = procurar(pai, j);

    if (ri == rj) {
        return;
    }

    if (peso[ri] < peso[rj]) {
        int temp = ri;
        ri = rj;
        rj = temp;
    }

    pai[rj] = ri;

    if (peso[ri] == peso[rj]) {
        peso[ri]++;
    }
}

ResultadoComponentes executarComponentes(Grafo g, double vl) {
    resultadoComponentes* r = (resultadoComponentes*) malloc(sizeof(resultadoComponentes));
    if (r == NULL) {
        printf("Erro ao alocar memória ao executarComponentes!\n");

        perror("Motivo do erro");
        exit(1);
    }

    r->numComponentes = 0;
    r->componentes = NULL;

    int nVertices = getNumVerticesGrafo(g);
    if (nVertices == 0) {
        return r;
    }

    Vertice* vertices = (Vertice*) malloc(nVertices * sizeof(Vertice));
    int* pai = (int*) malloc(nVertices * sizeof(int));
    int* peso = (int*) malloc(nVertices * sizeof(int));

    if (!vertices || !pai || !peso) {
        printf("Erro ao alocar memória dos vetores ao executarComponentes!\n");

        perror("Motivo do erro");
        exit(1);
    }

    Lista listaVertices = getVerticesGrafo(g);
    Nopont noLista = getPrimeiroNoLista(listaVertices);
    for (int i = 0; i < nVertices; i++) {
        vertices[i] = (Vertice) getItemNoLista(noLista);
        pai[i] = i;
        peso[i] = 0;
        noLista = getProximoNoLista(noLista);
    }

    for (int i = 0; i < nVertices; i++) {
        Lista arestas = getArestasVertice(vertices[i]);
        Nopont noListaArestas = getPrimeiroNoLista(arestas);
        while (noListaArestas != NULL) {
            Aresta a = (Aresta) getItemNoLista(noListaArestas);
            if (getVelocidadeAresta(a) >= vl) {
                char* IDDestino = getIDVerticeDestinoAresta(a);
                Vertice vDestino = buscaVertice(g, IDDestino);

                int j = (vDestino != NULL) ? getIndiceVertice(vDestino) : -1;
                if (j != -1) {
                    unir(pai, peso, i, j);
                }
            }
            noListaArestas = getProximoNoLista(noListaArestas);
        }
    }

    int* raizParaComponente = (int*) malloc(nVertices * sizeof(int));
    if (!raizParaComponente) {
        printf("Erro ao alocar memória raizParaComponente ao executarComponentes!\n");

        perror("Motivo do erro");
        exit(1);
    }
    for (int i = 0; i < nVertices; i++) {
        raizParaComponente[i] = -1;
    }

    int numeroComponentes = 0;
    for (int i = 0; i < nVertices; i++) {
        int raiz = procurar(pai, i);
        if (raizParaComponente[raiz] == -1) {
            raizParaComponente[raiz] = numeroComponentes++;
        }
    }

    Lista* componentes = (Lista*) malloc(numeroComponentes * sizeof(Lista));
    if (!componentes) {
        printf("Erro ao alocar memória para vetor de Lista de componentes ao executarComponentes!\n");

        perror("Motivo do erro");
        exit(1);
    }

    for (int i = 0; i < numeroComponentes; i++) {
        componentes[i] = iniciarLista();
    }

    for (int i = 0; i < nVertices; i++) {
        int raiz = procurar(pai, i);
        int componenteIndice = raizParaComponente[raiz];
        inserirListaFim(componentes[componenteIndice], vertices[i]);
    }

    r->numComponentes = numeroComponentes;
    r->componentes = componentes;

    free(vertices);
    free(pai);
    free(peso);
    free(raizParaComponente);

    return r;
}

int getNumComponentes(ResultadoComponentes resultado) {
    resultadoComponentes* r = (resultadoComponentes*)resultado;
    return r->numComponentes;
}

Lista getVerticesComponentes(ResultadoComponentes resultado, int i) {
    resultadoComponentes* r = (resultadoComponentes*)resultado;
    return r->componentes[i];
}

void liberarResultadoComponentes(ResultadoComponentes resultado) {
    resultadoComponentes* r = (resultadoComponentes*)resultado;

    for (int i = 0; i < r->numComponentes; i++) {
        liberarLista(r->componentes[i]);
    }
    free(r->componentes);
    free(r);
}

