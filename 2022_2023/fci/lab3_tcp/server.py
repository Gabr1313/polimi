from socket import *

serverPort = 12000

welcomeSocket = socket(AF_INET, SOCK_STREAM)
binding = ('', serverPort)
welcomeSocket.bind(binding)

welcomeSocket.listen(1)
# number of unaccepted connections that the system will allow
# before refusing new connections
print('Server ready to receive')

while True:
    connectionSocket, clientAddress = welcomeSocket.accept()
    print('Connected with: ', clientAddress)

    message = connectionSocket.recv(1024)
    message = message.decode('utf-8')
    modified_message = message.upper()

    connectionSocket.send(modified_message.encode('utf-8'))
    connectionSocket.close()
