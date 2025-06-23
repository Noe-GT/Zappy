##
## EPITECH PROJECT, 2024
## zap
## File description:
## circular_buffer.py
##

from ctypes import *
import os

class CircularBuffer:
    def __init__(self, lib_path):
        self.lib = CDLL(os.path.abspath(lib_path))
        self.lib.create_buffer.restype = c_void_p
        self.lib.write_string.argtypes = [c_void_p, c_char_p]
        self.lib.read_string.restype = c_void_p
        self.lib.read_string.argtypes = [c_void_p]
        self.lib.destroy_buffer.argtypes = [c_void_p]
        self.lib.clean_buffer.restype = c_void_p
        self.lib.clean_buffer.argtypes = [c_void_p]
        self.lib.free_str.argtypes = [c_void_p]

        self.ptr = self.lib.create_buffer()
        if not self.ptr:
            raise MemoryError("Failed to create circular buffer")

    def write(self, string: str):
        self.lib.write_string(self.ptr, string.encode('utf-8'))

    def read(self) -> str:
        ptr = self.lib.read_string(self.ptr)
        if not ptr:
            return None
        result = cast(ptr, c_char_p).value.decode('utf-8')
        self.lib.free_str(ptr)
        return result

    def clean(self):
        self.ptr = self.lib.clean_buffer(self.ptr)

    def __del__(self):
        self.lib.destroy_buffer(self.ptr)