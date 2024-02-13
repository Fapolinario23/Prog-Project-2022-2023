/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário e Rodrigo Sereno
 *
 * NAME: main.c
 *
 * DESCRIPTION: Programa main
 ******************************************************************************/
#include "candidatos.h"
#include "cursos.h"
#include "entry.h"
#include "files.h"

/******************************************************************************
 * main ()
 *
 * ARGUMENTS:   (int)   argc - número de argumentos na linha de comandos
 *              (char*) argv - tabela de ponteiros para os argumentos
 * 
 * RETURNS:     (int)   0
 *
 * DESCRIPTION: Programa main
 *****************************************************************************/
int main (int argc, char* argv[])
{
    param *p = NULL;                /*Estrutura com os parâmetros provenientes da linha de comando*/
    var *v = NULL;                  /*Estrutura com as variáveis específicas ao problema*/
    p = Inicialize_param();         /*Inicialização da struct *p*/
    v = Inicialize_var();           /*Inicialização da struct *v*/
    Check_call(argc, argv, p, v);   /*Confirma que a linha de comando foi inserida corretamente, e guarda as variáveis dadas necessárias*/
    Completa_param(p);              /*Preenche as variáveis pertencentes à estrutura p não recebidas pela linha de comandos*/
    Read_curso(p, v);               /*Lê os diversos cursos do ficheiro dado, aloca a memória necessária para depois copiar a informação dos cursos*/
    Read_candidato(p, v);           /*Lê os diversos candidatos do ficheiro dado, aloca a memória necessária para copiar a informação dos candidatos*/  
    Distribui_candidatos(v);        /*Realiza a distribuição dos candidatos pelos diversos cursos de acordo com as suas opções(5)*/
    Obtem_nota_min(v);              /*Obtém a nota mínima de cada curso, para facilitar a posterior saída dos resultados*/
    Cria_Files(p, v);               /*Cria e preenche os ficheiros de saida com a informação alterada*/
    Free_var(v);                    /*Liberta a memória alocada para a estrutura v e os seus elementos (cursos e candidatos)*/    
    Free_Param(p);                  /*Liberta a memória alocada para a estrutura p e os seus elementos (files de entrada e saída)*/
    return 0;
}