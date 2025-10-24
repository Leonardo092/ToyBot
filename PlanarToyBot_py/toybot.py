import sys

class ToyBot:
    def __init__(self):
        self.grid_dimension = (5, 5)
        self.state_ = {'x': 0, 'y': 0, 'direction': 'N'}
        self.Place()

    def Place(self, a=None, b=None, dir=None):
        if a is None or b is None or dir is None:
            # Default place at (0,0) facing 'N'
            self.state_ = {'x': 0, 'y': 0, 'direction': 'N'}
            return True

        if not self.isValidPosition(a, b):
            print()
            print("Careful! The target position is out of the table.", file=sys.stderr)
            print()
            return False
        elif not self.isValidDirection(dir):
            print()
            print("Invalid direction! Use one of the following: N, E, S, W.", file=sys.stderr)
            print()
            return False
        else:
            self.state_['x'] = a
            self.state_['y'] = b
            self.state_['direction'] = dir
            return True

    def Report(self):
        print()
        print(f"Robot is at position [{self.state_['x']},{self.state_['y']}] facing {self.state_['direction']}")
        print()

    def isValidPosition(self, a, b):
        return (0 <= a < self.grid_dimension[0]) and (0 <= b < self.grid_dimension[1])

    def ShiftPosition(self, a, b):
        target_x = self.state_['x'] + a
        target_y = self.state_['y'] + b

        if not self.isValidPosition(target_x, target_y):
            print()
            print("Invalid move! Please do not push the robot down the table :(", file=sys.stderr)
            print()
            return
        else:
            self.state_['x'] = target_x
            self.state_['y'] = target_y

    def isValidDirection(self, dir):
        return dir in ["N", "E", "S", "W"]

    def ShiftDirection(self, increment):
        dir_list = ["N", "E", "S", "W"]
        try:
            curr_idx = dir_list.index(self.state_['direction'])
            target_idx = curr_idx + increment

            if target_idx < 0:
                target_idx = len(dir_list) - 1
            elif target_idx >= len(dir_list):
                target_idx = 0

            self.state_['direction'] = dir_list[target_idx]
        except ValueError:
            print()
            print("Invalid direction! Maintaining previous direction", file=sys.stderr)
            print()

    def Left(self):
        self.ShiftDirection(-1)

    def Right(self):
        self.ShiftDirection(1)

    def Move(self):
        if self.state_['direction'] == "N":
            self.ShiftPosition(1, 0)
        elif self.state_['direction'] == "S":
            self.ShiftPosition(-1, 0)
        elif self.state_['direction'] == "E":
            self.ShiftPosition(0, 1)
        elif self.state_['direction'] == "W":
            self.ShiftPosition(0, -1)
        else:
            print("Invalid direction!", file=sys.stderr)