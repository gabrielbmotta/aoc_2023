class game():
    
    def __init__(self, gameString):
        self.idx = int(gameString.split(":")[0].split(" ")[1])
        self.gameReveals = gameString.split(":")[1].split(";")
        self.redMax = 12
        self.greenMax = 13
        self.blueMax = 14
        self.redMaxReveal = 0
        self.greenMaxReveal = 0
        self.blueMaxReveal = 0
    
    def isPossible(self):
        for reveal in self.gameReveals:
            for color in reveal.split(","):
                color = color.strip()
                revealColor = color.split(" ")[1]
                revealValue = int(color.split(" ")[0])
                if revealValue > getattr(self, revealColor+"MaxReveal"):
                    setattr(self, revealColor+"MaxReveal", revealValue)
                    
        isPossible = True
        for color in ["red", "green", "blue"]:
            if getattr(self, color+"MaxReveal") > getattr(self, color+"Max"):
                isPossible = False
            
        return isPossible

class game2(game):
    def __init__(self, gameString):
        pass
        super().__init__(gameString)
        self.isPossible() # set MaxReveal variables
        self.power = self.redMaxReveal * self.greenMaxReveal * self.blueMaxReveal

with open("input.txt", "r") as f:
    input = f.readlines()

#Part One
games = [game(line) for line in input]
sum = 0
for game in games:
    if game.isPossible():
        sum += game.idx
print(f"Part One: {sum}")

#Part Two
games2 = [game2(line) for line in input]
sum = 0
for game in games2:
    sum += game.power
print(f"Part Two: {sum}")