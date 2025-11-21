#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/utils.h"

// Define o comando Python conforme o sistema
static const char* py_cmd(void) {
    return "python";  // ou "python3" se for o nome no seu PATH

    return "python3";
}

// --- Executa um script Python e captura o resultado ---
void executarPython(const char* script, const char* param, char* output, int size) {
    char caminhoScript[260];
    char comando[512];

    construirCaminho(caminhoScript, script);

    //  Corrigido: agora os parâmetros não são agrupados entre aspas
    // Exemplo final: python "scripts/read_json_aula.py" data/aulas.json 5
    snprintf(comando, sizeof(comando), "%s \"%s\" %s", py_cmd(), caminhoScript, param ? param : "");

    FILE* fp = _popen(comando, "r");

    if (!fp) {
        snprintf(output, size, "Erro ao executar comando Python.\n");
        return;
    }

    char buffer[256];
    output[0] = '\0';

    // Lê toda a saída do script Python
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strlen(output) + strlen(buffer) < (size_t)(size - 1)) {
            strcat(output, buffer);
        }
    }

    _pclose(fp);
}

// --- Executa um script Python diretamente no terminal (sem capturar saída) ---
void systemPython(const char* script, const char* param) {
    char caminhoScript[260];
    char comando[512];

    construirCaminho(caminhoScript, script);
    snprintf(comando, sizeof(comando), "%s \"%s\" %s", py_cmd(), caminhoScript, param ? param : "");
    system(comando);
}

// --- Constrói um caminho relativo ao projeto ---
void construirCaminho(char* destino, const char* subcaminho) {
    snprintf(destino, 260, "%s/%s", ".", subcaminho);
}

// --- Limpa a tela ---
void limparTela(void) {
    system("cls");
}
// --- Pausa até pressionar Enter ---
void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // limpa buffer residual
}
