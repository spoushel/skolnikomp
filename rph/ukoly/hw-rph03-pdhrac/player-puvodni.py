import random

payoff_matice = (((4,4),(1,6)), ((6,1),(2,2)))

class MyPlayer():
    ''' Hrac spolupracuje poprve a vzdy kdyz i protihrac, jinak 1:2 C:D.'''
    def __init__(self, payoff_matice, iterations=None):
        self.payoff_matice = payoff_matice
        self.iterations = iterations
        self.memlength = 50
        self.history = [None] * self.memlength
        self.my_history = [None] * self.memlength
        self.first_move = True

    def select_move(self): 
        if self.first_move: # Pokud jde o první kolo tak vždy spoulpracuje
            self.first_move = False
            return True
        
        last_opp_move = self.history[0]
        
        if last_opp_move:
            return True
        else:
            rand_num = random.randint(1,3) # Poměr cooperate : defect je po defectu protihráče 1:2
            return rand_num == 3

    def record_last_moves(self, my_move, opp_move):
        if type(opp_move) != bool:
            print(f"Špatný vstup!")
            return
        
        self.history.insert(0, opp_move)
        if len(self.history) >= self.memlength:
            del self.history[-1]

        self.my_history.insert(0, my_move) # Zatím nevyužíváme 
        if len(self.my_history) >= self.memlength:
            del self.my_history[-1]