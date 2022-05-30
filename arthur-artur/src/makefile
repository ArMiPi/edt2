### makefile ###

# Nome do compilador
CC = gcc

# FLAGS
CC_FLAGS = -std=c99					\
		   -fstack-protector-all	\
		   -Wall					\
		   -ggdb3					\
		   -g

# Ligação com as bibliotecas EX: -lm
#LBFLAGS = -lm

# wildcard é utilizado para listar os arquivos-fonte no diretório atual
FONTES = $(wildcard *.c)

# Gera a lista dos arquivos-objeto usando a lista de arquivos-fonte
OBJETOS = $(FONTES:.c=.o)

# Nome do programa
EXECUTAVEL = ted

# all: ted
all: $(EXECUTAVEL)

# ted: ted.o stack.o
#	gcc -o ted ted.o stack.o
# Se tivesse algum LBFLAGS:
#	${CC} -o $@ $^ ${LBFLAGS}
$(EXECUTAVEL): $(OBJETOS)
	${CC} -o $@ $^

# ted.o: ted.c
#	gcc -c ted.c
# stack.o: stack.c
#	gcc -c stack.c
%.o: %.c
	${CC} -c ${CC_FLAGS} $^

clean:
	rm -rf *.o

# rmproper: clean
#	rm -rf ted
rmproper: clean
	rm -rf ${EXECUTAVEL}
	rm ../../testes/BSD/*.svg
	rm ../../testes/BSD/*.txt

# run: ted
#	./ted
run: ${EXECUTAVEL}
	./${EXECUTAVEL}

geo: ${EXECUTAVEL}


qry: ${EXECUTAVEL}


teste: ${EXECUTAVEL}
	./${EXECUTAVEL}