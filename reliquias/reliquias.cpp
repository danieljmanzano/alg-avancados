/* versão iterativa do código pro problema. segue a mesma lógica do recursivo, mas torna mais otimizado para rodar os casos grandes */
// detalhe: até o momento ainda não consigo rodar 3 casos específicos por causa de 'core_dumped'
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false); // coisa pra otimizar
    cin.tie(NULL); // coisa pra otimizar

    int n;
    cin >> n;
    
    vector<long long> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    
    
    // tabela DP 3D para memoizar os resultados: dp[inicio][fim][dano_inicial]
    // a terceira dimensão vai até n porque o dano de queda não passa desse valor
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(n + 1, INF))); // doidera rs

    // lógica iterativa preenche a tabela dos menores subproblemas para os maiores
    for (int len = 1; len <= n; len++) {
        for (int inicio = 0; inicio <= n - len; inicio++) {
            int fim = inicio + len - 1;
            
            // itera sobre todos os possíveis danos que este subproblema pode ter recebido (até n)
            for (int dano_inicial = 0; dano_inicial <= n; dano_inicial++) {
                
                // lógica da função 'solve'

                long long estab_primeiro = s[inicio] - dano_inicial;

                // caso da reação em cadeia
                if (estab_primeiro <= 0) {
                    // o próximo bloco [inicio+1, fim] sofre 1 de dano
                    long long custo_recursivo = (inicio + 1 > fim) ? 0 : dp[inicio + 1][fim][1];
                    dp[inicio][fim][dano_inicial] = custo_recursivo;
                    continue; 
                }

                long long min_custo_estado = INF;

                // itera sobre 'j', o ponto a ser quebrado primeiro
                for (int j = inicio; j <= fim; j++) {
                    long long estab_j = s[j];
                    if (j == inicio) {
                        estab_j -= dano_inicial;
                    }
                    
                    // se estab_j já for 0 ou menos, não podemos escolher bater nela (a lógica de reação em cadeia já trataria disso)
                    if (estab_j <= 0) continue;
                    
                    // custo para limpar o que ficou embaixo
                    long long custo_embaixo = (j > inicio) ? dp[inicio][j - 1][dano_inicial] : 0;
                    
                    // custo para limpar o que caiu ao lado
                    long long custo_lado = 0;
                    if (j < fim) {
                        long long altura_queda = j - inicio + 1;
                        // o dano de queda (altura_queda) não passa de n
                        custo_lado = dp[j + 1][fim][altura_queda];
                    }
                    
                    min_custo_estado = min(min_custo_estado, estab_j + custo_embaixo + custo_lado);
                }
                
                dp[inicio][fim][dano_inicial] = min_custo_estado;
            }
        }
    }
    
    // a resposta final é para o problema original [0, n-1] com dano inicial 0.
    cout << dp[0][n-1][0] << endl;
    
    return 0;
}