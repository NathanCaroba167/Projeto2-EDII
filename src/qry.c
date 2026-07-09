//
// Created by natha on 09/10/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <float.h>
#include <math.h>

#include "../include/qry.h"
#include "../include/aresta.h"
#include "../include/arvoreGeradoraMinima.h"
#include "../include/componentes.h"
#include "../include/dijkstra.h"
#include "../include/quadra.h"
#include "../include/registrador.h"
#include "../include/svg.h"

#define TAMANHO_MAX_BUFFER 256
#define NUM_CORES_COMPONENTES 10

static char* CORES_COMPONENTES[] = {
    "blue", "green", "purple", "orange", "brown", "pink", "cyan", "magenta", "yellow", "teal"
};

static void comandoArrobaOInterrogacao(Arquivo svg, Arquivo txt, char* reg, char* cep, char face, double num, Registradores estoque, Lista quadras) {
    Quadra q = NULL;
    Nopont noLista = getPrimeiroNoLista(quadras);
    while (noLista != NULL) {
        Quadra cand = (Quadra) getItemNoLista(noLista);
        if (strcmp(getCEPQuadra(cand), cep) == 0) {
            q = cand;
            break;
        }
        noLista = getProximoNoLista(noLista);
    }

    if (q != NULL) {
        double x, y;
        calcularPosicaoEndereco(q, face, num, &x, &y);
        setRegistrador(estoque, reg, x, y);

        fprintf(txt, "@o? %s %s %c %.2lf -> (%.2lf, %.2lf)\n", reg, cep, face, num, x, y);

        fprintf(svg, "\t<line x1=\"%lf\" "
                 "y1=\"0\" "
                 "x2=\"%lf\" "
                 "y2=\"%lf\" "
                 "stroke=\"red\" "
                 "stroke-dasharray=\"4,4\" "
                 "stroke-width=\"1\" "
                 "/>\n",
                 x,
                 x,
                 y);

        fprintf(svg, "\t<text x=\"%lf\" "
                 "y=\"12\" "
                 "font-size=\"10\" "
                 "fill=\"red\" "
                 ">%s</text>\n",
                 x,
                 reg);
    }
}

static void comandoMvm(Grafo g, double v, double rx, double ry, double rw, double rh) {
    Lista vertices = getVerticesGrafo(g);
    Nopont noListaV = getPrimeiroNoLista(vertices);
    while (noListaV != NULL) {
        Vertice vertice = (Vertice) getItemNoLista(noListaV);
        double vx = getXVertice(vertice);
        double vy = getYVertice(vertice);

        if (vx >= rx && vx <= rx + rw && vy >= ry && vy <= ry + rh) {
            Lista arestas = getArestasVertice(vertice);
            Nopont noListaA = getPrimeiroNoLista(arestas);
            while (noListaA != NULL) {
                setVelocidadeAresta((Aresta) getItemNoLista(noListaA), v);
                noListaA = getProximoNoLista(noListaA);
            }
        }

        noListaV = getProximoNoLista(noListaV);
    }
}

static void comandoRegs(Arquivo svg, Arquivo txt, Grafo g, double vl) {
    ResultadoComponentes rc = executarComponentes(g, vl);

    fprintf(txt, "regs %.2lf -> %d componentes conexos\n", vl, getNumComponentes(rc));

    for (int i = 0; i < getNumComponentes(rc); i++) {
        Lista componente = getVerticesComponentes(rc, i);
        double minX = DBL_MAX;
        double minY = DBL_MAX;
        double maxX = -DBL_MAX;
        double maxY = -DBL_MAX;

        Nopont noLista = getPrimeiroNoLista(componente);
        while (noLista != NULL) {
            Vertice v = (Vertice) getItemNoLista(noLista);
            double vx = getXVertice(v);
            double vy = getYVertice(v);

            if (vx < minX) minX = vx;
            if (vy < minY) minY = vy;
            if (vx > maxX) maxX = vx;
            if (vy > maxY) maxY = vy;

            noLista = getProximoNoLista(noLista);
        }

        char* cor = CORES_COMPONENTES[i % NUM_CORES_COMPONENTES];
        desenharBoundingBoxComponenteSVG(svg, minX - 5, minY - 5, (maxX - minX) + 10, (maxY - minY) + 10, cor);
    }
    liberarResultadoComponentes(rc);

}

