from socket import *

serverPort = 9764

serverSocket = socket(AF_INET, SOCK_DGRAM)

binding = ("", serverPort)
serverSocket.bind(binding)

print("Server pronto a ricevere")

message, clientAddress = serverSocket.recvfrom(2048)
print('Contattato da: ', clientAddress)
message = message.decode('utf-8')
n = 0
for c in message:
    if c not in "aeiou" and c.lower() >= a and c.lower() <= z:
        n += 1
serverSocket. sendto(str(n).encode('utf-8'), clientAddress)

serverSocket.close()
print("Server closed correctly")
