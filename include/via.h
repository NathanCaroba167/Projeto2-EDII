//
// Created by natha on 06/06/2026.
//

#ifndef VIA_H
#define VIA_H

#include <stdio.h>
#include "grafo.h"

/*
 Módulo encarregado de ler um arquivo (.via) e inicializar as vias com a operação de lerVia
 */

/*
 Ponteiro do tipo FILE Arquivo
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @brief Cria vias lidos do (.via) e coloca na cidade (grafo).
/// @param caminho String com o nome do arquivo (.via) que será lido.
/// @return Grafo com vias preenchidas.
/// @warning
Grafo lerVia(Nome caminho) ;

#endif //VIA_H
