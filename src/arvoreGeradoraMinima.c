//
// Created by natha on 15/06/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <error.h>

#include "../include/filaPrioridade.h"
#include "../include/vertice.h"
#include "../include/aresta.h"
#include "../include/arvoreGeradoraMinima.h"

typedef struct {
    Lista arestas;
}resultadoArvoreGeradoraMinima;

static int procurar(int* pai, int i) {
    if (pai[i] != i) {
        pai[i] = procurar(pai, pai[i]);
    }
    return pai[i];
}

static bool unir(int* pai, int* peso, int i, int j) {
    int ri = procurar(pai, i);
    int rj = procurar(pai, j);

    if (ri == rj) {
        return false;
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

    return true;
}

typedef struct {
    Aresta aresta;
    int origemIndice;
}parArestaAuxiliar;

ResultadoArvoreGeradoraMinima executarArvoreGeradoraMinima(Grafo g, double vl) {
    resultadoArvoreGeradoraMinima* r = (resultadoArvoreGeradoraMinima*) malloc(sizeof(resultadoArvoreGeradoraMinima));
    if (r == NULL) {
        printf("Erro ao alocar memória ao executarArvoreGeradoraMinima!\n");

        perror("Motivo do erro");
        exit(1);
    }

    r->arestas = iniciarLista();

    int nVertices = getNumVerticesGrafo(g);
    if (nVertices == 0) {
        return r;
    }

    Vertice* vertices = (Vertice*) malloc(nVertices * sizeof(Vertice));
    int* pai = (int*) malloc(nVertices * sizeof(int));
    int* peso = (int*) malloc(nVertices * sizeof(int));

    if (!vertices || !pai || !peso) {
        printf("Erro ao alocar memória dos vetores ao executarArvoreGeradoraMinima!\n");

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

    int nArestas = getNumArestasGrafo(g);
    parArestaAuxiliar* pares = (parArestaAuxiliar*) malloc (nArestas * sizeof(parArestaAuxiliar));
    if (!pares && nArestas > 0) {
        printf("Erro ao alocar memória dos pares auxiliares ao executarArvoreGeradoraMinima!\n");

        perror("Motivo do erro");
        exit(1);
    }

    FilaPrioridade fP = criarFilaPrioridade();
    int paresIndice = 0;
    for (int i = 0; i < nVertices; i++) {
        Lista arestas = getArestasVertice(vertices[i]);
        Nopont noListaArestas = getPrimeiroNoLista(arestas);
        while (noListaArestas != NULL) {
            Aresta a = (Aresta) getItemNoLista(noListaArestas);
            pares[paresIndice].aresta = a;
            pares[paresIndice].origemIndice = i;
            inserirFilaPrioridade(fP, &pares[paresIndice], getComprimentoAresta(a));
            paresIndice++;
            noListaArestas = getProximoNoLista(noListaArestas);
        }
    }

    while (!filaPrioridadeVazia(fP)) {
        parArestaAuxiliar* par = (parArestaAuxiliar*) extrairFilaPrioridadeMinima(fP);
        Aresta a = par->aresta;
        int origemIndice = par->origemIndice;

        char* IDDestino = getIDVerticeDestinoAresta(a);

        Vertice vDestino = buscaVertice(g, IDDestino);

        int destinoIndice = (vDestino != NULL) ? getIndiceVertice(vDestino) : -1;

        if (destinoIndice == -1) {
            continue;
        }

        bool entrou = unir(pai, peso, origemIndice, destinoIndice);
        if (entrou && getVelocidadeAresta(a) < vl) {
            setVelocidadeAresta(a, getVelocidadeAresta(a) * 1.5);
            inserirListaFim(r->arestas, a);
        }
    }

    liberarFilaPrioridade(fP);
    free(pares);
    free(vertices);
    free(pai);
    free(peso);

    return r;
}

Lista getArestasArvoreGeradoraMinima(ResultadoArvoreGeradoraMinima resultado) {
    resultadoArvoreGeradoraMinima* r = (resultadoArvoreGeradoraMinima*)resultado;
    return r->arestas;
}

int getNumArestasArvoreGeradoraMinima(ResultadoArvoreGeradoraMinima resultado) {
    resultadoArvoreGeradoraMinima* r = (resultadoArvoreGeradoraMinima*)resultado;
    return getTamanhoLista(r->arestas);
}

void liberarResultadoArvoreGeradoraMinima(ResultadoArvoreGeradoraMinima resultado) {
    resultadoArvoreGeradoraMinima* r = (resultadoArvoreGeradoraMinima*)resultado;

    liberarLista(r->arestas);
    free(r);
}

