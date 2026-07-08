//
// Created by natha on 04/07/2026.
//

#ifndef REGISTRADOR_H
#define REGISTRADOR_H

/*
 Módulo encarregado de coordenar um estoque de registradores (R0 a R10) com operações de criar, get, set, registradorOcupado e liberar
 */

/*
 Ponteiro void Registradores
 */
typedef void* Registradores;

/// @brief Cria um estoque de registradores com 11 posições(R0 a R10) vazias.
/// @return Ponteiro para o estoque de registradores.
/// @warning
Registradores criarRegistradores();

/// @brief Define a posição (x,y) no registrador indicado.
/// @param estoque Ponteiro para o estoque de registradores.
/// @param IDRegistrador Identificador do registrador (String "R0" a "R10").
/// @param x Coordenada x da posição a ser definida no registrador.
/// @param y Coordenada y da posição a ser definida no registrador.
/// @warning
void setRegistrador(Registradores estoque, char* IDRegistrador, double x, double y);

/// @brief Pega a coordenada x da posição gravada no registrador indicado.
/// @param estoque Ponteiro para o estoque de registradores
/// @param IDRegistrador Identificador do registrador (String "R0" a "R10").
/// @return Coordenada x da posição gravada no registrador indicado
/// @warning
double getXRegistrador(Registradores estoque, char* IDRegistrador);

/// @brief Pega a coordenada y da posição gravada no registrador indicado.
/// @param estoque Ponteiro para o estoque de registradores
/// @param IDRegistrador Identificador do registrador (String "R0" a "R10").
/// @return Coordenada y da posição gravada no registrador indicado
/// @warning
double getYRegistrador(Registradores estoque, char* IDRegistrador);

/// @brief Verifica se o registrador indicado está ocupado.
/// @param estoque Ponteiro para o estoque de registradores
/// @param IDRegistrador Identificador do registrador (String "R0" a "R10").
/// @return True se o registrador está ocupado, False se ainda está vazio.
/// @warning
bool registradorOcupado(Registradores estoque, char* IDRegistrador);

/// @brief Libera a memória do estoque de registradores.
/// @param estoque Ponteiro para o estoque de registradores que será liberado.
/// @warning
void liberarRegistradores(Registradores estoque);

#endif //REGISTRADOR_H
