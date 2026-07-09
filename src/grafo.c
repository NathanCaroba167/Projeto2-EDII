//
// Created by natha on 15/06/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/grafo.h"

#define HASH_CAPACIDADE 1009

typedef struct EntradaHash {
    char* chave;
    Vertice valor;
    struct EntradaHash* proxima;
}EntradaHash;

typedef struct {
    EntradaHash** buckets;
    int capacidade;
    int tamanho;
}tabelaHash;

static unsigned int calcularHash(const char* chave, int capacidade) {
    unsigned int h = 2166136261u;
    while (*chave) {
        h ^=(unsigned char)(*chave++);
        h *= 16777619u;
    }
    return h % (unsigned int) capacidade;
}

static tabelaHash* criarTabelaHash(int capacidade) {
    tabelaHash* t = (tabelaHash*) malloc (sizeof(tabelaHash));
    if (t == NULL) {
        printf("Erro ao alocar memória ao criarTabelaHash!\n");

        perror("Motivo do erro");
        exit(1);
    }

    t->buckets = (EntradaHash**) calloc (capacidade, sizeof(EntradaHash*));
    if (t->buckets == NULL) {
        printf("Erro ao alocar memória ao criarTabelaHash!\n");

        perror("Motivo do erro");
        exit(1);
    }

    t->capacidade = capacidade;
    t->tamanho = 0;

    return t;
}

static void inserirTabelaHash(tabelaHash* t, char* chave, Vertice v) {
    unsigned int indice = calcularHash(chave, t->capacidade);

    EntradaHash* nova = (EntradaHash*) malloc(sizeof(EntradaHash));
    if (nova == NULL) {
        printf("Erro ao alocar memória ao inserirTabelaHash!\n");

        perror("Motivo do erro");
        exit(1);
    }

    nova->chave = (char*) malloc(strlen(chave) + 1);
    if (nova->chave == NULL) {
        printf("Erro ao alocar memória da chave ao inserirTabelaHash!\n");

        perror("Motivo do erro");
        exit(1);
    }

    strcpy(nova->chave, chave);
    nova->valor = v;
    nova->proxima = t->buckets[indice];
    t->buckets[indice] = nova;
    t->tamanho++;
}

static Vertice buscarTabelaHash(tabelaHash* t, char* chave) {
    unsigned int indice = calcularHash(chave, t->capacidade);
    EntradaHash* entrada = t->buckets[indice];

    while (entrada != NULL) {
        if (strcmp(entrada->chave, chave) == 0) {
            return entrada->valor;
        }
        entrada = entrada->proxima;
    }
    return NULL;
}

static void liberarTabelaHash(tabelaHash* t) {
    for (int i = 0; i < t->capacidade; i++) {
        EntradaHash* entrada = t->buckets[i];
        while (entrada != NULL) {
            EntradaHash* proxima = entrada->proxima;
            free(entrada->chave);
            free(entrada);
            entrada = proxima;
        }
    }
    free(t->buckets);
    free(t);
}

typedef struct {
    Lista vertices;
    tabelaHash* hash;
    int numArestas;
}grafo;

Grafo criarGrafo(int numVerticesEsperados) {
    grafo* g = (grafo*)malloc(sizeof(grafo));
    if(g == NULL){
        printf("Erro ao alocar memória ao criarGrafo!\n");

        perror("Motivo do erro");
        exit(1);
    }
    g->vertices = iniciarLista();

    int capacidadeHash = numVerticesEsperados > 0 ? (int)(numVerticesEsperados * 1.5) : HASH_CAPACIDADE;
    if (capacidadeHash % 2 == 0) {
        capacidadeHash++;
    }
    g->hash = criarTabelaHash(capacidadeHash);
    g->numArestas = 0;
    return g;
}

void inserirVerticeGrafo(Grafo g, Vertice v) {
    grafo* gf = (grafo*)g;
    inserirListaFim(gf->vertices, v);
    inserirTabelaHash(gf->hash, getIDVertice(v), v);
}

bool inserirArestaGrafo(Grafo g, char* IDOrigem, char* IDDestino, char* ldir, char* lesq, double cmp, double vm, char* nome) {
    grafo* gf = (grafo*)g;

    Vertice origem = buscarTabelaHash(gf->hash, IDOrigem);
    Vertice destino = buscarTabelaHash(gf->hash, IDDestino);

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

    return buscarTabelaHash(gf->hash, id);
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

    Nopont noLista = getPrimeiroNoLista(gf->vertices);
    while (noLista != NULL) {
        Vertice v = (Vertice) getItemNoLista(noLista);
        liberarVertice(v);
        noLista = getProximoNoLista(noLista);
    }
    liberarLista(gf->vertices);

    liberarTabelaHash(gf->hash);
    free(gf);
}