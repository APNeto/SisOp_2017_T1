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
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TST_DIR=./teste
EXP_DIR=./exemplos

all: regra1 regra2 regra3 regra4

regra1: $(SRC_DIR)/cthread.c $(INC_DIR)/cdata.h $(INC_DIR)/cthread.h $(INC_DIR)/support.h $(BIN_DIR)/support.o
	$(CC) -c $(SRC_DIR)/cthread.c -Wall

regra2: 
	mv *.o $(BIN_DIR)
	

regra3:	$(BIN_DIR)/cthread.o
	ar crs libcthread.a $(BIN_DIR)/*.o

regra4:
	mv *.a $(LIB_DIR)


clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/cthread.o $(TST_DIR)/*.exe $(TST_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~


