# =============================================================================
# Makefile — Projeto TED (GIS Bitnópolis) — PROJETO 2
# Disciplina: Estrutura de Dados II — UEL 2026
# Aluno: Nathan Felipe Caroba dos Santos
#
# Estrutura de diretórios:
#   include/ — arquivos de cabeçalho (.h)
#   src/     — arquivos-fonte (.c) e executável ted
#   tst/     — testes unitários (t_modulo.c para cada módulo)
#   unity/   — framework Unity (unity.c, unity.h, unity_internals.h)
# =============================================================================

# -----------------------------------------------------------------------------
# Configuração geral
# -----------------------------------------------------------------------------

PROJ_NAME  = ted
NOME_ALUNO = Nathan Felipe Caroba dos Santos

CC     = gcc
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb \
         -Werror=implicit-function-declaration
LIBS   = -lm

# -----------------------------------------------------------------------------
# Diretórios
# -----------------------------------------------------------------------------

INC_DIR   = ../include
SRC_DIR   = .
TST_DIR   = ../tst
UNITY_DIR = ../unity

# -----------------------------------------------------------------------------
# Módulos da aplicação (Todos os arquivos .c do Projeto 2)
# -----------------------------------------------------------------------------

MODULOS = \
	aresta                \
	arquivos              \
	arvoreGeradoraMinima  \
	componentes           \
	dijkstra              \
	filaPrioridade        \
	grafo                 \
	lista                 \
	quadra                \
	registrador           \
	svg                   \
	vertice               \
	geo                   \
	via                   \
	qry

# Objetos dos módulos (gerados em src/)
MOD_OBJS = $(addprefix $(SRC_DIR)/, $(addsuffix .o, $(MODULOS)))

# Objeto principal do programa
TED_OBJ = $(SRC_DIR)/ted.o

# Todos os objetos do executável final
OBJS = $(MOD_OBJS) $(TED_OBJ)

# Executável produzido dentro de src/
TED_BIN = $(SRC_DIR)/$(PROJ_NAME)

# -----------------------------------------------------------------------------
# Unity
# -----------------------------------------------------------------------------

UNITY_OBJ = $(UNITY_DIR)/unity.o

# -----------------------------------------------------------------------------
# Regras Principais
# -----------------------------------------------------------------------------

.PHONY: all
all: ted

.PHONY: ted
ted: $(TED_BIN)

