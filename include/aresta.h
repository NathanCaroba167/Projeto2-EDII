//
// Created by natha on 25/05/2026.
//

#ifndef ARESTA_H
#define ARESTA_H

#include "../include/vertice.h"

/*
 Módulo encarregado de coordenar uma aresta com operações de criar, get, set e eliminar
 */

/*
 Ponteiro void Aresta
 */

typedef void* Aresta;

/// @brief Cria uma aresta com os atributos indicados.
/// @param IDDestino Identificador do vértice de destino da aresta.
/// @param ldir CEP da quadra que está no lado direito da aresta
/// @param lesq CEP da quadra que está no lado esquerdo da aresta
/// @param cmp Comprimento da aresta
/// @param vm Velocidade média da aresta
/// @param nome Nome da aresta
/// @return Ponteiro para a aresta criada
/// @warning
Aresta criarAresta(char* IDDestino, char* ldir, char* lesq, double cmp, double vm, char* nome);

/// @brief Pega o ID do vértice de destino da aresta.
/// @param a Ponteiro para a aresta analisada.
/// @return String com o identificador do vértice de destino.
/// @warning
char* getIDVerticeDestinoAresta(Aresta a);

/// @brief Pega o CEP da quadra que está no lado direito da aresta
/// @param a Ponteiro para a aresta analisada
/// @return CEP da quadra que está no lado direito da aresta
/// @warning
char* getQuadraLadoDireitoAresta(Aresta a);

/// @brief Pega o CEP da quadra que está no lado esquerdo da aresta
/// @param a Ponteiro para a aresta analisada
/// @return CEP da quadra que está no lado esquerdo da aresta
/// @warning
char* getQuadraLadoEsquerdoAresta(Aresta a);

/// @brief Pega o comprimento da aresta
/// @param a Ponteiro para a aresta analisada
/// @return Comprimento da aresta
/// @warning
double getComprimentoAresta(Aresta a);

/// @brief Pega a velocidade média da aresta
/// @param a Ponteiro para a aresta analisada
/// @return Velocidade média da aresta
/// @warning
double getVelocidadeAresta(Aresta a);

/// @brief Pega o nome da aresta
/// @param a Ponteiro para a aresta analisada
/// @return Nome da aresta
/// @warning
char* getNomeAresta(Aresta a);

/// @brief Define a nova velocidade média da aresta
/// @param a Ponteiro para a aresta onde a velocidade será definida.
/// @param vm Velocidade média que será definida
/// @warning
void setVelocidadeAresta(Aresta a, double vm);

/// @brief Libera a memória alocada para a aresta, incluindo as strings internas.
/// @param a Ponteiro para a aresta que será liberada.
/// @warning
void liberarAresta(Aresta a);

#endif //ARESTA_H
