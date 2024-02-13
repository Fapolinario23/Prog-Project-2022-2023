/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno 
 *
 * NAME: defs.h
 *
 * DESCRIPTION: Este ficheiro .h declara as interfaces de variáveis globais e 
 *              estruturas a ser utilizadas por diversos ficheiros .c.
 *              Dá também include de código pré-compilado das várias bibliotecas.
 *              É portanto a base de todo o programa.
 ******************************************************************************/
#ifndef _DEFS_H
#define _DEFS_H

#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX 60000

/******************************************************************************
 * struct candidatos
 * 
 * DESCRIPTION: Estrutura que contêm toda a informação respetiva a um candidato, 
 *              possui ainda um pointer para o próximo candidato, uma vez que 
 *              estes são dispostos numa lista simplesmente ligada.
 ******************************************************************************/
typedef struct alunos_candidatos candidatos;
struct alunos_candidatos
{
    int ID_cand;        /*Identificador do candidato*/
    float Nt_PI;        /*Nota da prova de ingresso do candidato*/
    float Nt_12;        /*Nota de 12º ano (secundário) do candidato*/
    float Nt_Cand;      /*Nota de candidatura do candidato*/
    int *E;             /*Contém os ID's das instituições dos cursos das várias opções de entrada*/
    char **C;           /*Contém os ID's dos cursos das várias opções de entrada*/
    int opcao_in;       /*Opção de entrada em que o candidato foi colocado (1-5)*/
    candidatos *next;   /*Ponteiro para o próximo candidato na lista*/
};

/******************************************************************************
 * struct cursos
 * 
 * DESCRIPTION: Estrutura que contêm toda a informação respetiva a um curso, 
 *              possui ainda um pointer para uma lista de candidatos, de modo a
 *              guardar as informações dos candidatos colocados em cada curso.
 ******************************************************************************/
typedef struct cursos_sup
{
    int ID_inst;        /*Identificador da instituição da qual o curso faz parte*/
    char *ID_curso;     /*Identificador do curso*/
    char *nm_inst;      /*Nome da instituição (string) em que o curso se insere*/
    char *nm_curso;     /*Nome do curso (string)*/
    char *grau;         /*Grau do curso*/
    int num_vagas;      /*Nº de vagas iniciais do curso*/
    int num_coloc;      /*Nº de colocados no curso*/
    float nota_min;     /*Nota mínima de entrada do curso*/
    candidatos *aluno;  /*Ponteiro para a lista de candidatos colocados no curso*/
}cursos;

/******************************************************************************
 * struct var
 * 
 * DESCRIPTION: Estrutura principal que vai conter um vetor de estruturas curso, 
 *              de modo a ter informação sobre todos os cursos, e uma lista de 
 *              candidatos para guardar momentaneamente os candidatos, isto é, 
 *              antes de se efetuar a distribuição. Contém ainda o número de 
 *              cursos existentes.
 ******************************************************************************/
typedef struct param_variaveis
{
    int num_cursos;         /*Nº de cursos existentes*/
    cursos **cursos;        /*Vetor de struct's cursos com os vários cursos existentes*/
    candidatos *candidatos; /*Lista com os candidatos a serem processados*/
}var;

/******************************************************************************
 * struct param_iniciais
 * 
 * DESCRIPTION: Estrutura que contêm toda a informação sobre a interface de 
 *              entrada e saida do programa.
 ******************************************************************************/
typedef struct param_iniciais
{
    int vagas;              /*Nº máximo de vagas por curso a considerar*/
    int num_candidatos;     /*Nº máximo de candidatos a considerar*/
    char *in_cursos;        /*Ficheiro de entrada com a informação dos cursos*/
    char *in_candidatos;    /*Ficheiro de entrada com a informação dos candidatos*/
    char *out_Colocacoes;   /*Ficheiro de saída correspondente a CNAES_Colocacoes*/
    char *out_Completo;     /*Ficheiro de saída correspondente a CNAES_Completo*/
    char *out_Cursos;       /*Ficheiro de saída correspondente a CNAES_Cursos*/
    char *out_NC;           /*Ficheiro de saída correspondente a CNAES_NC*/
}param;
#endif /*_DEFS_H*/