/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno
 *
 * NAME: cursos.h
 *
 * DESCRIPTION: Este ficheiro .h declara as interfaces de funções, utilizadas 
 *              no ficheiro cursos.c, relacionadas com os cursos.
 ******************************************************************************/
#ifndef _CURSOS_H
#define _CURSOS_H

#include "defs.h"
                                    /*FUNCTION HEADRS*/
void Read_curso(param*, var*);
cursos *Aloca_cursos(int, char*, char*, char*, char*, int);
void Obtem_nota_min(var*);
void Free_var(var*);
void Free_alunos(candidatos*);
#endif  /*_CURSOS_H*/