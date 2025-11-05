#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "headers/aluno.h"
#include "headers/turma.h"
#include "headers/aula.h"
#include "headers/atividade.h"
#include "headers/professor.h"
#include "headers/administrador.h"
#include "headers/login.h"
#include "headers/utils.h"
#include "headers/notas.h"

void menuPrincipalAdmin();
void menuPrincipalProfessor();
void menuPrincipalAluno();

void menuAlunos();
void menuTurmas();
void menuAulas();
void menuAtividades();
void menuProfessores();
void menuAdministrador();
void menuNotas();

int main(void) {
    system("chcp 65001 > nul");

    // 1) Realiza o login
    int tipoUsuario = realizarLogin();

    if (tipoUsuario == SAIR_SISTEMA) {
        printf("\nEncerrando o sistema...\n");
        return 0;
    }

    // 2) Direciona para o menu conforme o tipo de usuário logado
    switch (tipoUsuario) {
        case ADMIN_ROLE:
            menuPrincipalAdmin();
            break;
        case PROFESSOR_ROLE:
            menuPrincipalProfessor();
            break;
        case ALUNO_ROLE:
            menuPrincipalAluno();
            break;
        default:
            printf("Erro: tipo de usuário inválido.\n");
            break;
    }

    // 3) Fim da execução
    printf("\nSessão finalizada.\n");
    return 0;
}

// ===============================================================
// MENUS PRINCIPAIS PERSONALIZADOS POR TIPO DE USUÁRIO
// ===============================================================

// 🧑‍💼 ADMINISTRADOR — acesso total
void menuPrincipalAdmin() {
    int opcao;
    do {
        system("cls");
        printf("========== MENU ADMINISTRADOR ==========\n");
        printf("Usuario logado: %s\n\n", usuarioNome);
        printf("1. Menu de Alunos\n");
        printf("2. Menu de Professores\n");
        printf("3. Menu de Atividades\n");
        printf("4. Menu de Notas\n");
        printf("5. Menu de Aulas\n");
        printf("6. Menu de Turmas\n");
        printf("7. Menu de Administrador\n");
        printf("8. Comunicação em rede (chat)\n");
        printf("9. Logout\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuAlunos();
                break;
            case 2:
                menuProfessores();
                break;
            case 3:
                menuAtividades();
                break;
            case 4:
                menuNotas();
                break;
            case 5:
                menuAulas();
                break;
            case 6:
                menuTurmas();
                break;
            case 7:
                menuAdministrador();
                break;
            case 8:
                system("python scripts/cliente_mensagens.py");
                _getch();
                break;
            case 9:
                tipoUsuarioAtual = 0;
                idUsuarioAtual = 0;
                strcpy(usuarioNome, "");
                printf("\nFazendo logout...\n");
                _getch();
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                }  // limpa buffer
                main();  // volta pro login
                return;
            default:
                printf("Opcao invalida!\n");
                _getch();
        }
    } while (opcao != 9);
}

void menuPrincipalProfessor() {
    int opcao;
    do {
        system("cls");
        printf("========== MENU PROFESSOR ==========\n");
        printf("Usuário logado: %s\n\n", usuarioNome);
        printf("1. Minhas Turmas\n");
        printf("2. Minhas Aulas\n");
        printf("3. Minhas Atividades\n");
        printf("4. Lançar/Editar Notas\n");
        printf("5. Comunicação em Rede (Chat)\n");
        printf("6. Logout\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuTurmas();
                break;
            case 2:
                menuAulas();
                break;
            case 3:
                menuAtividades();
                break;
            case 4:
                menuNotas();
                break;
            case 5:
                system("python scripts/cliente_mensagens.py");
                _getch();
                break;
            case 6:
                tipoUsuarioAtual = 0;
                idUsuarioAtual = 0;
                strcpy(usuarioNome, "");
                printf("\nFazendo logout...\n");
                _getch();
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                }  // limpa buffer
                main();  // volta pro login
                return;
            default:
                printf("Opção inválida!\n");
                _getch();
        }
    } while (opcao != 6);
}

