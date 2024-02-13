/******************************************************************************
 * (C) Projeto Programação 2022/2022
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno 
 *
 * NAME: entry.c
 *
 * DESCRIPTION: Este ficheiro .c apresenta todas as funções associadas ao ínicio 
 *              do programa. Tais como, funções para obtenção das opções da linha 
 *              de comandos, alocação dinâmica de memória e libertações de memória.
 ******************************************************************************/
#include "entry.h"

/******************************************************************************
 * Inicialize_param ()
 *
 * ARGUMENTS:   (void)
 * 
 * RETURNS:     (param*) p - ponteiro para a struct com os parâmetros iniciais 
 *                           do problema (ficheiros, nº de vagas e nº máx. de candidaos)   
 *
 * DESCRIPTION: Inicializa estrutura que possui toda asobre a interface de 
 *              entrada e saida do programa.
 * 
 *****************************************************************************/
param *Inicialize_param()
{
    param *p = (param*)malloc(sizeof(param));           /*Aloca memória para a struct*/
    if(p == NULL)                                       /*Verifica que não houve problemas a alocar espaço para a struct*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    /*Inicializa as variáveis*/
    p->in_candidatos = NULL;
    p->in_cursos = NULL;
    p->out_Colocacoes = NULL;
    p->out_Completo = NULL;
    p->out_Cursos = NULL;
    p->out_NC = NULL;
    p->num_candidatos = MAX;                            /*MAX representa o número máximo de candidatos (60000)*/ 
    p->vagas = -1;                                  
    return p;
}

/******************************************************************************
 * Inicialize_var ()
 *
 * ARGUMENTS:   (void)
 * 
 * RETURNS:     (var*)   v - pointeiro para a struct com os parâmetros variáveis 
 *                           (candidatos, cursos, e nº de cursos)    
 *
 * DESCRIPTION: Inicializa a estutura que possui toda a informação sobre os 
 *              cursos e candidatos.
 *****************************************************************************/
var *Inicialize_var()
{
    var *v = (var*)malloc(sizeof(var));                 /*Aloca memória para a struct*/
    if(v == NULL)                                       /*Verifica que não houve problemas a alocar espaço para a struct*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    /*Inicializa as variáveis*/
    v->cursos = NULL;
    v->candidatos = NULL;
    v->num_cursos = 0;
    return v;
}

/******************************************************************************
 * Check_call ()
 *
 * ARGUMENTS:   (int)    argc - número de argumentos na linha de comandos
 *              (char*)  argv - tabela de ponteiros para os argumentos
 *              (param*) p    - ponteiro para a struct com os parâmetros iniciais 
 *                              do problema (ficheiros, nº de vagas e nº máx. de candidaos)
 *              (var*)   v    - pointeiro para a struct com os parâmetros variáveis 
 *                              (candidatos, cursos, e nº de cursos)
 * 
 * RETURNS:     (void)
 *
 * DESCRIPTION: Verifica se os parâmetros da linha de comandos foram bem inseridos, 
 *              e se sim guarda as informações fornecidas
 * 
 *****************************************************************************/