static void comandoExp(Arquivo svg, Grafo g, double vl){
    ResultadoArvoreGeradoraMinima ra = executarArvoreGeradoraMinima(g, vl);

    Lista arestasArvore = getArestasArvoreGeradoraMinima(ra);
    Nopont noListaVertice = getPrimeiroNoLista(getVerticesGrafo(g));
    while (noListaVertice != NULL) {
        Vertice v = (Vertice) getItemNoLista(noListaVertice);
        double x1 = getXVertice(v);
        double y1 = getYVertice(v);

        Nopont noListaAresta = getPrimeiroNoLista(getArestasVertice(v));
        while (noListaAresta != NULL) {
            Aresta a = (Aresta) getItemNoLista(noListaAresta);
            Nopont noListaModificada = getPrimeiroNoLista(arestasArvore);
            while (noListaModificada != NULL) {
                if (getItemNoLista(noListaModificada) == a) {
                    Vertice destino = buscaVertice(g, getIDVerticeDestinoAresta(a));
                    if (destino != NULL) {
                        desenharArestaArvoreGeradoraMinimaSVG(svg, x1, y1, getXVertice(destino), getYVertice(destino));
                    }
                    break;
                }
                noListaModificada = getProximoNoLista(noListaModificada);
            }
            noListaAresta = getProximoNoLista(noListaAresta);
        }
        noListaVertice = getProximoNoLista(noListaVertice);
    }
    liberarResultadoArvoreGeradoraMinima(ra);
}

static void comandoPInterrogacao(Arquivo svg, Arquivo txt, Grafo g, char* reg1, char* reg2, char* cc, char* cr, double xOrigem, double yOrigem, double xDestino, double yDestino, int idPercurso){
    Vertice vOrigem = NULL;
    Vertice vDestino = NULL;
    double distanciaOrigem = DBL_MAX;
    double distanciaDestino = DBL_MAX;

    Nopont noListaVertice = getPrimeiroNoLista(getVerticesGrafo(g));
    while (noListaVertice != NULL) {
        Vertice v = (Vertice) getItemNoLista(noListaVertice);
        double dx;
        double dy;
        double distancia;

        dx = getXVertice(v) - xOrigem;
        dy = getYVertice(v) - yOrigem;
        distancia = dx*dx + dy*dy;

        if (distancia < distanciaOrigem) {
            distanciaOrigem = distancia;
            vOrigem = v;
        }

        dx = getXVertice(v) - xDestino;
        dy = getYVertice(v) - yDestino;
        distancia = dx*dx + dy*dy;

        if (distancia < distanciaDestino) {
            distanciaDestino = distancia;
            vDestino = v;
        }

        noListaVertice = getProximoNoLista(noListaVertice);
    }

    if (vOrigem == NULL || vDestino == NULL) {
        fprintf(txt, "p? %s %s -> grafo vazio\n", reg1, reg2);
        return;
    }

    ResultadoDijkstra rdCurto = executarDijkstra(g, getIDVertice(vOrigem), getIDVertice(vDestino), pesoCurtoDijkstra);

    if (!encontrouCaminhoDijkstra(rdCurto)) {
        fprintf(txt, "p? %s %s cc -> destino inacessivel\n", reg1, reg2);
    }else {
        fprintf(txt, "p? %s %s cc -> custo %.2lf m\n", reg1, reg2, getCustoDijkstra(rdCurto));

        desenharPercursoSVG(svg, g, getXVertice(vOrigem), getYVertice(vOrigem), getCaminhoDijkstra(rdCurto), cc, idPercurso++);
        desenharMarcadorSVG(svg, getXVertice(vOrigem), getYVertice(vOrigem), 'I', cc);
        desenharMarcadorSVG(svg, getXVertice(vDestino), getYVertice(vDestino), 'F', cc);
    }

    liberarResultadoDijkstra(rdCurto);

    ResultadoDijkstra rdRapido = executarDijkstra(g, getIDVertice(vOrigem), getIDVertice(vDestino), pesoRapidoDijkstra);

    if (!encontrouCaminhoDijkstra(rdRapido)) {
        fprintf(txt, "p? %s %s cr -> destino inacessivel\n", reg1, reg2);
    }else {
        fprintf(txt, "p? %s %s cr -> custo %.2lf m\n", reg1, reg2, getCustoDijkstra(rdRapido));

        desenharPercursoSVG(svg, g, getXVertice(vOrigem), getYVertice(vOrigem), getCaminhoDijkstra(rdRapido), cr, idPercurso++);
        desenharMarcadorSVG(svg, getXVertice(vOrigem), getYVertice(vOrigem), 'I', cr);
        desenharMarcadorSVG(svg, getXVertice(vDestino), getYVertice(vDestino), 'F', cr);
    }

    liberarResultadoDijkstra(rdRapido);
}

