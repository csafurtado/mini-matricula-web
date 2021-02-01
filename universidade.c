#include "universidade.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Funções de instanciação dos tipos:

LISTA_ALUNOS *cria_lista_alunos(){
    LISTA_ALUNOS *lista_alunos = (LISTA_ALUNOS *) malloc(sizeof(LISTA_ALUNOS));
    if(lista_alunos == NULL)    exit(1);

    lista_alunos->head = NULL;
    lista_alunos->qtdAlunos = 0;

    return lista_alunos;
}

ALUNO *cria_aluno(){
    ALUNO *aluno = (ALUNO *) malloc(sizeof(ALUNO));
    if(aluno == NULL)   exit(1);

    aluno->nome = (char *) malloc(30 * sizeof(char));
    aluno->sobrenome = (char *) malloc(100 * sizeof(char));
    aluno->matricula = (char *) malloc(10 * sizeof(char));
    aluno->email = (char *) malloc(100 * sizeof(char));
    aluno->disciplinas = cria_lista_disciplinas();
    aluno->prox = NULL;

    return aluno;
}

LISTA_DISCIPLINAS *cria_lista_disciplinas(){
    LISTA_DISCIPLINAS *lista_disciplinas = (LISTA_DISCIPLINAS *) malloc(sizeof(LISTA_DISCIPLINAS));
    if(lista_disciplinas == NULL)   exit(1);

    lista_disciplinas->head = NULL;
    lista_disciplinas->qtdDisciplinas = 0;
    
    return lista_disciplinas;
}

DISCIPLINA *cria_disciplina(){
    DISCIPLINA *disciplina = (DISCIPLINA *) malloc(sizeof(DISCIPLINA));
    if(disciplina == NULL)  exit(1);
    
    disciplina->mencao = 0;
    disciplina->nome_disciplina = (char *) malloc(50 * sizeof(char));
    disciplina->prox = NULL;

    return disciplina;
}


//Funções auxiliares:


int lista_alunos_vazia(LISTA_ALUNOS *lista_alunos){
    if(lista_alunos->qtdAlunos == 0){
        printf("\nNao ha alunos cadastrados\n");
        return 1;
    }
    else
        return 0;
}

int lista_disciplina_vazia(ALUNO *aluno){
    if(aluno->disciplinas->qtdDisciplinas == 0){
        printf("\n\nAluno nao possui disciplinas cadastradas\n");
        return 1;
    }
    else
        return 0;
}

char *mencao_real(float mencao){
    if(mencao == 0.0f)
        return "SR";
    if(mencao > 0.0f && mencao < 3.0f)
        return "II";
    if(mencao >= 3.0f && mencao < 5.0f)
        return "MI";
    if(mencao >= 5.0f && mencao < 7.0f)
        return "MM";
    if(mencao >= 7.0f && mencao < 8.5f)
        return "MS";
    if(mencao >= 8.5f && mencao <= 10.0)
        return "SS";
    if(mencao == -1)
        return "TR";
}

int indice_aluno(LISTA_ALUNOS *lista_alunos, ALUNO *aluno){
    ALUNO *aux = lista_alunos->head;
    int i = lista_alunos->qtdAlunos;

    while(aux != NULL){
        if(aux == aluno)
            return i;
        aux = aux->prox;
        i--;
    }
}

ALUNO *posicao_aluno(LISTA_ALUNOS *lista_alunos, int pos){
    if(lista_alunos_vazia(lista_alunos))
        return NULL;
    
    ALUNO *aux = lista_alunos->head;   
    for(int i=lista_alunos->qtdAlunos; i>pos; i--){
        aux = aux->prox; 
    }
    return aux;
}

int indice_disciplina(ALUNO *aluno, DISCIPLINA *disciplina){
    DISCIPLINA *aux = aluno->disciplinas->head;
    int i = aluno->disciplinas->qtdDisciplinas;

    while(aux != NULL){
        if(aux == disciplina)
            return i;
        aux = aux->prox;
        i--;
    }
}

