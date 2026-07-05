//
// Created by natha on 04/07/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>

#include "../include/registrador.h"

#define NUMERO_REG 11

typedef struct {
    double x;
    double y;
    //bool ocupado;
}registrador;

typedef struct{
    registrador vetor[NUMERO_REG];
}registradores;


Registradores criarRegistradores() {
    registradores* estoque = (registradores*)malloc(sizeof(registradores));
    if (estoque == NULL) {
        printf("Erro ao alocar memória ao criarRegistradores!\n");

        perror("Motivo do erro");
        exit(1);
    }

    for (int i = 0; i < NUMERO_REG; i++) {
        estoque->vetor[i].x = 0.0;
        estoque->vetor[i].y = 0.0;
    }

    return estoque;
}

void setRegistrador(Registradores estoque, char* IDRegistrador, double x, double y) {
    registradores* est = estoque;

    int indice = atoi(IDRegistrador + 1);

    est->vetor[indice].x = x;
    est->vetor[indice].y = y;
}

double getXRegistrador(Registradores estoque, char* IDRegistrador) {
    registradores* est = estoque;

    int indice = atoi(IDRegistrador + 1);
    return est->vetor[indice].x;
}

double getYRegistrador(Registradores estoque, char* IDRegistrador) {
    registradores* est = estoque;

    int indice = atoi(IDRegistrador + 1);
    return est->vetor[indice].y;
}

void liberarRegistradores(Registradores estoque) {
    registradores* est = estoque;

    free(est);
}