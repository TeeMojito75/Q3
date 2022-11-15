# Grafos

Si queremos hacer un algoritmo con un grafo no dirigido, creamos una matriz de adjacencias.

Esta matriz está implementada con un vector de vectores de enteros(vertices).

```c++
typedef int vertex;
typedef vector<vertex> adjacency_list;
typedef vector<adjacency_list> graph;

graph G(n, adjacency_list(0));
		for (int i = 0; i < m; ++i)	{ 	
			int a, b;
			cin >> a >> b;
			G[a].push_back(b);					// a -> b
			G[b].push_back(a);					// b -> a
		}
```

Ponemos la adyacencia en los vectores que representan los vértices implicados.


Para los grafos dirigidos, la adyacencia se pone solo en el vector el cual "envía el arco".

```c++
typedef int vertex;
typedef vector<vertex> adjacency_list;
typedef vector<adjacency_list> graph;

graph G(n, adjacency_list(0));
		for (int i = 0; i < m; ++i)	{
			int a, b;
			cin >> a >> b;
			G[a].push_back(b);					// a -> b
		}
```

Si el grafo tiene pesos, el proceso es el mismo, pero se suelen utilizar pairs que permitan guardar el peso y el vector adyacente. Además, se usan priority_queues<peso,vertice> para ordenarlas.


## DFS: Depth-First-Search

Búsqueda en profundidad. Se avanza por el grafo hasta encontrar un punto por el que no podemos avanzar y realizamos el mismo proceso para cada uno de los vértices recorridos anteriormente, hacia atrás.

#### Ejemplo: Black-Red trees:


```c++
bool check_if(graph& G, vector<int>& visitats, int v, int father, int color) {
	visitats[v] = color;
	for (auto w : G[v]) {
		if (visitats[w] == -1) {
			if (not check_if(G, visitats, w, v, 1 - color)) return false;
		}
		else {
			if (color == visitats[w]) return false;	// father has same color as adjacency
		}
	}
	return true;
}

bool black_red(graph& G) {
	vector<int> visitats(G.size(), -1);

	for (int i = 0; i < G.size(); ++i) {
		if (visitats[i] == -1) {
			if (not check_if(G, visitats, i, i, 0)) return false; 
		}
	}
	return true;
}
```

## BFS: Breadth-First-Search

Búsqueda en amplitud. Recorremos todos los vértices adyacentes a un vector antes de avanzar al siguiente

#### Ejemplo:

```c++
list<int> bfs (const graph& G) {
	int n = G.size();
	list<int> L;
	queue<int> Q;
	vector<bool> enc(n, false);
	for (int u = 0; u < n; ++u) {
		if (not enc[u]) {
			Q.push(u);
			enc[u] = true;
			while (not Q.empty()) {
				int v = Q.front(); Q.pop();
				L.push_back(v);
				for (int w : G[v]) {
					if (not enc[w]) {
						Q.push(w); enc[w] = true;
					} 
				} 
			}
		}
	}
	return L; 
}
```

## Topological sort

Ordenación por prioridades. Se leen diversos elementos cada uno con una prioridad sobre otro.

#### Ejemplo:

```c++
typedef vector<vector<int>> graph;

void topographical_sort(graph& G) {

	vector<int> pred(G.size(), 0);

	for (int i = 0; i < G.size(); ++i) {
		for (int j = 0; j < G[i].size(); ++j) {
			++pred[G[i][j]];
		}
	}

	priority_queue<int, vector<int>, greater<int>> order;

	for (int i = 0; i < G.size(); ++i) {
		if (pred[i] == 0) order.push(i);
	}
	while (not order.empty()) {
		cout << order.top();
		int x = order.top();
		order.pop();
		for (int i = 0; i < G[x].size(); ++i) {
			--pred[G[x][i]];
			if(pred[G[x][i]] == 0) order.push(G[x][i]);
		}
		if(not order.empty()) cout << " ";
	}
	cout << endl;
}

int main() {
	int n,m;

	while (cin >> n >> m) {
		int a,b;
		graph elems(n, vector<int>(0));

		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			elems[a].push_back(b);		// a should appear before b
		}
		topographical_sort(elems);
	}
}
```

## Dijkstra's algorithm

Nos permite encontrar el camino mínimo para un grafo con pesos dirigido.

* Respetamos siempre el algoritmo base
* Si hemos de computar algo además del peso mínimo, se pone como añadido a la función original

#### Ejemplo:


```c++
const int INF = 1e9;
typedef pair<int, int> arch;
typedef vector<arch> adjacency_list;
typedef vector< adjacency_list> weighted_graph;

void Dijkstra(weighted_graph& G, int i, int j, int& cost){	// i is starting point, j is ending point
	vector<int> weights(G.size(), INF);
	vector<bool> visits(G.size(), false);
	weights[i] = 0;
	priority_queue<arch, vector<arch>, greater<arch> > candidates;
	candidates.push(arch(0, i));

	while (!candidates.empty()) {
		int u = candidates.top().second;
		candidates.pop();
		if (not visits[u]) {
			visits[u] = true;
			for (auto w : G[u]) {	// para cada elemento de sus aristas
				int a = w.first;	// pos
				int b = w.second;	// weight

				if (weights[a] > weights[u] + b) {
					weights[a] = weights[u] + b;
					candidates.push(arch(weights[a], a));
				}
			}
		}
	}

	cost = weights[j];
}

int main() {
	int n, m;

	while (cin >> n >> m) {
		int a,b,c;
		weighted_graph G(n);
		for (int i = 0; i < m; ++i) {
			cin >> a >> b >> c;
			G[a].push_back(make_pair(b,c));
		}
		int i,j;
		cin >> i >> j;
		int cost;
		Dijkstra(G, i, j, cost);
		if (cost == INF) cout << "no path from " << i << " to " << j << endl;
		else cout << cost << endl;
	}
}
```

## Prim's Algorithm for MSTs (Minnimum Spanning Trees)

Sigue la base del algoritmo de Dijkstra, con la diferencia de que el grafo no es dirigido, por lo que la matriz de adyacencias seguirá el estilo que hemos visto anteriormente: a -> b && b -> a.

#### Ejemplo:

```c++
typedef pair<int, int> edge;
typedef vector<edge> adjacency_list;
typedef vector< adjacency_list> weighted_graph;

void Prim_algorithm(const weighted_graph& G, int& MST_weight) {
	vector<bool> visited(G.size(), false);	// none have been visited yet
	priority_queue <edge, vector<edge>, greater<edge>> candidates;	// where the first member of the edge represents it's weight, and the second the vertex it arrives to
	visited[0] = true;

	for (auto w : G[0]) candidates.push(w);
	int size = 1;

	while (size < G.size()) {
		int a = candidates.top().first;		// weight
		int b = candidates.top().second;	// vertex

		candidates.pop();

		if (not visited[b]) {
			visited[b] = true;

			for (auto q : G[b]) candidates.push(q);
			MST_weight += a;
			++size;
		}
	}
}

int main() {
	int n, m;

	while (cin >> n >> m) {
		int a,b,c;
		weighted_graph G(n);
		for (int i = 0; i < m; ++i) {
			cin >> a >> b >> c;
			G[a - 1].push_back(edge(c,b - 1));		// dirección de arco con su peso
			G[b - 1].push_back(edge(c,a - 1));		// dirección de arco con su peso
		}
		int MST_weight = 0;
		Prim_algorithm(G, MST_weight);

		cout << MST_weight << endl;
	}
}
```