DISCIPLINA *posicao_disciplina(ALUNO *aluno, int pos){
    if(lista_disciplina_vazia(aluno))
        return NULL;
    
    DISCIPLINA *aux = aluno->disciplinas->head;   
    for(int i=aluno->disciplinas->qtdDisciplinas; i>pos; i--){
        aux = aux->prox; 
    }
    return aux;
}

void liberar_lista_alunos(LISTA_ALUNOS *lista_alunos){
    ALUNO *aux1 = lista_alunos->head;
    ALUNO *aux2;

    while(aux1 != NULL){
        aux2 = aux1;
        aux1 = aux1->prox;
        free(aux2);
    }
    free(lista_alunos);
}


//Funções do menu principal:

ALUNO *pesquisar_aluno(LISTA_ALUNOS *lista_alunos){    
    char op;

    if(lista_alunos->qtdAlunos == 1)
        return lista_alunos->head;

    printf("Deseja procurar o aluno pelo nome, email ou indice?\n\n'1' para nome\n'2' para email\n'3' para indice\n\n");
    scanf(" %c", &op);

    while(op != '1' && op != '2' && op != '3'){
        printf("\nOpcao incorreta. Tente novamente.\n");
        scanf(" %c", &op);
    }
        
    switch (op){
        case '1':
            {
            char *nome_pesquisa = (char *) malloc(30 * sizeof(char));

            printf("\nDigite o primeiro nome pra pesquisa:\t");
            scanf(" %[^\n]s", nome_pesquisa);

            ALUNO *aux = lista_alunos->head;
            int *iguais = (int *) malloc(sizeof(int));                          // vetor que vai guardar as posições dos alunos que possuem parte do nome da pesquisa. Esta função será case-sensitive
            int j = 0,  add = 0;                                                // j é o tamanho do vetor 'iguais', 'add' é a váriavel que definirá se tal posição será adicionada ou não no vetor.

            while(aux != NULL){
                for(int i=0; i<strlen(nome_pesquisa); i++){
                    if(aux->nome[i] != nome_pesquisa[i]){
                        add = 0;
                        break;
                    }
                    add = 1;
                }

                if(add){
                    iguais[j] = indice_aluno(lista_alunos, aux);
                    iguais = (int *) realloc(iguais, (j+1) * sizeof(int));
                    j++;
                }

                aux = aux->prox;
            }

            if(j == 0){
                printf("\n\nAluno não encontrado!\n\n");
                free(iguais);
                return NULL;
            }

            if(j == 1){
                return posicao_aluno(lista_alunos, iguais[0]);
            }

            system("clear");

            printf("\nAlunos encontrados!");
            printf("\n\nQuais desses alunos deseja escolher?\n\n");

            for(int i=0; i<j; i++){
                ALUNO *pp = posicao_aluno(lista_alunos, iguais[i]);                 // Alunos que possuem o nome de pesquisa;
                
                printf("\n-------------OPCAO %d--------------------\n", i+1);
                printf("Nome completo: %s %s\n", pp->nome, pp->sobrenome);
                printf("Matricula: %s\n", pp->matricula);
                printf("\n");
            }

            int escolha;

            printf("\nDigite a opcao para escolher o aluno:\t");
            scanf(" %d", &escolha);

            while(escolha <= 0 || escolha > j){
                printf("Numero invalido! Tente novamente!\n");
                scanf(" %d", &escolha);                
            }

            for(int i=0; i<j; i++){
                if(i == (escolha-1)){
                    printf("\n\nAluno encontrado!\n\n");
                    return posicao_aluno(lista_alunos, iguais[i]);
                }
            }            
            
            }
            break;
            
        case '2':
            {
            char *email_pesquisa = (char *) malloc(100 * sizeof(char));

            printf("\nDigite o email pra pesquisa:\t");
            scanf(" %[^\n]s", email_pesquisa);

            ALUNO *aux = lista_alunos->head;

            while(aux != NULL){
                if(!strcmp(email_pesquisa, aux->email)){
                    printf("\n\nAluno encontrado!\n\n");
                    return aux;
                }
                aux = aux->prox;
            }

            printf("\n\nAluno não encontrado!\n\n");
            return NULL;
            }
            break;
        
        case '3':
            {
            int indice_pesquisa;

            printf("\nQuantidade de alunos cadastrados: %d\n", lista_alunos->qtdAlunos);
            printf("\nDigite por qual indice procurar:\t");
            scanf(" %d", &indice_pesquisa);

            while(indice_pesquisa <= 0 || indice_pesquisa > lista_alunos->qtdAlunos){
                printf("\nOpcao invalida! Tente novamente:\t");
                scanf(" %d", &indice_pesquisa);
            }

            ALUNO *aux = lista_alunos->head;

            for(int i=lista_alunos->qtdAlunos; i >= 0; i--){
                if(i == indice_pesquisa){
                    printf("\nAluno encontrado!\n\n");
                    return aux;
                }
                aux = aux->prox;
            }

            }
            break;
        
        default:
            break;
    }
}

