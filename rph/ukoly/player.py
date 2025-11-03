class MyPlayer():
    ''' Hrac spolupracuje poprve a pozdeji na zaklade likeability skore.'''
    def __init__(self, payoff_matrix, number_of_iterations=None):
        self.payoff_matrix = payoff_matrix
        self.number_of_iterations = number_of_iterations
        
        # memory setup
        self.memlength = 10
        self.history = []
        self.my_history = []
        self.first_move = True
        
        # payoff matrix values
        R, S, T, P = payoff_matrix[0][0][0], payoff_matrix[0][1][0], payoff_matrix[1][0][0], payoff_matrix[1][1][0]
        coop_gain = R - P
        sucker_cost = R - S 
        tempt_gain = T - R
        
        # logic
        self.plus = max(0.1 * coop_gain, 0.1)
        self.minus = max(0.2 * sucker_cost, 0.2)
        if coop_gain < 0.05:
            self.threshold = 1.4
        else:
            self.threshold = min(1.0 + tempt_gain / coop_gain, 2.0)
        self.likeability = 1.0
        self.self_mode = False

    def select_move(self):
        if self.first_move:
            self.first_move = False
            return False  
        
        if self.self_mode:
            return False 
        
        # decide depending on likeability and threshold
        if self.likeability >= self.threshold:
            return False  
        else:
            return True 

    def record_last_moves(self, my_move, opp_move):
        if type(opp_move) != bool:
            print("Špatný vstup!")
            return
                
        self.history.append(opp_move)
        self.my_history.append(my_move)
        if len(self.history) > self.memlength: 
            self.history.pop(0)
        if len(self.my_history) > self.memlength:
            self.my_history.pop(0)

        if opp_move == False:  
            self.likeability = min(self.likeability + self.plus, 3.0)  
        else: 
            self.likeability = max(self.likeability - self.minus, 0.0)
        
        # self-play detection
        if not self.self_mode and len(self.history) >= 10:
            mismatches = sum(1 for i in range(-10, 0) if self.my_history[i] != self.history[i])
            if mismatches <= 1:
                self.self_mode = True