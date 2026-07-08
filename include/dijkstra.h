//
// Created by natha on 15/06/2026.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "grafo.h"

/*
 Módulo encarregado de executar e coordenar um algoritmo de Dijkstra com operações de executar, encontrou, getCaminho e liberar
 */

/*
 Ponteiro void ResultadoDijkstra
 */
typedef void* ResultadoDijkstra;

/// @brief Função de peso que retorna o comprimento da aresta.
/// @param a Ponteiro para a aresta analisada.
/// @return Comprimento da aresta
/// @warning
double pesoCurtoDijkstra(Aresta a);

/// @brief Função de peso que retorna o tempo de travessia da aresta.
/// @param a Ponteiro para a aresta analisada.
/// @return Tempo de travessia (cmp / vm)
/// @warning
double pesoRapidoDijkstra(Aresta a);

/// @brief Executa o algoritmo de Dijkstra no grafo a partir da origem até o destino.
/// @param g Ponteiro para o grafo onde o algoritmo será executado.
/// @param IDOrigem Identificador do vértice de origem.
/// @param IDDestino Identificador do vértice de destino.
/// @param funcaoPesoCusto Função de peso que determina o custo de cada aresta
/// @return Ponteiro para o resultado da execução(lista de aresta do caminho formado)
/// @warning
ResultadoDijkstra executarDijkstra(Grafo g, char* IDOrigem, char* IDDestino, double (*funcaoPesoCusto)(Aresta a));

/// @brief Verifica se o Dijkstra encontrou um caminho até o destino
/// @param resultado Ponteiro para o resultado da execução do algoritmo Dijkstra
/// @return True (1) se encontrou o caminho e o destino foi alcançado, ou False (0) se não encontrou o caminho e o destino é inacessível a partir da origem.
/// @warning
bool encontrouCaminhoDijkstra(ResultadoDijkstra resultado);

/// @brief Pega o custo total do caminho encontrado pelo algoritmo Dijkstra.
/// @param resultado Ponteiro para o resultado da execução do algoritmo Dijkstra.
/// @return Custo total do caminho (soma dos pesos das arestas percorridas).
/// @warning
double getCustoDijkstra(ResultadoDijkstra resultado);

/// @brief Pega a Lista de Arestas que formam o caminho encontrado pelo algoritmo, em ordem da origem até o destino.
/// @param resultado Ponteiro para o resultado da execução do algoritmo Dijkstra
/// @return Lista de Arestas que formam o caminho
/// @warning
Lista getCaminhoDijkstra(ResultadoDijkstra resultado);

/// @brief Libera a memória do resultado do Dijkstra e da Lista de Arestas que formam o caminho encontrado.
/// @param resultado Ponteiro para o resultado da execução do algoritmo Dijkstra que será liberado.
/// @warning
void liberarResultadoDijkstra(ResultadoDijkstra resultado);

#endif //DIJKSTRA_H
