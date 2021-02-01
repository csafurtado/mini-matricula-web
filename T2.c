#include <stdio.h>
#include <stdlib.h>
#include "universidade.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main(){

    int b = 1;
    int op;
    LISTA_ALUNOS *lista_alunos = cria_lista_alunos();

    while(b){

        system("clear");

        printf("************************************************\n");
        printf("\tMini Matricula Web\n");
        printf("************************************************\n");

        printf("\n\nEscolha a opcao desejada:\n\n");
        printf("1- Cadastrar novo aluno\n2- Listar alunos cadastrados\n3- Visualizar aluno\n4- Editar cadastro de um aluno\n5- Excluir aluno\n6- Sair do programa\n\n");

        scanf(" %d", &op);
        
        switch (op){
            case 1:
                {
                system("clear");
                printf("************************************************\n");
                printf("\tCadastrar Aluno\n");
                printf("************************************************\n\n");
                
                ALUNO *novo_aluno = cria_aluno();
                cadastrar_aluno(lista_alunos, novo_aluno);            
                
                sleep(1);
                }
                break;
            
            case 2:
                {
                system("clear");
                printf("************************************************\n");
                printf("\tLista de Alunos\n");
                printf("************************************************\n\n");
                
                listar_alunos(lista_alunos);

                printf("\n\n\nAperte ENTER para voltar.\n");

                getchar();
                getchar();
                }
                break;

            case 3:
                {
                    system("clear");
                    printf("************************************************\n");
                    printf("\tVisualizar Aluno\n");
                    printf("************************************************\n\n\n");
                
                int op2;
                int b2 = 1;
                
                if(lista_alunos_vazia(lista_alunos)){
                    sleep(1);
                    break;
                }

                ALUNO *aluno_escolhido = pesquisar_aluno(lista_alunos);
                if(aluno_escolhido == NULL)
                    b2 = 0;              

                    while(b2){
                        system("clear");
                        printf("************************************************\n");
                        printf("\tVisualizar Aluno\n");
                        printf("************************************************\n\n\n");
                
                        printf("------------------------------------------------\n");
                        printf("| Nome do aluno: %s %s|\n", aluno_escolhido->nome, aluno_escolhido->sobrenome);
                        printf("| Matricula: %s |\n", aluno_escolhido->matricula);
                        printf("| Email: %s |\n", aluno_escolhido->email);
                        printf("------------------------------------------------\n");

                        printf("\n\nEscolha a opcao:\n\n");
                        printf("1- Cadastrar disciplina\n2- Listar disciplinas do aluno\n3- Editar disciplina\n4- Excluir disciplina\n5- Filtrar disciplinas por mencao\n6- Relatorio geral do aluno\n7- Voltar ao menu principal\n\n");
                        
                        scanf(" %d", &op2);
                        
                        switch (op2){
                            case 1:
                                system("clear");
                                
                                printf("************************************************\n");
                                printf("\tCadastrar Disciplina\n");
                                printf("************************************************\n\n");
                                
                                cadastrar_disciplina(aluno_escolhido);

                                sleep(1);
                                break;

                            case 2:
                                system("clear");
                                
                                printf("************************************************\n");
                                printf("\tLista de Disciplinas\n");
                                printf("************************************************\n\n");
                                
                                listar_disciplinas(aluno_escolhido);
                                
                                printf("\n\n\nAperte ENTER para voltar.\n");

                                getchar();
                                getchar();

                                break;

                            case 3:
                                system("clear");
                                                            
                                printf("************************************************\n");
                                printf("\tEditar Disciplina\n");
                                printf("************************************************\n\n");
                                
                                editar_disciplina(aluno_escolhido);
                                
                                sleep(1);
                                break;

                            case 4:
                                system("clear");
                                
                                printf("************************************************\n");
                                printf("\tExcluir Disciplina\n");
                                printf("************************************************\n\n");
                                
                                excluir_disciplina(aluno_escolhido);
                                
                                sleep(1);
                                break;

                            case 5:
                                system("clear");
                                                                
                                printf("************************************************\n");
                                printf("\tFiltrar Disciplinas\n");
                                printf("************************************************\n\n");
                                
                                filtrar_disciplinas(aluno_escolhido);

                                printf("\n\n\nAperte ENTER para voltar.\n");

                                getchar();
                                getchar();
                              
                                break;

                            case 6:
                                system("clear");
                                                                
                                printf("************************************************\n");
                                printf("\tRelatório do Aluno\n");
                                printf("************************************************\n\n");
                                
                                apresentar_relatorio(aluno_escolhido);

                                printf("\n\n\nAperte ENTER para voltar.\n");

                                getchar();
                                getchar();
                     
                                break;

                            case 7:
                                printf("\n\nVoltando ao menu principal...\n");
                                b2 = 0;
                                break;

                            default:
                                printf("\n\nOpcao invalida! Tente novamente.\n\n");
                                sleep(1);
                                break;
                        }
                    }

                sleep(1);
                }
                break;

            case 4:
                {
                system("clear");
                printf("************************************************\n");
                printf("\tEdição de Aluno\n");
                printf("************************************************\n\n");
                
                editar_aluno(lista_alunos);
                
                sleep(1);
                }
                break;
            
            case 5:
                {
                system("clear");
                printf("************************************************\n");
                printf("\tExclusão de Aluno\n");
                printf("************************************************\n\n");
                
                excluir_aluno(lista_alunos);
                
                sleep(1);
                }
                break;
            
            case 6:
                {
                printf("\n\nSaindo do programa...\n\n");
                sleep(1);
                b = 0;
                system("clear");
                }
                break;
            
            default:
                printf("\n\nOpcao invalida! Tente novamente.\n");
                sleep(1);
                break;
        }
    }

    system("clear");
    liberar_lista_alunos(lista_alunos);

    return 0;
}