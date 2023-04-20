# analisi performance di un server http
import requests
import matplotlib.pyplot as plt

ITER = 10
URL = "http://www.google.it"

statistiche = []
for _ in range(10):
    r = requests.get(URL)
    statistiche.append(r)
    print(f"Status code = {r.status_code}")
w = [e.elapsed.microseconds/1e3 for e in statistiche]
print(f"Var type = {type(statistiche[0])}")
print(f"Avg elapsed time = {sum(w)/ITER} ms")
print(f"Min elapsed time = {min(w)} ms")
plt.plot(w)
plt.plot(w, "ro")
plt.bar([e for e in range(ITER)], w)
plt.xlabel("Requests")
plt.ylabel("Time")
plt.title("Analysis")
plt.grid()
# plt.xlim(min(w), max(w))
# plt.ylim()
plt.axhline(sum(w)/ITER)
plt.show()