void cadastrar_aluno(LISTA_ALUNOS *lista_alunos, ALUNO *aluno){
    printf("Por favor digite os dados do aluno:\n\n");
    
    printf("Nome:\t");
    scanf(" %[^\n]s", aluno->nome);
    printf("\nSobrenome:\t");
    scanf(" %[^\n]s", aluno->sobrenome);
    printf("\nMatricula:\t");
    scanf(" %[^\n]s", aluno->matricula);
    printf("\nEmail:\t");
    scanf(" %[^\n]s", aluno->email);

    aluno->prox = lista_alunos->head;
    lista_alunos->head = aluno;
    lista_alunos->qtdAlunos++;

    printf("\n\nAluno cadastrado com sucesso!\n\n");
}

void listar_alunos(LISTA_ALUNOS *lista_alunos){
    if(lista_alunos_vazia(lista_alunos))
        return;

    ALUNO *aux = lista_alunos->head;
    
        printf("\n------------------------------------------------\n");
    
    while(aux != NULL){
        printf("Indice do aluno: %d\n", indice_aluno(lista_alunos,aux));
        printf("Nome Completo: %s %s\n", aux->nome, aux->sobrenome);
        printf("Matricula: %s\n", aux->matricula);
        printf("Email: %s\n", aux->email);
        if(aux->disciplinas->qtdDisciplinas == 0) 
            printf("Histórico: Aluno sem disciplinas\n");
        else
            printf("Histórico: %d disciplina(s)\n", aux->disciplinas->qtdDisciplinas);
        
        printf("\n------------------------------------------------\n\n");

        aux = aux->prox;
    }
}

void editar_aluno(LISTA_ALUNOS *lista_alunos){
    if(lista_alunos_vazia(lista_alunos))
        return;
    
    ALUNO *aluno_p = pesquisar_aluno(lista_alunos);                                 // Variável que recebe o aluno pesquisado 
    if(aluno_p == NULL)
        return;

    printf("\n------------------------------------------------\n");
    printf("| Nome do aluno: %s %s|\n", aluno_p->nome, aluno_p->sobrenome);
    printf("| Matricula: %s |\n", aluno_p->matricula);
    printf("| Email: %s |\n", aluno_p->email);
    printf("------------------------------------------------\n\n");

    char *nome_novo = (char *) malloc(30 * sizeof(char));
    char *sobrenome_novo = (char *) malloc(100 * sizeof(char));
    char *matricula_nova = (char *) malloc(10 * sizeof(char));
    char *email_novo = (char *) malloc(100 * sizeof(char));

    printf("Insira o novo nome do aluno:\t");
    scanf(" %[^\n]s", nome_novo);
    printf("Insira o novo sobrenome do aluno:\t");
    scanf(" %[^\n]s", sobrenome_novo);
    printf("Insira a nova matricula do aluno:\t");
    scanf(" %[^\n]s", matricula_nova);
    printf("Insira o novo email do aluno:\t");
    scanf(" %[^\n]s", email_novo);

    strcpy(aluno_p->nome, nome_novo);
    strcpy(aluno_p->sobrenome, sobrenome_novo);
    strcpy(aluno_p->matricula, matricula_nova);
    strcpy(aluno_p->email, email_novo);

    printf("\n\nDados do aluno alterados com sucesso!\n");
}

