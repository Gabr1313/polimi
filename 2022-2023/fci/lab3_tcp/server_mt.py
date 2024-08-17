from socket import *
from threading import Thread


def handler(connectionSocket):
    while True:
        message = connectionSocket.recv(1024)
        message = message.decode('utf-8')
        if message == '.':
            break
        response = message.upper()
        connectionSocket.send(response.encode('utf-8'))
    connectionSocket.close()


serverPort = 12000
welcomeSocket = socket(AF_INET, SOCK_STREAM)
binding = ('', serverPort)
welcomeSocket.bind(binding)
welcomeSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
welcomeSocket.listen(1)
print('Server ready to receive')

while True:
    new_socket, client_addr = welcomeSocket.accept()
    thread = Thread(target=handler, args=[new_socket])
    thread.start()
