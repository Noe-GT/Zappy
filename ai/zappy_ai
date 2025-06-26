#! /usr/bin/env python3
##
## EPITECH PROJECT, 2024
## zap
## File description:
## zappy_ai
##

import argparse
import sys
import select
import time
import os
import random
from enum import Enum, auto
from typing import Optional, Tuple, List, Dict
from ctypes import *
import socket
from collections import deque
import threading

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

class ResponseType(Enum):
    OK = auto()
    KO = auto()
    DEAD = auto()
    ELEVATION = auto()
    INVENTORY = auto()
    VISION = auto()
    MESSAGE = auto()
    EJECT = auto()
    LEVEL = auto()
    UNKNOWN = auto()

class ProtocolParser:
    @staticmethod
    def parse_response(message):
        message = message.strip()
        if message == "dead":
            return (ResponseType.DEAD, None)
        elif message == "ok":
            return (ResponseType.OK, None)
        elif message == "ko":
            return (ResponseType.KO, None)
        elif message.startswith("Current level:"):
            level = int(message.split()[2])
            return (ResponseType.LEVEL, level)
        elif message.startswith("Elevation underway"):
            return (ResponseType.ELEVATION, None)
        elif message.startswith("eject"):
            return (ResponseType.EJECT, None)
        elif message.startswith("message"):
            parts = message[7:].strip()
            if ',' in parts:
                direction_str, text = parts.split(',', 1)
                try:
                    direction = int(direction_str.strip())
                    text = text.strip()
                    return (ResponseType.MESSAGE, {'direction': direction, 'text': text})
                except ValueError:
                    return (ResponseType.MESSAGE, {'direction': 0, 'text': parts})
            else:
                return (ResponseType.MESSAGE, {'direction': 0, 'text': parts})
        elif message.startswith('['):
            content = message.strip('[]')
            if any(char.isdigit() for char in content):
                return (ResponseType.INVENTORY, ProtocolParser.parse_inventory(message))
            return (ResponseType.VISION, ProtocolParser.parse_vision(message))
        else:
            return (ResponseType.UNKNOWN, message)

    @staticmethod
    def parse_inventory(inv_str):
        try:
            items = inv_str.strip('[]').split(',')
            inventory = {}
            for item in items:
                parts = item.strip().split()
                if len(parts) >= 2 and parts[0] in ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']:
                    try:
                        inventory[parts[0]] = int(parts[1])
                    except ValueError:
                        inventory[parts[0]] = 0
            return inventory
        except Exception as e:
            return None

    @staticmethod
    def parse_vision(vision_str):
        try:
            content = vision_str.strip('[]').strip()
            if not content:
                return []
            raw_cells = []
            current_cell = ""
            paren_level = 0
            for char in content:
                if char == '[':
                    paren_level += 1
                elif char == ']':
                    paren_level -= 1
                elif char == ',' and paren_level == 0:
                    raw_cells.append(current_cell.strip())
                    current_cell = ""
                    continue
                current_cell += char
            if current_cell.strip():
                raw_cells.append(current_cell.strip())
            cells = []
            for cell in raw_cells:
                cell = cell.strip()
                if cell.startswith('[') and cell.endswith(']'):
                    cell_content = cell[1:-1].strip()
                    if cell_content:
                        items = cell_content.split()
                        cells.append(items)
                    else:
                        cells.append([])
                else:
                    if cell:
                        items = cell.split()
                        cells.append(items)
                    else:
                        cells.append([])
            return cells
        except Exception as e:
            return []

class Command:
    def __init__(self, name: str, args: tuple = None):
        self.name = name
        self.args = args or ()
        self.sent_time = 0
        self.response_received = False

    def to_string(self) -> str:
        if self.args:
            return f"{self.name} {' '.join(str(arg) for arg in self.args)}"
        return self.name

    def handle_ok(self, player_state):
        pass

    def handle_ko(self, player_state):
        pass

class ForwardCommand(Command):
    def __init__(self):
        super().__init__("Forward")

    def handle_ok(self, player_state):
        player_state.move_forward()

class RightCommand(Command):
    def __init__(self):
        super().__init__("Right")

    def handle_ok(self, player_state):
        player_state.turn_right()

class LeftCommand(Command):
    def __init__(self):
        super().__init__("Left")

    def handle_ok(self, player_state):
        player_state.turn_left()

class IncantationCommand(Command):
    def __init__(self):
        super().__init__("Incantation")

class LookCommand(Command):
    def __init__(self):
        super().__init__("Look")

class InventoryCommand(Command):
    def __init__(self):
        super().__init__("Inventory")

