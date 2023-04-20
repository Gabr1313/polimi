from socket import *

serverPort = 12000
welcomeSocket = socket(AF_INET, SOCK_STREAM)
binding = ('', serverPort)
welcomeSocket.bind(binding)
welcomeSocket.listen(2)
print('Il server è pronto a ricevere')

while True:
    connectionSocket, clientAddress = welcomeSocket.accept()
    print(f'Connected to: {clientAddress}')
    while True:
        message = connectionSocket.recv(1024)
        message = message.decode('utf-8')
        if message == '.':
            break
        response = message.upper()
        connectionSocket.send(response.encode('utf-8'))
    connectionSocket.close()
