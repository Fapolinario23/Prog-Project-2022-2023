/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno 
 *
 * NAME: files.c
 *
 * DESCRIPTION: Este ficheiro .c apresenta todas as funções associadas aos 
 *              ficheiros de saida. Nomeadamente de escrita dos mesmos.
 ******************************************************************************/
#include "files.h"

/******************************************************************************
 * Cria_Files ()
 *
 * ARGUMENTS:   (param*) p - ponteiro para a struct com os parâmetros iniciais 
 *                           do problema (ficheiros, nº de vagas e nº máx. de candidaos)
 *              (var*)   v - pointeiro para a struct com os parâmetros variáveis 
 *                           (candidatos, cursos, e nº de cursos) 
 * 
 * RETURNS:     (void) 
 *
 * DESCRIPTION: Cria os ficheiros de saida e escreve nos mesmos os devidos 
 *              outputs.
 *****************************************************************************/
void Cria_Files(param *p, var *v)
{
    FILE *fp_Colocacoes = NULL, *fp_Completo = NULL, *fp_Cursos = NULL, *fp_NC = NULL;  /*File pointers para os ficheiros de saída*/
    candidatos *aux = NULL;                                                             /*Auxiliar de tipo candidatos para facilitar o uso de listas*/
    cursos *aux_c = NULL;                                                               /*Auxiliar de tipo cursos para facilitar o uso de listas*/
    int i;                                                                              /*Inteiro com papel de contador usado no correto funcionamento da função*/
    
    /*Criação do file CNAES_Colocacoes.csv*/
    fp_Colocacoes = fopen(p->out_Colocacoes, "w");
    if(fp_Colocacoes == NULL)                                                           /*Verifica que não houve problemas na criaçao do file*/
    {
        fprintf(stdout, "Erro a criar ficheiro %s!\n", p->out_Colocacoes);
        exit(EXIT_FAILURE);
    }
    /*Coloca o cabeçalho do ficheiro*/
    fprintf(fp_Colocacoes, "Candidato,Nota,Opçao,Instituição,Curso\n");
    for(i = 1; i < v->num_cursos; i++)                                                  
    {
        /*Para cada curso excepto o cursos[0](NC) escreve no ficheiro os seus colocados*/
        printf_Completo(fp_Colocacoes, v->cursos[i]->aluno, v->cursos[i]);
    }
    fclose(fp_Colocacoes);                                                              /*Fecha o ficheiro*/

    /*Criação do file CNAES_Completo.csv*/
    fp_Completo = fopen(p->out_Completo, "w");
    if(fp_Completo == NULL)                                                             /*Verifica que não houve problemas na criaçao do file*/
    {
        fprintf(stdout, "Erro a criar ficheiro %s!\n", p->out_Completo);
        exit(EXIT_FAILURE);
    }
    for(i = 1; i < v->num_cursos; i++)
    {
        aux_c = v->cursos[i];
        /*Coloca o cabeçalho respetivo a cada curso no ficheiro (Nome_inst,Nome_curso,Nº_vagas,Nº_colocados,Nota_mínima)*/
        fprintf(fp_Completo, "%s,%s,%d,%d,%f\n", aux_c->nm_inst, aux_c->nm_curso, 
                aux_c->num_vagas, aux_c->num_coloc, aux_c->nota_min);
        /*Para cada curso excepto o cursos[0](NC) escreve no ficheiro os seus colocados*/
        printf_Completo(fp_Completo, aux_c->aluno, aux_c);
    }
    fclose(fp_Completo);                                                                /*Fecha o ficheiro*/

    /*Criação do file CNAES_Cursos.csv*/
    fp_Cursos = fopen(p->out_Cursos, "w");
    if(fp_Cursos == NULL)                                                               /*Verifica que não houve problemas na criaçao do file*/
    {
        fprintf(stdout, "Erro a criar ficheiro %s!\n", p->out_Cursos);
        exit(EXIT_FAILURE);
    }
    /*Coloca o cabeçalho do ficheiro*/
    fprintf(fp_Cursos, "Instituição,Curso,Vagas,Colocacoes,Nota_Mínima\n");
    for(i = 1; i < v->num_cursos; i++)
    {
        aux_c = v->cursos[i];
        /*Para cada curso escreve no ficheiro a informação correspondente (Nome_inst,Nome_curso,Nº_vagas,Nº_colocados,Nota_mínima)*/
        fprintf(fp_Cursos, "%s,%s,%d,%d,%f\n", aux_c->nm_inst, aux_c->nm_curso, 
                aux_c->num_vagas, aux_c->num_coloc, aux_c->nota_min);
    }
    fclose(fp_Cursos);                                                                  /*Fecha o ficheiro*/

    /*Criação do file CNAES_NC.csv*/
    fp_NC = fopen(p->out_NC, "w");
    if(fp_NC == NULL)                                                                   /*Verifica que não houve problemas na criaçao do file*/
    {
        fprintf(stdout, "Erro a criar ficheiro %s!\n", p->out_NC);
        exit(EXIT_FAILURE);
    }
    /*Coloca o cabeçalho do ficheiro*/
    fprintf(fp_NC, "Candidato,Nota\n");
    aux =v->cursos[0]->aluno;                                                           /*cursos[0] corresponde aos NC*/
    while(aux != NULL)
    {
        /*Corre a lista dos NC (ordenada por ID_candidato ascendente)
        e escreve a informação respetiva de cada candidato(ID_candidato,Nota_mínima)*/
        fprintf(fp_NC, "%d,%f\n", aux->ID_cand, aux->Nt_Cand);
        aux = aux->next;
    }
    fclose(fp_NC);                                                                      /*Fecha o ficheiro*/
    return;
}

/******************************************************************************
 * printf_Completo ()
 *
 * ARGUMENTS:   (FILE*)          fp - fichiro onde vai ser escrita a informação
 *              (candidatos*) aluno - ponteiro para o primeiro colocado do curso
 *              (cursos*)     curso - curso cujas informações estão a ser escritas
 * 
 * RETURNS:     (void)
 *
 * DESCRIPTION: Printa recursivamente a lista de alunos de um curso. Esta
 *              recursividade serve para inveter a ordem de aparecimento dos
 *              alunos no ficheiro de saida. Isto é com média crescente, uma 
 *              vez que a lista está ordenada por média decrescente.
 *****************************************************************************/
void printf_Completo(FILE *fp, candidatos *aluno, cursos *curso)
{
    if(aluno != NULL)   /*Verifica se existe pelo menos 1 aluno colocado no curso, caso contrário não há o que printar*/
    {
        /*Enquanto não chega ao fim da lista a função chama-se novamente*/
        if(aluno->next != NULL) printf_Completo (fp, aluno -> next, curso); 
        fprintf(fp, "%d,%f,%d,%s,%s\n", aluno->ID_cand, aluno->Nt_Cand, 
                aluno->opcao_in, curso->nm_inst, curso->nm_curso);
        /*Escreve no ficheiro a lista de candidatos por ordem (Nota_Candidatura ascendente)*/
    }
    return;
}