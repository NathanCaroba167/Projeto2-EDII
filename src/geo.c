//
// Created by natha on 09/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "../include/via.h"
#include "../include/geo.h"

#include "../include/quadra.h"

#define TAMANHO_MAX_BUFFER 256

static Arquivo abrirGeo(Nome arquivoGeo) {
    Arquivo geo = fopen(arquivoGeo,"r");
    if (geo == NULL) {
        printf("Erro ao abrir o arquivo geo!\n");

        perror("Motivo do erro");
        exit(1);
    }
    return geo;
}

Lista lerGeo(Nome caminho) {
    Arquivo arquivoGeo = abrirGeo(caminho);
    Lista quadras = iniciarLista();

    char corP[32] = "orange";
    char corB[32] = "black";
    double sw = 1.0;

    char buffer[TAMANHO_MAX_BUFFER];
    while(fgets(buffer,sizeof(buffer),arquivoGeo) != NULL) {
        // Remove quebras de linha e trata linhas vazias
        if (buffer[0] == '\n' || buffer[0] == '\r') {
            continue;
        }

        char* comando = strtok(buffer," \t\r\n");
        if (comando == NULL) {
            continue;
        }

        if (strcmp(comando, "q") == 0) {
            char* cep = strtok(NULL," \t\r\n");
            double x = atof(strtok(NULL," \t\r\n"));
            double y = atof(strtok(NULL," \t\r\n"));
            double w = atof(strtok(NULL," \t\r\n"));
            double h = atof(strtok(NULL," \t\r\n"));

            Quadra q = criarQuadra(cep, x, y, w, h);
            setCorPQuadra(q, corP);
            setCorBQuadra(q, corB);
            setSWQuadra(q, sw);
            inserirListaFim(quadras, q);

        }else if (strcmp(comando, "cq") == 0) {
            double novaSW = atof(strtok(NULL," \t\r\n"));
            char* novaCorP = strtok(NULL," \t\r\n");
            char* novaCorB = strtok(NULL," \t\r\n");

            sw = novaSW;
            if (novaCorP) {
                strncpy(corP, novaCorP, 31);
            }
            if (novaCorB) {
                strncpy(corB, novaCorB, 31);
            }

        }else {
            printf("Comando desconhecido: '%s'\n", comando);
        }
    }
    fclose(arquivoGeo);
    printf("DEBUB: passou geo\n");
    return quadras;
}