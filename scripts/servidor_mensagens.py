import socket
from datetime import datetime
import os

# === CONFIGURAÇÃO DO SERVIDOR ===
HOST = '0.0.0.0'
PORT = 5050

LOG_PATH = os.path.join("data", "log_servidor.txt")

def registrar_log(mensagem, usuario="desconhecido"):
    """Registra eventos do servidor em um arquivo TXT."""
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    linha = f"[{timestamp}] ({usuario}) {mensagem}\n"

    with open(LOG_PATH, "a", encoding="utf-8") as f:
        f.write(linha)

# ======== FUNÇÕES DO MURAL ========

def caminho_mural(turma_id):
    """Monta o caminho do arquivo de mural de uma turma."""
    return os.path.join("data", f"mural_turma_{turma_id}.txt")

def postar_no_mural(turma_id, autor_nome, tipo_autor, texto):
    """Salva uma mensagem no mural da turma em um arquivo TXT."""
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    linha = f"[{timestamp}] ({tipo_autor}) {autor_nome}: {texto}\n"

    caminho = caminho_mural(turma_id)
    with open(caminho, "a", encoding="utf-8") as f:
        f.write(linha)

def ler_mural(turma_id):
    """Lê e retorna o conteúdo do mural da turma como string."""
    caminho = caminho_mural(turma_id)

    if not os.path.exists(caminho):
        return "Nenhuma mensagem no mural ainda.\n"
    
    with open(caminho, "r", encoding="utf-8") as f:
        return f.read()

# ======== INÍCIO DO SERVIDOR ========

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen()

print(f"[SERVIDOR ONLINE] Ouvindo em {HOST}:{PORT}")
registrar_log("Servidor iniciado", usuario="sistema")
print("[AGUARDANDO CONEXÕES...]")

while True:
    conn, addr = server.accept()
    print(f"\n[+] Novo usuário conectado: {addr}")
    registrar_log(f"Cliente conectado: {addr}", usuario="socket")

    data = conn.recv(4096).decode('utf-8')
    if not data:
        conn.close()
        continue

    print(f"[MENSAGEM RECEBIDA] {data}")
    registrar_log(f"Mensagem recebida: {data}", usuario="socket")

    # ======== INTERPRETAÇÃO DE COMANDOS ========
    parts = data.split("|")
    comando = parts[0] if parts else ""

    resposta = ""

    if comando == "MURAL_POST":
        # Formato esperado:
        # MURAL_POST|turmaId|tipoUsuario|nomeAutor|mensagem
        if len(parts) < 5:
            resposta = "ERRO|Formato inválido para MURAL_POST."
        else:
            turma_id = parts[1]
            tipo_autor = parts[2]
            autor_nome = parts[3]
            texto = parts[4]

            postar_no_mural(turma_id, autor_nome, tipo_autor, texto)
            registrar_log(
                f"MURAL_POST turma={turma_id} autor={autor_nome}",
                usuario=tipo_autor
            )
            resposta = "OK|Mensagem publicada no mural."

    elif comando == "MURAL_LIST":
        # Formato esperado:
        # MURAL_LIST|turmaId
        if len(parts) < 2:
            resposta = "ERRO|Formato inválido para MURAL_LIST."
        else:
            turma_id = parts[1]
            conteudo = ler_mural(turma_id)
            registrar_log(
                f"MURAL_LIST turma={turma_id}",
                usuario="cliente"
            )
            # Prefixo "MURAL|" só pra cliente saber o tipo da resposta
            resposta = "MURAL|" + conteudo

    else:
        # Comando desconhecido → comportamento antigo (eco)
        resposta = f"[SERVIDOR] Mensagem recebida: {data}"

    conn.sendall(resposta.encode('utf-8'))
    conn.close()
