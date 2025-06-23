##
## EPITECH PROJECT, 2024
## zap
## File description:
## commands.py
##

from .core import PlayerState, Direction
from enum import Enum, auto
from typing import Optional

class CommandStatus(Enum):
    SUCCESS = auto()
    FAILURE = auto()
    PENDING = auto()

class CommandHandler:
    def __init__(self, state: PlayerState):
        self.state = state
        self.pending_commands = []

    def execute(self, command: str, *args):
        method_name = f"cmd_{command.lower()}"
        if hasattr(self, method_name):
            return getattr(self, method_name)(*args)
        return None

    def cmd_forward(self):
        self.state.set_last_command("Forward")
        return "Forward"

    def cmd_right(self):
        self.state.set_last_command("Right")
        return "Right"

    def cmd_left(self):
        self.state.set_last_command("Left")
        return "Left"

    def cmd_look(self):
        self.state.set_last_command("Look")
        return "Look"

    def cmd_inventory(self):
        self.state.set_last_command("Inventory")
        return "Inventory"

    def cmd_broadcast(self, message):
        self.state.set_last_command("Broadcast", (message,))
        return f"Broadcast {message}"

    def cmd_connect_nbr(self):
        self.state.set_last_command("Connect_nbr")
        return "Connect_nbr"

    def cmd_fork(self):
        self.state.set_last_command("Fork")
        return "Fork"

    def cmd_eject(self):
        self.state.set_last_command("Eject")
        return "Eject"

    def cmd_take(self, obj):
        self.state.set_last_command("Take", (obj,))
        return f"Take {obj}"

    def cmd_set(self, obj):
        self.state.set_last_command("Set", (obj,))
        return f"Set {obj}"

    def cmd_incantation(self):
        self.state.set_last_command("Incantation")
        return "Incantation"

    def handle_response(self, response_type, data):
        if response_type == "ok":
            self._handle_ok()
        elif response_type == "ko":
            self._handle_ko()

    def _handle_ok(self):
        if not self.state.last_command:
            return
        cmd = self.state.last_command
        args = self.state.last_args
        if cmd == "Forward":
            self._handle_move_ok()
        elif cmd in ["Right", "Left"]:
            self._handle_turn_ok(cmd == "Right")
        elif cmd == "Take":
            self._handle_take_ok(args[0] if args else None)
        elif cmd == "Set":
            self._handle_set_ok(args[0] if args else None)
        elif cmd == "Incantation":
            self.state.elevating = True

    def _handle_ko(self):
        cmd = self.state.last_command
        args = self.state.last_args
        print(f"Command failed: {cmd} {args if args else ''}")

    def _handle_move_ok(self):
        x, y = self.state.position
        if self.state.direction == Direction.NORTH:
            y -= 1
        elif self.state.direction == Direction.EAST:
            x += 1
        elif self.state.direction == Direction.SOUTH:
            y += 1
        elif self.state.direction == Direction.WEST:
            x -= 1
        self.state.update_position(x, y)

    def _handle_turn_ok(self, clockwise):
        current = self.state.direction.value
        if clockwise:
            new_dir = Direction((current % 4) + 1)
        else:
            new_dir = Direction(4 if current == 1 else current - 1)
        self.state.update_direction(new_dir)

    def _handle_take_ok(self, obj):
        if obj and obj in self.state.inventory:
            self.state.inventory[obj] += 1
            print(f"[AI] Successfully took {obj}, now have {self.state.inventory[obj]}")

    def _handle_set_ok(self, obj):
        if obj and obj in self.state.inventory and self.state.inventory[obj] > 0:
            self.state.inventory[obj] -= 1
            print(f"[AI] Successfully set {obj}, now have {self.state.inventory[obj]}")

    def go_to_resource(self, resource: str, distance: int, direction: str) -> str:
        commands = []

        if direction == "here":
            commands.append(f"Take {resource}")
            return "|".join(commands)
        if direction == "front":
            for _ in range(distance):
                commands.append("Forward")
        elif direction == "front-right":
            commands.append("Right")
            for _ in range(distance):
                commands.append("Forward")
        elif direction == "right":
            commands.append("Right")
            for _ in range(distance):
                commands.append("Forward")
        elif direction == "back-right":
            commands.append("Right")
            commands.append("Right")
            for _ in range(distance):
                commands.append("Forward")
        elif direction == "back":
            commands.append("Right")
            commands.append("Right")
            for _ in range(distance):
                commands.append("Forward")
        elif direction == "back-left":
            commands.append("Right")
            commands.append("Right")
            for _ in range(distance):
                commands.append("Forward")
        elif direction == "left":
            commands.append("Left")
            for _ in range(distance):
                commands.append("Forward")
        elif direction == "front-left":
            commands.append("Left")
            for _ in range(distance):
                commands.append("Forward")
        commands.append(f"Take {resource}")
        return "|".join(commands)