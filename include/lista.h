//
// Created by natha on 13/11/2025.
//

#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

/*
 Módulo encarregado de executar e coordenar uma lista com operações de iniciar, inserir, remover, 'listavazia' e liberar
 */

/*
 Ponteiro void Lista
 */
typedef void* Lista;

/*
 Ponteiro void Item
 */
typedef void* Item;
typedef struct Elemento* Nopont;

/// @brief Inicializa uma lista vazia.
/// @return Ponteiro para nova lista iniciada.
/// @warning
Lista iniciarLista();

/// @brief Lista um Item no início da lista.
/// @param l Ponteiro para lista a qual o Item será listado.
/// @param i Ponteiro para o Item que será listado.
/// @warning
void inserirListaInicio(Lista l, Item i);

/// @brief Lista um Item no fim da lista.
/// @param l Ponteiro para lista a qual o Item será listado.
/// @param i Ponteiro para o Item que será listado.
/// @warning
void inserirListaFim(Lista l, Item i);

/// @brief Remove o Item da lista e libera o nó da lista.
/// @param l Ponteiro para lista que o item será removido.
/// @param i Ponteiro para o Item que será removido.
/// @return True se o item foi removido, False caso contrário
/// @warning
bool removerItemLista(Lista l, Item i);

/// @brief Pega o próximo nó (elemento) da lista a partir do nó (elemento) anterior.
/// @param p Ponteiro para o nó (elemento) anterior.
/// @return Ponteiro para o próximo nó (elemento).
/// @warning
Nopont getProximoNoLista(Nopont p);

/// @brief Pega o primeiro nó (elemento) da lista.
/// @param l Ponteiro para a lista analisada.
/// @return Ponteiro para o primeiro nó (elemento) da lista.
/// @warning
Nopont getPrimeiroNoLista(Lista l);

/// @brief Pega o item de um nó (elemento) da lista.
/// @param p Ponteiro para o nó (elemento) analisado.
/// @return Ponteiro para o item do nó (elemento).
/// @warning
Item getItemNoLista(Nopont p);

/// @brief Pega a quantidade de itens da lista.
/// @param l Ponteiro para a lista analisada.
/// @return O tamanho da lista.
/// @warning
int getTamanhoLista(Lista l);

/// @brief Verifica se a lista está vazia.
/// @param l Ponteiro para lista que será verificada.
/// @return True (1) se a lista estiver vazia, ou False (0) se a lista não estiver vazia.
/// @warning
bool listaVazia(Lista l);

/// @brief Libera a memória da lista e de todos os seus elementos (nós).
/// @param l Ponteiro para lista que será liberada.
/// @warning
void liberarLista(Lista l);

#endif //LISTA_H