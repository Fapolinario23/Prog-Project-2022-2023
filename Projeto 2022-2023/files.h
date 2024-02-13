/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno 
 *
 * NAME: files.h
 *
 * DESCRIPTION: Este ficheiro .h declara as interfaces de funções, 
 *              utilizadas no ficheiro files.c, relacionadas com a escrita 
 *              nos ficheiros de saída. 
 ******************************************************************************/
#ifndef _FILES_H
#define _FILES_H

#include "defs.h"
                                /*FUNCTION HEADERS*/
void Cria_Files(param *p, var *v);
void printf_Completo(FILE*, candidatos*, cursos*);
#endif /*_FILES_H*/