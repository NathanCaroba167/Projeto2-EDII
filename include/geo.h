//
// Created by natha on 08/07/2026.
//

#ifndef GEO_H
#define GEO_H
#include <stdio.h>
#include "lista.h"

/*
 Módulo encarregado de ler um arquivo (.geo) e inicializar as quadras com a operação de lerGeo
 */

/*
 Ponteiro do tipo FILE Arquivo
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @brief Cria quadras lidas do (.geo).
/// @param caminho String com o nome do arquivo (.geo) que será lido.
/// @return Lista com as quadras lidas.
/// @warning
Lista lerGeo(Nome caminho) ;

#endif //GEO_H
