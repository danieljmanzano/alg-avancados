/* versão recursiva do código pro problema. não roda casos muito grandes do runcodes, então tem outra versão pra isso em reliquias.cpp */
/* teoricamente, essa versão é "mais correta" (ou pelo menos mais intuitiva). a outra é mais concisa e linear (mas meio confuso de se pensar) */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<long long> s;
map<pair<pair<int,int>, long long>, long long> memo;

// resolve o intervalo [inicio, fim] onde a primeira relíquia tem dano_inicial
long long solve(int inicio, int fim, long long dano_inicial) {
    if (inicio > fim) return 0;
    
    auto chave = make_pair(make_pair(inicio, fim), dano_inicial);
    if (memo.count(chave)) return memo[chave];
    
    long long estab = s[inicio] - dano_inicial;
    
    // se já quebrou por dano, reação em cadeia (próxima relíquia tem dano 1 por estar na base obrigatoriamente)
    if (estab <= 0) return memo[chave] = solve(inicio + 1, fim, 1);
    
    long long min_custo = 1e18;
    
    // tentamos quebrar primeiro em cada posição j no intervalo
    for (int j = inicio; j <= fim; j++) {
        // batidas apenas para quebrar j (não contamos inicio..j-1 pois será recursivo)
        long long estab_j = s[j];
        if (j == inicio) estab_j -= dano_inicial;
        
        if (estab_j <= 0) // já quebrou, reação em cadeia
            continue;
        
        
        // ao quebrar j criamos duas colunas:
        // 1. [inicio, j-1] - coluna que fica embaixo (resolve recursivamente)
        // 2. [j+1, fim] - coluna que cai ao lado, com dano (j - inicio + 1)
        
        long long custo_embaixo = solve(inicio, j - 1, dano_inicial);
        long long altura_queda = j - inicio + 1;
        long long custo_lado = solve(j + 1, fim, altura_queda);
        
        min_custo = min(min_custo, estab_j + custo_embaixo + custo_lado);
    }
    
    return memo[chave] = min_custo;
}

int main() {
    int n;
    cin >> n;
    
    s.resize(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    
    cout << solve(0, n - 1, 0) << endl;
    
    return 0;
}