/******************************************************************************
 * (C) Projeto Programação 2022/2023
 * 
 * AUTHORS: Francisco Apolinário, Rodrigo Sereno 
 *
 * NAME: candidatos.c
 *
 * DESCRIPTION: Este ficheiro .c apresenta todas as funções associadas aos candidatos.
 *              Tais como, funções para leitura de ficheiros e alocação dinâmica de
 *              memória.
 ******************************************************************************/
#include "candidatos.h"

/***************************************************************************************
 * Read_candidato ()
 *
 * ARGUMENTS:   (param*) p - ponteiro para a struct com os parâmetros iniciais 
 *                           do problema (ficheiros, nº de vagas e nº máx. de candidaos)
 *              (var*)   v - pointeiro para a struct com os parâmetros variáveis 
 *                           (candidatos, cursos, e nº de cursos)
 * 
 * RETURNS:     (void) 
 *
 * DESCRIPTION: Lê o ficheiro que contém a informação sobre os candidatos e 
 *              e guarda essa informação nos nós de uma lista simplesmente
 *              ligada.
 **************************************************************************************/
void Read_candidato(param *p, var *v)
{
    FILE *fp = fopen(p->in_candidatos, "r");                            /*File pointer usado para ler o ficheiro de entrada com os candidatos*/
    char line[100];                                                     /*char return value usado para guardar a linha do ficheiro "candidatos"*/
    int num_cand = 0;                                                   /*int com o número máximo de candidatos, usado para o correto funcionamento da função*/

    if(fp == NULL)                                                      /*Verifica se o ficheiro foi aberto corretamente*/
    {
        fprintf(stdout, "Erro na abertura do ficheiro %s\n", p->in_candidatos);
        exit(EXIT_FAILURE);
    }

    if(fgets(line, sizeof(line), fp) == NULL) exit(EXIT_FAILURE);       /*Salta a 1ª linha do ficheiro contendo a legenda*/
    /*Enquanto não chega ao fim do ficheiro ou ao limite de candidatos permitido, lê as linhas do ficheiro "candidatos"*/
    while((fgets(line, sizeof(line), fp) != NULL) && (num_cand < p->num_candidatos))
    {
        v->candidatos = Adiciona_candidato(v->candidatos, line);        /*Adiciona uma struct candidatos com a informação lida*/
        num_cand++;/*Incrementa o nº de candidatos lidos do ficheiro*/
    }
    fclose(fp);                                                         /*Fecha o ficheiro*/
    return;
}

/********************************************************************************
 * Adiciona_candidato ()
 *
 * ARGUMENTS:   (candidatos*)   head - ponteiro para a cabeça da lista de candidatos
 *              (char*)         line - linha do ficheiro de entrada com os candidatos, 
 *                                     contendo a informação do candidato em processamento
 * 
 * RETURNS:     (candidatos*)   head - no caso de sucesso na inserção
 *                              NULL - no caso de insucesso na inserção
 *
 * DESCRIPTION: Adiciona o novo nó à lista e guarda nesse nó a informação sobre
 *              o novo candidato. A insersão é feita de forma a obter uma lista
 *              ordenada por nota de candidatura (decrescente), no caso das
 *              notas de candidatura serem iguais os candidatos ficam ordenados 
 *              por ordem de ID (crescente).
 ********************************************************************************/
