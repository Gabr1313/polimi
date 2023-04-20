from socket import *

serverName = 'localhost'
serverPort = 12000

clientSocket = socket(AF_INET, SOCK_STREAM)
welcomeSocket = (serverName, serverPort)

clientSocket.connect(welcomeSocket)  # 3-way handshake
message = input('Inserisci stringa: ').encode('utf-8')
# `send` not `sendto`: IP permamente (handshake)
clientSocket.send(message)

# `recv` not `recvfrom`: IP permamente (handshake)
modified_message = clientSocket.recv(1024).decode('utf-8')
print(f'From server {modified_message}')

clientSocket.close()