// 👨‍🎓 ALUNO — pode ver aulas, atividades e suas notas
void menuPrincipalAluno() {
    int opcao;
    do {
        system("cls");
        printf("========== MENU ALUNO ==========\n");
        printf("Usuario logado: %s\n\n", usuarioNome);
        printf("1. Ver Aulas\n");
        printf("2. Ver Atividades\n");
        printf("3. Consultar Minhas Notas\n");
        printf("4. Logout\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuAulas();
                break;
            case 2:
                menuAtividades();
                break;
            case 3:
                menuNotas();
                break;
            case 4:
                tipoUsuarioAtual = 0;
                idUsuarioAtual = 0;
                strcpy(usuarioNome, "");
                printf("\nFazendo logout...\n");
                _getch();
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                }  // limpa buffer
                main();  // volta pro login
                return;
            default:
                printf("Opcao invalida!\n");
                _getch();
        }
    } while (opcao != 4);
}

void menuAlunos() {
    int opcao;
    do {
        system("cls");
        printf("========== MENU DE ALUNOS ==========\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Editar Aluno\n");
        printf("3. Excluir Aluno\n");
        printf("4. Lista de Alunos\n");
        printf("5. Voltar ao Menu Anterior\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                cadastrarAluno();
                _getch();
                break;
            case 2:
                system("cls");
                editarAluno();
                _getch();
                break;
            case 3:
                system("cls");
                excluirAluno();
                _getch();
                break;
            case 4:
                system("cls");
                listarAlunos();
                printf("Pressione qualquer tecla para Fechar a listagem de alunos.");
                _getch();
                break;
            case 5:
                printf("Voltando ao menu Principal...");
                break;
            default:
                break;
        }

    } while (opcao != 5);
}

void menuProfessores() {
    int opcao;

    do {
        system("cls");
        printf("========== MENU DE PROFESSORES ==========\n");
        printf("1. Cadastrar Professor\n");
        printf("2. Editar Professor\n");
        printf("3. Excluir Professor\n");
        printf("4. Lista de Professores\n");
        printf("5. Relatorio de Disciplinas\n");
        printf("6. Voltar ao Menu Anterior\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                cadastrarProfessor();
                _getch();
                break;
            case 2:
                system("cls");
                editarProfessor();
                _getch();
                break;
            case 3:
                system("cls");
                excluirProfessor();
                _getch();
                break;
            case 4:
                system("cls");
                listarProfessores();
                printf("Pressione qualquer tecla para Fechar a listagem de professores.");
                _getch();
                break;
            case 5:
                system("cls");
                relatorioDisciplinasdoProfessor();
                printf("Pressione qualquer tecla para Fechar o relatório.");
                _getch();
                break;
            case 6:
                printf("Voltando ao menu Principal...");
                break;
            default:
                break;
        }

    } while (opcao != 6);
}

void menuAdministrador() {
    int opcao;

    do {
        system("cls");
        printf("========== MENU DE ADMINISTRADOR ==========\n");
        printf("1. Cadastrar Administrador\n");
        printf("2. Editar Administrador\n");
        printf("3. Excluir Administrador\n");
        printf("4. Lista de Administradores\n");
        printf("5. Voltar ao Menu Anterior\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                cadastrarAdministrador();
                _getch();
                break;
            case 2:
                system("cls");
                editarAdministrador();
                _getch();
                break;
            case 3:
                system("cls");
                excluirAdministrador();
                _getch();
                break;
            case 4:
                system("cls");
                listarAdministradores();
                printf("Pressione qualquer tecla para Fechar a listagem de administradores.");
                _getch();
                break;
            case 5:
                printf("Voltando ao menu Principal...");
                break;
            default:
                break;
        }

    } while (opcao != 5);
}

void menuTurmas() {
    int opcao;

    do {
        system("cls");
        printf("========== MENU DE TURMAS ==========\n");
        printf("1. Cadastrar Turma\n");
        printf("2. Editar Turma\n");
        printf("3. Excluir Turma\n");
        printf("4. Lista de Turmas\n");
        printf("5. Relatorio de Alunos por Turma\n");
        printf("6. Voltar ao Menu Anterior\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                cadastrarTurma();
                _getch();
                break;
            case 2:
                system("cls");
                editarTurma();
                _getch();
                break;
            case 3:
                system("cls");
                excluirTurma();
                _getch();
                break;
            case 4:
                system("cls");
                listarTurmas();
                printf("Pressione qualquer tecla para voltar...");
                _getch();
                break;
            case 5:
                system("cls");
                relatorioTurma();
                printf("Pressione qualquer tecla para voltar...");
                _getch();
                break;
            case 6:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                _getch();
        }

    } while (opcao != 6);
}

