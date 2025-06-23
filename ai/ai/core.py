##
## EPITECH PROJECT, 2024
## zap
## File description:
## core.py
##

from enum import Enum
from typing import Optional, Tuple

class Direction(Enum):
    NORTH = 1
    EAST = 2
    SOUTH = 3
    WEST = 4

class PlayerState:
    def __init__(self, team_name):
        self.team_name = team_name
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
        self.id = None
        self.is_alive = True
        self.elevating = False
        self.last_command: Optional[str] = None
        self.last_args: Optional[tuple] = None

    def update_position(self, x: int, y: int):
        self.position = (x, y)

    def update_direction(self, direction: Direction):
        self.direction = direction

    def update_inventory(self, inventory: dict):
        self.inventory.update(inventory)

    def update_vision(self, vision: list):
        if vision is None:
            self.vision = []
        else:
            self.vision = vision

    def update_level(self, level: int):
        self.level = level

    def set_last_command(self, command: str, args: tuple = None):
        self.last_command = command
        self.last_args = args

    def has_low_food(self, threshold=7) -> bool:
        return self.inventory.get('food', 0) < threshold

    def find_closest_resource(self, resource_name: str):
        if not self.vision:
            return None
        for i, tile in enumerate(self.vision):
            if resource_name in tile:
                distance = self._get_distance_for_tile(i)
                direction = self._get_direction_for_tile(i)
                return (distance, direction)
        return None

    def _get_distance_for_tile(self, tile_index: int) -> int:
        if tile_index == 0:
            return 0
        ring = 0
        while tile_index >= (ring + 1) * (2 * ring + 1):
            ring += 1
        return ring

    def _get_direction_for_tile(self, tile_index: int) -> str:
        if tile_index == 0:
            return "here"

        ring = self._get_distance_for_tile(tile_index)
        positions_in_ring = 8 * ring
        position_in_ring = tile_index - (ring - 1) * (2 * (ring - 1) + 1)
        directions = ["front", "front-right", "right", "back-right", "back", "back-left", "left", "front-left"]

        return directions[(position_in_ring - 1) // ring]