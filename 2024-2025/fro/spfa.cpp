#include <bits/stdc++.h>
using namespace std;

string input =
    " 2"

    " 10 17"
    " 1 2 30"
    " 1 3 28"
    " 1 5 24"
    " 1 7 16"
    " 1 9 0"
    " 3 2 1"
    " 4 2 0"
    " 3 4 0"
    " 5 3 2"
    " 6 3 0"
    " 5 6 0"
    " 7 5 4"
    " 8 5 0"
    " 7 8 0"
    " 9 7 8"
    " 10 7 0"
    " 9 10 0"

    " 19 26"
    " 1 2 30"
    " 1 3 31"
    " 1 4 32"
    " 1 5 33"
    " 1 6 34"
    " 2 7 0"
    " 3 9 -3"
    " 4 11 -8"
    " 5 13 -17"
    " 6 15 -34"
    " 9 8 1"
    " 8 7 0"
    " 9 16 2"
    " 16 7 -2"
    " 11 10 2"
    " 10 9 0"
    " 11 17 4"
    " 17 9 -4"
    " 13 12 4"
    " 12 11 0"
    " 13 18 8"
    " 18 11 -8"
    " 15 14 8"
    " 14 13 0"
    " 15 19 16"
    " 19 13 -16";

typedef vector<vector<pair<int, int>>> Graph;
typedef tuple<bool, vector<int>, vector<int>> Retval;

Retval spfaFIFO(Graph g, int s) {
	deque<int> q;
	vector<int> dist(g.size(), INT_MAX);
	vector<bool> inQ(g.size(), false);
	vector<int> cntQ(g.size(), false);
	vector<int> order;
	dist[s] = 0;
	q.push_back(s);
	inQ[s] = true;
	while (q.size()) {
		int v = q.front();
		q.pop_front();
		inQ[v] = false;
		order.push_back(v);
		cntQ[v]++;
		if (cntQ[v] >= g.size()) return {true, dist, order};
		for (auto [u, w] : g[v]) {
			if (dist[u] > dist[v] + w) {
				dist[u] = dist[v] + w;
				if (!inQ[u]) q.push_back(u);
				inQ[u] = true;
			}
		}
	}
	return {false, dist, order};
}

Retval spfaSmallestLabel(Graph g, int s) {
	set<int> q;
	vector<int> dist(g.size(), INT_MAX);
	vector<bool> inQ(g.size(), false);
	vector<int> cntQ(g.size(), false);
	vector<int> order;
	dist[s] = 0;
	q.insert(s);
	inQ[s] = true;
	while (q.size()) {
		int v = *q.begin();
		q.extract(v);
		inQ[v] = false;
		order.push_back(v);
		cntQ[v]++;
		if (cntQ[v] >= g.size()) return {true, dist, order};
		for (auto [u, w] : g[v]) {
			if (dist[u] > dist[v] + w) {
				dist[u] = dist[v] + w;
				if (!inQ[u]) q.insert(u);
				inQ[u] = true;
			}
		}
	}
	return {false, dist, order};
}

Retval spfaShortestPath(Graph g, int s) {
	set<pair<int, int>> q;
	vector<int> dist(g.size(), INT_MAX);
	vector<bool> inQ(g.size(), false);
	vector<int> cntQ(g.size(), false);
	vector<int> order;
	dist[s] = 0;
	q.emplace(dist[s], s);
	inQ[s] = true;
	while (q.size()) {
		auto [distV, v] = *q.begin();
		q.extract({distV, v});
		inQ[v] = false;
		order.push_back(v);
		cntQ[v]++;
		if (cntQ[v] >= g.size()) return {true, dist, order};
		for (auto [u, w] : g[v]) {
			if (dist[u] > dist[v] + w) {
				if (inQ[u]) q.extract({dist[u], u});
				dist[u] = dist[v] + w;
				q.emplace(dist[u], u);
				inQ[u] = true;
			}
		}
	}
	return {false, dist, order};
}

void test(string Name, Graph g, Retval (*spfa)(Graph g, int s)) {
	bool negLoop;
	vector<int> dist, order;
	cout << Name << ":\n";
	tie(negLoop, dist, order) = spfa(g, 1);
	if (negLoop) {
		cout << "Negative loop";
	} else {
		cout << "Distances: ";
		for (int i = 1; i < g.size(); i++) cout << "(" << i << ", " << dist[i] << ") ";
	}
	cout << "\nProcessing order: [";
	bool first = true;
	for (auto x : order) {
		if (first) first = false;
		else cout << ", ";
		cout << x;
	}
	cout << "]\n\n";
}

void solve(istringstream& stream) {
	int nodes, edges;
	stream >> nodes >> edges;
	Graph g(nodes + 1);
	for (int e = 0; e < edges; e++) {
		int u, v, w;
		stream >> u >> v >> w;
		g[u].push_back({v, w});
	}
	test("FIFO", g, spfaFIFO);
	test("SMALLEST LABEL", g, spfaSmallestLabel);
	test("SHORTEST PATH", g, spfaShortestPath);
}

int main() {
	istringstream stream(input);
	int t = 1;
	stream >> t;
	while (t--) {
		cout << "\n";
		solve(stream);
	}
	return 0;
}
