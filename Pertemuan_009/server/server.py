"""
TCP Server module to handle connections and receive DHT11 sensor data from ESP clients.
"""

import socket
from threading import Thread

class ClientThread(Thread):
    """
    Thread to handle individual client connections.
    """
    
    def __init__(self, ip, port, conn):
        """
        Initialize the client thread.
        
        Args:
            ip (str): The IP address of the connected client.
            port (int): The port number of the connected client.
            conn (socket.socket): The socket connection object.
        """
        Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.conn = conn
        print(f"[+] Ada koneksi masuk dari {ip}:{port}")

    def run(self):
        """
        Continuously listen for incoming data from the client, process it, 
        and send an acknowledgment response back.
        """
        while True:
            try:
                data = self.conn.recv(2048)
                if not data:
                    break
                
                data_str = data.decode('utf8').strip()
                if data_str:
                    print(f"Data dari ESP: {data_str}")
                
                response_message = "Data DHT11 aman diterima server!\n"
                self.conn.send(response_message.encode("utf8"))
                
            except Exception as e:
                print(f"Koneksi terputus: {e}")
                break

TCP_IP = "0.0.0.0"
TCP_PORT = 2004

tcpServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
tcpServer.bind((TCP_IP, TCP_PORT))
threads = []

print(f"Server berjalan dan menunggu koneksi ESP di port {TCP_PORT}...")
tcpServer.listen(4)

while True:
    (conn, (ip, port)) = tcpServer.accept()
    newthread = ClientThread(ip, port, conn)
    newthread.start()
    threads.append(newthread)