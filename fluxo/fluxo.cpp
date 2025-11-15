#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

// função BFS para encontrar o caminho aumentante
long long bfs(int s, int t, int n, vector<int>& parent, const vector<vector<int>>& adj, const vector<vector<long long>>& capacity) {
    // reseta o vetor de pais para rastrear o caminho nesta iteração
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2; // marca origem
    
    queue<pair<int, long long>> q;
    q.push({s, INF}); // começa com fluxo infinito

    while (!q.empty()) {
        int cur = q.front().first;
        long long flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            // se não visitado E tem capacidade sobrando no cano
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                long long new_flow = min(flow, capacity[cur][next]);
                
                if (next == t)
                    return new_flow; // achou caminho até o destino
                
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

// função principal para calcular o fluxo máximo usando Edmonds-Karp
long long solve(int n, const vector<vector<int>>& adj, vector<vector<long long>>& capacity) {
    long long max_flow = 0;
    vector<int> parent(n + 1); // Vetor auxiliar para reconstruir o caminho
    long long new_flow;

    // enquanto houver caminho com capacidade > 0 da origem (1) ao destino (n)
    while (new_flow = bfs(1, n, n, parent, adj, capacity)) {
        max_flow += new_flow;
        int cur = n;

        // backtracking: atualiza as capacidades no grafo residual
        while (cur != 1) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow; // reduz no sentido de ida
            capacity[cur][prev] += new_flow; // aumenta no sentido de volta
            cur = prev;
        }
    }

    return max_flow;
}

int main(void) {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    // matriz de adjacência para capacidades
    vector<vector<long long>> capacity(n + 1, vector<long long>(n + 1, 0)); // usa n+1 para indexar mais facilmente
    
    // lista de adjacência
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        
        // adiciona arestas (grafo não direcionado para a estrutura, mas o fluxo é direcionado pela capacidade)
        adj[a].push_back(b);
        adj[b].push_back(a); // aresta de volta é necessária para o grafo residual
        
        // como pode haver múltiplos cabos entre os mesmos computadores, soma (não tem problema porque inicializa com 0)
        capacity[a][b] += c; 
        // capacity[b][a] permanece 0 (fluxo unilateral inicial)
    }

    long long resultado = solve(n, adj, capacity);
    cout << resultado << endl;

    return 0;
}