# Definiciones comunes a todos los make

BIN_DIR= ../bin/

CC	= g++
CFLAGS = -Wall -pedantic -Werror -pedantic-errors -g -ggdb
LIBS = 

#Comando para remover
RM	= rm

#Comando para imprimir por consola
ECHO	= echo

#Shell a utilizar
SHELL	= /bin/bash

.SILENT :