void menuAulas() {
    int opcao;
    do {
        system("cls");
        printf("========== MENU DE AULAS ==========\n");
        printf("Usuário logado: %s\n\n", usuarioNome);

        if (tipoUsuarioAtual == ALUNO_ROLE) {
            printf("1. Listar Aulas\n");
            printf("2. Voltar ao Menu Anterior\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    system("cls");
                    listarAulas();
                    printf("Pressione qualquer tecla para voltar...");
                    _getch();
                    break;
                case 2:
                    printf("Voltando ao menu anterior...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    _getch();
            }
        } else {
            printf("1. Cadastrar Aula\n");
            printf("2. Editar Aula\n");
            printf("3. Excluir Aula\n");
            printf("4. Listar Aulas\n");
            printf("5. Voltar ao Menu Anterior\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    system("cls");
                    cadastrarAula();
                    _getch();
                    break;
                case 2:
                    system("cls");
                    editarAula();
                    _getch();
                    break;
                case 3:
                    system("cls");
                    excluirAula();
                    _getch();
                    break;
                case 4:
                    system("cls");
                    listarAulas();
                    printf("Pressione qualquer tecla para voltar...");
                    _getch();
                    break;
                case 5:
                    printf("Voltando ao menu anterior...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    _getch();
            }
        }

    } while (opcao != 5 && opcao != 2);
}

void menuAtividades() {
    int opcao;
    do {
        system("cls");
        printf("========== MENU DE ATIVIDADES ==========\n");
        printf("Usuário logado: %s\n\n", usuarioNome);

        // Se for aluno, mostra só a opção de visualizar
        if (tipoUsuarioAtual == ALUNO_ROLE) {
            printf("1. Listar Atividades\n");
            printf("2. Voltar ao Menu Anterior\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    system("cls");
                    listarAtividades();
                    printf("Pressione qualquer tecla para voltar...");
                    _getch();
                    break;
                case 2:
                    printf("Voltando ao menu anterior...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    _getch();
            }
        } else {
            // Professor/Admin têm acesso completo
            printf("1. Cadastrar Atividade\n");
            printf("2. Editar Atividade\n");
            printf("3. Excluir Atividade\n");
            printf("4. Listar Atividades\n");
            printf("5. Voltar ao Menu Anterior\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    system("cls");
                    cadastrarAtividade();
                    _getch();
                    break;
                case 2:
                    system("cls");
                    editarAtividade();
                    _getch();
                    break;
                case 3:
                    system("cls");
                    excluirAtividade();
                    _getch();
                    break;
                case 4:
                    system("cls");
                    listarAtividades();
                    printf("Pressione qualquer tecla para voltar...");
                    _getch();
                    break;
                case 5:
                    printf("Voltando ao menu anterior...\n");
                    break;
                default:
                    printf("Opção invalida!\n");
                    _getch();
            }
        }

    } while (opcao != 5 && opcao != 2);
}

void menuNotas() {
    int opcao;

    do {
        system("cls");
        printf("========== MENU DE NOTAS ==========\n");
        printf("Usuario logado: %s\n\n", usuarioNome);

        if (tipoUsuarioAtual == ALUNO_ROLE) {
            printf("1. Consultar Minhas Notas\n");
            printf("2. Voltar ao Menu Anterior\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    system("cls");
                    listarNotas();  // Aqui você pode futuramente filtrar pelo aluno logado
                    _getch();
                    break;
                case 2:
                    printf("Voltando ao menu anterior...\n");
                    break;
                default:
                    printf("Opção invalida!\n");
                    _getch();
            }
        } else {
            printf("1. Lançar nova nota\n");
            printf("2. Editar nota existente\n");
            printf("3. Consultar notas\n");
            printf("4. Voltar ao menu principal\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", &opcao);
            getchar();

            switch (opcao) {
                case 1:
                    system("cls");
                    cadastrarNota();
                    _getch();
                    break;
                case 2:
                    system("cls");
                    editarNota();
                    _getch();
                    break;
                case 3:
                    system("cls");
                    listarNotas();
                    _getch();
                    break;
                case 4:
                    printf("\nVoltando ao menu principal...\n");
                    break;
                default:
                    printf("Opção invalida!\n");
                    _getch();
            }
        }

    } while (opcao != 4 && opcao != 2);
}
