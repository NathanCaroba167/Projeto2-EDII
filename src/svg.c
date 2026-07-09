//
// Created by natha on 04/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "../include/aresta.h"
#include "../include/vertice.h"
#include "../include/svg.h"

static int idSVG = 0;

Arquivo abrirSVG(Nome arquivoSvg) {
    Arquivo svg = fopen(arquivoSvg,"w");
    if (svg == NULL) {
        printf("Erro ao abrir o arquivo svg!\n");

        perror("Motivo do erro");
        exit(1);
    }
    return svg;
}

void inicializarSVG(Arquivo svg) {
    if (svg == NULL) return;
    fprintf(svg,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svg,"<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" width=\"10000\" height=\"10000\" viewBox=\"0 0 10000 10000\">\n");
    fprintf(svg,"\t<g>\n");
}

void desenharQuadraSVG(Arquivo svg, Quadra q) {
    if (svg == NULL || q == NULL) return;

    double x = getXQuadra(q);
    double y = getYQuadra(q);
    double w = getWQuadra(q);
    double h = getHQuadra(q);

    char* corB = getCorBQuadra(q);
    char* corP = getCorPQuadra(q);
    double sw = getSWQuadra(q);

    fprintf(svg, "\t<rect id=\"%d\" "
                 "x=\"%lf\" "
                 "y=\"%lf\" "
                 "width=\"%lf\" "
                 "height=\"%lf\" "
                 "stroke=\"%s\" "
                 "fill=\"%s\" "
                 "opacity=\"%lf\" "
                 "stroke-width=\"%lf\" "
                 "/>\n",
                 idSVG++,
                 x,
                 y,
                 w,
                 h,
                 corB,
                 corP,
                 1.0,
                 sw);

    fprintf(svg, "\t<text id=\"%d\" "
                 "x=\"%lf\" "
                 "y=\"%lf\" "
                 "text-anchor=\"middle\" "
                 "dominant-baseline=\"middle\" "
                 "font-size=\"10\" "
                 ">%s</text>\n",
                 idSVG++,
                 x + w / 2.0,
                 y + h / 2.0,
                 getCEPQuadra(q));
}

void desenharArestaSVG(Arquivo svg, double x1, double y1, double x2, double y2) {
    if (svg == NULL) return;

    fprintf(svg, "\t<line id=\"%d\" "
                 "x1=\"%lf\" "
                 "y1=\"%lf\" "
                 "x2=\"%lf\" "
                 "y2=\"%lf\" "
                 "stroke=\"gray\" "
                 "stroke-width=\"1.0\" "
                 "/>\n",
                 idSVG++,
                 x1,
                 y1,
                 x2,
                 y2);
}

void desenharBoundingBoxComponenteSVG(Arquivo svg, double x, double y, double w, double h, char* cor) {
    if (svg == NULL || cor == NULL) return;

    fprintf(svg, "\t<rect id=\"%d\" "
                 "x=\"%lf\" "
                 "y=\"%lf\" "
                 "width=\"%lf\" "
                 "height=\"%lf\" "
                 "stroke=\"%s\" "
                 "fill=\"%s\" "
                 "opacity=\"0.5\" "
                 "stroke-width=\"1.5\" "
                 "/>\n",
                 idSVG++,
                 x,
                 y,
                 w,
                 h,
                 cor,
                 cor);
}

void desenharArestaArvoreGeradoraMinimaSVG(Arquivo svg, double x1, double y1, double x2, double y2) {
    if (svg == NULL) return;

    fprintf(svg, "\t<line id=\"%d\" "
                 "x1=\"%lf\" "
                 "y1=\"%lf\" "
                 "x2=\"%lf\" "
                 "y2=\"%lf\" "
                 "stroke=\"red\" "
                 "stroke-width=\"4.0\" "
                 "/>\n",
                 idSVG++,
                 x1,
                 y1,
                 x2,
                 y2);
}

void desenharPercursoSVG(Arquivo svg, Grafo g, double xOrigem, double yOrigem, double xDestino, double yDestino, Lista caminho, char* cor, int idPercurso) {
    if (svg == NULL || g == NULL || caminho == NULL || cor == NULL) return;
    if (listaVazia(caminho)) return;

    fprintf(svg, "\t<path id=\"percurso%d\" d=\"M %lf,%lf", idPercurso, xOrigem, yOrigem);

    Nopont noLista = getPrimeiroNoLista(caminho);
    while (noLista != NULL) {
        Aresta a = (Aresta) getItemNoLista(noLista);
        Vertice destino = buscaVertice(g, getIDVerticeDestinoAresta(a));
        if (destino != NULL) {
            fprintf(svg, " L %lf %lf ", getXVertice(destino), getYVertice(destino));
        }
        noLista = getProximoNoLista(noLista);
    }

    fprintf(svg, "L %lf %lf\" ", xDestino, yDestino);

    fprintf(svg, "stroke=\"%s\" fill=\"none\" stroke-width=\"2\"/>\n", cor);

    fprintf(svg, "\t<circle r=\"5\" "
                 "fill=\"%s\">\n "
                 "\t\t<animateMotion dur=\"3s\" repeatCount=\"indefinite\">\n"
                 "\t\t\t<mpath href=\"#percurso%d\"/>\n"
                 "\t\t</animateMotion>\n"
                 "\t</circle>\n",
                 cor,
                 idPercurso);


}

void desenharMarcadorSVG(Arquivo svg, double x, double y, char letra, char* cor) {
    if (svg == NULL || cor == NULL) return;

    fprintf(svg, "\t<rect id=\"%d\" "
                 "x=\"%lf\" "
                 "y=\"%lf\" "
                 "width=\"16\" "
                 "height=\"16\" "
                 "stroke=\"black\" "
                 "fill=\"%s\" "
                 "stroke-width=\"1\" "
                 "/>\n",
                 idSVG++,
                 x - 8.0,
                 y - 8.0,
                 cor);

    fprintf(svg, "\t<text id=\"%d\" "
                 "x=\"%lf\" "
                 "y=\"%lf\" "
                 "font-size=\"11\" "
                 "font-weight=\"bold\" "
                 "text-anchor=\"middle\" "
                 "dominant-baseline=\"middle\" "
                 "fill=\"white\" "
                 ">%c</text>\n",
                 idSVG++,
                 x,
                 y,
                 letra);
}

void fecharSVG(Arquivo svg) {
    if (svg == NULL) return;
    fprintf(svg, "</g>\n");
    fprintf(svg,"</svg>\n");
    fclose(svg);

    printf("Arquivo SVG gerado com sucesso!\n");

}