class TakeCommand(Command):
    def __init__(self, obj: str):
        super().__init__("Take", (obj,))

    def handle_ok(self, player_state):
        obj = self.args[0]
        if obj in player_state.inventory:
            player_state.inventory[obj] += 1

class SetCommand(Command):
    def __init__(self, obj: str):
        super().__init__("Set", (obj,))

    def handle_ok(self, player_state):
        obj = self.args[0]
        if obj in player_state.inventory and player_state.inventory[obj] > 0:
            player_state.inventory[obj] -= 1

class ForkCommand(Command):
    def __init__(self):
        super().__init__("Fork")

class BroadcastCommand(Command):
    def __init__(self, message: str):
        super().__init__("Broadcast", (message,))

class NetworkManager:
    def __init__(self, host: str, port: int):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(False)
        self.poll = select.poll()
        self.send_queue = deque()
        self.pending_send = b""
        self.command_queue = deque()
        self.current_command = None

    def connect(self):
        try:
            self.socket.connect((self.host, self.port))
        except BlockingIOError:
            pass
        self.poll.register(self.socket, select.POLLIN | select.POLLOUT | select.POLLERR)
        return True

    def send_command(self, command: Command):
        self.command_queue.append(command)
        self._try_send_next_command()

    def _try_send_next_command(self):
        if self.current_command is None and self.command_queue:
            self.current_command = self.command_queue.popleft()
            self.current_command.sent_time = time.time() * 1000
            cmd_str = self.current_command.to_string()
            self.queue_send(cmd_str)

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

    def handle_response(self, response_type: ResponseType, data, player_state):
        if self.current_command:
            if response_type == ResponseType.OK:
                self.current_command.handle_ok(player_state)
            elif response_type == ResponseType.KO:
                self.current_command.handle_ko(player_state)
            self.current_command = None
            self._try_send_next_command()

    def has_pending_command(self) -> bool:
        return self.current_command is not None

    def close(self):
        self.poll.unregister(self.socket)
        self.socket.close()

class Direction(Enum):
    NORTH = 1
    EAST = 2
    SOUTH = 3
    WEST = 4

