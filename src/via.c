//
// Created by natha on 06/04/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "../include/grafo.h"
#include "../include/via.h"

#define TAMANHO_MAX_BUFFER 256

static Arquivo abrirVia(Nome arquivoVia) {
    Arquivo via = fopen(arquivoVia,"r");
    if (via == NULL) {
        printf("Erro ao abrir o arquivo via!\n");

        perror("Motivo do erro");
        exit(1);
    }
    return via;
}

Grafo lerVia(Nome caminho) {
    printf("DEBUG: Abrindo arquivo: %s\n", caminho);
    Arquivo arquivoVia = abrirVia(caminho);

    char buffer[TAMANHO_MAX_BUFFER];
    bool primeiraLinha = true;
    Grafo g = NULL;
    int indiceVerticaAtual = 0;

    while(fgets(buffer,sizeof(buffer),arquivoVia) != NULL) {
        // Remove quebras de linha e trata linhas vazias
        if (buffer[0] == '\n' || buffer[0] == '\r') {
            continue;
        }

        if (primeiraLinha) {
            primeiraLinha = false;
            char copia[TAMANHO_MAX_BUFFER];
            strcpy(copia, buffer);
            char* token = strtok(copia," \r\n");

            bool ehNumero = true;
            for (int i = 0; token != NULL && token[i] != '\0'; i++) {
                if (token[i] < '0' || token[i] > '9') {
                    ehNumero = false;
                }
            }
            if (ehNumero && token != NULL) {
                int qtdVertices = atoi(token);
                g = criarGrafo(qtdVertices);
                continue;
            } else {
                g = criarGrafo(0);
            }
        }

        char* comando = strtok(buffer," ");
        if (comando == NULL) {
            continue;
        }

        if (strcmp(comando, "v") == 0) {
            char* id = strtok(NULL," ");
            double x = atof(strtok(NULL," "));
            double y = atof(strtok(NULL," "));

            inserirVerticeGrafo(g, criarVertice(id, x, y, indiceVerticaAtual++));

        }else if (strcmp(comando, "e") == 0) {
            char* V1 = strtok(NULL," ");
            char* V2 = strtok(NULL," ");
            char* ldir = strtok(NULL," ");
            char* lesq = strtok(NULL," ");
            double cmp = atof(strtok(NULL," "));
            double vm = atof(strtok(NULL," "));
            char* nome = strtok(NULL," ");

            char* ldirFinal = (ldir && strcmp(ldir, "-") != 0) ? ldir : NULL;
            char* lesqFinal = (lesq && strcmp(lesq, "-") != 0) ? lesq : NULL;

            inserirArestaGrafo(g, V1, V2, ldirFinal, lesqFinal, cmp, vm, nome);
        }else {
            printf("Comando desconhecido: '%s'\n", comando);
        }
    }
    fclose(arquivoVia);
    printf("DEBUB: passou via\n");
    return g;
}
