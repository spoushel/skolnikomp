import random

class MyPlayer():
    #def moves
    ''' Hrac najde legitimni moves a jeden si vybere nahodne'''
    def __init__(self, my_color, opponent_color):
        self.my_color = my_color
        self.opponent_color = opponent_color

    def select_move(self, board):
        self.board = board
        dirs = [(0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0), (-1, 1)]
        my_fields = []
        valid_moves = []
        for r in range(len(board)):
            for c in range(len(board[r])):
                if board[r][c] == self.my_color:
                    my_fields.append((r, c))
        for x in range(len(my_fields)):
            curr_pos = my_fields[x]
            curr_r, curr_c = curr_pos

            for d in dirs:
                r_ev = curr_r + d[0]
                c_ev = curr_c + d[1] 

                if(0 <= r_ev < len(board) and 0 <= c_ev < len(board[0])):
                    if board[r_ev][c_ev] == self.opponent_color:
                        #continue in the same dir looking for opp pieces
                        while True:
                            r_ev += d[0]
                            c_ev += d[1]
                            
                            if not (0 <= r_ev < len(board) and 0 <= c_ev < len(board[0])):
                                break
                            if board[r_ev][c_ev] == -1:
                                if (r_ev, c_ev) not in valid_moves:
                                    valid_moves.append((r_ev, c_ev))
                                break
                            elif board[r_ev][c_ev] == self.my_color:
                                break    
        
        if not valid_moves:
            return None
        else:
            return random.choice(valid_moves)
