//
// Created by natha on 15/06/2026.
//

#ifndef GRAFO_H
#define GRAFO_H

#include "../include/vertice.h"
#include "../include/aresta.h"

/*
 Módulo encarregado de coordenar um grafo com operações de criar, inserir, buscar, get e liberar
 */

/*
 Ponteiro void Grafo
 */

typedef void* Grafo;

/// @brief Cria um grafo direcionado vazio.
/// @return Ponteiro para o grafo criado.
/// @warning
Grafo criarGrafo();

/// @brief Insere um vértice no grafo
/// @param g Ponteiro para o grafo onde o vértice será inserido
/// @param v Ponteiro para o vértice que será inserido
/// @warning
void inserirVerticeGrafo(Grafo g, Vertice v);

/// @brief Insere uma aresta no grafo
/// @param g Ponteiro para o grafo onde a aresta será inserida.
/// @param a Ponteiro para a aresta que será inserida.
/// @warning
void inserirArestaGrafo(Grafo g, Aresta a);

/// @brief Busca no grafo o vértice de id correspondente.
/// @param g Ponteiro para o grafo analisado.
/// @param id Identificador do vértice em busca
/// @return Ponteiro para o vértice encontrado, ou NULL caso não encontrar no grafo o vértice com id correspondente.
/// @warning
Vertice buscaVertice(Grafo g, char* id);

/// @brief Pega a lista de vértices do grafo.
/// @param g Ponteiro para o grafo analisado.
/// @return Lista de vértices do grafo.
/// @warning
Lista getVerticesGrafo(Grafo g);

/// @brief Pega a quantidade de vértices do grafo
/// @param g Ponteiro para o grafo analisado.
/// @return Quantidade de vértices do grafo.
/// @warning
int getNumVerticesGrafo(Grafo g);

/// @brief Pega a quantidade de arestas do grafo
/// @param g Ponteiro para o grafo analisado.
/// @return Quantidade de arestas do grafo.
/// @warning
int getNumArestasGrafo(Grafo g);

/// @brief Libera a memória alocada para o grafo, incluindo todos os vertices e arestas.
/// @param g Ponteiro para o grafo que será liberar.
/// @warning
void liberarGrafo(Grafo g);

#endif //GRAFO_H