static Arquivo abrirQry(Nome arquivo) {
    Arquivo qry = fopen(arquivo,"r");
    if (qry == NULL) {
        printf("Erro ao abrir o arquivo qry!\n");

        perror("Motivo do erro");
        exit(1);
    }
    return qry;
}

void lerComandosExecutar(Arquivo svg, Arquivo txt, Nome caminho, Grafo g, Lista quadras) {
    Arquivo arquivoQry = abrirQry(caminho);
    Registradores estoque = criarRegistradores();


    char buffer[TAMANHO_MAX_BUFFER];
    int idPercurso = 0;

    while(fgets(buffer,sizeof(buffer),arquivoQry) != NULL) {

        buffer[strcspn(buffer,"\n")] = 0;

        if (buffer[0] == '\n' || buffer[0] == '\0') {
            continue;
        }

        fprintf(txt,"\n[*] %s\n", buffer);

        char* comando = strtok(buffer," ");
        if (comando == NULL) {
            continue;
        }

        if (strcmp(comando, "@o?") == 0) {
            char* reg = strtok(NULL," ");
            char* cep = strtok(NULL," ");
            char face = strtok(NULL," ")[0];
            double num = atof(strtok(NULL," "));


            comandoArrobaOInterrogacao(svg, txt, reg, cep, face, num, estoque, quadras);

        }else if (strcmp(comando, "mvm") == 0) {
            double v = atof(strtok(NULL," "));
            double rx = atof(strtok(NULL," "));
            double ry = atof(strtok(NULL," "));
            double rw = atof(strtok(NULL," "));
            double rh = atof(strtok(NULL," "));


            comandoMvm(g, v, rx, ry, rw, rh);

        }else if (strcmp(comando, "regs") == 0) {
            double vl = atof(strtok(NULL," "));

            comandoRegs(svg, txt, g, vl);

        }else if (strcmp(comando, "exp") == 0) {
            double vl = atof(strtok(NULL," "));


            comandoExp(svg, g, vl);

        }else if (strcmp(comando, "p?") == 0) {
            char* reg1 = strtok(NULL," ");
            char* reg2 = strtok(NULL," ");
            char* cc = strtok(NULL," ");
            char* cr = strtok(NULL," ");

            if (!registradorOcupado(estoque, reg1) || !registradorOcupado(estoque, reg2)) {
                fprintf(txt, "p? %s %s -> registrador nao ocupado\n", reg1, reg2);
                continue;
            }

            double xOrigem = getXRegistrador(estoque, reg1);
            double yOrigem = getYRegistrador(estoque, reg1);
            double xDestino = getXRegistrador(estoque, reg2);
            double yDestino = getYRegistrador(estoque, reg2);

            comandoPInterrogacao(svg, txt, g, reg1, reg2, cc, cr, xOrigem, yOrigem, xDestino, yDestino, idPercurso);

        }else{
            printf("Comando desconhecido: '%s' \n", comando);
        }
    }
    fclose(arquivoQry);
    liberarRegistradores(estoque);
}