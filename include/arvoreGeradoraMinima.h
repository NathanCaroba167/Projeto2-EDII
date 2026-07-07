//
// Created by natha on 15/06/2026.
//

#ifndef ARVOREGERADORAMINIMA_H
#define ARVOREGERADORAMINIMA_H

#include "grafo.h"
#include "lista.h"

/*
 Módulo encarregado de executar e coordenar um algoritmo da Árvore Geradora Mínima com operações de executar, getNumArestas, getArestas e liberar
 */

/*
 Ponteiro void ResultadoArvoreGeradoraMinima
 */
typedef void* ResultadoArvoreGeradoraMinima;

/// @brief Seleciona arestas da árvore geradora mínima com vm < vl, aumenta 50% e retorna o resultado
/// @param g Ponteiro para o grafo onde o algoritmo será executado.
/// @param vl Velocidade limite, arestas com vm < vl são modificadas e retornadas
/// @return Ponteiro para o resultado da execução
/// @warning
ResultadoArvoreGeradoraMinima executarArvoreGeradoraMinima(Grafo g, double vl);

/// @brief Pega a Lista de Arestas da árvore geradora mínima que tinham vm < vl e tiveram vm aumentado em 50%
/// @param resultado Ponteiro para o resultado após a execução da árvore geradora mínima.
/// @return Lista de Arestas modificadas
/// @warning
Lista getArestasArvoreGeradoraMinima(ResultadoArvoreGeradoraMinima resultado);

/// @brief Pega a quantidade de arestas da árvore que tinham vm < vl e foram modificadas após a execução.
/// @param resultado Ponteiro para o resultado após a execução da árvore geradora mínima.
/// @return Número de arestas modificadas
/// @warning
int getNumArestasArvoreGeradoraMinima(ResultadoArvoreGeradoraMinima resultado);

/// @brief Libera a memória do resultado da árvore geradora mínima e da Lista de Arestas.
/// @param resultado Ponteiro para o resultado da árvore geradora mínima que será liberada.
/// @warning
void liberarResultadoArvoreGeradoraMinima(ResultadoArvoreGeradoraMinima resultado);

#endif //ARVOREGERADORAMINIMA_H
