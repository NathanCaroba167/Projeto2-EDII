//
// Created by natha on 04/10/2025.
//

#ifndef SVG_H
#define SVG_H

#include "aresta.h"
#include "quadra.h"
#include "grafo.h"
#include "lista.h"

/*
 Módulo encarregado de gerar um arquivo SVG a partir das quadras e ações do qry e executar os comandos com as operações de abrir,
 inicializar, desenhar, gerar e fechar
 */

/*
 Ponteiro do tipo FILE Arquivo
 Ponteiro char Nome
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @brief Cria e abre o arquivo SVG para escrita (sobrescrevendo o conteúdo existentes).
/// @param arquivo Ponteiro para o nome do arquivo que será criado e aberto.
/// @return Ponteiro para o arquivo (FILE*).
/// @warning
Arquivo abrirSVG(Nome arquivo);

/// @brief Adiciona a tag iniciais do arquivo SVG.
/// @param svg Ponteiro para o arquivo que será inicializado.
/// @warning
void inicializarSVG(Arquivo svg);

/// @brief Desenha uma quadra no arquivo SVG.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param q Quadra que será desenhado.
/// @warning
void desenharQuadraSVG(Arquivo svg, Quadra q);

/// @brief Desenha um segmento de rua (aresta) no arquivo SVG.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param a Aresta que será desenhada.
/// @warning
void desenharArestaSVG(Arquivo svg, Aresta a);

/// @brief Desenha o bounding box de um componente conexo sendo um retângulo de 50% de transparência.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param xBox Coordenada x do canto superior-esquerdo do bounding box.
/// @param yBox Coordenada y do canto superior-esquerdo do bounding box.
/// @param wBox Largura do bounding box.
/// @param hBox Altura do bounding box.
/// @param corBox Cor de preenchimento do bounding box (50% de transparência).
/// @warning
void desenharBoundingBoxComponenteSVG(Arquivo svg, double xBox, double yBox, double wBox, double hBox, char* corBox);

/// @brief Desenha um segmento de rua (aresta) que foi selecionada pela árvore geradora minima, no arquivo SVG.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param a Aresta que será desenhada.
/// @warning
void desenharArestaArvoreGeradoraMinimaSVG(Arquivo svg, Aresta a);

/// @brief Desenha um percurso animado (animateMotion) ao longo da lista de arestas com a cor indicada.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param g Grafo usado para buscar as coordenadas dos vértices de destino de cada aresta.
/// @param xOrigem Coordenada x do vértice de origem do percurso.
/// @param yOrigem Coordenada y do vértice de origem do percurso.
/// @param caminho Lista de arestas que formam o percurso, em ordem da origem ao destino.
/// @param corPercurso Cor do percurdo e do marcador animado
/// @param idPercurso Identificador único usado como id SVG do path(evita colisão entre dois percursos).
/// @warning
void desenharPercursoSVG(Arquivo svg, Grafo g, double xOrigem, double yOrigem, Lista caminho, char* corPercurso, int idPercurso);

/// @brief Desenha uma placa (retângulo + letra) marcando o início ou fim do percurso
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param x Coordenada x do ponto indicado.
/// @param y Coordenada y do ponto indicado.
/// @param letra Letra da placa: I (início) ou F (fim).
/// @param cor Cor de fundo da placa(retângulo).
/// @warning
void desenharMarcadorSVG(Arquivo svg, double x, double y, char letra, char* cor);

/// @brief Fecha o arquivo SVG, adicionando as tags de fechamento.
/// @param svg Ponteiro para o arquivo que será fechado.
/// @warning
void fecharSVG(Arquivo svg);

#endif //SVG_H