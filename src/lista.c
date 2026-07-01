//
// Created by natha on 13/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <error.h>

#include "../include/lista.h"

typedef struct Elemento{
    Item form;
    struct Elemento *prox;
}Elemento;

typedef Elemento* Nopont;

typedef struct{
    int tamanho;
    Nopont inicio;
    Nopont fim;
}lista;

Lista iniciarLista() {
    lista* l = (lista*)malloc(sizeof(lista));
    if(l == NULL){
        printf("Erro ao alocar memória ao iniciarLista!\n");

        perror("Motivo do erro");
        exit(1);
    }
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void inserirListaInicio(Lista l, Item i){
    lista* ls = (lista*)l;
    Nopont novo = malloc(sizeof(Elemento));
    if(novo == NULL){
        printf("Erro ao alocar memória ao inserirListaInicio!\n");

        perror("Motivo do erro");
        return;
    }
    novo->form = i;
    novo->prox = ls->inicio;
    ls->inicio = novo;
    if (ls->fim == NULL) {
        ls->fim = novo;
    }
    ls->tamanho++;
}

void inserirListaFim(Lista l, Item i) {
    lista* ls = (lista*)l;
    if (ls->inicio == NULL) {
        inserirListaInicio(l,i);
        return;
    }
    Nopont novo = malloc(sizeof(Elemento));
    if(novo == NULL) {
        printf("Erro ao alocar memória ao inserirListaFim!\n");

        perror("Motivo do erro");
        return;
    }
    novo->form = i;
    novo->prox = NULL;
    ls->fim->prox = novo;
    ls->fim = novo;
    ls->tamanho++;
}

void removerElementoLista(Lista l, Item i){
    lista* ls = (lista*)l;
    if(ls->inicio == NULL){
        printf("Nao e possivel excluir algo de uma lista vazia\n");
        return;
    }
    Nopont atual = ls->inicio;
    Nopont anterior = NULL;
    while(atual != NULL && atual->form != i){
        anterior = atual;
        atual = atual->prox;
    }
    if(atual == NULL){
        return;

    }
    if(anterior == NULL){
        ls->inicio = atual->prox;

        if (ls->inicio == NULL) {
            ls->fim = NULL;
        }
    }else{
        anterior->prox = atual->prox;

        if (atual == ls->fim) {
            ls->fim = anterior;
        }
    }
    free(atual);
    ls->tamanho--;

}

Item getPorIdLista(Lista l, int id) {
    lista* ls = (lista*)l;
    pont atual = ls->inicio;
    while(atual != NULL){
        if(getIDForma(atual->form) == id){
            printf("Elemento %d encontrado!\n",id);
            return atual->form;
        }
        atual = atual->prox;
    }
    printf("Elemento %d nao encontrado!\n",id);
    return NULL;
}

void removerPorIdLista(Lista l, int id) {
    lista* ls = (lista*)l;
    if(ls->inicio == NULL){
        printf("Nao e possivel excluir algo de uma lista vazia\n");
        return;
    }
    pont atual = ls->inicio;
    pont anterior = NULL;
    while(atual != NULL && getIDForma(atual->form) != id){
        anterior = atual;
        atual = atual->prox;
    }
    if(atual == NULL){
        return;
    }
    if(anterior == NULL){
        ls->inicio = atual->prox;
        if(ls->inicio == NULL) {
            ls->fim = NULL;
        }
    }else{
        anterior->prox = atual->prox;
        if(atual == ls->fim) {
            ls->fim = anterior;
        }
    }
    free(atual);
    ls->tamanho--;
}

Nopont getPrimeiroNoLista(Lista l) {
    lista* LISTA = (lista*)l;
    return LISTA->inicio;
}

Nopont getProximoNoLista(Nopont p) {
    return p->prox;
}

Nopont getUltimoNoLista(Lista l) {
    lista* LISTA = (lista*)l;
    return LISTA->fim;
}

Item getItemNoLista(Nopont n) {
    return n->form;
}

void concatenaListas(Lista l1, Lista l2) {
    lista* a = (lista*)l1;
    lista* b = (lista*)l2;

    if (b->inicio == NULL) {
        printf("Lista b vazia, erro de concatenacao!");
        return;
    }
    if (a->inicio == NULL) {
        a->inicio = b->inicio;
        a->fim = b->fim;
    } else {
        a->fim->prox = b->inicio;
        a->fim = b->fim;
    }

    a->tamanho += b->tamanho;
    b->inicio = NULL;
    b->fim = NULL;
    b->tamanho = 0;
}

int getTamanhoLista(Lista l) {
    lista* ls = (lista*)l;
    return ls->tamanho;
}

bool listaVazia(Lista l) {
    lista* LISTA = (lista*)l;
    return LISTA->inicio == NULL ? true : false;
}

void liberarLista(Lista l){
    lista* ls = (lista*)l;
    Nopont atual = ls->inicio;
    while(atual != NULL){
        Nopont temp = atual;
        atual = atual->prox;
        if (temp->form != NULL) {
            liberarForma(getPacoteElementoLista(temp));
        }
        free(temp);
    }
    ls->inicio = NULL;
    ls->fim = NULL;
    ls->tamanho = 0;
    free(ls);
}