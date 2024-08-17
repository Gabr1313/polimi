from socket import *

serverPort = 9764
serverName = "localhost"  # 127.0.0.1

id_server = (serverName, serverPort)  # tuple not modifiable
clientSocket = socket(AF_INET, SOCK_DGRAM)

message = input("Write a message: ")

clientSocket.sendto(message.encode('utf-8'), id_server)
timeout = 5  # seconds
clientSocket.settimeout(timeout)
try:
    modified_message, serverAddress = clientSocket.recvfrom(2048)
    modified_message = modified_message.decode('utf-8')
    print(f"Message received: {modified_message}")
except:  # `settimeout` da errore dopo il timeout
    print(f"Message not received")
# finally:

clientSocket.close()
print("Client closed correctly")