void Check_call(int argc, char *argv[], param *p, var *v)
{
    int i, opt;                                         /*Contador(i) e  return da função "getopt"(opt) usados no correto funcionamento da função*/
    char options[9][3] = {"-h", "-v", "-n", "-i", "-c", "-o", "-u", "-m", "-x"};
    /*Vetor char com as diferentes opcoes de funcionalidade da linha de comandos*/

    while((opt = getopt(argc, argv, "hv:n:i:c:o:u:m:x:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                help();
                Free_Param(p);
                free(v);
                exit(EXIT_FAILURE);
                break;
            case 'v':
                if(optarg != NULL)                  /*Foi selecionada a opção -v com argumento seguinte não nulo*/
                {
                    for(i = 0; i < strlen(optarg); i++)
                    {
                        /*Verifica que o argumento dado para o nº de vagas é um inteiro*/
                        if((optarg[i] > '9') || (optarg[i] < '0'))
                        {
                            /*Caso não seja validado, escreve a mensagem de erro e liberta a memória alocada até ao momento, saindo com erro do programa*/
                            fprintf(stdout, "Argumento invalido! '-v' espera um inteiro >=0.\n");
                            Free_Param(p);
                            free(v);
                            exit(EXIT_FAILURE);
                        }
                    }
                    /*Caso seja válido guarda o valor no formato int na struct com os parâmetros (p)*/
                    p->vagas = atoi(optarg);
                    break;
                }
            case 'n':             
                if(optarg != NULL)                  /*Foi selecionada a opção -n com argumento seguinte não nulo*/
                {
                    for(i = 0; i < strlen(optarg); i++)
                    {
                        /*Verifica que o argumento dado para o nº de candidatos é um inteiro*/
                        if((optarg[i] > '9') || (optarg[i] < '0'))
                        {
                            /*Caso não seja validado, escreve a mensagem de erro e liberta a memória alocada até ao momento, saindo com erro do programa*/
                            fprintf(stdout, "Argumento invalido! '-n' espera um inteiro >=0.\n");
                            Free_Param(p);
                            free(v);
                            exit(EXIT_FAILURE);
                        }
                    }
                    /*Caso seja válido guarda o valor no formato int na struct com os parâmetros (p)*/
                    p->num_candidatos = atoi(optarg);
                    break;
                }
            case 'i':
                if(optarg != NULL)                  /*Foi selecionada a opção -i com argumento seguinte não nulo*/
                {
                    for(i = 0; i < 9; i++)
                    {
                        /*Verifica que o argumento correspondente não é igual a um outro comando das opções de funcionamento*/
                        if(strcasecmp(optarg, options[i]) == 0)
                        {
                            /*Caso não seja validado, escreve a mensagem de erro e liberta a memória alocada até ao momento, saindo com erro do programa*/
                            fprintf(stdout, "Argumento invalido! '-i' espera um ficheiro.\n");
                            Free_Param(p);
                            free(v);
                            exit(EXIT_FAILURE);
                        }
                    }
                    /*Caso seja validado, aloca o espaço necessário e copia o argumento dado para a variável correspondente na struct p(in_cursos)*/
                    p->in_cursos = Alloc(optarg);
                    break;
                }
            case 'c':
                if(optarg != NULL)                  /*Foi selecionada a opção -c com argumento seguinte não nulo*/
                {
                    for(i = 0; i < 9; i++)
                    {
                        /*Verifica que o argumento correspondente não é igual a um outro comando das opções de funcionamento*/
                        if(strcasecmp(optarg, options[i]) == 0)
                        {
                            /*Caso não seja validado, escreve a mensagem de erro e liberta a memória alocada até ao momento, saindo com erro do programa*/
                            fprintf(stdout, "Argumento invalido! '-c' espera um ficheiro.\n");
                            Free_Param(p);
                            free(v);
                            exit(EXIT_FAILURE);
                        }
                    }
                    /*Caso seja validado, aloca o espaço necessário e copia o argumento dado para a variável correspondente na struct p(in_candidatos)*/
                    p->in_candidatos = Alloc(optarg);
                    break;
                }
            case 'o':
                if(optarg != NULL)                  /*Foi selecionada a opção -o com argumento seguinte não nulo*/
                {
                    for(i = 0; i < 9; i++)
                    {
                        /*Verifica que o argumento correspondente não é igual a um outro comando das opções de funcionamento*/
                        if(strcasecmp(optarg, options[i]) == 0)
                        {
                            /*Caso não seja validado, escreve a mensagem de erro e liberta a memória alocada até ao momento, saindo com erro do programa*/
                            fprintf(stdout, "Argumento invalido! '-o' espera um ficheiro.\n");
                            Free_Param(p);
                            free(v);
                            exit(EXIT_FAILURE);
                        }
                    }
                    /*Caso seja validado, aloca o espaço necessário e copia 
                    o argumento dado para a variável correspondente na struct p(out_Colocacoes)*/
                    p->out_Colocacoes = Alloc(optarg);
                    break;
                }
            case 'u':
                if(optarg != NULL)                  /*Foi selecionada a opção -u com argumento seguinte não nulo*/
                {
                    for(i = 0; i < 9; i++)
                    {
                        /*Verifica que o argumento correspondente não é igual a um outro comando das opções de funcionamento*/
                        if(strcasecmp(optarg, options[i]) == 0)
                        {
                            /*Caso não seja validado, escreve a mensagem de erro e liberta a memória alocada até ao momento, saindo com erro do programa*/
                            fprintf(stdout, "Argumento invalido! '-u' espera um ficheiro.\n");
                            Free_Param(p);
                            free(v);
                            exit(EXIT_FAILURE);
                        }
                    }
                    /*Caso seja validado, aloca o espaço necessário e copia 
                    o argumento dado para a variável correspondente na struct p(out_Completo)*/
                    p->out_Completo = Alloc(optarg);
                    break;
                }
            case 'm':
                if(optarg != NULL)                  /*Foi selecionada a opção -m com argumento seguinta não nulo*/
                {
                    for(i = 0; i < 9; i++)
                    {
                        /*Verifica que o argumento correspondente não é igual a um outro comando das opções de funcionamento*/
                        if(strcasecmp(optarg, options[i]) == 0)
                        {
                            /*Caso não seja validado, escreve a mensagem de erro e liberta a memória alocada até ao momento, saindo com erro do programa*/
                            fprintf(stdout, "Argumento invalido! '-m' espera um ficheiro.\n");
                            Free_Param(p);
                            free(v);
                            exit(EXIT_FAILURE);
                        }
                    }
                    /*Caso seja validado, aloca o espaço necessário e copia 
                    o argumento dado para a variável correspondente na struct p(out_Cursos)*/
                    p->out_Cursos = Alloc(optarg);
                    break;
                }
            case 'x':
                if(optarg != NULL)                  /*Foi selecionada a opção -x com argumento seguinta não nulo*/
                {
                    for(i = 0; i < 9; i++)
                    {
                        /*Verifica que o argumento correspondente não é igual a um outro comando das opções de funcionamento*/
                        if(strcasecmp(optarg, options[i]) == 0)
                        {
                            /*Caso não seja validado, escreve a mensagem de erro e liberta a memória alocada até ao momento, saindo com erro do programa*/
                            fprintf(stdout, "Argumento invalido! '-x' espera um ficheiro.\n");
                            Free_Param(p);
                            free(v);
                            exit(EXIT_FAILURE);
                        }
                    }
                    /*Caso seja validado, aloca o espaço necessário e copia 
                    o argumento dado para a variável correspondente na struct p(out_NC)*/
                    p->out_NC = Alloc(optarg);
                    break;
                }
            case '?':                               /*A opção recebida na linha de comando não corresponde a uma opção válida (unknown option)*/
                /*Escreve a mensagem de erro, e liberta a memória alocada até ao momento, saindo com erro do programa*/
                fprintf(stdout, "Argumento invalido! Faça -h para conhecer as opções disponiveis.\n");
                Free_Param(p);
                free(v);
                exit(EXIT_FAILURE);
            default:
                /*Se existir algum problema na obtenção da opções da linha de comandos é libertada a memória alocada até ao momento*/
                Free_Param(p);
                free(v);
                exit(EXIT_FAILURE);
        }
    }
    return;
}

/******************************************************************************
 * help ()
 *
 * ARGUMENTS:   (void)
 * 
 * RETURNS:     (void)
 *
 * DESCRIPTION: Escreve o manual de ajuda do programa.
 *****************************************************************************/
void help()
{
    fprintf(stdout, "\nOpcoes de funcionamento:\n\n");	
    fprintf(stdout, "-h               Ajuda para o utilizador.\n");
    fprintf(stdout, "-v valor         Numero de vagas a considerar em cada curson.\n");
    fprintf(stdout, "-n valor         Numero de candidatos a considerar da lista de candidatos.\n");
    fprintf(stdout, "-i filename      Nome do ficheiro entrada com lista de cursos.\n");
    fprintf(stdout, "-c filename      Nome do ficheiro de entrada com a lista de candidatos.\n");
    fprintf(stdout, "-o filename      Nome do ficheiro de saida com as colocacoes.\n");
    fprintf(stdout, "-u filename      Nome do ficheiro de saida com a lista de universidades e colocados.\n");
    fprintf(stdout, "-m filename      Nome do ficheiro de saida com a lista de cursos.\n");
    fprintf(stdout, "-x filename      Nome do ficheiro de saida com lista de nao colocados.\n\n");
    return;
}

/******************************************************************************
 * Alloc ()
 *
 * ARGUMENTS:   (char*) optarg  - paramêtro lido da linha de comandos
 * 
 * RETURNS:     (char*) file_nm - nome do ficheiro a ser guardado
 *
 * DESCRIPTION: Aloca memória dinâmica e guarda o nome do ficheiro.
 *****************************************************************************/
char *Alloc(char *optarg)
{
    char *file_nm;                                              /*Char pointer onde vai ser guardado o argumento recebido na linha de comandos*/

    file_nm = (char*)malloc((strlen(optarg)+1)*sizeof(char));   /*Aloca a memória necessária ao tamanho do argumento dado*/
    if(file_nm == NULL)                                         /*Verifica se houve problemas a alocar o espaço para a variável*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(file_nm, optarg);                                    /*Copia a variável dada no terminal para o programa*/
    return file_nm;                                             /*Retorna a variável (vai ser colocada na struct dos parâmetros iniciais(p))*/
}

/******************************************************************************
 * Completa_param ()
 *
 * ARGUMENTS:   (param*) p - ponteiro para a struct com os parâmetros iniciais 
 *                           do problema (ficheiros, nº de vagas e nº máx. de candidaos)
 * 
 * RETURNS:     (void)
 *
 * DESCRIPTION: Completa a estrutura p com as alternativas aos paramêtros da
 *              linha de comandos, caso estes não tenham sido atribuidos.
 *****************************************************************************/
void Completa_param(param *p)
{
    if(p->in_cursos == NULL)                                /*Verifica se foi dado um ficheiro específico com os cursos no terminal*/
    {
        /*Caso não tenha sido dado, usar o predefinifo ("cursos.csv")*/
        p->in_cursos = (char*)malloc((strlen("cursos.csv")+1)*sizeof(char));
        if(p->in_cursos == NULL)                            /*Verifica se houve problemas a alocar o espaço para o file_name*/
        {
            fprintf(stdout, "Erro na alocacao de memoria!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(p->in_cursos, "cursos.csv");                 /*Guarda o file_name na estrutura com os parâmetros iniciais (p)*/
    }
    if(p->in_candidatos == NULL)                            /*Verifica se foi dado um ficheiro específico com os candidatos no terminal*/
    {
        /*Caso não tenha sido dado, usar o predefinifo ("candidatos.csv")*/
        p->in_candidatos = (char*)malloc((strlen("candidatos.csv")+1)*sizeof(char));
        if(p->in_candidatos == NULL)                        /*Verifica se houve problemas a alocar o espaço para o file_name*/
        {
            fprintf(stdout, "Erro na alocacao de memoria!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(p->in_candidatos, "candidatos.csv");         /*Guarda o file_name na estrutura com os parâmetros iniciais (p)*/
    }
    if(p->out_Colocacoes == NULL)                           /*Verifica se foi dado um ficheiro de saída "Colocacoes" específico no terminal*/
    {
        /*Caso não tenha sido dado, usar o predefinifo ("CNAES_Colocacoes.csv")*/
        p->out_Colocacoes = (char*)malloc((strlen("CNAES_Colocacoes.csv")+1)*sizeof(char));
        if(p->out_Colocacoes == NULL)                       /*Verifica se houve problemas a alocar o espaço para o file_name*/
        {
            fprintf(stdout, "Erro na alocacao de memoria!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(p->out_Colocacoes, "CNAES_Colocacoes.csv");  /*Guarda o file_name na estrutura com os parâmetros iniciais (p)*/
    }
    if(p->out_Completo == NULL)                             /*Verifica se foi dado um ficheiro de saída "Completo" específico no terminal*/
    {
        /*Caso não tenha sido dado, usar o predefinifo ("CNAES_Completo.csv")*/
        p->out_Completo = (char*)malloc((strlen("CNAES_Completo.csv")+1)*sizeof(char));
        if(p->out_Completo == NULL)/*Verifica se houve problemas a alocar o espaço para o file_name*/
        {
            fprintf(stdout, "Erro na alocacao de memoria!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(p->out_Completo, "CNAES_Completo.csv");      /*Guarda o file_name na estrutura com os parâmetros iniciais (p)*/
    }
    if(p->out_Cursos == NULL)/*Verifica se foi dado um ficheiro de saída "Cursos" específico no terminal*/
    {
        /*Caso não tenha sido dado, usar o predefinifo ("CNAES_Cursos.csv")*/
        p->out_Cursos = (char*)malloc((strlen("CNAES_Cursos.csv")+1)*sizeof(char));
        if(p->out_Cursos == NULL)                           /*Verifica se houve problemas a alocar o espaço para o file_name*/
        {
            fprintf(stdout, "Erro na alocacao de memoria!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(p->out_Cursos, "CNAES_Cursos.csv");          /*Guarda o file_name na estrutura com os parâmetros iniciais (p)*/
    }
    if(p->out_NC == NULL)/*Verifica se foi dado um ficheiro de saída "NC" específico no terminal*/
    {
        /*Caso não tenha sido dado, usar o predefinifo ("CNAES_NC.csv")*/
        p->out_NC = (char*)malloc((strlen("CNAES_NC.csv")+1)*sizeof(char));
        if(p->out_NC == NULL)                               /*Verifica se houve problemas a alocar o espaço para o file_name*/
        {
            fprintf(stdout, "Erro na alocacao de memoria!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(p->out_NC, "CNAES_NC.csv");                  /*Guarda o file_name na estrutura com os parâmetros iniciais (p)*/
    }
    return;
}

/******************************************************************************
 * Free_Param ()
 *
 * ARGUMENTS:   (param*) p - ponteiro para a struct com os parâmetros iniciais 
 *                           do problema (ficheiros, nº de vagas e nº máx. de candidaos)
 * 
 * RETURNS:     (void)
 *
 * DESCRIPTION: Liberta a memória da estrutura que possui toda a informação
 *              sobre a interface de entrada/saida do programa.
 *****************************************************************************/
void Free_Param(param *p)
{
    /*Liberta a memória alocada pelas varias variáveis da estrutura dos parâmetros iniciais(p), 
    antes de libertar a memória alocada para a mesma*/
    if(p->in_candidatos != NULL) free(p->in_candidatos);
    if(p->in_cursos != NULL) free(p->in_cursos);
    if(p->out_Colocacoes != NULL) free(p->out_Colocacoes);
    if(p->out_Completo != NULL) free(p->out_Completo);
    if(p->out_Cursos != NULL) free(p->out_Cursos);
    if(p->out_NC != NULL) free(p->out_NC);
    free(p);
    return;
}