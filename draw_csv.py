import csv
import matplotlib.pyplot as plt

# lit et affiche le csv
# format : posX, posY, num de l'objet (int, de 0 à n, svp sautez pas des nums)

x = [[]]
y = [[]]
n = 0

with open("test.csv") as csvFile :
    readCSV = csv.reader(csvFile, delimiter=',')
    for i in readCSV :
        obj = int(i[2])
        if (obj > n) :
            n = obj
            x.append([])
            y.append([])
        x[obj].append(float(i[0]))
        y[obj].append(float(i[1]))


couleur = ['r', 'g', 'b']
print(x, y)
plt.xlim([-10, 400])
plt.ylim([-100, 100])
for i in range(n+1) :
    plt.plot(x[i], y[i], 'o', color=couleur[i])
plt.ylabel('test')
plt.show()

# g++ -Wall -I include/ src/Vector3.cpp src/Particule.cpp -o exe
# ./exe > test.csv && python3 draw_csv.py 