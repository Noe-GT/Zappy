##
## EPITECH PROJECT, 2024
## zap
## File description:
## main.py
##

import argparse
import sys
import select
import time
import os
from circular_buffer import CircularBuffer
from network import NetworkManager
from protocol import ProtocolParser, ResponseType
from ai.core import PlayerState
from ai.commands import CommandHandler

class ZappyClient:
    def __init__(self, host, porcasse, team_name ):
        self.host = host
        self.port = porcasse
        self.team_name = team_name
        self.network = NetworkManager(host, porcasse)
        self.buffer = CircularBuffer("./libprotocol.so")
        self.state = PlayerState(team_name)
        self.command_handler = CommandHandler(self.state)
        self.running = False
        self.remaining_slots = 0
        self.looking_for_food = False
        self.last_look_time = 0

    def connect(self):
        try:
            self._connect_and_check_slots()
        except Exception as e:
            print(f"Connection error: {e}")
            sys.exit(1)

    def _connect_and_check_slots(self):
        self.network = NetworkManager(self.host, self.port)
        self.network.connect()
        self.running = True
        team_name_sended = False
        responses = []
        while len(responses) < 3 and self.running:
            if len(responses) != 0:
                if not team_name_sended:
                    self._send_team_name()
                    team_name_sended = True
            for event_type, data in self.network.process_io():
                if event_type == 'receive':
                    self.buffer.write(data)
                    while True:
                        msg = self.buffer.read()
                        if not msg:
                            break
                        responses.append(msg.strip())
                        print(f"<-- {msg.strip()}")
        if len(responses) >= 3:
            if responses[0] == "WELCOME":
                try:
                    self.remaining_slots = int(responses[1])
                    if self.remaining_slots > 0:
                        self._fork_new_instance()
                except ValueError:
                    pass
        self.main_loop()

    def _fork_new_instance(self):
        pid = os.fork()
        if pid == 0:
            time.sleep(0.1)
            client = ZappyClient(self.host, self.port, self.team_name)
            client._connect_and_check_slots()
            sys.exit(0)

    def _send_team_name(self):
        self.network.queue_send(self.state.team_name)

    def main_loop(self):
        while self.running:
            try:
                self._process_network()
                self._process_stdin()
                self._ai_think()
            except KeyboardInterrupt:
                self.running = False
            except Exception as e:
                print(f"\ng tou pt: {e}")
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
            print(f"\n<-- {message.strip()}")
            response_type, data = ProtocolParser.parse_response(message)
            if response_type == ResponseType.DEAD:
                self.state.is_alive = False
                self.running = False
            else:
                self.command_handler.handle_response(response_type.name.lower(), data)
                if response_type == ResponseType.INVENTORY:
                    self.state.update_inventory(data)
                elif response_type == ResponseType.VISION:
                    self.state.update_vision(data)
                    if self.looking_for_food:
                        self._handle_food_search()
                elif response_type == ResponseType.LEVEL:
                    self.state.update_level(data)

    def _process_stdin(self):
        if select.select([sys.stdin], [], [], 0)[0]:
            command = sys.stdin.readline().strip()
            if command.lower() == 'exit':
                self.running = False
            else:
                self._execute_command(command)

    def _execute_command(self, command_str):
        parts = command_str.split()
        if not parts:
            return
        command = parts[0]
        args = parts[1:] if len(parts) > 1 else None
        cmd_str = self.command_handler.execute(command, *args) if args else self.command_handler.execute(command)
        if cmd_str:
            self.network.queue_send(cmd_str)

    def _ai_think(self):
        if not self.state.is_alive:
            return
        if not hasattr(self, '_last_inventory_time'):
            self._last_inventory_time = 0
        current_time = time.time() * 1000
        if current_time - self._last_inventory_time >= 1000:
            self._execute_command("Inventory")
            self._last_inventory_time = current_time
        if self.state.has_low_food():
            if not self.looking_for_food:
                self.looking_for_food = True
                self.last_look_time = current_time
                print(f"[AI] Low food detected, looking around...")
                self._execute_command("Look")
        else:
            self._execute_command("Fork")
            time.sleep(0.2)
            self._fork_new_instance()

    def _handle_food_search(self):
        if not self.looking_for_food:
            return
        food_info = self.state.find_closest_resource('food')
        if food_info:
            distance, direction = food_info
            print(f"[AI] Food found at distance {distance} in direction {direction}")
            commands = self.command_handler.go_to_resource('food', distance, direction)
            for cmd in commands.split("|"):
                if cmd.strip():
                    print(f"[AI] Executing: {cmd.strip()}")
                    self._execute_command(cmd.strip())
                    time.sleep(0.2)
            self.looking_for_food = False
        else:
            print("[AI] No food visible, moving forward to explore")
            self._execute_command("Forward")
            self.looking_for_food = False

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