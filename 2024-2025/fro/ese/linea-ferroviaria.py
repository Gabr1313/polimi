import mip

# Dati
L = 10 # distanza tra citta' iniziale e citta' finale
D = [0, # posizioni antenne
     1,2,3,4,6,7,8,9,
     L]
R = 5 # raggio
N = len(D)-2
M = [[int((D[i] < D[j] and D[j] - D[i] <= R)) for j in range(N+2)] for i in range(N+2)]

I = 4
J = 3

# Var
model = mip.Model()
y   = [[model.add_var(var_type=mip.BINARY) for j in range(N+2)] for i in range(N+2)]

# FOB
model.objective = mip.minimize(mip.xsum(y[i][j] for j in range(N+2) for i in range(N+2)))

# Vincoli
for i in range(N+2):
    for j in range(N+2):
        model += y[i][j] <= M[i][j]

model += mip.xsum(y[0][j]   for j in range(N+2)) >= 1
model += mip.xsum(y[i][N+1] for i in range(N+2)) >= 1

for j in range(1, N+1):
    model +=         mip.xsum(y[i][j] for i in range(N+2)) <= (N+2) * mip.xsum(y[j][k] for k in range(N+2))
    model += (N+2) * mip.xsum(y[i][j] for i in range(N+2)) >=         mip.xsum(y[j][k] for k in range(N+2))

# Risoluzione
model.optimize()

sum = 0
for i in range(1, N+1):
    for j in range(0, N+2):
        sum += y[i][j].x

print("Cost = ", int(sum))
for i in range(N+2):
    for j in range(i+1, N+2):
        if (y[i][j].x == 1):
            print(D[i], D[j])
