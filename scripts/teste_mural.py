import socket

HOST = "127.0.0.1"
PORT = 5050

def enviar_mensagem(mensagem):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(mensagem.encode("utf-8"))
        resposta = s.recv(4096).decode("utf-8")
        print("Resposta do servidor:")
        print(resposta)
        print("-" * 40)

# 1) Testar MURAL_POST
mensagem_post = "MURAL_POST|1|aluno|Gabriel|Primeira mensagem de teste no mural!"
print("Enviando:", mensagem_post)
enviar_mensagem(mensagem_post)

# 2) Testar MURAL_LIST
mensagem_list = "MURAL_LIST|1"
print("Enviando:", mensagem_list)
enviar_mensagem(mensagem_list)
