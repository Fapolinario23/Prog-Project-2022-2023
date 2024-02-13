/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno
 *
 * NAME: candidatos.h
 *
 * DESCRIPTION: Este ficheiro .h declara as interfaces de funções, utilizadas 
 *              no ficheiro candidatos.c, relacionadas com os candidatos.
 ******************************************************************************/
#ifndef _CANDIDATOS_H
#define _CANDIDATOS_H

#include "defs.h"

                                    /*FUNCTION HEADERS*/
void Read_candidato(param*, var*);
candidatos *Adiciona_candidato(candidatos*, char*);
candidatos *Aloca_candidatos();
void Distribui_candidatos(var*);
int Insere_aluno(cursos*, candidatos*, int);
void Insere_NC(cursos*, candidatos*);
#endif /*_CANDIDATOS_H*/