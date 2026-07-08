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
/// @param v1 Primero vértice da aresta
/// @param v2 Segundo vértice da aresta
/// @param ldir CEP da quadra que está no lado direito da aresta
/// @param lesq CEP da quadra que está no lado esquerdo da aresta
/// @param cmp Comprimento da aresta
/// @param vm Velocidade média da aresta
/// @param nome Nome da aresta
/// @return Ponteiro para a aresta criada
/// @warning
Aresta criarAresta(Vertice v1, Vertice v2, char* ldir, char* lesq, double cmp, double vm, char* nome);

/// @brief Pega o primeiro vértice da aresta
/// @param a Ponteiro para a aresta analisada.
/// @return Ponteiro para o primeiro vértice da aresta
/// @warning
Vertice getVerticeV1Aresta(Aresta a);

/// @brief Pega o segundo vértice da aresta
/// @param a Ponteiro para a aresta analisada
/// @return Ponteiro para o segundo vértice da aresta
/// @warning
Vertice getVerticeV2Aresta(Aresta a);

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

/// @brief Define o novo primeiro vértice da aresta
/// @param a Ponteiro para a aresta onde o primeiro vértice será definido.
/// @param v Primeiro vértice da aresta que será definido
/// @warning
void setVerticeV1Aresta(Aresta a, Vertice v);

/// @brief Define o novo segundo vértice da aresta
/// @param a Ponteiro para a aresta onde o segundo vértice será definido.
/// @param v Segundo vértice da aresta que será definido
/// @warning
void setVerticeV2Aresta(Aresta a, Vertice v);

/// @brief Define o novo CEP da quadra direita da aresta
/// @param a Ponteiro para a aresta onde o CEP da quadra direita será definido.
/// @param ldir CEP da quadra direita que será definida
/// @warning
void setQuadraLadoDireitoAresta(Aresta a, char* ldir);

/// @brief Define o novo CEP da quadra esquerda da aresta
/// @param a Ponteiro para a aresta onde o CEP da quadra esquerda será definido.
/// @param lesq CEP da quadra esquerda que será definida
/// @warning
void setQuadraLadoEsquerdoAresta(Aresta a, char* lesq);

/// @brief Define o novo comprimento da aresta
/// @param a Ponteiro para a aresta onde o comprimento será definido.
/// @param cmp Comprimento que será definido
/// @warning
void setComprimentoAresta(Aresta a, double cmp);

/// @brief Define a nova velocidade média da aresta
/// @param a Ponteiro para a aresta onde a velocidade será definida.
/// @param vm Velocidade média que será definida
/// @warning
void setVelocidadeAresta(Aresta a, double vm);

/// @brief Define o novo nome da aresta
/// @param a Ponteiro para a aresta onde o nome será definido.
/// @param nome Nome que será definido
/// @warning
void setNomeAresta(Aresta a, char* nome);

/// @brief Libera a memória alocada para a aresta, !!!incluindo as strings.
/// @param a Ponteiro para a aresta que será liberada.
/// @warning
void liberarAresta(Aresta a);

#endif //ARESTA_H
