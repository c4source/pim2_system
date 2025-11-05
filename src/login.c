// src/login.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/login.h"
#include "headers/utils.h"

int tipoUsuarioAtual = 0;  // 1=Admin, 2=Professor, 3=Aluno
int idUsuarioAtual = 0;
char usuarioNome[128] = "";  // nome do usuário logado

#include <conio.h>  // para _getch() no Windows
#include <windows.h>

static void animacaoVerificacao(void) {
    printf("Verificando credenciais...");
    fflush(stdout);
    for (int i = 0; i < 3; i++) {
        Sleep(400);

        printf(".");
        fflush(stdout);
    }
    printf("\n\n");

    Sleep(300);
}

// no seu Windows o comando é "python"
static const char* py_cmd(void) {
    return "python";
}

// executa scripts/validar_login.py "<email>" "<senha>" e lê "tipo|id|nome" do stdout
static int validar_com_python(const char* email, const char* senha) {
    char cmd[512];
    // aspas duplas permitem espaços nos argumentos
    snprintf(cmd, sizeof(cmd), "%s scripts/validar_login.py \"%s\" \"%s\"", py_cmd(), email, senha);

    FILE* fp = _popen(cmd, "r");

    if (!fp) return 0;

    char out[256] = {0};
    if (!fgets(out, sizeof(out), fp)) {
        _pclose(fp);
        return 0;
    }
    _pclose(fp);

    // --- Processa o retorno "tipo|id|nome"
    int role = 0;
    idUsuarioAtual = 0;
    usuarioNome[0] = '\0';

    // Exemplo de saída: "2|5|Prof. João Souza"
    char* sep1 = strchr(out, '|');
    if (sep1) {
        *sep1 = '\0';
        role = atoi(out);

        char* idPart = sep1 + 1;
        char* sep2 = strchr(idPart, '|');
        if (sep2) {
            *sep2 = '\0';
            idUsuarioAtual = atoi(idPart);

            strncpy(usuarioNome, sep2 + 1, sizeof(usuarioNome));
            usuarioNome[strcspn(usuarioNome, "\n")] = '\0';  // remove quebra de linha
        }
    } else {
        role = atoi(out);
        strcpy(usuarioNome, "Usuário");
    }

    return role;  // 1=admin, 2=professor, 3=aluno, 0=erro
}

void lerSenhaOculta(char* dest, int maxlen, int mostrarAsterisco) {
    int i = 0;
    char ch;

    while ((ch = _getch()) != '\r' && i < maxlen - 1) {
        if (ch == '\b') {  // Backspace
            if (i > 0) {
                i--;
                if (mostrarAsterisco) {
                    printf("\b \b");
                }
            }
        } else {
            dest[i++] = ch;
            if (mostrarAsterisco) {
                printf("*");
            }
        }
    }

    dest[i] = '\0';
    printf("\n");
}
// tela de login + integração com python
// retorna: 1=admin, 2=professor, 3=aluno, -1=sair

int realizarLogin(void) {
    char email[64];
    char senha[64];
    int tentativas = 0;

    while (tentativas < MAX_TENTATIVAS) {
        limparTela();
        printf("╔══════════════════════════════════════╗\n");
        printf("║  \033[1;36m     PIM SYSTEM - LOGIN (%d/%d)     \033[0m  ║\n", tentativas + 1,
               MAX_TENTATIVAS);
        printf("╚══════════════════════════════════════╝\n\n");
        printf("Digite suas credenciais a baixo.\n");
        printf("--------------------------------------\n");
        printf("E-mail (ou 'sair'): ");
        if (!fgets(email, sizeof(email), stdin)) return SAIR_SISTEMA;
        email[strcspn(email, "\n")] = '\0';
        if (strcmp(email, "sair") == 0) return SAIR_SISTEMA;

        printf("Senha: ");
        // Solicita a senha sem exibi-la no terminal
        lerSenhaOculta(senha, sizeof(senha), 1);

        // Executa validação de login via Python
        int role = validar_com_python(email, senha);  // retorna 0/1/2/3
        animacaoVerificacao();                        // opcional, apenas visual

        if (role == ADMIN_ROLE || role == PROFESSOR_ROLE || role == ALUNO_ROLE) {
            tipoUsuarioAtual = role;
            printf("\nLogin bem-sucedido! Bem-vindo(a), %s.\n", usuarioNome);

            pausar();
            return role;
        }

        tentativas++;
        printf("\nCredenciais inválidas. Tentativas restantes: %d.\n", MAX_TENTATIVAS - tentativas);
        pausar();
    }

    printf("\nLimite de tentativas excedido. Encerrando.\n");
    pausar();
    return SAIR_SISTEMA;
}
