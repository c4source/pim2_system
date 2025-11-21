import socket
import sys
import os

PORT = 5050


def limpar_tela():
    os.system("cls" if os.name == "nt" else "clear")


def obter_host():
    # Se o C passar o IP como argumento: python cliente_mensagens.py 127.0.0.1
    if len(sys.argv) > 1:
        return sys.argv[1]
    # Fallback para rodar localmente direto no terminal
    return "127.0.0.1"


HOST = obter_host()


def enviar(mensagem):
    """Envia uma mensagem ao servidor e retorna a resposta."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
        client.connect((HOST, PORT))
        client.sendall(mensagem.encode("utf-8"))
        resposta = client.recv(4096).decode("utf-8")
        return resposta


def postar_mural():
    limpar_tela()
    print("--- Nova mensagem no mural ---")
    turma = input("ID da turma: ").strip()
    tipo = input("Você é (aluno/professor): ").strip().lower()
    nome = input("Seu nome: ").strip()
    texto = input("Digite a mensagem: ").strip()

    if not turma or not tipo or not nome or not texto:
        print("\n[Aviso] Todos os campos são obrigatórios.")
        input("\nPressione ENTER para continuar...")
        return

    comando = f"MURAL_POST|{turma}|{tipo}|{nome}|{texto}"
    resp = enviar(comando)
    print("\n[Resposta do servidor]")
    print(resp)
    input("\nPressione ENTER para continuar...")


def ler_mural():
    limpar_tela()
    print("--- Consultar mural ---")
    turma = input("ID da turma: ").strip()

    if not turma:
        print("\n[Aviso] Informe o ID da turma.")
        input("\nPressione ENTER para continuar...")
        return

    comando = f"MURAL_LIST|{turma}"
    resp = enviar(comando)

    limpar_tela()
    print("===== MURAL DA TURMA =====")
    if resp.startswith("MURAL|"):
        print(resp[6:])
    else:
        print(resp)
    print("===========================")
    input("\nPressione ENTER para continuar...")


def main():
    while True:
        limpar_tela()
        print("==================================================")
        print(" SISTEMA ACADÊMICO COLABORATIVO - MURAL DA TURMA ")
        print("==================================================")
        print(f" Servidor conectado em: {HOST}:{PORT}")
        print("--------------------------------------------------")
        print("\n[ Mural de Mensagens ]")
        print("1 - Ver mural da turma")
        print("2 - Postar mensagem no mural")
        print("0 - Voltar ao sistema")

        opc = input("\nEscolha uma opção: ").strip()

        if opc == "1":
            ler_mural()
        elif opc == "2":
            postar_mural()
        elif opc == "0":
            limpar_tela()
            print("Retornando ao sistema...")
            break
        else:
            print("\n[Aviso] Opção inválida!")
            input("Pressione ENTER para continuar...")


if __name__ == "__main__":
    main()
