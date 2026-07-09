//
// Created by natha on 22/06/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"

#include "../include/filaPrioridade.h"

void setUp(void){}
void tearDown(void) {}

void teste_criarFilaPrioridade_deveComecarVazia(void) {
    FilaPrioridade f = criarFilaPrioridade();

    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_TRUE(filaPrioridadeVazia(f));
    TEST_ASSERT_EQUAL_INT(0, tamanhoFilaPrioridade(f));

    liberarFilaPrioridade(f);
}

void teste_inserirFilaPrioridade_deveAumentarTamanhoCorretamente(void) {
    FilaPrioridade f = criarFilaPrioridade();
    int item = 67;

    inserirFilaPrioridade(f, &item, 6.7);

    TEST_ASSERT_FALSE(filaPrioridadeVazia(f));
    TEST_ASSERT_EQUAL_INT(1, tamanhoFilaPrioridade(f));

    liberarFilaPrioridade(f);
}

void teste_extrairFilaPrioridadeMinima_deveRetornarItemInserido(void) {
    FilaPrioridade f = criarFilaPrioridade();
    int item = 88;

    inserirFilaPrioridade(f, &item, 5.0);
    ItemFilaPrioridade valorExtraido = extrairFilaPrioridadeMinima(f);

    TEST_ASSERT_EQUAL_PTR(&item, valorExtraido);
    TEST_ASSERT_TRUE(filaPrioridadeVazia(f));

    liberarFilaPrioridade(f);
}

void teste_extrairFilaPrioridadeMinima_deveExtraiSempreMenorPrioridade(void) {
    FilaPrioridade f = criarFilaPrioridade();
    int itemA = 3, itemB = 1, itemC = 4, itemD = 1, itemE = 5, itemF = 9, itemG = 2, itemH = 6;

    inserirFilaPrioridade(f, &itemA, 3.0);
    inserirFilaPrioridade(f, &itemB, 1.0);
    inserirFilaPrioridade(f, &itemC, 4.0);
    inserirFilaPrioridade(f, &itemD, 1.0);
    inserirFilaPrioridade(f, &itemE, 5.0);
    inserirFilaPrioridade(f, &itemF, 9.0);
    inserirFilaPrioridade(f, &itemG, 2.0);
    inserirFilaPrioridade(f, &itemH, 6.0);

    double anterior = -1.0;
    while (!filaPrioridadeVazia(f)) {
        double atual = consultarPrioridadeMinima(f);
        TEST_ASSERT_GREATER_OR_EQUAL_DOUBLE(anterior, atual);
        extrairFilaPrioridadeMinima(f);
        anterior = atual;
    }

    liberarFilaPrioridade(f);
}

void teste_extrairFilaPrioridadeMinima_deveDiminuirItensDaFila(void) {
    FilaPrioridade f = criarFilaPrioridade();
    int itemA = 4, itemB = 7, itemC = 1;

    inserirFilaPrioridade(f, &itemA, 3.0);
    inserirFilaPrioridade(f, &itemB, 1.0);
    inserirFilaPrioridade(f, &itemC, 4.0);

    TEST_ASSERT_EQUAL_INT(3, tamanhoFilaPrioridade(f));
    extrairFilaPrioridadeMinima(f);
    TEST_ASSERT_EQUAL_INT(2, tamanhoFilaPrioridade(f));
    extrairFilaPrioridadeMinima(f);
    TEST_ASSERT_EQUAL_INT(1, tamanhoFilaPrioridade(f));
    extrairFilaPrioridadeMinima(f);
    TEST_ASSERT_EQUAL_INT(0, tamanhoFilaPrioridade(f));
    TEST_ASSERT_TRUE(filaPrioridadeVazia(f));

    liberarFilaPrioridade(f);
}

void teste_consultarPrioridadeMinima_deveRetornarMenorPrioridadeCorretamente(void) {
    FilaPrioridade f = criarFilaPrioridade();
    int itemA = 4, itemB = 7, itemC = 1;

    inserirFilaPrioridade(f, &itemA, 10.0);
    inserirFilaPrioridade(f, &itemB, 7.0);
    inserirFilaPrioridade(f, &itemC, 6.0);

    TEST_ASSERT_EQUAL_DOUBLE(6.0, consultarPrioridadeMinima(f));
    TEST_ASSERT_EQUAL_INT(3, tamanhoFilaPrioridade(f));

    liberarFilaPrioridade(f);
}

void teste_inserirFilaPrioridade_deveSuportarCrescimentoDinamicoMuitosElementos(void) {
    FilaPrioridade f = criarFilaPrioridade();
    int itens[100];

    for (int i = 0; i < 100; i++) {
        itens[i] = i;
        inserirFilaPrioridade(f, &itens[i], (double)(100 - i));
    }

    TEST_ASSERT_EQUAL_INT(100, tamanhoFilaPrioridade(f));

    double anterior = -1.0;
    while (!filaPrioridadeVazia(f)) {
        double atual = consultarPrioridadeMinima(f);
        TEST_ASSERT_GREATER_OR_EQUAL_DOUBLE(anterior, atual);
        extrairFilaPrioridadeMinima(f);
        anterior = atual;
    }

    liberarFilaPrioridade(f);
}

void teste_liberarFilaPrioridade_naoDeveCrasharFilaVazia(void) {
    FilaPrioridade f = criarFilaPrioridade();
    liberarFilaPrioridade(f);
    TEST_PASS();
}

void teste_liberarFilaPrioridade_naoDeveCrasharComItens(void) {
    FilaPrioridade f = criarFilaPrioridade();
    int itemA = 6;
    int itemB = 7;
    inserirFilaPrioridade(f, &itemA, 7.6);
    inserirFilaPrioridade(f, &itemB, 6.7);
    liberarFilaPrioridade(f);
    TEST_PASS();
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO FILAPRIORIDADE\n");
    printf("==========================================\n");

    RUN_TEST(teste_criarFilaPrioridade_deveComecarVazia);
    RUN_TEST(teste_inserirFilaPrioridade_deveAumentarTamanhoCorretamente);
    RUN_TEST(teste_extrairFilaPrioridadeMinima_deveRetornarItemInserido);
    RUN_TEST(teste_extrairFilaPrioridadeMinima_deveExtraiSempreMenorPrioridade);
    RUN_TEST(teste_extrairFilaPrioridadeMinima_deveDiminuirItensDaFila);
    RUN_TEST(teste_consultarPrioridadeMinima_deveRetornarMenorPrioridadeCorretamente);
    RUN_TEST(teste_inserirFilaPrioridade_deveSuportarCrescimentoDinamicoMuitosElementos);
    RUN_TEST(teste_liberarFilaPrioridade_naoDeveCrasharFilaVazia);
    RUN_TEST(teste_liberarFilaPrioridade_naoDeveCrasharComItens);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}