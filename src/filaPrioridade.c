//
// Created by natha on 15/06/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <error.h>

#include "../include/filaPrioridade.h"

#define CAPACIDADE_INICIAL 16

typedef struct {
    ItemFilaPrioridade item;
    double prioridade;
}NoFilaPrioridade;

typedef struct {
    NoFilaPrioridade* itens;
    int tamanho;
    int capacidade;
}filaprioridade;

static void trocar(NoFilaPrioridade* itens, int i, int j) {
    NoFilaPrioridade temp = itens[i];
    itens[i] = itens[j];
    itens[j] = temp;
}

static void sobeElemento(filaprioridade* fP, int indice){
    while (indice > 0) {
        int pai = (indice - 1) / 2;
        if (fP->itens[indice].prioridade < fP->itens[pai].prioridade) {
            trocar(fP->itens, indice, pai);
            indice = pai;
        } else {
            break;
        }
    }
}

static void desceElemento(filaprioridade* fP, int indice) {
    while (1) {
        int menor = indice;
        int esq = 2 * indice + 1;
        int dir = 2 * indice + 2;

        if (esq < fP->tamanho && fP->itens[esq].prioridade < fP->itens[menor].prioridade) {
            menor = esq;
        }
        if (dir < fP->tamanho && fP->itens[dir].prioridade < fP->itens[menor].prioridade) {
            menor = dir;
        }

        if (menor == indice) break;

        trocar(fP->itens, indice, menor);
        indice = menor;
    }
}

static void cresceFilaPrioridade(filaprioridade* fP) {
    int novaCapacidade = fP->capacidade * 2;
    NoFilaPrioridade* novosItens = (NoFilaPrioridade*) realloc(fP->itens, novaCapacidade * sizeof(NoFilaPrioridade));
    if (novosItens == NULL) {
        printf("Erro ao realocar memória em cresceFilaPrioridade!\n");

        perror("Motivo do erro");
        exit(1);
    }
    fP->itens = novosItens;
    fP->capacidade = novaCapacidade;
}

FilaPrioridade criarFilaPrioridade() {
    filaprioridade* f = (filaprioridade*) malloc(sizeof(filaprioridade));
    if(f == NULL){
        printf("Erro ao alocar memória ao criarFilaPrioridade!\n");

        perror("Motivo do erro");
        exit(1);
    }

    f->itens = (NoFilaPrioridade*) malloc(CAPACIDADE_INICIAL * sizeof(NoFilaPrioridade));
    if(f->itens == NULL) {
        printf("Erro ao alocar memória do vetor de nos em criarFilaPrioridade!\n");

        perror("Motivo do erro");
        exit(1);
    }

    f->tamanho = 0;
    f->capacidade = CAPACIDADE_INICIAL;

    return f;
}

void inserirFilaPrioridade(FilaPrioridade f, ItemFilaPrioridade i, double prioridade) {
    filaprioridade* fila = (filaprioridade*)f;

    if (fila->tamanho == fila->capacidade) {
        cresceFilaPrioridade(f);
    }

    fila->itens[fila->tamanho].item = i;
    fila->itens[fila->tamanho].prioridade = prioridade;
    fila->tamanho++;

    sobeElemento(fila, fila->tamanho - 1);
}

ItemFilaPrioridade extrairFilaPrioridadeMinima(FilaPrioridade f) {
    filaprioridade* fila = (filaprioridade*)f;

    ItemFilaPrioridade itemMinimo = fila->itens[0].item;

    fila->tamanho--;
    if (fila->tamanho > 0) {
        fila->itens[0] = fila->itens[fila->tamanho];
        desceElemento(fila, 0);
    }

    return itemMinimo;
}

double consultarPrioridadeMinima(FilaPrioridade f) {
    filaprioridade* fila = (filaprioridade*)f;
    return fila->itens[0].prioridade;
}

bool filaPrioridadeVazia(FilaPrioridade f) {
    filaprioridade* fila = (filaprioridade*)f;
    return fila->tamanho == 0;

}

int tamanhoFilaPrioridade(FilaPrioridade f) {
    filaprioridade* fila = (filaprioridade*)f;
    return fila->tamanho;
}

void liberarFilaPrioridade(FilaPrioridade f) {
    filaprioridade* fila = (filaprioridade*)f;

    free(fila->itens);
    free(fila);
}