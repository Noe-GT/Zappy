import socket
import argparse
import threading
import sys
from ctypes import *
import os

lib = CDLL(os.path.abspath("./libprotocol.so"))

lib.create_buffer.restype = c_void_p
lib.write_string.argtypes = [c_void_p, c_char_p]
lib.read_string.restype = c_void_p
lib.read_string.argtypes = [c_void_p]
lib.destroy_buffer.argtypes = [c_void_p]
lib.clean_buffer.restype = c_void_p
lib.clean_buffer.argtypes = [c_void_p]
lib.free_str.argtypes = [c_void_p]

class CircularBuffer:
    def __init__(self):
        self.ptr = lib.create_buffer()
        if not self.ptr:
            raise MemoryError("Failed to create circular buffer")

    def write(self, string: str):
        lib.write_string(self.ptr, string.encode('utf-8'))

    def read(self) -> str:
        ptr = lib.read_string(self.ptr)
        if not ptr:
            return None
        result = cast(ptr, c_char_p).value.decode('utf-8')
        lib.free_str(ptr)
        return result

    def clean(self):
        self.ptr = lib.clean_buffer(self.ptr)

    def __del__(self):
        lib.destroy_buffer(self.ptr)

class ZappyClient:
    def __init__(self, host, port, team_name):
        self.host = host
        self.port = port
        self.team_name = team_name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.buffer = CircularBuffer()
        self.running = False
        self.initialized = False

    def connect(self):
        try:
            self.socket.connect((self.host, self.port))
            print(f"Connected to server {self.host}:{self.port}")
            self.running = True
            threading.Thread(target=self.receive_data, daemon=True).start()
            while not self.initialized:
                pass
            self.interactive_loop()
        except Exception as e:
            print(f"Connection error: {e}")
            sys.exit(1)

    def send_command(self, command):
        if not command.endswith('\n'):
            command += '\n'
        self.socket.send(command.encode('utf-8'))

    def receive_data(self):
        while self.running:
            try:
                data = self.socket.recv(1024)
                if not data:
                    print("Server disconnected")
                    self.running = False
                    sys.exit(0)
                self.buffer.write(data.decode('utf-8'))
                while True:
                    message = self.buffer.read()
                    if not message:
                        break
                    print(f"\n <-- {message.strip()}")
                    if not self.initialized:
                        if "WELCOME" in message:
                            self.send_command(self.team_name)
                            self.initialized = True
                    else:
                        sys.stdout.write("> ")
                        sys.stdout.flush()

            except Exception as e:
                print(f"\nReceive error: {e}")
                self.running = False
                sys.exit(1)

    def interactive_loop(self):
        while self.running:
            try:
                command = input("> ")
                if command.lower() == 'exit':
                    self.running = False
                    self.socket.close()
                    sys.exit(0)

                self.send_command(command)

            except KeyboardInterrupt:
                print("\nClosing connection...")
                self.running = False
                self.socket.close()
                sys.exit(0)
            except Exception as e:
                print(f"Error: {e}")

def parse_arguments():
    parser = argparse.ArgumentParser(description='Zappy AI Client', add_help=False)
    parser.add_argument('-p', '--port', type=int, required=True, help='Port number')
    parser.add_argument('-n', '--name', required=True, help='Team name')
    parser.add_argument('-h', '--host', default='localhost', help='Host machine (default: localhost)')
    parser.add_argument('--help', action='store_true', help='USAGE: ./zappy_ai -p port -n name -h machine')
    return parser.parse_args()

if __name__ == "__main__":
    args = parse_arguments()
    client = ZappyClient(args.host, args.port, args.name)
    client.connect()

