import socket
import os

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
buffsize = 4096


s.connect(("localhost", 8080))
print(s.getsockname()[1])
while(True):
    s.send("hola".encode())
    message = s.recv(buffsize)