$(TED_BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

# Regra genérica para objetos em src/
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@

# Objeto do Unity
$(UNITY_OBJ): $(UNITY_DIR)/unity.c $(UNITY_DIR)/unity.h
	$(CC) -c $(CFLAGS) -I$(UNITY_DIR) $< -o $@

# -----------------------------------------------------------------------------
# Dependências explícitas dos módulos (.c -> .h)
# -----------------------------------------------------------------------------

$(SRC_DIR)/aresta.o: $(SRC_DIR)/aresta.c $(INC_DIR)/aresta.h
$(SRC_DIR)/arquivos.o: $(SRC_DIR)/arquivos.c $(INC_DIR)/arquivos.h
$(SRC_DIR)/lista.o: $(SRC_DIR)/lista.c $(INC_DIR)/lista.h
$(SRC_DIR)/quadra.o: $(SRC_DIR)/quadra.c $(INC_DIR)/quadra.h
$(SRC_DIR)/registrador.o: $(SRC_DIR)/registrador.c $(INC_DIR)/registrador.h
$(SRC_DIR)/filaPrioridade.o: $(SRC_DIR)/filaPrioridade.c $(INC_DIR)/filaPrioridade.h

$(SRC_DIR)/vertice.o: $(SRC_DIR)/vertice.c $(INC_DIR)/vertice.h $(INC_DIR)/lista.h

$(SRC_DIR)/grafo.o: $(SRC_DIR)/grafo.c $(INC_DIR)/grafo.h $(INC_DIR)/vertice.h \
                     $(INC_DIR)/aresta.h $(INC_DIR)/lista.h

$(SRC_DIR)/componentes.o: $(SRC_DIR)/componentes.c $(INC_DIR)/componentes.h $(INC_DIR)/grafo.h

$(SRC_DIR)/arvoreGeradoraMinima.o: $(SRC_DIR)/arvoreGeradoraMinima.c $(INC_DIR)/arvoreGeradoraMinima.h \
                                   $(INC_DIR)/grafo.h $(INC_DIR)/lista.h

$(SRC_DIR)/dijkstra.o: $(SRC_DIR)/dijkstra.c $(INC_DIR)/dijkstra.h $(INC_DIR)/grafo.h \
                       $(INC_DIR)/filaPrioridade.h $(INC_DIR)/lista.h

$(SRC_DIR)/svg.o: $(SRC_DIR)/svg.c $(INC_DIR)/svg.h $(INC_DIR)/quadra.h \
                  $(INC_DIR)/aresta.h $(INC_DIR)/grafo.h

$(SRC_DIR)/geo.o: $(SRC_DIR)/geo.c $(INC_DIR)/geo.h $(INC_DIR)/quadra.h $(INC_DIR)/lista.h

$(SRC_DIR)/via.o: $(SRC_DIR)/via.c $(INC_DIR)/via.h $(INC_DIR)/grafo.h \
                  $(INC_DIR)/vertice.h $(INC_DIR)/aresta.h

$(SRC_DIR)/qry.o: $(SRC_DIR)/qry.c $(INC_DIR)/qry.h $(INC_DIR)/grafo.h $(INC_DIR)/quadra.h \
                  $(INC_DIR)/svg.h $(INC_DIR)/registrador.h $(INC_DIR)/dijkstra.h \
                  $(INC_DIR)/arvoreGeradoraMinima.h $(INC_DIR)/componentes.h

$(SRC_DIR)/ted.o: $(SRC_DIR)/ted.c $(INC_DIR)/arquivos.h $(INC_DIR)/grafo.h \
                  $(INC_DIR)/quadra.h $(INC_DIR)/svg.h $(INC_DIR)/geo.h \
                  $(INC_DIR)/via.h $(INC_DIR)/qry.h

# -----------------------------------------------------------------------------
# Alvos de Testes Unitários Individuais
# -----------------------------------------------------------------------------

define roda_teste
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(UNITY_DIR) $^ -o $@ $(LIBS)
	@echo ">>> Executando testes: $(1) <<<"
	@$@
	@echo ""
endef

.PHONY: tst_aresta
tst_aresta: $(TST_DIR)/t_aresta
$(TST_DIR)/t_aresta: $(TST_DIR)/t_aresta.c $(SRC_DIR)/aresta.o $(UNITY_OBJ)
	$(call roda_teste,aresta)

.PHONY: tst_arquivos
tst_arquivos: $(TST_DIR)/t_arquivos
$(TST_DIR)/t_arquivos: $(TST_DIR)/t_arquivos.c $(SRC_DIR)/arquivos.o $(UNITY_OBJ)
	$(call roda_teste,arquivos)

.PHONY: tst_lista
tst_lista: $(TST_DIR)/t_lista
$(TST_DIR)/t_lista: $(TST_DIR)/t_lista.c $(SRC_DIR)/lista.o $(UNITY_OBJ)
	$(call roda_teste,lista)

.PHONY: tst_quadra
tst_quadra: $(TST_DIR)/t_quadra
$(TST_DIR)/t_quadra: $(TST_DIR)/t_quadra.c $(SRC_DIR)/quadra.o $(UNITY_OBJ)
	$(call roda_teste,quadra)

.PHONY: tst_registrador
tst_registrador: $(TST_DIR)/t_registrador
$(TST_DIR)/t_registrador: $(TST_DIR)/t_registrador.c $(SRC_DIR)/registrador.o $(UNITY_OBJ)
	$(call roda_teste,registrador)

.PHONY: tst_filaPrioridade
tst_filaPrioridade: $(TST_DIR)/t_filaPrioridade
$(TST_DIR)/t_filaPrioridade: $(TST_DIR)/t_filaPrioridade.c $(SRC_DIR)/filaPrioridade.o $(UNITY_OBJ)
	$(call roda_teste,filaPrioridade)

.PHONY: tst_vertice
tst_vertice: $(TST_DIR)/t_vertice
$(TST_DIR)/t_vertice: $(TST_DIR)/t_vertice.c $(SRC_DIR)/vertice.o $(SRC_DIR)/lista.o $(UNITY_OBJ)
	$(call roda_teste,vertice)

.PHONY: tst_grafo
tst_grafo: $(TST_DIR)/t_grafo
$(TST_DIR)/t_grafo: $(TST_DIR)/t_grafo.c $(SRC_DIR)/grafo.o $(SRC_DIR)/vertice.o $(SRC_DIR)/aresta.o $(SRC_DIR)/lista.o $(UNITY_OBJ)
	$(call roda_teste,grafo)

.PHONY: tst_componentes
tst_componentes: $(TST_DIR)/t_componentes
$(TST_DIR)/t_componentes: $(TST_DIR)/t_componentes.c $(SRC_DIR)/componentes.o $(SRC_DIR)/grafo.o $(SRC_DIR)/vertice.o $(SRC_DIR)/aresta.o $(SRC_DIR)/lista.o $(UNITY_OBJ)
	$(call roda_teste,componentes)

.PHONY: tst_arvoreGeradoraMinima
tst_arvoreGeradoraMinima: $(TST_DIR)/t_arvoreGeradoraMinima
$(TST_DIR)/t_arvoreGeradoraMinima: $(TST_DIR)/t_arvoreGeradoraMinima.c $(SRC_DIR)/arvoreGeradoraMinima.o $(SRC_DIR)/grafo.o $(SRC_DIR)/vertice.o $(SRC_DIR)/aresta.o $(SRC_DIR)/lista.o $(UNITY_OBJ)
	$(call roda_teste,arvoreGeradoraMinima)

.PHONY: tst_dijkstra
tst_dijkstra: $(TST_DIR)/t_dijkstra
$(TST_DIR)/t_dijkstra: $(TST_DIR)/t_dijkstra.c $(SRC_DIR)/dijkstra.o $(SRC_DIR)/grafo.o $(SRC_DIR)/vertice.o $(SRC_DIR)/aresta.o $(SRC_DIR)/lista.o $(SRC_DIR)/filaPrioridade.o $(UNITY_OBJ)
	$(call roda_teste,dijkstra)

.PHONY: tst_svg
tst_svg: $(TST_DIR)/t_svg
$(TST_DIR)/t_svg: $(TST_DIR)/t_svg.c $(SRC_DIR)/svg.o $(SRC_DIR)/quadra.o $(SRC_DIR)/aresta.o $(SRC_DIR)/grafo.o $(SRC_DIR)/vertice.o $(SRC_DIR)/lista.o $(UNITY_OBJ)
	$(call roda_teste,svg)

.PHONY: tst_geo
tst_geo: $(TST_DIR)/t_geo
$(TST_DIR)/t_geo: $(TST_DIR)/t_geo.c $(SRC_DIR)/geo.o $(SRC_DIR)/quadra.o $(SRC_DIR)/lista.o $(UNITY_OBJ)
	$(call roda_teste,geo)

.PHONY: tst_via
tst_via: $(TST_DIR)/t_via
$(TST_DIR)/t_via: $(TST_DIR)/t_via.c $(SRC_DIR)/via.o $(SRC_DIR)/grafo.o $(SRC_DIR)/vertice.o $(SRC_DIR)/aresta.o $(SRC_DIR)/lista.o $(UNITY_OBJ)
	$(call roda_teste,via)

.PHONY: tst_qry
tst_qry: $(TST_DIR)/t_qry
$(TST_DIR)/t_qry: $(TST_DIR)/t_qry.c $(SRC_DIR)/qry.o $(SRC_DIR)/grafo.o $(SRC_DIR)/vertice.o \
                  $(SRC_DIR)/aresta.o $(SRC_DIR)/lista.o $(SRC_DIR)/quadra.o $(SRC_DIR)/registrador.o \
                  $(SRC_DIR)/svg.o $(SRC_DIR)/dijkstra.o $(SRC_DIR)/arvoreGeradoraMinima.o \
                  $(SRC_DIR)/componentes.o $(SRC_DIR)/filaPrioridade.o $(UNITY_OBJ)
	$(call roda_teste,qry)

# -----------------------------------------------------------------------------
# Execução global de testes
# -----------------------------------------------------------------------------

.PHONY: tstall
tstall: tst_aresta tst_arquivos tst_lista tst_quadra tst_registrador \
        tst_filaPrioridade tst_vertice tst_grafo tst_componentes \
        tst_arvoreGeradoraMinima tst_dijkstra tst_svg tst_geo tst_via tst_qry
	@echo "=== [SUCESSO] Todos os testes unitários foram executados! ==="

# -----------------------------------------------------------------------------
# Limpeza do ambiente
# -----------------------------------------------------------------------------

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(UNITY_DIR)/*.o
	rm -f $(TED_BIN)
	rm -f $(TST_DIR)/t_aresta
	rm -f $(TST_DIR)/t_arquivos
	rm -f $(TST_DIR)/t_lista
	rm -f $(TST_DIR)/t_quadra
	rm -f $(TST_DIR)/t_registrador
	rm -f $(TST_DIR)/t_filaPrioridade
	rm -f $(TST_DIR)/t_vertice
	rm -f $(TST_DIR)/t_grafo
	rm -f $(TST_DIR)/t_componentes
	rm -f $(TST_DIR)/t_arvoreGeradoraMinima
	rm -f $(TST_DIR)/t_dijkstra
	rm -f $(TST_DIR)/t_svg
	rm -f $(TST_DIR)/t_geo
	rm -f $(TST_DIR)/t_via
	rm -f $(TST_DIR)/t_qry