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
        if inventory:
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

    def has_low_food(self, threshold = 15) -> bool:
        return self.inventory.get('food', 0) < threshold

    def find_closest_resource(self, resource_name: str):
        if not self.vision:
            return None

        for i, tile in enumerate(self.vision):
            if isinstance(tile, list) and resource_name in tile:
                distance = self._get_distance_for_tile(i)
                direction = self._get_direction_for_tile(i)
                return (distance, direction)

        return None

    def _get_distance_for_tile(self, tile_index: int) -> int:
        """Calcule la distance d'une case basée sur son index dans la vision"""
        if tile_index == 0:
            return 0

        # Calculer le niveau/ring de la case
        level = 1
        total_tiles = 1  # Case 0 (position actuelle)

        while tile_index >= total_tiles:
            tiles_in_level = 8 * level  # Chaque niveau a 8 * niveau cases
            if tile_index < total_tiles + tiles_in_level:
                return level
            total_tiles += tiles_in_level
            level += 1

        return level

    def _get_direction_for_tile(self, tile_index: int) -> str:
        """Détermine la direction d'une case basée sur son index dans la vision"""
        if tile_index == 0:
            return "here"

        level = self._get_distance_for_tile(tile_index)

        # Calculer la position dans le niveau
        tiles_before_level = 1  # Case 0
        for i in range(1, level):
            tiles_before_level += 8 * i

        position_in_level = tile_index - tiles_before_level
        tiles_per_direction = level
        if position_in_level < tiles_per_direction:
            return "front"
        elif position_in_level < 2 * tiles_per_direction:
            return "front-right"
        elif position_in_level < 3 * tiles_per_direction:
            return "right"
        elif position_in_level < 4 * tiles_per_direction:
            return "back-right"
        elif position_in_level < 5 * tiles_per_direction:
            return "back"
        elif position_in_level < 6 * tiles_per_direction:
            return "back-left"
        elif position_in_level < 7 * tiles_per_direction:
            return "left"
        else:
            return "front-left"