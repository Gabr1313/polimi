from socket import *

serverPort = 9764
serverSocket = socket(AF_INET, SOCK_DGRAM)

binding = ("", serverPort)
serverSocket.bind(binding)
print("Server pronto a ricevere")

while True:
    message, clientAddress = serverSocket.recvfrom(2048)
    message.decode('utf-8')
    print('Contattato da: ', clientAddress)
    modified_message = message.upper()
    serverSocket.sendto(modified_message.encode('utf-8'), clientAddress)

serverSocket.close()
print("Server closed correctly")
