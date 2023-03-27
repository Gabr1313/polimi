# analisi prestazioni server multipli
import requests
import matplotlib.pyplot as plt

URLS = [
        "https://www.google.com",
        "https://www.facebook.com",
        "https://www.youtube.com"
]
COLORS = ["r", "g", "b"]
ITER = 5 

stat = []
time = []
for i in range(len(URLS)) :
    stat.append([])
    for _ in range(ITER) :
        r = requests.get(URLS[i])
        stat[i].append(r)
        print(f"{URLS[i]} {r.status_code} in {r.elapsed.microseconds/1e3} ms")
    time.append([e.elapsed.microseconds/1e3 for e in stat[i]])
    plt.plot(time[i], COLORS[i], label = URLS[i])
    plt.plot(time[i], "o" + COLORS[i])
    plt.axhline(sum(time[i])/ITER, color = COLORS[i], linestyle = "--")

plt.xlabel("Requests")
plt.ylabel("Time")
plt.title("Analysis")
plt.grid()
plt.legend(loc = "best")
plt.show()
