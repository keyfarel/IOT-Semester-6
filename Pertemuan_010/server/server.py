"""
Smart Village Server

This module provides a multi-threaded TCP server to handle incoming connections
from IoT clients (e.g., ESP32), process sensor data such as Day/Night conditions,
and send appropriate control commands back to the clients.
"""

import socket
import logging
from threading import Thread
from time import sleep

# Konfigurasi dasar logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

class ClientThread(Thread):
    """
    Background worker thread to handle a single client's connection.
    
    Attributes:
        ip (str): IP address of the connected client.
        port (int): Port number of the connected client.
        conn (socket.socket): Socket object representing the connection.
    """

    def __init__(self, ip: str, port: int, conn: socket.socket):
        """Initialize the client thread with connection details."""
        super().__init__()
        self.ip = ip
        self.port = port
        self.conn = conn
        logging.info(f"[+] Ada koneksi masuk dari {ip}:{port}")

    def run(self):
        """
        Listen for incoming messages on the established connection,
        process 'Malam'/'Siang' conditions, and send control commands. 
        """
        while True:
            try:
                data = self.conn.recv(2048)
                if not data:
                    break
                
                data_str = data.decode("utf8").strip()
                if data_str:
                    logging.info(f"[Menerima] {data_str}")
                    
                    if "Malam" in data_str:
                        command = "led-on\n"
                        logging.info("[Logika Server] Kondisi Malam: Mengirim perintah LED ON")
                    else:
                        command = "led-off\n"
                        logging.info("[Logika Server] Kondisi Siang: Mengirim perintah LED OFF")
                        
                    self.conn.send(command.encode("utf8"))
                    
            except Exception as e:
                # Menggunakan warning untuk koneksi yang terputus tidak wajar
                logging.warning(f"[-] Koneksi terputus: {e}")
                break
            
            sleep(0.25)


if __name__ == "__main__":
    TCP_IP = "0.0.0.0"
    TCP_PORT = 2004

    tcp_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_server.bind((TCP_IP, TCP_PORT))
    
    threads = []

    logging.info(f"Server Smart Village berjalan di port {TCP_PORT}...")
    tcp_server.listen(4)

    try:
        while True:
            (conn, (ip, port)) = tcp_server.accept()
            new_thread = ClientThread(ip, port, conn)
            new_thread.start()
            threads.append(new_thread)
    except KeyboardInterrupt:
        logging.info("Server dihentikan.")
    finally:
        tcp_server.close()