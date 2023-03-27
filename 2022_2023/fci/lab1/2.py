# analisi prestazioni server multipli
import requests
import matplotlib.pyplot as plt

URLS = [
        "https://www.google.com",
        "https://www.facebook.com",
        "https://www.netflix.com",
        "https://www.gazzetta.it",
        "https://www.corriere.it",
]
ITER = 5 

stat = []
avg_min = float("inf") 
url_min = ""
for i in range(len(URLS)) :
    stat.append([])
    for _ in range(ITER) :
        r = requests.get(URLS[i])
        stat[i].append(r)
        print(f"{URLS[i]} {r.status_code} in {r.elapsed.microseconds/1e3} ms")
    avg = sum([e.elapsed.microseconds/1e3 for e in stat[i]]) / ITER
    if avg < avg_min :
        avg_min = avg
        url_min = URLS[i]

print(f"Avg min is {url_min} with {avg_min}")
