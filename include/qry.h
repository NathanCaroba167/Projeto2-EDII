//
// Created by natha on 08/07/2026.
//

#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "grafo.h"

/*
 Módulo encarregado de ler um arquivo (.geo) e inicializar as quadras com a operação de lerGeo
 */

/*
 Ponteiro do tipo FILE Arquivo
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @brief Executa comandos lidos do (.qry), na cidade(grafo) e retorna resultados.
/// @param svg Ponteiro para o arquivo SVG (para visualização dinâmica).
/// @param txt Ponteiro para o arquivo TXT (para reportar resultados).
/// @param caminho String com o nome do arquivo (.qry) que será lido.
/// @param g Grafo com esquinas(vértices) e vias(arestas) da cidade.
/// @param quadras Lista de quadras da cidade.
/// @return Lista com as quadras lidas.
/// @warning
void lerComandosExecutar(Arquivo svg, Arquivo txt, Nome caminho, Grafo g, Lista quadras) ;

#endif //QRY_H
