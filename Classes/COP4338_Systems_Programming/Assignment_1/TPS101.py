"""
    This is the Villager class.
    It is a base class for all villagers.
    It contains the basic information for a villager.
"""

class Villager:
    def __init__(self, name, species, catchphrase):
        self.name = name
        self.species = species
        self.catchphrase = catchphrase
        self.furniture = []
	
    def set_catchphrase(self,new_catchphrase):
        if len(new_catchphrase) > 20:
              print("invalid Catchphrase ")
              return
        for i in range(len(new_catchphrase)):
            if new_catchphrase[i] == " " or new_catchphrase[i].isalpha():
                 continue
            else:
                 print("Invalid Catchphrase")
                 return
        self.catchphrase = new_catchphrase
alice = Villager("Alice", "Koala", "guvnor")

alice.set_catchphrase("sweet dreams")
print(alice.catchphrase)
alice.set_catchphrase("#?!")
print(alice.catchphrase)
        