void excluir_aluno(LISTA_ALUNOS *lista_alunos){
    if(lista_alunos_vazia(lista_alunos))
    return;

    if(lista_alunos->qtdAlunos == 1){
        ALUNO *aluno_p = lista_alunos->head;
        
        printf("\nDados do Aluno:\n\n");                        
        printf("------------------------------------------------\n");
        printf("| Nome do aluno: %s %s|\n", aluno_p->nome, aluno_p->sobrenome);
        printf("| Matricula: %s |\n", aluno_p->matricula);
        printf("| Email: %s |\n", aluno_p->email);
        printf("------------------------------------------------\n");
        
        char del;
        
        printf("\nDeseja deletar esse aluno? Aperte 'Y' para confirmar, senão insira qualquer outro caracter.\t");
        scanf(" %c", &del);

        if(del != 'Y' && del != 'y'){
            printf("\nAluno não deletado!\n\nVoltando ao menu principal...\n");
            return;
        }
        
        lista_alunos->head = NULL;
        lista_alunos->qtdAlunos--;
        
        free(aluno_p);   
        
        printf("\nCadastro deletado com sucesso!\n");
        return;
    }

    ALUNO *aluno_p = pesquisar_aluno(lista_alunos);
    if(aluno_p == NULL){
        return;
    }

    if(lista_alunos->head == aluno_p){
        printf("\nDados do Aluno:\n\n");                        
        printf("------------------------------------------------\n");
        printf("| Nome do aluno: %s %s|\n", aluno_p->nome, aluno_p->sobrenome);
        printf("| Matricula: %s |\n", aluno_p->matricula);
        printf("| Email: %s |\n", aluno_p->email);
        printf("------------------------------------------------\n");
        
        char del;
        
        printf("Deseja deletar esse aluno? Aperte 'Y' para confirmar, senão insira qualquer outro caracter.\t");
        scanf(" %c", &del);

        if(del != 'Y' && del != 'y'){
            printf("\nAluno não deletado!\nVoltando ao menu principal...\n");
            return;
        }
        
        lista_alunos->head = aluno_p->prox;
        free(aluno_p);
        lista_alunos->qtdAlunos--;
        
        printf("\nCadastro deletado com sucesso!\n");
        return;
    }

    ALUNO *ant_aluno_p = posicao_aluno(lista_alunos, indice_aluno(lista_alunos, aluno_p)+1);

    printf("\nDados do Aluno:\n\n");                        
    printf("------------------------------------------------\n");
    printf("| Nome do aluno: %s %s|\n", aluno_p->nome, aluno_p->sobrenome);
    printf("| Matricula: %s |\n", aluno_p->matricula);
    printf("| Email: %s |\n", aluno_p->email);
    printf("------------------------------------------------\n");
        
    char del;
        
    printf("Deseja deletar esse aluno? Aperte 'Y' para confirmar, senão insira qualquer outro caracter.\t");
    scanf(" %c", &del);

    if(del != 'Y' && del != 'y'){
        printf("\nAluno não deletado!\nVoltando ao menu principal...\n");
        return;
    }

    ant_aluno_p->prox = aluno_p->prox;
    free(aluno_p);
    lista_alunos->qtdAlunos--;

    printf("\nCadastro deletado com sucesso!\n");
}


//Funções do menu do aluno

