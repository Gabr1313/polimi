import mip

I = 4
J = 3

b = [5000,2400,4000,1500]
c = [9,7,12,6]
g = [12,18,10]
m = [[  0,  0,  0],
     [0.2,  0,  0],
     [  0,0.4,  0],
     [  0,  0,  0]]
M = [[  1,  1,  1],
     [  1,  1,0.5],
     [0.3,  1,  1],
     [  1,  1,  1]]

mod = mip.Model()
x = [mod.add_var(var_type=mip.INTEGER) for i in range(I)]
y = [mod.add_var(var_type=mip.INTEGER) for j in range(J)]
z = [[mod.add_var(var_type=mip.INTEGER) for j in range(J)] for i in range(I)]

mod.objective = mip.maximize(mip.xsum(y[j]*g[j] for j in range(J)) -
                           mip.xsum(x[i]*c[i] for i in range(I)))

for i in range(I):
    for j in range(J):
        mod.add_constr(z[i][j] >= m[i][j] * y[j])
        mod.add_constr(z[i][j] <= M[i][j] * y[j])

for j in range(J):
    mod.add_constr(mip.xsum(z[i][j] for i in range(I)) == y[j])

for i in range(I):
    mod.add_constr(mip.xsum(z[i][j] for j in range(J)) <= x[i])
    mod.add_constr(x[i] <= b[i])

mod.optimize()

print([x[i].x for i in range(I)])
print([y[j].x for j in range(J)])
print([[z[i][j].x for i in range(I)] for j in range(J)])
