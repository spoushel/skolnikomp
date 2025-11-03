class MyVector:
    def __init__(self, seznam):
        self.data = list(seznam)
        
    def get_vector(self):
        return list(self.data)
    
    def __mul__(self, other):
        if len(self.data) != len(other.data):
            raise ValueError("Vectors must have the same length")
        soucin = 0
        for i in range(len(self.data)):
            soucin = soucin + self.data[i] * other.data[i]    
        return soucin

#local test
#v1 = MyVector([3, 5, 8])
#v2 = MyVector([2, 6, 9])
#print(v1.get_vector())
#print(v1 * v2)