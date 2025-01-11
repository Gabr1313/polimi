import mip

# PARAMETHERS
N = 5   # number of card
K = 4   # number of symbols per card
U = 1   # symbols in common for pair of cards

# getting this lower improves the speed by so much
S = U + N * (K - U) # max number of symbols (every card shares the same symbol
                    #                        and the others are different)
assert S > 0

# VARIABLES
m = mip.Model()
# la carta i condivide con la carta j il simbolo s
x = [[[m.add_var(var_type=mip.BINARY) for s in range(S)] for j in range(N)] for i in range(N)]
# la carta i usa il simbolo s
z = [[m.add_var(var_type=mip.BINARY) for s in range(S)] for i in range(N)]
# il simbolo s e' usato
y = [m.add_var(var_type=mip.BINARY) for s in range(S)]

# OBJECTIVE FUNCTION
m.objective = mip.minimize(mip.xsum(y[s] for s in range(S)))

# CONSTRAINS
for i in range(N):
    for j in range(i):
        for s in range(S):
            # symmtric matrix x
            m.add_constr(x[i][j][s] == x[j][i][s])
            # z[i][s] && z[j][s] <=> x[i][j][s]
            m.add_constr(x[i][j][s] + 1 >= z[i][s] + z[j][s])
            m.add_constr(x[i][j][s] * 2 <= z[i][s] + z[j][s])

# every pair of cards have U symbols in common
for i in range(N):
    for j in range(i):
        m.add_constr(U == mip.xsum(x[i][j][s] for s in range(S)))

for s in range(S):
    # if exists(i : (z[i][s] == 1)) => (y[s] == 1)
    m.add_constr(N * y[s] >= mip.xsum(z[i][s] for i in range(N)))

# every card has K symbols
for i in range(N):
    m.add_constr(K == mip.xsum(z[i][s] for s in range(S)))

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
