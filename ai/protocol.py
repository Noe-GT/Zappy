##
## EPITECH PROJECT, 2024
## zap
## File description:
## protocol.py
##

from enum import Enum, auto

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
            return (ResponseType.MESSAGE, message[7:].strip())
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
                if len(parts) >= 2 and parts[0] in ['food',
                    'linemate',
                    'deraumere',
                    'sibur',
                    'mendiane',
                    'phiras',
                    'thystame']:
                    try:
                        inventory[parts[0]] = int(parts[1])
                    except ValueError:
                        inventory[parts[0]] = 0
            return inventory
        except Exception as e:
            print(f"Error parsing inventory: {e}")
            return None

    @staticmethod
    def parse_vision(vision_str):
        try:
            content = vision_str.strip('[]').strip()
            if not content:
                return []

            cells = []
            current_items = []
            buffer = ""
            in_sub_array = False

            for char in content:
                if char == '[':
                    in_sub_array = True
                    buffer = ""
                elif char == ']':
                    in_sub_array = False
                    if buffer.strip():
                        current_items.extend(buffer.strip().split())
                elif char == ',' and not in_sub_array:
                    if buffer.strip():
                        current_items.extend(buffer.strip().split())
                    if current_items:
                        cells.append(current_items)
                    current_items = []
                    buffer = ""
                else:
                    buffer += char

            if buffer.strip():
                current_items.extend(buffer.strip().split())
            if current_items:
                cells.append(current_items)
            return cells
        except Exception as e:
            print(f"Error parsing vision '{vision_str}': {e}")
            return None