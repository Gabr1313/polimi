# does not work still

import mip
import math

# PARAMETHERS
K = 3   # number of symbols per card
S = 5   # number of symbols
U = 1   # symbols in common for pair of cards

# getting this lower improves the speed by so much
N = math.comb(S, K) # number of card max
assert N > 0

# VARIABLES
m = mip.Model()
# la carta i condivide con la carta j il simbolo s
x = [[[m.add_var(var_type=mip.BINARY) for s in range(S)] for j in range(N)] for i in range(N)]
# la carta i usa il simbolo s
z = [[m.add_var(var_type=mip.BINARY) for s in range(S)] for i in range(N)]
# la carta i e' usata 
y = [m.add_var(var_type=mip.BINARY) for i in range(N)]
# cards i and j are used
w = [[m.add_var(var_type=mip.BINARY) for j in range(N)] for i in range(N)]

# OBJECTIVE FUNCTION
m.objective = mip.maximize(mip.xsum(y[i] for i in range(N)))

# CONSTRAINS
for i in range(N):
    for j in range(i):
        for s in range(S):
            # symmtric matrix x
            m.add_constr(x[i][j][s] == x[j][i][s])
            # z[i][s] && z[j][s] <=> x[i][j][s]
            m.add_constr(x[i][j][s] + 1 >= z[i][s] + z[j][s])
            m.add_constr(x[i][j][s] * 2 <= z[i][s] + z[j][s])

for i in range(N):
    for j in range(N):
        # w[i] <=> y[i] && y[j]
        m.add_constr(w[i][j] + 1 >= y[i] + y[j])
        m.add_constr(w[i][j] * 2 <= y[i] + y[j])

for i in range(N):
    # y[i] => exists s: z[i][s]
    m.add_constr(y[i] <= mip.xsum(z[i][s] for s in range(S)))
    # every card, if used, uses K symbols (if the card is used)
    m.add_constr(y[i] * K == mip.xsum(z[i][s] for s in range(S)))

for i in range(N):
    for j in range(N):
        # number of symbols shared = U
        m.add_constr(w[i][j] * U == mip.xsum(x[i][j][s] for s in range(S)))

# OPTIMIZATION
m.optimize()

# RESULTS
# sum = 0
# for s in range(S):
#     sum += y[s].x
# print(sum)

print()
if m.num_solutions:
    print(m.objective_value)
    for n in range(N):
        print("carta " , n, ": ", end="")
        for s in range(S):
            if (z[n][s].x == 1):
                print(s, " ", end="")
        print()
else:
    print("No solution found")
