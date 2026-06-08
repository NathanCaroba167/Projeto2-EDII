//
// Created by natha on 25/05/2026.
//

#ifndef VERTICE_H
#define VERTICE_H

/*
 Módulo encarregado de coordenar um vértice com operações de criar, get, set e eliminar
 */

/*
 Ponteiro void Aresta
 */

typedef void* Vertice;

/// @brief Cria um vértice com os atributos indicados.
/// @param id Identificador universal do vértice
/// @param x Coordenada x do vértice
/// @param y Coordenada y do vértice
/// @return Ponteiro para o vértice criado
/// @warning
Vertice criarVertice(char* id, double x, double y);

/// @brief Pega o ID do vértice
/// @param v Ponteiro para o vértice analisado
/// @return String do ID do vértice
/// @warning
char* getVerticeId(Vertice v);

/// @brief Pega a coordenada x do vértice
/// @param v Ponteiro para o vértice analisado
/// @return A coordenada x do vértice
/// @warning
double getXVertice(Vertice v);

/// @brief Pega a coordenada y do vértice
/// @param v Ponteiro para o vértice analisado
/// @return A coordenada y do vértice
/// @warning
double getYVertice(Vertice v);

/// @brief Define a nova coordenada x do vértice
/// @param v Ponteiro para o vértice onde a nova coordenada x será definida
/// @param x Coordenada x que será definida
/// @warning
void setXVertice(Vertice v, double x);

/// @brief Define a nova coordenada y do vértice
/// @param v Ponteiro para o vértice onde a nova coordenada y será definida
/// @param y Coordenada y que será definida
/// @warning
void setYVertice(Vertice v, double y);

#endif //VERTICE_H
