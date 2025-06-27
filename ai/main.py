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

def test_circular_buffer():

    buf = CircularBuffer()
    buf.write("hello ")

    while True:
        msg = buf.read()
        if msg is None:
            break
        print(f"{msg.strip()}")\

    buf.write("world \n")

    while True:
        msg = buf.read()
        if msg is None:
            break
        print(f"-> {msg.strip()}")

if __name__ == "__main__":
    test_circular_buffer()