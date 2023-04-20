from socket import *

serverName = "localhost"  # 127.0.0.1
serverPort = 9764

clientSocket = socket(AF_INET, SOCK_DGRAM)
id_server = (serverName, serverPort)

message = input("Write a message: ")
clientSocket.sendto(message.encode('utf-8'), id_server)

modified_message, serverAddress = clientSocket.recvfrom(2048)
modified_message.decode('utf-8')
print(f"Message received: {modified_message}")

clientSocket.close()
print("Client closed correctly")