DISCIPLINA *pesquisar_disciplina(ALUNO *aluno){
    if(lista_disciplina_vazia(aluno))
        return NULL;

    if(aluno->disciplinas->qtdDisciplinas == 1)
        return aluno->disciplinas->head;

    char op;

    printf("Deseja procurar a disciplina pelo nome ou indice?\n\n'1' para nome\n'2' para indice\n\n");
    scanf(" %c", &op);

    while(op != '1' && op != '2'){
        printf("\nOpcao incorreta. Tente novamente.\n");
        scanf(" %c", &op);
    }
        
    switch (op){
        case '1':
                    {
            char *nome_pesquisa = (char *) malloc(30 * sizeof(char));

            printf("\nDigite o primeiro nome pra pesquisa:\t");
            scanf(" %[^\n]s", nome_pesquisa);

            DISCIPLINA *aux = aluno->disciplinas->head;
            int *iguais = (int *) malloc(sizeof(int));                          // vetor que vai guardar as posições das disciplinas que possuem parte do nome da pesquisa.  Esta função será case-sensitive
            int j = 0,  add = 0;                                                // j é o tamanho do vetor 'iguais', 'add' é a váriavel que definirá se tal posição será adicionada ou não no vetor.

            while(aux != NULL){
                for(int i=0; i<strlen(nome_pesquisa); i++){
                    if(aux->nome_disciplina[i] != nome_pesquisa[i]){
                        add = 0;
                        break;
                    }
                    add = 1;
                }

                if(add){
                    iguais[j] = indice_disciplina(aluno, aux);
                    iguais = (int *) realloc(iguais, (j+1) * sizeof(int));
                    j++;
                }

                aux = aux->prox;
            }

            if(j == 0){
                printf("\n\nDisciplina não encontrada!\n\n");
                free(iguais);
                return NULL;
            }

            if(j == 1){
                return posicao_disciplina(aluno, iguais[0]);
            }

            system("clear");

            printf("\nDisciplinas encontrados!");
            printf("\n\nQuais dessas disciplinas deseja escolher?\n\n");

            for(int i=0; i<j; i++){
                DISCIPLINA *pp = posicao_disciplina(aluno, iguais[i]);                 // Disciplinas que possuem o nome de pesquisa;
                
                printf("\n-------------OPCAO %d--------------------\n", i+1);
                printf("Nome da disciplina: %s\n", pp->nome_disciplina);
                printf("Mencao: %s\n", mencao_real(pp->mencao));
                printf("\n");
            }

            int escolha;

            printf("\nDigite a opcao para a escolha da disciplina:\t");
            scanf(" %d", &escolha);

            while(escolha <= 0 || escolha > j){
                printf("Numero invalido! Tente novamente!\n");
                scanf(" %d", &escolha);                
            }

            for(int i=0; i<j; i++){
                if(i == (escolha-1)){
                    printf("\n\nDisciplina encontrada!\n\n");
                    return posicao_disciplina(aluno, iguais[i]);
                }
            }            
            
            }
            break;
            
        case '2':
            {
            int indice_pesquisa;

            printf("\nQuantidade de disciplinas cadastradas: %d\n", aluno->disciplinas->qtdDisciplinas);
            printf("\nDigite por qual indice procurar:\t");
            scanf(" %d", &indice_pesquisa);

            while(indice_pesquisa <= 0 || indice_pesquisa > aluno->disciplinas->qtdDisciplinas){
                printf("\nOpcao invalida! Tente novamente:\t");
                scanf(" %d", &indice_pesquisa);
            }

            DISCIPLINA *aux = aluno->disciplinas->head;

            for(int i=aluno->disciplinas->qtdDisciplinas; i >= 0; i--){
                if(i == indice_pesquisa){
                    printf("\nDisciplina encontrada!\n\n");
                    return aux;
                }
                aux = aux->prox;
            }

            }
            break;
        
        default:
            break;
    } 
}

void cadastrar_disciplina(ALUNO *aluno){
    char *nome_disciplina_nova = (char *) malloc(50 * sizeof(char));
    float mencao_disciplina;

    if(nome_disciplina_nova == NULL)    exit(1);
    
    printf("Nome da disciplina:\t");
    scanf(" %[^\n]s", nome_disciplina_nova);    
    printf("Nota obtida: (Insira -1 para TR)\t");
    scanf(" %f", &mencao_disciplina);

    while((mencao_disciplina > -1 && mencao_disciplina < 0  || mencao_disciplina < -1) || mencao_disciplina > 10){
        printf("\nNota invalida! Tente novamente.\n");
        printf("Nota obtida:\t");
        scanf(" %f", &mencao_disciplina);
    }
    
    DISCIPLINA *aux = cria_disciplina();
    if(aux == NULL)    exit(1);
    
    strcpy(aux->nome_disciplina, nome_disciplina_nova);   
    aux->mencao = mencao_disciplina;

    aux->prox = aluno->disciplinas->head;
    aluno->disciplinas->head = aux;
    aluno->disciplinas->qtdDisciplinas++;

    free(nome_disciplina_nova);
}

