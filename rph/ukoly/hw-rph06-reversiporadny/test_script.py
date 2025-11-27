from new_player import MyPlayer
from copy import deepcopy

board = [
    [-1, -1, -1, -1, -1, -1, -1, -1],
    [-1, -1, -1, -1, -1, -1, -1, -1],
    [-1, -1, -1, -1, -1,  1, -1, -1],
    [-1, -1, -1,  1,  0, -1, -1, -1],
    [-1, -1, -1,  0,  1, -1, -1, -1],
    [-1, -1,  1, -1, -1, -1, -1, -1],
    [-1, -1, -1, -1, -1, -1, -1, -1],
    [ 0, -1, -1, -1, -1, -1, -1, -1]
]

player = MyPlayer(my_color=0, opponent_color=1)

# Test get_valid_moves
valid_moves = player.get_valid_moves(board, player.my_color)
print("Legal moves:", valid_moves)
print("Number of legal moves:", len(valid_moves))

# Test filter_dangerous_moves
safe_moves = player.filter_dangerous_moves(board, valid_moves)
print("Filtered moves:", safe_moves)
print("Number of filtered moves:", len(safe_moves))

# Test get_corners_valid
corner_moves = player.get_corners_valid(valid_moves)
print("Valid corner moves:", corner_moves)

# Test is_second_half
is_secondhalf = player.is_second_half(board)
print("Second half:", is_secondhalf)

# Test score_by_mobility
mobility_scores = player.score_by_mobility(board, valid_moves)
print("Mobility scores (move, opponent options):", mobility_scores)

# Test pick_best (using mobility scores)
best_move = player.pick_best(mobility_scores)
print("Best move by mobility:", best_move)

# Test pick_max_flips
max_flips_move = player.pick_max_flips(board, valid_moves)
print("Move with max flips:", max_flips_move)

# Test simulate (show board after a move)
if valid_moves:
    move_to_simulate = valid_moves[0]
    simulated_board = player.simulate(deepcopy(board), player.my_color, move_to_simulate)
    print(f"Board after simulating move {move_to_simulate}:")
    for row in simulated_board:
        print(row)

# Test select_move
selected_move = player.select_move(board)
print("Selected move:", selected_move)