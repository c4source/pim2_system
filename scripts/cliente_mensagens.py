import socket

# === CONFIGURAÇÃO DO CLIENTE ===
print("=== CLIENTE DE MENSAGENS PIM ===")

# O usuário escolhe o IP do servidor (ex: IP da máquina do professor)
HOST = input("Digite o IP do servidor (ex: 127.0.0.1): ") or "127.0.0.1"
PORT = 5050

# Cria o socket TCP
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    client.connect((HOST, PORT))
    print(f"[CONECTADO] Conectado ao servidor {HOST}:{PORT}\n")

    # Envia mensagem
    mensagem = input("Digite a mensagem que deseja enviar: ")
    client.sendall(mensagem.encode("utf-8"))

    # Recebe resposta do servidor
    resposta = client.recv(1024).decode("utf-8")
    print(f"[RESPOSTA DO SERVIDOR] {resposta}")

except ConnectionRefusedError:
    print("[ERRO] Não foi possível conectar ao servidor. Verifique o IP e se ele está rodando.")
except Exception as e:
    print(f"[ERRO] Ocorreu um problema: {e}")
finally:
    client.close()
    print("\n[CLIENTE] Conexão encerrada.")