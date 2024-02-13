/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno
 *
 * NAME: cursos.c
 *
 * DESCRIPTION: Este ficheiro .c apresenta todas as funções associadas aos cursos.
 *              Tais como, funções para leitura de ficheiros, alocação dinâmica de
 *              memória e libertações de memória.
 ******************************************************************************/
#include "cursos.h"

/***************************************************************************************
 * Read_curso ()
 *
 * ARGUMENTS:   (param*) p - ponteiro para a struct com os parâmetros iniciais 
 *                           do problema (ficheiros, nº de vagas e nº máx. de candidaos)
 *              (var*)   v - pointeiro para a struct com os parâmetros variáveis 
 *                           (candidatos, cursos, e nº de cursos) 
 * 
 * RETURNS:     (void)
 *
 * DESCRIPTION: Aloca a memória para a o vetor de estruturas dos cursos, e 
 *              guarda no mesmo, após a leitura dos ficheiro, os cursos com
 *              a respetiva informação sobre os mesmos.
 **************************************************************************************/
void Read_curso(param *p,  var *v)
{
    FILE *fp = fopen(p->in_cursos, "r");                                /*File pointer usado para ler o ficheiro de entrada com os cursos*/
    int i = 1,  ID_inst = 0, vagas = 0;
    /*Contador (i) e int return variables (ID_inst e vagas) usados para guardar valores do ficheiro "cursos"*/
    /*ID_inst->guarda o identificador da instituição do curso, vagas->guarda o nº de vags do curso especificado no ficheiro*/
    char line[300], ID_curso[5], nm_inst[200], nm_curso[100], grau[3];  /*char return values usados para guardar valores do ficheiro "cursos"*/
    /*line->guarda a linha do ficheiro, ID_curso->guarda o identificador de cada curso, nm_inst->guarda o nome da instituição 
    nm_curso->guarda o nome do curso, grau->guarda o grau do curso*/

    if(fp == NULL)                                                      /*Verifica se o ficheiro de entrada dos cursos foi aberto corretamente*/
    {
        fprintf(stdout, "Erro na abertura do ficheiro %s\n", p->in_cursos);
        exit(EXIT_FAILURE);
    }

    /*Conta o nº de cursos no ficheiro (conta 1 a mais para a struct com os não colocados)*/
    while(fgets(line, sizeof(line), fp) != NULL) v->num_cursos++;
    rewind(fp);                                                         /*Voltar ao início do ficheiro dos cursos*/
    v->cursos = (cursos**)malloc(v->num_cursos*sizeof(cursos*));        /*Aloca memória para o vetor de structs dos cursos*/ 
    if(v->cursos == NULL)                                               /*Verifica se houve problemas a alocar memória para o vetor*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }  
    
    if(fgets(line, sizeof(line), fp) == NULL) exit(EXIT_FAILURE);       /*Saltar a 1ª linha do ficheiro que contem a legenda*/

    /*Ter em atenção que a estrutura de i = 0, corresponde à estrutura dos não colocados*/
    v->cursos[0] = Aloca_cursos(0, "0", "0", "Não Colocados", "0", MAX);
    /*Enquanto há valores para copiar do ficheiro, aloca uma nova estrutura para o curso*/
    while(fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d", &ID_inst, ID_curso, nm_inst, nm_curso, grau, &vagas) != EOF)
    {
        if(p->vagas != -1) vagas = p->vagas;                            /*Foi indicado um número de vagas limite no terminal*/
        /*Aloca o espaço do para o curso[i], e preenche com as respetivas informações*/
        v->cursos[i] = Aloca_cursos(ID_inst, ID_curso, nm_inst, nm_curso, grau, vagas);
        i++;
    }
    fclose(fp);                                                         /*Fecha o ficheiro*/
    return;
}

/******************************************************************************
 * Aloca_cursos ()
 *
 * ARGUMENTS:   (int)   Id_i  - ID da instituição em que o curso se insere
 *              (char*) Id_c  - ID do curso
 *              (char*) nm_i  - nome da instituição em que o curso se insere
 *              (char*) nm_c  - nome do curso
 *              (char*) grau  - grau do curso
 *              (int)   vagas - nº de vagas iniciais do curso
 * 
 * RETURNS:     (cursos*) new - novo curso alocado e com informação guardada
 *
 * DESCRIPTION: Aloca a memória para a estrutura do novo curso e guarda na
 *              mesma as informações deste.
 *****************************************************************************/
cursos* Aloca_cursos(int Id_i, char* Id_c , char* nm_i, char* nm_c, char* grau, int vagas)
{
    cursos *new = NULL;/*Struct cursos a retornar da função*/

    new = (cursos*)malloc(sizeof(cursos));/*Aloca memória para a struct*/
    if(new == NULL)/*Verifica se houve problemas a alocar a memória para a struct*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    new->ID_curso = (char*)malloc((strlen(Id_c)+1)*sizeof(char));       /*Aloca memória para a o Identificador do curso*/
    if(new->ID_curso == NULL)                                           /*Verifica se houve problemas a alocar a memória para a variável*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    new->nm_inst = (char*)malloc((strlen(nm_i)+1)*sizeof(char));        /*Aloca memória para o nome da isntituição*/
    if(new->nm_inst == NULL)                                            /*Verifica se houve problemas a alocar a memória para a variável*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    new->nm_curso = (char*)malloc((strlen(nm_c)+1)*sizeof(char));       /*Aloca memória para o nome do curso */
    if(new->nm_curso == NULL)                                           /*Verifica se houve problemas a alocar a memória para a variável*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    new->grau = (char*)malloc((strlen(grau)+1)*sizeof(char));           /*Aloca memória para o grau do curso*/
    if(new->grau == NULL)                                               /*Verifica se houve problemas a alocar a memória para a variável*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    
    /*Preenche os espaços da struct curso com os respetivos dados lidos do ficheiro*/
    new->ID_inst = Id_i;
    strcpy(new->ID_curso, Id_c);
    strcpy(new->nm_inst, nm_i);
    strcpy(new->nm_curso, nm_c);
    strcpy(new->grau, grau);
    new->num_vagas = vagas;
    new->nota_min = 0;
    new->num_coloc = 0;
    new->aluno = NULL;                                                  /*Coloca o ponteiro dos alunos a NULL (onde vão ser postos os candidatos colocados)*/
    return new;                                                         /*Retorna a struct criada*/
}

/******************************************************************************
 * Obtem_nota_min ()
 *
 * ARGUMENTS:   (var*) v - pointeiro para a struct com os parâmetros variáveis 
 *                         (candidatos, cursos, e nº de cursos) 
 *             
 * RETURNS:     (void)
 *
 * DESCRIPTION: Obtém a nota mínima de ingresso em cada um dos cursos e guarda
 *              a mesma na estrutura associada a esse curso.
 *****************************************************************************/
void Obtem_nota_min(var* v)
{
    int i;                                                              /*Contador para ajudar no correto funcionamento da função*/
    candidatos *aux = NULL;                                             /*Auxiliar de tipo candidatos(struct) para correr a lista de colocados*/

    for(i = 1; i < v->num_cursos; i++)
    {
        aux =  v->cursos[i]->aluno;
        if(aux != NULL)                                                 /*Verifica se foi colocado pelo menos 1 aluno*/
        {
            while(aux->next != NULL) aux = aux->next;                   /*Corre a lista dos colocados até chegar ao último (menor média de entrada)*/
            /*Caso o curso tenha as vagas completamente preenchidas a nota mínima é igual à nota de candidatura do último colocado*/
            if(v->cursos[i]->num_vagas <= v->cursos[i]->num_coloc) v->cursos[i]->nota_min = aux->Nt_Cand;
            else v->cursos[i]->nota_min = 10;                           /*Caso não tenha as vagas preenchidas, a nota mínima é igual a 10.000000*/
        } 
        else v->cursos[i]->nota_min = 10;                               /*Caso não haja colocados a nota mínima é também igual a 10.000000*/
    }
    return;
}

/******************************************************************************
 * Free_var ()
 *
 * ARGUMENTOS:  (var*) v - pointeiro para a struct com os parâmetros variáveis 
 *                         (candidatos, cursos, e nº de cursos)  
 * 
 * RETURNS:     (void)
 *
 * DESCRIPTION: Liberta a memória alocada para a struct var e os seus elementos 
 *              (vetor cursos e candidatos)
 *****************************************************************************/
void Free_var(var *v)
{
    int i;                                                  /*Contador para ajudar no correto funcionamento da função*/

    for(i = 0; i < v->num_cursos; i++)
    {
        /*Liberta a memória alocada para as diversas variáveis da struct curso*/
        free(v->cursos[i]->ID_curso);
        free(v->cursos[i]->nm_inst);
        free(v->cursos[i]->nm_curso);
        free(v->cursos[i]->grau);
        Free_alunos(v->cursos[i]->aluno);                   /*Chama a função Free_alunos que liberta as struct's candidatos dos candidatos colocados no curso*/
        free(v->cursos[i]);
    }
    free(v->cursos);                                        /*Liberta o vetor de struct's cursos*/
    free(v);                                                /*Liberta a struct de param_variáveis (v)*/
    return;
}

/***********************************************************************************
 * Free_alunos ()
 *
 * ARGUMENTS:   (candidatos*) candidato - apontador para o primeiro elemento da 
 *                                        lista de alunos colocados num determinado 
 *                                        curso
 *             
 * RETURNS:     (void) 
 *
 * DESCRIPTION: Liberta a memória alocada para a lista de alunos colocados num
 *              determinado curso.
 **********************************************************************************/
void Free_alunos(candidatos *candidato)
{
    int i;                                                  /*Contador para ajudar no correto funcionamento da função*/
    candidatos *aux = NULL, *next = NULL;                   /*Auxiliares de tipo candidatos(struct) para correr a lista de candidatos*/

    for(aux = candidato; aux != NULL; aux = next)
    {
        next = aux->next;                                   /*Guarda o próximo nó da lista*/
        for(i = 0; i < 5; i++) free(aux->C[i]);             /*Liberta a memória alocada para as escolhas do candidato(C[i])*/
        free(aux->E);                                       /*Liberta a memória alocada para o vetor E*/
        free(aux->C);                                       /*Liberta a memória alocada para o vetor C*/
        free(aux);                                          /*Liberta a memória alocada para o nó atual (struct)*/
    }
    return;
}