/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno 
 *
 * NAME: entry.h
 *
 * DESCRIPTION: Este ficheiro .h declara as interfaces de funções, variáveis e 
 *              estruturas relacionadas com os dados de entrada do programa que 
 *              são utilizadas no ficheiro entry.c.
 ******************************************************************************/

#ifndef _ENTRY_H
#define _ENTRY_H

#include "defs.h"

                                /*FUNCTION HEADERS*/
param* Inicialize_param();
var* Inicialize_var();
void Check_call(int, char**, param*, var*);
void help();
char *Alloc(char*);
void Completa_param(param*);
void Free_Param(param*);
#endif /*_ENTRY_H*/