void listar_disciplinas(ALUNO *aluno){
    DISCIPLINA *aux = aluno->disciplinas->head;

    if(lista_disciplina_vazia(aluno))
        return;
    
    while(aux != NULL){
        printf("Disciplina: %s \n", aux->nome_disciplina);
        printf("Mencao: %s\n\n", mencao_real(aux->mencao));
        aux = aux->prox;
    }
}

void editar_disciplina(ALUNO *aluno){
    if(lista_disciplina_vazia(aluno)) 
        return;
    
    DISCIPLINA *disciplina_p = pesquisar_disciplina(aluno);                 // Variável que recebe a disciplina pesquisada
    if(disciplina_p == NULL)    
        return;

    float nova_mencao;

    printf("\n-----------------------------------------\n");
    printf("Disciplina: %s\n", disciplina_p->nome_disciplina);
    printf("Mencao: %s", mencao_real(disciplina_p->mencao));
    printf("\n-----------------------------------------\n");
    
    printf("\n\nDigite o novo nome da disciplina:\t");
    scanf(" %[^\n]s", disciplina_p->nome_disciplina);
    printf("Digite a nova mencao:\t");
    scanf(" %f", &nova_mencao);

    while((nova_mencao > -1 && nova_mencao < 0 || nova_mencao < -1) || nova_mencao > 10){
        printf("\nNota invalida! Tente novamente.\n");
        printf("Nota obtida:\t");
        scanf(" %f", &nova_mencao);
    }

    disciplina_p->mencao = nova_mencao;

    printf("\n\nDisciplina editada com sucesso!\n");
    
    return;
}

void excluir_disciplina(ALUNO *aluno){

    if(lista_disciplina_vazia(aluno))
    return;

    if(aluno->disciplinas->qtdDisciplinas == 1){
        DISCIPLINA *aux = aluno->disciplinas->head;
        
        printf("\nDisciplina escolhida:\n\n");                        
        printf("------------------------------------------------\n");
        printf("| Nome: %s |\n", aux->nome_disciplina);
        printf("| Mencao do aluno: %s |\n", mencao_real(aux->mencao));
        printf("------------------------------------------------\n\n");
        
        char del;

        printf("Deseja deletar esta disciplina? Digite 'Y' para sim ou qualquer outra tecla para não.\n");
        scanf(" %c", &del);

    if(del != 'Y' && del != 'y'){
        printf("\nDisciplina não foi excluida! Voltando ao menu do aluno...\n");
        return;
    }

        aluno->disciplinas->head = NULL;
        aluno->disciplinas->qtdDisciplinas--;
        
        free(aux);   
        
        printf("\nDisciplina deletada com sucesso!\n");
        return;
    }

    DISCIPLINA *disciplina_p = pesquisar_disciplina(aluno);
    if(disciplina_p == NULL){
        printf("\nDisciplina nao encontrada!\n");
        return;
    }

    if(aluno->disciplinas->head == disciplina_p){                       
        printf("\n------------------------------------------------\n");
        printf("| Nome: %s |\n", disciplina_p->nome_disciplina);
        printf("| Mencao do aluno: %s |\n", mencao_real(disciplina_p->mencao));
        printf("------------------------------------------------\n\n");
        
        char del;

        printf("Deseja deletar esta disciplina? Digite 'Y' para sim ou qualquer outra tecla para não.\n");
        scanf(" %c", &del);

    if(del != 'Y' && del != 'y'){
        printf("\nDisciplina não foi excluida! Voltando ao menu do aluno...\n");
        return;
    }
        
        aluno->disciplinas->head = disciplina_p->prox;
        free(disciplina_p);
        aluno->disciplinas->qtdDisciplinas--;
        
        printf("\nCadastro deletado com sucesso!\n");
        return;
    }

    DISCIPLINA *ant_disciplina_p = posicao_disciplina(aluno, indice_disciplina(aluno, (disciplina_p))+1);

    printf("\nDisciplina escolhida:\n\n");                        
    printf("------------------------------------------------\n");
    printf("| Nome: %s |\n", disciplina_p->nome_disciplina);
    printf("| Mencao do aluno: %s |\n", mencao_real(disciplina_p->mencao));
    printf("------------------------------------------------\n\n");
        
    char del;

    printf("Deseja deletar esta disciplina? Digite 'Y' para sim ou qualquer outra tecla para não.\n");
    scanf(" %c", &del);

    if(del != 'Y' && del != 'y'){
        printf("\nDisciplina não foi excluida! Voltando ao menu do aluno...\n");
        return;
    }

    ant_disciplina_p->prox = disciplina_p->prox;
    free(disciplina_p);
    aluno->disciplinas->qtdDisciplinas--;

    printf("\nDisciplina deletada com sucesso!\n");
}

