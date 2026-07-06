//
// Created by natha on 15/06/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <error.h>

#include "../include/filaPrioridade.h"

typedef struct {
    ItemFilaPrioridade item;
    double prioridade;
}NoFilaPrioridade;

typedef struct {
    NoFilaPrioridade* itens;
    int tamanho;
}filaprioridade;

FilaPrioridade criarFilaPrioridade() {
    filaprioridade* f = (filaprioridade*) malloc(sizeof(filaprioridade));
    if(f == NULL){
        printf("Erro ao alocar memória ao criarFilaPrioridade!\n");

        perror("Motivo do erro");
        exit(1);
    }

    f->itens = (NoFilaPrioridade*) malloc(sizeof(NoFilaPrioridade));
    if(f->itens == NULL) {
        printf("Erro ao alocar memória do vetor de nos em criarFilaPrioridade!\n");

        perror("Motivo do erro");
        exit(1);
    }

    f->tamanho = 0;

    return f;
}

void inserirFilaPrioridade(FilaPrioridade f, ItemFilaPrioridade i, double prioridade) {
    filaprioridade* fila = (filaprioridade*)f;

    fila->itens[fila->tamanho].item = i;
    fila->itens[fila->tamanho].prioridade = prioridade;
    fila->tamanho++;

}

ItemFilaPrioridade extrairFilaPrioridadeMinima(FilaPrioridade f) {
    filaprioridade* fila = (filaprioridade*)f;

    ItemFilaPrioridade itemMinimo = fila->itens[0].item;
    fila->tamanho--;

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