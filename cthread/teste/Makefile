#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=../lib
INC_DIR=../include
BIN_DIR=../bin
SRC_DIR=../src
TST_DIR=../teste
EXP_DIR=../exemplos

all: regra1 regra2 regra4 regra5 regra6

regra1:
	$(CC) -o $(TST_DIR)/teste_ccreate $(TST_DIR)/teste_ccreate.c -L$(LIB_DIR) -lcthread

regra2:
	$(CC) -o $(TST_DIR)/teste_cyield $(TST_DIR)/teste_cyield.c -L$(LIB_DIR) -lcthread
	
regra3:
	$(CC) -o $(TST_DIR)/teste_cjoin $(TST_DIR)/teste_cjoin.c -L$(LIB_DIR) -lcthread

regra4:
	$(CC) -o $(TST_DIR)/caso1 $(TST_DIR)/caso1.c -L$(LIB_DIR) -lcthread

regra5:
	$(CC) -o $(TST_DIR)/caso2 $(TST_DIR)/caso2.c -L$(LIB_DIR) -lcthread

regra6:
	$(CC) -o $(TST_DIR)/caso3 $(TST_DIR)/caso3.c -L$(LIB_DIR) -lcthread


clean:
	rm -rf $(TST_DIR)/*.a $(TST_DIR)/*.o $(TST_DIR)/*.exe


