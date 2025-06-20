import socket
import argparse
import sys
import select
from ctypes import *
import os
from collections import deque

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
        self.socket.setblocking(False)
        self.buffer = CircularBuffer()
        self.running = False
        self.initialized = False
        self.poll = select.poll()
        self.send_queue = deque()
        self.pending_send = b""

    def connect(self):
        try:
            try:
                self.socket.connect((self.host, self.port))
            except BlockingIOError:
                pass
            print(f"Connecting to {self.host}:{self.port}...")
            self.poll.register(self.socket, select.POLLIN | select.POLLOUT | select.POLLERR)
            self.poll.register(sys.stdin, select.POLLIN)
            self.running = True
            self.main_loop()
        except Exception as e:
            print(f"Connection error: {e}")
            sys.exit(1)

    def queue_command(self, command):
        if not command.endswith('\n'):
            command += '\n'
        self.send_queue.append(command.encode('utf-8'))
        self._update_poll_registration()

    def _update_poll_registration(self):
        self.poll.unregister(self.socket)
        events = select.POLLIN | select.POLLERR
        if self.send_queue or self.pending_send:
            events |= select.POLLOUT
        self.poll.register(self.socket, events)

    def _handle_send(self):
        if not self.pending_send:
            if self.send_queue:
                self.pending_send = self.send_queue.popleft()
            else:
                self._update_poll_registration()
                return
        try:
            sent = self.socket.send(self.pending_send)
            self.pending_send = self.pending_send[sent:]
            if not self.pending_send:
                self._update_poll_registration()
        except BlockingIOError:
            pass
        except Exception as e:
            print(f"Send error: {e}")
            self.running = False

    def _handle_receive(self):
        try:
            data = self.socket.recv(4096)
            if not data:
                print("Server disconnected")
                self.running = False
                return
            self.buffer.write(data.decode('utf-8'))
            while True:
                message = self.buffer.read()
                if not message:
                    break
                print(f"\n<-- {message.strip()}")
                if not self.initialized and "WELCOME" in message:
                    self.queue_command(self.team_name)
                    self.initialized = True
        except BlockingIOError:
            pass
        except Exception as e:
            print(f"Receive error: {e}")
            self.running = False

    def _handle_stdin(self):
        command = sys.stdin.readline().strip()
        if command.lower() == 'exit':
            self.running = False
        else:
            self.queue_command(command)

    def main_loop(self):
        while self.running:
            try:
                events = self.poll.poll(100)
                for fd, event in events:
                    if fd == self.socket.fileno():
                        if event & select.POLLERR:
                            print("Socket error")
                            self.running = False
                            break
                        if event & select.POLLIN:
                            self._handle_receive()
                        if event & select.POLLOUT:
                            self._handle_send()
                    elif fd == sys.stdin.fileno() and event & select.POLLIN:
                        self._handle_stdin()
            except KeyboardInterrupt:
                print("\nClosing connection...")
                self.running = False
            except Exception as e:
                print(f"\nError: {e}")
                self.running = False

        self.socket.close()
        sys.exit(0)

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