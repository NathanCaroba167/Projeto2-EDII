//
// Created by natha on 15/06/2026.
//

#ifndef COMPONENTES_H
#define COMPONENTES_H

#include "grafo.h"
#include "lista.h"

/*
 Módulo encarregado de executar e coordenar um algoritmo de Componentes com operações de executar, getNumComponentes, getVertices e liberar
 */

/*
 Ponteiro void ResultadoComponentes
 */
typedef void* ResultadoComponentes;

/// @brief Calcula os componentes conexos do grafo, usando arestas com vm >= vl
/// @param g Ponteiro para o grafo onde o algoritmo será executado.
/// @param vl Velocidade limite, arestas com vm < vl são desconsideradas
/// @return Ponteiro para o resultado da execução
/// @warning
ResultadoComponentes executarComponentes(Grafo g, double vl);

/// @brief Pega a quantidade de componentes conexos encontrados após a execução.
/// @param resultado Ponteiro para o resultado das componentes.
/// @return Quantidade de componentes conexos.
/// @warning
int getNumComponentes(ResultadoComponentes resultado);

/// @brief Pega a Lista de Vertices que formam o componente conexo indicado
/// @param resultado Ponteiro para o resultado das componentes.
/// @param i Índice do componente analisado (de 0 a (numComponentes - 1))
/// @return Lista de Vertices do componente
/// @warning
Lista getVerticesComponentes(ResultadoComponentes resultado, int i);

/// @brief Libera a memória do resultado das componentes e da Lista de Vertices de cada componente
/// @param resultado Ponteiro para o resultado das componentes que será liberado.
/// @warning
void liberarResultadoComponentes(ResultadoComponentes resultado);

#endif //COMPONENTES_H
