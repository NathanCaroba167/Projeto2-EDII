//
// Created by natha on 15/06/2026.
//

#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H
#include <stdbool.h>

/*
 Módulo encarregado de coordenar uma fila de prioridade com operações de criar, inserir, extrai, consultar, filaprioridadeVazia, tamanhofila e liberar
 */

/*
 Ponteiro void FilaPrioridade
 */

typedef void* FilaPrioridade;

/*
 Ponteiro void ItemFilaPrioridade
 */

typedef void* ItemFilaPrioridade;

/// @brief Cria uma fila de prioridade mínima vazia.
/// @return Ponteiro para nova fila de prioridade mínima criada.
/// @warning
FilaPrioridade criarFilaPrioridade();

/// @brief Insere um item na fila de prioridade com o prioridade indicada
/// @param f Ponteiro para a fila de prioridade mínima onde o item será inserido
/// @param i Ponteiro para o item que será inserido.
/// @param prioridade Prioridade do item (menor valor = maior prioridade)
/// @warning
void inserirFilaPrioridade(FilaPrioridade f, ItemFilaPrioridade i, double prioridade);

/// @brief Remove o item com menor prioridade da fila e retorna-o
/// @param f Ponteiro para a fila de prioridade mínima analisada.
/// @return Ponteiro para o item com menor prioridade da fila.
/// @warning
ItemFilaPrioridade extrairFilaPrioridadeMinima(FilaPrioridade f);

/// @brief Consultar qual a menor prioridade da fila sem remover o item
/// @param f Ponteiro para a fila de prioridade analisada.
/// @return A menor prioridade da fila.
/// @warning
double consultarPrioridadeMinima(FilaPrioridade f);

/// @brief Verifica se a fila de prioridade está vazia.
/// @param f Ponteiro para a fila de prioridade que será verificada.
/// @return True (1) se a fila de prioridade estiver vazia, ou False (0) se a fila de prioridade não estiver vazia.
/// @warning
bool filaPrioridadeVazia(FilaPrioridade f);

/// @brief Pega a quantidade de itens da fila de prioridade.
/// @param f Ponteiro para a fila de prioridade analisada.
/// @return O tamanho da fila de prioridade(a quantidade de itens na fila).
/// @warning
int tamanhoFilaPrioridade(FilaPrioridade f);

/// @brief Libera a memória da fila de prioridade e de todos os seus elementos (nós).
/// @param f Ponteiro para a fila de prioridade que será liberada.
/// @warning
void liberarFilaPrioridade(FilaPrioridade f);

#endif //FILAPRIORIDADE_H
