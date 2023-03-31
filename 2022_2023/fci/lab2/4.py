from socket import *

serverPort = 9764
serverName = "localhost" #127.0.0.1
id_server = (serverName, serverPort) #tuple not modifiable

clientSocket = socket(AF_INET, SOCK_DGRAM)

message = input("Write a message: ")
encoded_message = message.encode('utf-8')

clientSocket.sendto(encoded_message, id_server)
modified_message, serverAddress = clientSocket.recvfrom(2048)
modified_message = modified_message.decode('utf-8')

clientSocket.close()
print(f"Message received: {modified_message}")
