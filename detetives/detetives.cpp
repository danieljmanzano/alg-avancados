#include <iostream>
#include <vector>

using namespace std;

// função recursiva com memoization para determinar se o jogador atual ganha
// u: vértice atual
// adj: lista de adjacência do grafo
// memo: vetor para armazenar resultados (-1: não calculado, 0: perde, 1: ganha)
int podeVencer(int u, const vector<vector<int>>& adj, vector<int>& memo) {
    // se já calculamos o resultado para este vértice, retorna o valor
    if (memo[u] != -1) 
        return memo[u];
    
    // tenta encontrar um movimento que deixe o oponente em uma posição perdedora
    // se eu movo para 'v' e o oponente perde (!podeVencer(v)), então eu ganho
    for (int v : adj[u]) {
        if (!podeVencer(v, adj, memo)) {
            memo[u] = 1; // encontrei uma estratégia vencedora
            return 1;
        }
    }

    // se não houver saídas (fim da linha) ou se todas as saídas levam o oponente a posições vencedoras, então eu perco.
    memo[u] = 0;
    return 0;
}

void solve(int n, int m, int s) {

    // cria o grafo (lista de adjacência)
    vector<vector<int>> adj(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    // vetor de memoization inicializado com -1
    vector<int> memo(n, -1);

    // ash começa jogando a partir de 's'
    // se a posição 's' for vencedora para quem joga, ash ganha
    if (podeVencer(s, adj, memo)) {
        cout << "Ash" << endl;
    } else {
        cout << "Noir" << endl;
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m, s;
        cin >> n >> m >> s;
        solve(n, m, s);
    }
    
    return 0;
}