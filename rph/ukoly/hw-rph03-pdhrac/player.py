import random

def opposite_move(move):
    if move == 'R':
        return 'P'
    elif move == 'P':
        return 'S'
    elif move == 'S':
        return 'R'
    else:
        print("Spatny vstup!")

class MyPlayer():
    ''' blablabla '''
    def __init__(self, memlength, weights=None):
        self.memlength = memlength
        self.history = [None] * self.memlength

        if weights is None:
            self.weights = [1,1,1]
        else: 
            self.weights = weights

    def select_move(self):
        if None in self.history:
            return random.choices('R', 'P', 'S'), self.weights
        else:
            random_opp_move = random.choice(self.history)
            return opposite_move(random_opp_move)

    def record_last_moves(self, opp_move):
        self.history.insert(0, opp_move)
        del self.history[-1]
