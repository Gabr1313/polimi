from socket import *

serverName = 'localhost'
serverPort = 13000
welcomeSocket = (serverName, serverPort)

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect(welcomeSocket)  # 3-way handshake

while True:
    message = input('Inserisci stringa: ')
    clientSocket.send(message.encode('utf-8'))
    if message == ".":
        break
    modified_message = clientSocket.recv(1024).decode('utf-8')
    print(f'From server {modified_message}')

clientSocket.close()
