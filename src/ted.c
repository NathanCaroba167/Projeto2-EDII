//
// Created by natha on 13/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "../include/arquivos.h"
#include "../include/quadra.h"
#include "../include/svg.h"
#include "../include/geo.h"
#include "../include/via.h"
#include "../include/qry.h"

#define MAX_CAMINHO 128
#define MAX_CAMINHO1 256
#define MAX_CAMINHO2 512

static void gerarMapaBase(Arquivo svg, Lista quadras, Grafo g) {
    Nopont noLista = getPrimeiroNoLista(quadras);
    while (noLista != NULL) {
        desenharQuadraSVG(svg, (Quadra) getItemNoLista(noLista));
        noLista = getProximoNoLista(noLista);
    }

    Lista vertice = getVerticesGrafo(g);
    Nopont noListaVertice = getPrimeiroNoLista(vertice);
    while (noListaVertice != NULL) {
        Vertice v = (Vertice) getItemNoLista(noListaVertice);
        double x1 = getXVertice(v);
        double y1 = getYVertice(v);

        Lista arestas = getArestasVertice(v);
        Nopont noListaAresta = getPrimeiroNoLista(arestas);
        while (noListaAresta != NULL) {
            Aresta a = (Aresta) getItemNoLista(noListaAresta);
            Vertice destino = buscaVertice(g, getIDVerticeDestinoAresta(a));
            if (destino != NULL) {
                desenharArestaSVG(svg, x1, y1, getXVertice(destino), getYVertice(destino));
            }
            noListaAresta = getProximoNoLista(noListaAresta);
        }
        noListaVertice = getProximoNoLista(noListaVertice);
    }
}

int main(int argc, char* argv[]) {
    // Variáveis de Argumentos
    char* dirEntrada = NULL; // -e
    char* nomeArqGeo = NULL; // -f
    char* nomeArqQry = NULL; // -q
    char* dirSaida = NULL; // -o
    char* nomeArqVia = NULL; // -v

    // Análise de argumentos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            dirEntrada = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            nomeArqGeo = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            dirSaida = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            nomeArqQry = argv[i + 1];
            i++;
        }else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) {
            nomeArqVia = argv[i + 1];
            i++;
        }else {
            printf("Parametro '%s' inválido!!\n", argv[i]);
        }
    }

    if (nomeArqGeo == NULL || nomeArqVia == NULL || dirSaida == NULL) {
        printf("ERRO: Parâmetros obrigatórios -f (.geo), -v arq.via e -o (diretorio saida1) não fornecidos!!\n");
        return 1;
    }

    // Construção de caminhos geo e via (necessário para SVG inicial)
    char caminhoCompletoGeo[MAX_CAMINHO];
    if (dirEntrada != NULL) {
        snprintf(caminhoCompletoGeo,MAX_CAMINHO, "%s/%s", dirEntrada, nomeArqGeo);
    } else {
        snprintf(caminhoCompletoGeo,MAX_CAMINHO, "%s", nomeArqGeo);
    }

    char caminhoCompletoVia[MAX_CAMINHO];
    if (nomeArqVia != NULL) {
        if (dirEntrada != NULL) {
            snprintf(caminhoCompletoVia,MAX_CAMINHO, "%s/%s", dirEntrada, nomeArqVia);
        } else {
            strcpy(caminhoCompletoVia,nomeArqVia);
        }
    }

    char* nomeBaseGeo = getNomeBase(nomeArqGeo);
    if (nomeBaseGeo ==  NULL) {
        printf("Erro: nome base do arquivo geo.\n");
        return 1;
    }

    Lista quadras = lerGeo(caminhoCompletoGeo);
    Grafo g = lerVia(caminhoCompletoVia);

    char caminhoSaidaSvgInicial[MAX_CAMINHO];
    snprintf(caminhoSaidaSvgInicial,MAX_CAMINHO, "%s/%s.svg", dirSaida, nomeBaseGeo);
    Arquivo svgInicial = abrirSVG(caminhoSaidaSvgInicial);
    inicializarSVG(svgInicial);
    gerarMapaBase(svgInicial, quadras, g);
    fecharSVG(svgInicial);
    printf("DEBUB: passou svgInicial\n");

    // Construção de caminhos qry (se existir)
    char caminhoCompletoQry[MAX_CAMINHO];
    char caminhoSaidaSvgFinal[MAX_CAMINHO2];
    char caminhoSaidaTxt[MAX_CAMINHO2];
    char caminhoBaseSaida[MAX_CAMINHO1];
    if (nomeArqQry != NULL) {
        if (dirEntrada != NULL) {
            snprintf(caminhoCompletoQry,MAX_CAMINHO, "%s/%s", dirEntrada, nomeArqQry);
        }else {
            strcpy(caminhoCompletoQry, nomeArqQry);
        }

        printf("DEBUG: Tentando abrir o arquivo QRY no caminho: [%s]\n", caminhoCompletoQry);

        char* nomeBaseQry = getNomeBase(nomeArqQry);
        if (nomeBaseQry ==  NULL) {
            free(nomeBaseGeo);
            return 1;
        }
        char nomeCombinado[MAX_CAMINHO];
        snprintf(nomeCombinado,MAX_CAMINHO, "%s-%s", nomeBaseGeo, nomeBaseQry);

        snprintf(caminhoBaseSaida,MAX_CAMINHO1, "%s/%s", dirSaida, nomeCombinado);

        snprintf(caminhoSaidaSvgFinal,MAX_CAMINHO2, "%s.svg", caminhoBaseSaida);
        snprintf(caminhoSaidaTxt,MAX_CAMINHO2, "%s.txt", caminhoBaseSaida);

        Arquivo svgFinal = abrirSVG(caminhoSaidaSvgFinal);
        inicializarSVG(svgFinal);
        gerarMapaBase(svgFinal, quadras, g);
        printf("DEBUB: passou svgFinal\n");

        Arquivo txt = fopen(caminhoSaidaTxt,"w");
        if (txt == NULL) {
            printf("Erro ao abrir o arquivo txt!\n");

            perror("Motivo do erro");
            exit(1);
        }

        lerComandosExecutar(svgFinal, txt, caminhoCompletoQry, g, quadras);
        printf("DEBUB: passou qry\n");

        fclose(txt);
        fecharSVG(svgFinal);

        free(nomeBaseQry);
    }

    free(nomeBaseGeo);

    // Limpeza da memória
    printf("Limpando a memória ...\n");
    Nopont noLista = getPrimeiroNoLista(quadras);
    while (noLista != NULL) {
        liberarQuadra((Quadra) getItemNoLista(noLista));
        noLista = getProximoNoLista(noLista);
    }
    liberarLista(quadras);
    liberarGrafo(g);

    return 0;
}
