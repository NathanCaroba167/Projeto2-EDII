//
// Created by natha on 16/10/2025.
//

#ifndef TXT_H
#define TXT_H

/*
 Módulo encarregado de criar um arquivo (.txt) e reportar os resultados de comandos com as operações de abrir e escrever
 */

/*
 Ponteiro do tipo FILE Arquivo
 Ponteiro char Nome
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @brief Cria e abre o arquivo TXT para escrita.
/// @param arquivo Ponteiro para o nome do arquivo que será criado e aberto.
/// @return Ponteiro para o arquivo (FILE*) que será criado e aberto.
/// @warning
Arquivo abrirTXT(Nome arquivo);

#endif //TXT_H