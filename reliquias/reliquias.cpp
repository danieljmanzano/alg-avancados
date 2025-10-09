#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Reliquia {
    long long peso;
    long long aqp; // custo acumulado quebrando depois 
    long long aqd; // custo acumulado quebrando primeiro 
};

int main() {
    int n;
    cin >> n;

    vector<Reliquia> reliquias(n);
    for (int i = 0; i < n; i++) {
        cin >> reliquias[i].peso;
    }
    
    // caso base para a primeira relíquia (índice 0)
    reliquias[0].aqp = reliquias[0].peso;
    reliquias[0].aqd = reliquias[0].peso;

    // itera da segunda relíquia em diante (base para o topo)
    for (int i = 1; i < n; i++) {
        Reliquia& atual = reliquias[i];
        const Reliquia& anterior = reliquias[i - 1];

        // transição para 'aqp' (quebrar a relíquia atual depois do pilar de baixo)
        atual.aqp = atual.peso + min(anterior.aqp, anterior.aqd);

        // transição para 'aqd' (quebrar a relíquia atual primeiro, causando queda no pilar de baixo)
        long long custo_se_ant_era_aqp = anterior.aqp + max(0LL, atual.peso - i);
        long long custo_se_ant_era_aqd = anterior.aqd + max(0LL, atual.peso - 1);
        
        atual.aqd = min(custo_se_ant_era_aqp, custo_se_ant_era_aqd);
    }
    
    // a resposta final é o melhor custo para a última relíquia (o pilar inteiro)
    cout << min(reliquias[n - 1].aqp, reliquias[n - 1].aqd) << endl;

    return 0;
}