void filtrar_disciplinas(ALUNO *aluno){
    if(lista_disciplina_vazia(aluno))
        return;
    
    DISCIPLINA *aux = aluno->disciplinas->head;
    int *disciplinas_mencoes = (int *) malloc(sizeof(int));
    int Ss = 0, Ms = 0, Mm = 0, Mi = 0, Ii = 0, Sr = 0, Tr = 0, j = 0;

    while(aux != NULL){
        char *mencao_comp = mencao_real(aux->mencao);

        if(!strcmp(mencao_comp, "SS")){
            disciplinas_mencoes[j] = indice_disciplina(aluno, aux);
            disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, (j+1) * sizeof(int));
            j++;
        }
        aux = aux->prox;
    }

    printf("\n");

    printf("Disciplinas com SS:\n\n");
    
    if(j != 0){
        for(int i=0; i<j; i++){
            printf("--> %s\n", posicao_disciplina(aluno, disciplinas_mencoes[i])->nome_disciplina);
        }
    }
    else{
        printf("(nenhuma disciplina)\n");
    }

    disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, sizeof(int));
    j = 0;
    aux = aluno->disciplinas->head;

    printf("\n");

    while(aux != NULL){
        char *mencao_comp = mencao_real(aux->mencao);

        if(!strcmp(mencao_comp, "MS")){
            disciplinas_mencoes[j] = indice_disciplina(aluno, aux);
            disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, (j+1) * sizeof(int));
            j++;
        }
        aux = aux->prox;
    }

    printf("Disciplinas com MS:\n\n");
    
    if(j != 0){
        for(int i=0; i<j; i++){
            printf("--> %s\n", posicao_disciplina(aluno, disciplinas_mencoes[i])->nome_disciplina);
        }
    }
    else{
        printf("(nenhuma disciplina)\n");
    }

    printf("\n");
   
    disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, sizeof(int));
    j = 0;
    aux = aluno->disciplinas->head;

    while(aux != NULL){
        char *mencao_comp = mencao_real(aux->mencao);

        if(!strcmp(mencao_comp, "MM")){
            disciplinas_mencoes[j] = indice_disciplina(aluno, aux);
            disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, (j+1) * sizeof(int));
            j++;
        }
        aux = aux->prox;
    }

    printf("Disciplinas com MM:\n\n");
    
    if(j != 0){
        for(int i=0; i<j; i++){
            printf("--> %s\n", posicao_disciplina(aluno, disciplinas_mencoes[i])->nome_disciplina);
        }
    }
    else{
        printf("(nenhuma disciplina)\n");
    }

    printf("\n");

    disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, sizeof(int));
    j = 0;    
    aux = aluno->disciplinas->head;

    while(aux != NULL){
        char *mencao_comp = mencao_real(aux->mencao);

        if(!strcmp(mencao_comp, "MI")){
            disciplinas_mencoes[j] = indice_disciplina(aluno, aux);
            disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, (j+1) * sizeof(int));
            j++;
        }
        aux = aux->prox;
    }

    printf("Disciplinas com MI:\n\n");
    
    if(j != 0){
        for(int i=0; i<j; i++){
            printf("--> %s\n", posicao_disciplina(aluno, disciplinas_mencoes[i])->nome_disciplina);
        }
    }
    else{
        printf("(nenhuma disciplina)\n");
    }

    printf("\n");

    disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, sizeof(int));
    j = 0;
    aux = aluno->disciplinas->head;

    while(aux != NULL){
        char *mencao_comp = mencao_real(aux->mencao);

        if(!strcmp(mencao_comp, "II")){
            disciplinas_mencoes[j] = indice_disciplina(aluno, aux);
            disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, (j+1) * sizeof(int));
            j++;
        }
        aux = aux->prox;
    }

    printf("Disciplinas com II:\n\n");
    
    if(j != 0){
        for(int i=0; i<j; i++){
            printf("--> %s\n", posicao_disciplina(aluno, disciplinas_mencoes[i])->nome_disciplina);
        }
    }
    else{
        printf("(nenhuma disciplina)\n");
    }

    printf("\n");

    disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, sizeof(int));
    j = 0;
    aux = aluno->disciplinas->head;

    while(aux != NULL){
        char *mencao_comp = mencao_real(aux->mencao);

        if(!strcmp(mencao_comp, "SR")){
            disciplinas_mencoes[j] = indice_disciplina(aluno, aux);
            disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, (j+1) * sizeof(int));
            j++;
        }
        aux = aux->prox;
    }

    printf("Disciplinas com SR:\n\n");
    
    if(j != 0){
        for(int i=0; i<j; i++){
            printf("--> %s\n", posicao_disciplina(aluno, disciplinas_mencoes[i])->nome_disciplina);
        }
    }
    else{
        printf("(nenhuma disciplina)\n");
    }

    printf("\n");

    disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, sizeof(int));
    j = 0;
    aux = aluno->disciplinas->head;

    while(aux != NULL){
        char *mencao_comp = mencao_real(aux->mencao);

        if(!strcmp(mencao_comp, "TR")){
            disciplinas_mencoes[j] = indice_disciplina(aluno, aux);
            disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, (j+1) * sizeof(int));
            j++;
        }
        aux = aux->prox;
    }

    printf("Disciplinas Trancadas:\n\n");
    
    if(j != 0){
        for(int i=0; i<j; i++){
            printf("--> %s\n", posicao_disciplina(aluno, disciplinas_mencoes[i])->nome_disciplina);
        }
    }
    else{
        printf("(nenhuma disciplina)\n");
    }

    printf("\n");

    disciplinas_mencoes = (int *) realloc(disciplinas_mencoes, sizeof(int));
    j = 0;
    aux = aluno->disciplinas->head;

    while(aux != NULL){
        char *mencao_comp = mencao_real(aux->mencao);

        if(!strcmp(mencao_comp, "SS"))
            Ss++;
        if(!strcmp(mencao_comp, "MS"))
            Ms++;
        if(!strcmp(mencao_comp, "MM"))
            Mm++;
        if(!strcmp(mencao_comp, "MI"))
            Mi++;
        if(!strcmp(mencao_comp, "II"))
            Ii++;
        if(!strcmp(mencao_comp, "SR"))
            Sr++;
        if(!strcmp(mencao_comp, "TR"))
            Tr++;
        
        aux = aux->prox;
    }

    printf("\nTotal de menções: %d\n\nSS: %d  MS: %d  MM: %d\nMI: %d  II: %d  SR: %d\nTR: %d\n",aluno->disciplinas->qtdDisciplinas ,Ss, Ms, Mm, Mi, Ii, Sr, Tr);
    free(disciplinas_mencoes);
}

void apresentar_relatorio(ALUNO *aluno){
    if(lista_disciplina_vazia(aluno)){
        printf("\nNao e possivel apresentar o relatorio do aluno.\n");
        return;
    }
    
    int AP = 0, RP = 0, TR = 0;

    DISCIPLINA *aux = aluno->disciplinas->head;

    while(aux != NULL){
        if(aux->mencao < 5.0 && aux->mencao >= 0)
            RP++;
        if(aux->mencao >= 5.0)
            AP++;
        if(aux->mencao < 0)
            TR++;

        aux = aux->prox;
    }

    printf("Aluno: %s %s\n", aluno->nome, aluno->sobrenome);
    printf("------------------------------------------------\n");
    printf("\nDisciplinas cursadas: %d\n", aluno->disciplinas->qtdDisciplinas);
    printf("\nAprovacoes: %d\nReprovacoes: %d\nTrancamentos: %d\n", AP, RP, TR);
}