candidatos *Adiciona_candidato(candidatos *head, char *line)
{
    /*Contador (i) usado no correto funcionamento da função 
    e int return values onde serão guardados o Identificador do candidato e os ID's das instituições das opções do candidato*/
    int i, ID_candidato, E[5];
    float Nt_PI, Nt_12, Nt_cand;                        /*float return values onde serão guardados as notas do candidato (Prova_Ingresso, 12º, Candidatura)*/
    char C[5][5];                                       /*char return valies onde serão guardadas os ID's das opções de curso do candidato*/
    for(i = 0; i < 5; i++) C[i][0] = '\0';              /*Inicialização da variável C[][]*/
    candidatos *new = NULL, *aux = NULL;                /*Novo candidato a ser adicionado (new) e auxiliar de tipo candidatos(struct pointer) 
                                                        para o correto uso de listas*/

    new = Aloca_candidatos();                           /*Chamada à função que realiza a alocação da memória para o novo candidato*/
    /*Leitura dos valores da linha correspondente ao candidato*/
    sscanf(line, "%d,%f,%f,%f,%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%s", &ID_candidato, &Nt_PI, 
           &Nt_12, &Nt_cand, &E[0], C[0], &E[1], C[1], &E[2], C[2], &E[3], C[3], &E[4], C[4]);

    new->ID_cand = ID_candidato;                        /*Guarda os vários valores correspondentes ao candidato em memória*/
    new->Nt_PI = Nt_PI;
    new->Nt_12 = Nt_12;
    new->Nt_Cand = Nt_cand;
    for(i = 0; i < 5; i++)
    {
        new -> E[i] = E[i];
        if((strcmp(C[i], "") == 0)) strcpy(new->C[i], "0000");  /*Caso não tenha sido dada opção de índice i, preencher com "0000"*/
        else strcpy(new->C[i], C[i]);                   /*Se foi dada opção, copiar o ID do curso para a struct do candidato*/
    }
    /*1º elemento da lista*/
    if(head == NULL) return new;/*A lista está a vazia, o novo candidato será a head*/
    /*Nota maior que a atual maior nota*/
    if(new->Nt_Cand > head->Nt_Cand)
    {
        new->next = head;
        return new;                                     /*O novo candidato toma a posição da anterior head, e substitui-a*/
    }
    /*Insere na posição correta (Nota de candidatura descendente) ao longo da lista*/
    aux = head;
    while(aux != NULL)
    {
        if(aux->next != NULL)                           /*Enquanto não chega ao último elemento da lista*/
        {
            if(aux->next->Nt_Cand < new->Nt_Cand)       /*Posição correta para inserção do candidato na lista*/
            {                                 
                new->next = aux->next;
                aux->next = new;
                return head;                            /*O novo candidato é inserido no meio da lista, a head anterior é retornada*/
            }
            if(new->Nt_Cand == aux->next->Nt_Cand)      /*No caso em que as notas são iguais*/
            {
                if(new->ID_cand < aux->next->ID_cand)   /*Vai ficar inserido por ID's de candidato crescente*/
                {
                    new->next = aux->next;
                    aux->next = new;
                    return head;
                }
            }
        }
        else                                            /*Não há mais elementos, inserir no fim da lista*/
        {
            aux->next = new;
            return head;                                /*O novo candidato é inserido no meio da lista, a head anterior é retornada*/
        }
        aux = aux -> next;
    }
    return NULL;                                        /*A insrção não ocorreu, retorna NULL*/
}
/******************************************************************************
 * Aloca_candidatos ()
 *
 * ARGUMENTS:   (void)            - a função não recebe argumentos
 * 
 * RETURNS:     (candidato*)  new - ponteiro para a struct candidatos alocada
 *
 * DESCRIPTION: Aloca a memória necessária para a o novo nó da lista e inicializa
 *              os parâmetros desse nó.
 * 
 *****************************************************************************/