class PlayerState:
    def __init__(self, team_name: str, ai_id: int = 0):
        self.team_name = team_name
        self.ai_id = ai_id
        self.max_ai_id = ai_id
        self.level = 1
        self.position = (0, 0)
        self.direction = Direction.NORTH
        self.inventory = {
            'food': 10,
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }
        self.vision = []
        self.is_alive = True
        self.last_look_position = None
        self.last_look_time = 0
        self.last_inventory_time = 0
        self.rally_direction = None
        self.rally_steps = 0
        self.gather_mode = True
        self.waiting_for_food_drop = False
        self.suicide_ai = False

    def can_elevate(self) -> bool:
        elevation_requirements = {
            1: {'players': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            2: {'players': 7, 'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            3: {'players': 7, 'linemate': 2, 'deraumere': 0, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0},
            4: {'players': 7, 'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
            5: {'players': 7, 'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0},
            6: {'players': 7, 'linemate': 1, 'deraumere': 2, 'sibur': 3, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
            7: {'players': 7, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1}
        }
        if self.level >= 8:
            return False
        if self.ai_id == 0 and self.get_total_food() < 25:
            return False
        req = elevation_requirements.get(self.level, {})
        current_tile = self.vision[0]
        if not self.vision or len(self.vision) == 0:
            return False
        tile_resources = {}
        for item in current_tile:
            if item in ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']:
                tile_resources[item] = tile_resources.get(item, 0) + 1
        for resource, needed in req.items():
            if resource != 'players' and tile_resources.get(resource, 0) < needed:
                return False
        return True

    def move_forward(self):
        x, y = self.position
        if self.direction == Direction.NORTH:
            y -= 1
        elif self.direction == Direction.EAST:
            x += 1
        elif self.direction == Direction.SOUTH:
            y += 1
        elif self.direction == Direction.WEST:
            x -= 1
        self.position = (x, y)

    def turn_right(self):
        current = self.direction.value
        self.direction = Direction((current % 4) + 1)

    def turn_left(self):
        current = self.direction.value
        self.direction = Direction(4 if current == 1 else current - 1)

    def update_inventory(self, inventory: dict):
        if inventory:
            self.inventory.update(inventory)
            self.last_inventory_time = time.time() * 1000

    def update_vision(self, vision: list):
        if vision is None:
            self.vision = []
        else:
            self.vision = vision
            self.last_look_position = self.position
            self.last_look_time = time.time() * 1000

    def update_level(self, level: int):
        self.level = level

    def get_total_resources(self) -> int:
        return sum(
            count for item, count in self.inventory.items()
            if item != 'food' and isinstance(count, int)
        )

    def get_total_food(self) -> int:
        return sum(
            count for item, count in self.inventory.items()
            if item == 'food' and isinstance(count, int)
        )

    def is_at_same_position_as_last_look(self) -> bool:
        return self.last_look_position == self.position

    def update_max_ai_id(self, new_id: int):
        if new_id > self.max_ai_id:
            self.max_ai_id = new_id

    def can_fork(self) -> bool:
        return True

    def is_suicide_ai(self) -> bool:
        return self.ai_id > 50

class Utils:
    @staticmethod
    def find_closest_resource(player_state: PlayerState, resource_name: str) -> Optional[Tuple[int, str]]:
        if not player_state.vision:
            return None
        for i, tile in enumerate(player_state.vision):
            if isinstance(tile, list) and resource_name in tile:
                distance, direction = Utils._get_position_for_tile(i, player_state.level)
                return (distance, direction)
        return None

    @staticmethod
    def _get_position_for_tile(tile_index: int, player_level: int) -> Tuple[int, str]:
        if tile_index == 0:
            return (0, "here")
        if player_level == 1:
            if tile_index == 1:
                return (1, "front-left")
            elif tile_index == 2:
                return (1, "front")
            elif tile_index == 3:
                return (1, "front-right")
        level = 1
        tiles_seen = 1
        while tile_index >= tiles_seen:
            tiles_in_current_level = (2 * level + 1)
            if tile_index < tiles_seen + tiles_in_current_level:
                position_in_level = tile_index - tiles_seen
                direction = Utils._get_direction_for_level_position(position_in_level, level)
                return (level, direction)
            tiles_seen += tiles_in_current_level
            level += 1
            if level > player_level:
                break
        return (1, "front")

    @staticmethod
    def _get_direction_for_level_position(position_in_level: int, level: int) -> str:
        if level == 1:
            directions = ["front-left", "front", "front-right"]
            return directions[position_in_level] if position_in_level < len(directions) else "front"
        total_positions = 2 * level + 1
        left_positions = level
        center_positions = 1

        if position_in_level < left_positions:
            return "front-left"
        elif position_in_level < left_positions + center_positions:
            return "front"
        else:
            return "front-right"

    @staticmethod
    def generate_path_to_resource(resource: str, distance: int, direction: str) -> List[Command]:
        commands = []
        if direction == "here":
            commands.append(TakeCommand(resource))
            return commands
        if direction == "front":
            pass
        elif direction == "front-left":
            commands.extend([ForwardCommand(), LeftCommand()])
        elif direction == "front-right":
            commands.extend([ForwardCommand(), RightCommand()])
        for _ in range(distance):
            commands.append(ForwardCommand())
        commands.append(TakeCommand(resource))
        return commands

class Logic:
    def __init__(self, player_state: PlayerState, network: NetworkManager):
        self.player_state = player_state
        self.network = network
        self.looking_for_food = False
        self.suicide_ai_spawned = False

    def think(self):
        if not self.player_state.is_alive:
            return
        if self.player_state.is_suicide_ai():
            self._handle_suicide_ai()
            return
        current_time = time.time() * 1000
        if self.network.has_pending_command():
            return
        if not self.player_state.vision or (current_time - self.player_state.last_look_time) > 500:
            self.network.send_command(LookCommand())
            return
        if not self.player_state.vision or (current_time - self.player_state.last_inventory_time) > 500:
            self.network.send_command(InventoryCommand())
            return
        if self.player_state.gather_mode:
            self._handle_gather_mode()
        else:
            self._handle_rally_mode()

    def _handle_gather_mode(self):
        current_time = time.time() * 1000
        if current_time - self.player_state.last_inventory_time >= 1000:
            self.network.send_command(InventoryCommand())
            return
        if self.player_state.waiting_for_food_drop:
            self._handle_waiting_for_food()
            return
        totalfood = self.player_state.get_total_food()
        if totalfood < 10 and self.player_state.max_ai_id > 50:
            if not self.suicide_ai_spawned:
                self._fork_suicide_ai()
                if self.player_state.ai_id == 0:
                    print("forking to sucide")
        elif totalfood < 20: #
            self._handle_resource_gathering()
        elif totalfood >= 20 and totalfood < 42:
            if self.player_state.max_ai_id < 50:
                self.network.send_command(ForkCommand())
                time.sleep(0.2)
                self._fork_new_instance()
            elif not self.suicide_ai_spawned:
                self._fork_suicide_ai()
            else:
                self._handle_resource_gathering()
        elif totalfood >= 170:
            self.player_state.gather_mode = False
            self._start_rally()
        elif not self.suicide_ai_spawned:
            self._fork_suicide_ai()
        self._handle_resource_gathering()

    def _handle_suicide_ai(self):
        totalfood = self.player_state.get_total_food()
        if totalfood > 0:
            for _ in range(totalfood):
                self.network.send_command(SetCommand("food"))
            self.player_state.is_alive = False
        else:
            time.sleep(0.1)

    def _fork_suicide_ai(self):
        new_id = 51 + (self.player_state.max_ai_id - 50)
        self.network.send_command(ForkCommand())
        self.network.send_command(BroadcastCommand(f"new_{new_id}"))
        self.player_state.update_max_ai_id(new_id)
        self.suicide_ai_spawned = True
        self.player_state.waiting_for_food_drop = True
        pid = os.fork()
        if pid == 0:
            client = ZappyAI(self.player_state.team_name, self.network.host, self.network.port, new_id)
            client.run()
            sys.exit(0)

    def _handle_waiting_for_food(self):
        current_time = time.time() * 1000
        if (current_time - self.player_state.last_look_time) > 500:
            self.network.send_command(LookCommand())
            return
        if self.player_state.vision and len(self.player_state.vision) > 0:
            current_tile = self.player_state.vision[0]
            if 'food' in current_tile:
                food_count = current_tile.count('food')
                for _ in range(food_count):
                    self.network.send_command(TakeCommand('food'))
                self.player_state.waiting_for_food_drop = False
                self.suicide_ai_spawned = False

    def _handle_rally_mode(self):
        totalfood = self.player_state.get_total_food()
        if totalfood < 20:
            self.player_state.gather_mode = True
            self.player_state.rally_direction = None
            return
        self._handle_rally()

    def _start_rally(self):
        if self.player_state.get_total_food() < 20:
            self.player_state.gather_mode = True
            self.player_state.rally_direction = None
            return

        self.network.send_command(BroadcastCommand("rally"))
        threading.Timer(0.3, self._start_rally).start()

        if self.player_state.can_elevate():
            self.network.send_command(IncantationCommand())
            return

    def _handle_rally(self):
        if self.player_state.can_elevate():
            self.network.send_command(IncantationCommand())
            return
        if self.player_state.rally_direction is None:
            return
        if self.player_state.rally_direction == 0:
            for item, count in self.player_state.inventory.items():
                if item != 'food' and count > 0:
                    for _ in range(count):
                        self.network.send_command(SetCommand(item))
            self.player_state.rally_mode = False
            return
        if self.player_state.vision and len(self.player_state.vision) > 0:
            current_tile = self.player_state.vision[0]
            for item in current_tile:
                if item != 'food' and item in ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']:
                    self.network.send_command(TakeCommand(item))

        self._move_toward_rally()

    def _move_toward_rally(self):
        tile = self.player_state.rally_direction
        if tile == 0:
            self.player_state.rally_direction = None
            return
        if tile == 1:
            self.network.send_command(ForwardCommand())
        elif tile == 2:
            self.network.send_command(ForwardCommand())
            self.network.send_command(LeftCommand())
            self.network.send_command(ForwardCommand())
        elif tile == 3:
            self.network.send_command(LeftCommand())
            self.network.send_command(ForwardCommand())
        elif tile == 4:
            self.network.send_command(LeftCommand())
            self.network.send_command(ForwardCommand())
            self.network.send_command(LeftCommand())
            self.network.send_command(ForwardCommand())
        elif tile == 5:
            self.network.send_command(RightCommand())
            self.network.send_command(RightCommand())
            self.network.send_command(ForwardCommand())
        elif tile == 6:
            self.network.send_command(RightCommand())
            self.network.send_command(ForwardCommand())
            self.network.send_command(RightCommand())
            self.network.send_command(ForwardCommand())

        elif tile == 7:
            self.network.send_command(RightCommand())
            self.network.send_command(ForwardCommand())
        elif tile == 8:
            self.network.send_command(ForwardCommand())
            self.network.send_command(RightCommand())
            self.network.send_command(ForwardCommand())
        self.player_state.rally_direction = None

    def handle_broadcast_message(self, message_data):
        if isinstance(message_data, dict):
            direction = message_data.get('direction', 0)
            text = message_data.get('text', '')
            if text.startswith("new_"):
                try:
                    new_id = int(text.split("_")[1])
                    self.player_state.update_max_ai_id(new_id)
                except (IndexError, ValueError):
                    pass
            elif text == "rally":
                if self.player_state.ai_id != 0:
                    self.player_state.gather_mode = False  # Changer de rally_mode à gather_mode
                    self.player_state.rally_direction = direction

    def _handle_resource_gathering(self):
        if self.player_state.waiting_for_food_drop:
            return
        if self.player_state.ai_id != 0 and self.player_state.get_total_food() >= 30:
            self._move_randomly()
            return
        if not self.looking_for_food:
            self.looking_for_food = True
            self.network.send_command(LookCommand())
        else:
            food_info = Utils.find_closest_resource(self.player_state, 'food')
            if food_info:
                distance, direction = food_info
                commands = Utils.generate_path_to_resource('food', distance, direction)
                for cmd in commands:
                    self.network.send_command(cmd)
                self.looking_for_food = False
            else:
                if self.player_state.is_at_same_position_as_last_look():
                    self._move_randomly()
                else:
                    self.network.send_command(LookCommand())

    def _move_randomly(self):
        if self.player_state.waiting_for_food_drop:
            return
        rand = random.random() * 100
        if rand < 5:
            self.network.send_command(RightCommand())
        elif rand < 10:
            self.network.send_command(LeftCommand())
        else:
            self.network.send_command(ForwardCommand())

    def _fork_new_instance(self):
        new_id = self.player_state.max_ai_id + 1
        self.network.send_command(BroadcastCommand(f"new_{new_id}"))
        self.player_state.update_max_ai_id(new_id)
        pid = os.fork()
        if pid == 0:
            client = ZappyAI(self.player_state.team_name, self.network.host, self.network.port, new_id)
            client.run()
            sys.exit(0)


class ZappyAI:
    def __init__(self, team_name: str, host: str, port: int, ai_id: int = 0):
        self.buffer = CircularBuffer("./libprotocol.so")
        self.network = NetworkManager(host, port)
        self.player_state = PlayerState(team_name, ai_id)
        self.logic = Logic(self.player_state, self.network)
        self.running = False

    def run(self):
        try:
            self._connect_and_initialize()
            self._main_loop()
        except Exception as e:
            sys.exit(1)

    def _connect_and_initialize(self):
        self.network.connect()
        self.running = True
        responses = []
        team_name_sent = False
        while len(responses) < 3 and self.running:
            if len(responses) != 0 and not team_name_sent:
                self.network.queue_send(self.player_state.team_name)
                team_name_sent = True
            for event_type, data in self.network.process_io():
                if event_type == 'receive':
                    self.buffer.write(data)
                    while True:
                        msg = self.buffer.read()
                        if not msg:
                            break
                        responses.append(msg.strip())

        if len(responses) >= 3 and responses[0] == "WELCOME":
            try:
                remaining_slots = int(responses[1])
                if self.player_state.ai_id == 0 and remaining_slots > 0 and self.player_state.can_fork():
                    self.logic._fork_new_instance()
            except ValueError:
                pass

    def _main_loop(self):
        while self.running:
            try:
                self._process_network()
                self.logic.think()
            except KeyboardInterrupt:
                self.running = False
            except Exception as e:
                self.running = False
        self.network.close()
        sys.exit(0)

    def _process_network(self):
        for event_type, data in self.network.process_io():
            if event_type == 'receive':
                self.buffer.write(data)
                self._process_messages()

    def _process_messages(self):
        while True:
            message = self.buffer.read()
            if not message:
                break
            response_type, data = ProtocolParser.parse_response(message)
            if response_type == ResponseType.DEAD:
                self.player_state.is_alive = False
                self.running = False
            elif response_type == ResponseType.INVENTORY:
                self.player_state.update_inventory(data)
            elif response_type == ResponseType.VISION:
                self.player_state.update_vision(data)
            elif response_type == ResponseType.LEVEL:
                self.player_state.update_level(data)
            elif response_type == ResponseType.MESSAGE:
                self.logic.handle_broadcast_message(data)
            self.network.handle_response(response_type, data, self.player_state)

def parse_arguments():
    parser = argparse.ArgumentParser(description='Zappy AI Client', add_help=False)
    parser.add_argument('-p', '--port', type=int, required=True, help='Port number')
    parser.add_argument('-n', '--name', required=True, help='Team name')
    parser.add_argument('-h', '--host', default='localhost', help='Host machine (default: localhost)')
    parser.add_argument('--help', action='store_true', help='USAGE: ./zappy_ai -p port -n name -h machine')
    return parser.parse_args()

if __name__ == "__main__":
    args = parse_arguments()
    client = ZappyAI(args.name, args.host, args.port)
    client.run()