//
// Created by natha on 21/06/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"

#include "../include/lista.h"

void setUp(void){}
void tearDown(void) {}

void teste_iniciarLista_deveRetornarListaVaziaComTamanhoZero(void) {
    Lista l = iniciarLista();
    TEST_ASSERT_NOT_NULL(l);
    TEST_ASSERT_TRUE(listaVazia(l));
    TEST_ASSERT_EQUAL_INT(0, getTamanhoLista(l));
    liberarLista(l);
}

void teste_inserirListaFim_deveAumentarTamanho(void) {
    Lista l = iniciarLista();
    int valor = 10;

    inserirListaFim(l,&valor);
    TEST_ASSERT_FALSE(listaVazia(l));
    TEST_ASSERT_EQUAL_INT(1, getTamanhoLista(l));
    liberarLista(l);
}

void teste_inserirListaInicio_deveInserirCorretamente(void) {
    Lista l = iniciarLista();
    int a = 1, b = 2, c = 3;

    inserirListaInicio(l,&a);
    inserirListaInicio(l,&b);
    inserirListaInicio(l,&c);

    Nopont n = getPrimeiroNoLista(l);
    TEST_ASSERT_EQUAL_INT(3, *(int*)getItemNoLista(n));
    n = getProximoNoLista(n);
    TEST_ASSERT_EQUAL_INT(2, *(int*)getItemNoLista(n));
    n = getProximoNoLista(n);
    TEST_ASSERT_EQUAL_INT(1, *(int*)getItemNoLista(n));

    liberarLista(l);
}

void teste_inserirListaFim_deveInserirCorretamente(void) {
    Lista l = iniciarLista();
    int a = 1, b = 2, c = 3;

    inserirListaFim(l,&a);
    inserirListaFim(l,&b);
    inserirListaFim(l,&c);

    Nopont n = getPrimeiroNoLista(l);
    TEST_ASSERT_EQUAL_INT(1, *(int*)getItemNoLista(n));
    n = getProximoNoLista(n);
    TEST_ASSERT_EQUAL_INT(2, *(int*)getItemNoLista(n));
    n = getProximoNoLista(n);
    TEST_ASSERT_EQUAL_INT(3, *(int*)getItemNoLista(n));
    n = getProximoNoLista(n);
    TEST_ASSERT_NULL(n);

    liberarLista(l);
}

void teste_removerItemLista_deveRemoverItemDoMeioCorretamente(void) {
    Lista l = iniciarLista();
    int a = 1, b = 2, c = 3;
    inserirListaFim(l,&a);
    inserirListaFim(l,&b);
    inserirListaFim(l,&c);

    bool removido = removerItemLista(l, &b);

    TEST_ASSERT_TRUE(removido);
    TEST_ASSERT_EQUAL_INT(2, getTamanhoLista(l));

    Nopont n = getPrimeiroNoLista(l);
    TEST_ASSERT_EQUAL_INT(1, *(int*)getItemNoLista(n));
    n = getProximoNoLista(n);
    TEST_ASSERT_EQUAL_INT(3, *(int*)getItemNoLista(n));
    n = getProximoNoLista(n);
    TEST_ASSERT_NULL(n);

    liberarLista(l);
}

void teste_removerItemLista_deveRemoverPrimeiroEUltimo(void) {
    Lista l = iniciarLista();
    int a = 1, b = 2, c = 3;
    inserirListaFim(l,&a);
    inserirListaFim(l,&b);
    inserirListaFim(l,&c);

    TEST_ASSERT_TRUE(removerItemLista(l, &a));
    TEST_ASSERT_TRUE(removerItemLista(l, &c));
    TEST_ASSERT_EQUAL_INT(1, getTamanhoLista(l));

    Nopont n = getPrimeiroNoLista(l);
    TEST_ASSERT_EQUAL_INT(2, *(int*)getItemNoLista(n));
    TEST_ASSERT_NULL(getProximoNoLista(n));

    liberarLista(l);
}

void teste_liberarLista_naoDeveCrasharComListaVazia(void) {
    Lista l = iniciarLista();
    liberarLista(l);
    TEST_PASS();
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO LISTA\n");
    printf("==========================================\n");

    RUN_TEST(teste_iniciarLista_deveRetornarListaVaziaComTamanhoZero);
    RUN_TEST(teste_inserirListaFim_deveAumentarTamanho);
    RUN_TEST(teste_inserirListaInicio_deveInserirCorretamente);
    RUN_TEST(teste_inserirListaFim_deveInserirCorretamente);
    RUN_TEST(teste_removerItemLista_deveRemoverItemDoMeioCorretamente);
    RUN_TEST(teste_removerItemLista_deveRemoverPrimeiroEUltimo);
    RUN_TEST(teste_liberarLista_naoDeveCrasharComListaVazia);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}