candidatos *Aloca_candidatos()
{
    int i;                                              /*Contador usado no correto funcionamento do programa*/
    candidatos *new = NULL;                             /*Novo candidato para o qual vai ser alocada memória*/

    new = (candidatos*)malloc(sizeof(candidatos));      /*Aloca memória para a struct*/
    if(new == NULL)                                     /*Verifica se houve problemas a alocar a memória para a struct*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    new->E = (int*)malloc(5*sizeof(int));               /*Aloca memória para o vetor contendo os E's(ID's da instituição das opções do candidato)*/
    if(new->E == NULL)                                  /*Verifica se houve problemas a alocar a memória para o vetor*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }   
    new->C = (char**)malloc(5*sizeof(char*));           /*Aloca memória para o vetor (de strings) contendo os C's(ID's dos cursos das opções do candidato)*/
    if(new->C == NULL)                                  /*Verifica se houve problemas a alocar a memória para o vetor*/
    {
        fprintf(stdout, "Erro na alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < 5; i++)
    {
        new->C[i] = (char*)malloc(5*sizeof(char));      /*Aloca a memória necessária para cada string C*/       
        if(new->C[i] == NULL)                           /*Verifica se houve problemas a alocar a memória para cada uma das strings*/
        {
            fprintf(stdout, "Erro na alocacao de memoria!\n");
            exit(EXIT_FAILURE);
        }
        new->C[i][0] = '\0';                            /*Inicializa as strings C*/        
    }
    new->next = NULL;                                   /*Iniciliza o ponteiro next do candidato a NULL*/
    return new;                                         /*Retorna o candidato alocado*/
}

/******************************************************************************
 * Distribui_candidatos ()
 *
 * ARGUMENTS:   (var*) v - estrutura onde os vários cursos serão guardados
 * 
 * RETURNS:     (void) 
 * 
 * DESCRIPTION: Realiza a colocação dos vários candidatos nos cursos de 
 *              acordo com as opções de cada candidato
 *****************************************************************************/
void Distribui_candidatos(var *v)
{
    candidatos *aux = NULL, *next = NULL;               /*Auxiliares de tipo candidatos(struct) para facilitarem o uso de listas*/
    int i, escolha, colocado;                           /*Contadores (i, escolha) e flag(colocado) usados no correto funcionamento da função*/

    aux = v->candidatos;
    while(aux != NULL)                                  /*Corre os alunos todos até não sobrar nenhum*/
    {
        colocado = 0;                                   /*No início colocado = 0 (o aluno ainda não foi colocado)*/
        next = aux->next;
        for(escolha = 0; escolha < 5; escolha++)        /*Para cada candidato corre as suas 5 opções*/
        {
            for(i = 1; i < v->num_cursos; i++)          /*Para cada opção verifica todos os cursos na lista, não se considera a estrutura dos NC (0)*/
            {   
                /*Verifica se há correspondência entre a escolha do candidato e o curso da lista*/
                if((strcmp(aux->C[escolha], v->cursos[i]->ID_curso) == 0) && (aux->E[escolha] == v->cursos[i]->ID_inst))
                {
                    /*A flag colocado toma o valor de retorno da função Insere_aluno(1 se foi inserido, 0 caso contrário)*/
                    colocado = Insere_aluno(v->cursos[i], aux, escolha);
                    break;                              /*Passa para a próxima opção do candidato*/
                }
            }
            /*Se o aluno já foi colocado , não analisa as outras opções, e avança para o próximo candidato*/
            if(colocado == 1) break;
        }
        /*O candidato não entrou em nenhuma das suas 5 opções*/
        if(escolha == 5) Insere_NC(v->cursos[0], aux);
        aux = next;
    }
    return;
}
/******************************************************************************
 * Insere_aluno ()
 *
 * ARGUMENTS:   (cursos*)         curso - curso correspondente à opção do candidato
 *              (candidatos*) candidato - novo candidato a ser inserido no curso
 *              (int)           escolha - indice do vetor das opções do candidato
 * 
 * RETURNS:     (int)                 1 - caso o candidato seja colocado
 *                                    0 - caso o candidato não seja colocado
 *
 * DESCRIPTION: Verifica se o candidato pode ser colocado no curso, 
 *              caso possa, coloca-o. Esta colocação é feita através da 
 *              inserção no fim da lista.
 *****************************************************************************/
int Insere_aluno (cursos *curso, candidatos *candidato, int escolha)
{
    candidatos *aux = NULL;                             /*Auxiliar de tipo candidatos(struct) para facilitar o uso de listas*/

    if(curso->num_vagas > 0)                            /*Se o nº de vagas for maior que 0 é o curso pode ter alunos colocados*/
    {
        if(curso->aluno == NULL)                        /*Se o curso não tiver candidatos colocados ainda, o atual candidato é o 1º a ser colocado*/
        {
            candidato->opcao_in = escolha +1;           /*A opção de entrada do candidato é a escolha +1(escolha vai de 0 a 4, opção de 1 a 5)*/
            curso->aluno = candidato;
            curso->aluno->next = NULL;
            curso->num_coloc++;                         /*O número de colocados no curso incrementa*/
            return 1;                                   /*Retorna 1(colocado fica a 1 na função Dsitribui_candidatos)*/
        }
        else                                            /*Caso já haja candidatos colocados no curso*/
        {
            aux = curso->aluno;
            while(aux->next != NULL) aux = aux->next;   /*Corre a lista de colocados até chegar ao último (menor nota de candidatura)*/
            if(curso->num_coloc < curso->num_vagas)     /*Se ainda houverem vagas disponíveis no curso, o candidato é colocado*/
            {
                candidato->opcao_in = escolha +1;       /*A opção de entrada do candidato é a escolha +1(escolha vai de 0 a 4, opção de 1 a 5)*/
                aux->next = candidato;
                aux->next->next = NULL;
                curso->num_coloc++;                     /*O número de colocados no curso incrementa*/
                return 1;                               /*Retorna 1(colocado fica a 1 na função Dsitribui_candidatos)*/
            }
            else                                        /*Caso o nº de colocados for igual ou superios ao nº de vagas*/
            {
                /*Se o candidato tiver a mesma nota de candidatura 
                que o último colocado (menor nota) o candidato é colocado (não há critério de desempate)*/
                if(aux->Nt_Cand == candidato->Nt_Cand)
                {
                    candidato->opcao_in = escolha +1;   /*A opção de entrada do candidato é a escolha +1(escolha vai de 0 a 4, opção de 1 a 5)*/
                    aux->next = candidato;
                    aux->next->next = NULL;
                    curso->num_coloc++;                 /*O número de colocados no curso incrementa*/
                    return 1;                           /*Retorna 1(colocado fica a 1 na função Dsitribui_candidatos)*/
                }
                else return 0;                          /*Retorna 0(colocado fica a 0 na função Dsitribui_candidatos)*/
            }
        }
    }
    else return 0;                                      /*Retorna 0(colocado fica a 0 na função Dsitribui_candidatos)*/
}

/******************************************************************************
 * Insere_NC ()
 *
 * ARGUMENTS:   (cursos*)            NC - ponteiro para a lista de alunos 
 *                                        da struct NC(não colocados)
 *              (candidatos*) candidato - novo candidato a ser inserido nos NC
 * 
 * RETURNS:     (void)
 *
 * DESCRIPTION: Realiza inserção ordenada, por ID crescente, de um novo 
 *              candidato na lista dos não colocados.
 *****************************************************************************/
void Insere_NC(cursos *NC, candidatos *candidato)
{
    candidatos *aux1 = NULL, *aux2 = NULL;      /*Auxiliares de tipo candidatos(struct) para facilitarem o uso de listas*/
    
    /*Se ainda não houverem candidatos nos NC*/
    if(NC->aluno == NULL)
    {
        NC->aluno = candidato; 
        candidato->next = NULL;
    }
    else                                        /*Já há candidatos nos NC*/
    {
        /*Candidato tem um ID menor que o atual menor nos NC*/
        if(NC->aluno->ID_cand > candidato->ID_cand)
        {
            candidato->next = NC->aluno;
            NC->aluno = candidato;
        }
        else                                    /*Vai procurar a posição correta nos NC do candidato (ordenado por ID ascendente)*/
        {
            aux1 = NC->aluno;
            aux2 = NC->aluno->next;
            while((aux2 != NULL) && (aux2->ID_cand < candidato->ID_cand))
            {
                aux1 = aux2;
                aux2 = aux2 -> next;
            }
            /*É colocado o candidato quando encontrada a posição correta*/
            candidato -> next = aux2;
            aux1 -> next = candidato;
        }
    }
    return;
}