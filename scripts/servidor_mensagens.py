import socket

# === CONFIGURAÇÃO DO SERVIDOR ===
HOST = '0.0.0.0'   # Escuta em todas as interfaces (permite conexões LAN)
PORT = 5050        # Porta fixa para o chat

# Cria o socket TCP
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen()

print(f"[SERVIDOR ONLINE] Ouvindo em {HOST}:{PORT}")
print("[AGUARDANDO CONEXÕES...]")

while True:
    conn, addr = server.accept()
    print(f"\n[+] Novo usuário conectado: {addr}")

    # Recebe mensagem
    data = conn.recv(1024).decode('utf-8')
    if not data:
        conn.close()
        continue

    print(f"[MENSAGEM RECEBIDA] {data}")

    # Envia confirmação ao cliente
    resposta = f"[SERVIDOR] Mensagem recebida: {data}"
    conn.sendall(resposta.encode('utf-8'))

    conn.close()
