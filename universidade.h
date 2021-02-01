#ifndef UNIVERSIDADE_H
#define UNIVERSIDADE_H

typedef struct disciplina {
    char *nome_disciplina;
    float mencao;
    struct disciplina *prox;
} DISCIPLINA;

typedef struct lista_disciplinas{
    DISCIPLINA *head;
    int qtdDisciplinas;
} LISTA_DISCIPLINAS;

typedef struct aluno{
    char *nome;
    char *sobrenome;
    char *matricula;
    char *email;
    LISTA_DISCIPLINAS *disciplinas;
    struct aluno *prox;
} ALUNO;

typedef struct lista_alunos{
    ALUNO *head;
    int qtdAlunos;
} LISTA_ALUNOS;

// Funções para a criação 
LISTA_ALUNOS *cria_lista_alunos();
ALUNO *cria_aluno();
LISTA_DISCIPLINAS *cria_lista_disciplinas();
DISCIPLINA *cria_disciplina();

//Funções do menu principal
ALUNO *pesquisar_aluno(LISTA_ALUNOS *lista_alunos);
void cadastrar_aluno(LISTA_ALUNOS *lista_alunos, ALUNO *aluno);
void listar_alunos(LISTA_ALUNOS *lista_alunos);
void editar_aluno(LISTA_ALUNOS *lista_alunos);
void excluir_aluno(LISTA_ALUNOS *lista_alunos);

//Funções do menu do aluno
DISCIPLINA *pesquisar_disciplina(ALUNO *aluno);
void cadastrar_disciplina(ALUNO *aluno);
void listar_disciplinas(ALUNO *aluno);
void editar_disciplina(ALUNO *aluno);
void excluir_disciplina(ALUNO *aluno);
void filtrar_disciplinas(ALUNO *aluno);
void apresentar_relatorio(ALUNO *aluno);

//Funções Auxiliares
int indice_disciplina(ALUNO *aluno, DISCIPLINA *disciplina);
DISCIPLINA *posicao_disciplina(ALUNO *aluno, int pos);
int indice_aluno(LISTA_ALUNOS *lista_alunos, ALUNO *aluno);
ALUNO *posicao_aluno(LISTA_ALUNOS *lista_alunos, int pos);
int lista_alunos_vazia(LISTA_ALUNOS *lista_alunos);
int lista_disciplina_vazia(ALUNO *aluno);
char *mencao_real(float mencao);
void liberar_lista_alunos(LISTA_ALUNOS *lista_alunos);

#endif