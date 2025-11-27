from copy import deepcopy
class MyPlayer():
    '''Hrac preferuje rohy, vyhyba se riziku a v druhe pulce hraje greedy.'''

    dirs = [(0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0), (-1, 1)]
    corners = [(0,0), (0,7), (7,0), (7,7)]

    def __init__(self, my_color, opponent_color):
        self.my_color = my_color
        self.opponent_color = opponent_color

    def get_valid_moves(self, board, player):
        """Pro stav desky a hrace vrati seznam moznych tahu."""
        opp_color = self.opponent_color if player == self.my_color else self.my_color
        player_fields = []
        valid_moves = []
        for r in range(len(board)):
            for c in range(len(board[r])):
                if board[r][c] == player:
                    player_fields.append((r, c))
        for curr_r, curr_c in player_fields:
            for d in self.dirs:
                r_new = curr_r + d[0]
                c_new = curr_c + d[1] 
                if 0 <= r_new < len(board) and 0 <= c_new < len(board[0]):
                    if board[r_new][c_new] == opp_color:
                        #continue in the same dir looking for opp pieces
                        temp_r, temp_c = r_new, c_new
                        while True:
                            temp_r += d[0]
                            temp_c += d[1]
                        
                            if not (0 <= temp_r < len(board) and 0 <= temp_c < len(board[0])):
                                break
                            if board[temp_r][temp_c] == -1:
                                if (temp_r, temp_c) not in valid_moves:
                                    valid_moves.append((temp_r, temp_c))
                                break
                            elif board[temp_r][temp_c] == player:
                                break    
        return valid_moves

    def get_corners_valid(self, valid_moves):
        """Vyfiltruje z moznych tahu jen rohy pokud nejake jsou mozne."""
        corner_valid_moves = []
        for move in valid_moves:
            if move in self.corners:
                corner_valid_moves.append(move)
        return corner_valid_moves
    
    def filter_dangerous_moves(self, board, valid_moves):
        """Vyfiltruje z moznych tahu ty, ktere by umoznily protihraci ziskat roh."""
        safe_moves = []
        for move in valid_moves:
            new_board = self.simulate(board, self.my_color, move)
            opponent_moves = self.get_valid_moves(new_board, self.opponent_color)
            if any (m in self.corners for m in opponent_moves):
                continue
            safe_moves.append(move)
        return safe_moves

    def is_second_half(self, board):
        """Podle obsazenosti desky vrati, zda je jiz druha pulka hry."""
        taken_fields = []
        num_fields = len(board) * len(board[0])
        for r in range(len(board)):
            for c in range(len(board[r])):
                if board[r][c] == self.my_color or board[r][c] == self.opponent_color:
                    taken_fields.append((r, c))
        return len(taken_fields) >= num_fields / 2
                
    def score_by_mobility(self, board, move_options):
        """Ohodnoti tahy podle toho jak moc nasledne znevyhodni protihrace."""
        scored_moves = []
        for move in move_options:
            new_board = self.simulate(board, self.my_color, move)
            opponent_moves = self.get_valid_moves(new_board, self.opponent_color)
            scored_moves.append((move, len(opponent_moves)))
        return scored_moves

    def pick_best(self, scored_moves):
        """Z ohodnocenych tahu vybere ten, ktery nejvice znevyhodni protihrace."""
        best_move = None
        best_score = float('inf')
        for move, score in scored_moves:
            if score < best_score:
                best_score = score
                best_move = move
        return best_move

    def pick_max_flips(self, board, move_options):
        """Vybira tah, ktery simulovane otoci nejvice kamenu."""
        max_flips = -1
        best_move = None
        for move in move_options:
            new_board = self.simulate(board, self.my_color, move)
            original_count = sum(row.count(self.my_color) for row in board)
            new_count = sum(row.count(self.my_color) for row in new_board)
            flips = new_count - original_count
            if flips > max_flips:
                max_flips = flips
                best_move = move
        return best_move
    
    def simulate(self, board, player, move):
        """Nasimuluje desku po konkretnim move."""
        new_board = deepcopy(board)
        r, c = move
        new_board[r][c] = player
        #flip discs
        for d in self.dirs:
            discs_to_flip = []
            r_new, c_new = r + d[0], c + d[1]
            while 0 <= r_new < len(board) and 0 <= c_new < len(board[0]):
                if new_board[r_new][c_new] == -1:
                    break 
                if new_board[r_new][c_new] == player:
                    for fr, fc in discs_to_flip:
                        new_board[fr][fc] = player
                    break
                else:
                    discs_to_flip.append((r_new, c_new))
                r_new += d[0]
                c_new += d[1]
        return new_board
 

    def select_move(self, board):
        self.board = board
        valid_moves = self.get_valid_moves(board, self.my_color)
        if not valid_moves: #kdyz nic nejde tak pokracuje hra
            return None
        corners = self.get_corners_valid(valid_moves)
        if corners:
            return self.pick_max_flips(board, corners)
        safe_moves = self.filter_dangerous_moves(board, valid_moves)
        move_options = safe_moves if safe_moves else valid_moves
        if not self.is_second_half(board):
            final_scores = self.score_by_mobility(board, move_options)
            return self.pick_best(final_scores)
        return self.pick_max_flips(board, move_options)
