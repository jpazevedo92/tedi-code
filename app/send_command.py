import socket

def send_command(ip, command):
    port = 8080
    buffer_size = 1024
    message = command
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ip, port))
    s.send(message.encode())
    data = s.recv(buffer_size)
    s.close()
    return data

print(send_command("10.0.10.2", "-A"))
