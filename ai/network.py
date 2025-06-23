##
## EPITECH PROJECT, 2024
## zap
## File description:
## network.py
##

import socket
import select
from collections import deque

class NetworkManager:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(False)
        self.poll = select.poll()
        self.send_queue = deque()
        self.pending_send = b""

    def connect(self):
        try:
            self.socket.connect((self.host, self.port))
        except BlockingIOError:
            pass
        self.poll.register(self.socket, select.POLLIN | select.POLLOUT | select.POLLERR)
        return True

    def queue_send(self, data):
        if not data.endswith('\n'):
            data += '\n'
        self.send_queue.append(data.encode('utf-8'))
        self._update_poll_events()

    def _update_poll_events(self):
        self.poll.unregister(self.socket)
        events = select.POLLIN | select.POLLERR
        if self.send_queue or self.pending_send:
            events |= select.POLLOUT
        self.poll.register(self.socket, events)

    def process_io(self, timeout=100):
        events = self.poll.poll(timeout)
        results = []
        for fd, event in events:
            if fd == self.socket.fileno():
                if event & select.POLLERR:
                    raise ConnectionError("Socket error")
                if event & select.POLLIN:
                    data = self._receive_data()
                    if data is not None:
                        results.append(('receive', data))
                if event & select.POLLOUT:
                    self._send_data()
        return results

    def _receive_data(self):
        try:
            data = self.socket.recv(4096)
            if not data:
                raise ConnectionError("Server disconnected")
            return data.decode('utf-8')
        except BlockingIOError:
            return None

    def _send_data(self):
        if not self.pending_send and self.send_queue:
            self.pending_send = self.send_queue.popleft()
        if self.pending_send:
            try:
                sent = self.socket.send(self.pending_send)
                self.pending_send = self.pending_send[sent:]
            except BlockingIOError:
                pass
        if not self.pending_send:
            self._update_poll_events()

    def close(self):
        self.poll.unregister(self.socket)
        self.socket.close()