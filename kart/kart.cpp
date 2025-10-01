#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct jogador_ {
    int s0, sf;

    bool operator<(const jogador_& outro) const {
        return s0 < outro.s0;
    }
} Jogador;

typedef struct resultado_ {
    long long ultrapassagens;
    int id;

    bool operator<(const resultado_& outro) const {
        if (ultrapassagens != outro.ultrapassagens)
            return ultrapassagens > outro.ultrapassagens; 
        return id < outro.id; // critério de desempate
    }
} Resultado;


// função que merja dois subvetores e conta as inversões
long long merge_e_conta(vector<int>& vet, vector<int>& temp, int esq, int meio, int dir) {
    int i = esq;
    int j = meio + 1;
    int k = esq;
    long long conta_inv = 0;

    while ((i <= meio) && (j <= dir)) {
        if (vet[i] <= vet[j]) 
            temp[k++] = vet[i++];
        else {
            temp[k++] = vet[j++];
            conta_inv += (meio - i + 1);
        }
    }

    while (i <= meio) temp[k++] = vet[i++];
    
    while (j <= dir) temp[k++] = vet[j++];

    for (i = esq; i <= dir; i++) vet[i] = temp[i];
    
    return conta_inv;
}

// mergesort recursivo para contar as inversões
long long mergesort(vector<int>& vet, vector<int>& temp, int esq, int dir) {
    long long conta_inv = 0;
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        conta_inv += mergesort(vet, temp, esq, meio);
        conta_inv += mergesort(vet, temp, meio + 1, dir);
        conta_inv += merge_e_conta(vet, temp, esq, meio, dir);
    }
    return conta_inv;
}

// função principal para calcular as ultrapassagens de um certo trecho
long long calcula_ultrapassagens() {
    int j;
    cin >> j;

    vector<Jogador> jogadores(j);
    for (int i = 0; i < j; ++i) cin >> jogadores[i].s0 >> jogadores[i].sf; // entrada

    sort(jogadores.begin(), jogadores.end()); // ordena os jogadores do trecho (com base em s0)

    vector<int> jogadores_sf(j);
    for (int i = 0; i < j; ++i) jogadores_sf[i] = jogadores[i].sf; // forma um vetor dos sf
    
    vector<int> temp(j);
    return mergesort(jogadores_sf, temp, 0, j - 1);
}

int main() {

    int n_trechos;
    cin >> n_trechos;

    vector<Resultado> resultados;
    for (int i = 0; i < n_trechos; ++i) {
        long long ultrapassagens = calcula_ultrapassagens();
        resultados.push_back({ultrapassagens, i});
    }

    sort(resultados.begin(), resultados.end());

    for (const auto& r : resultados) 
        cout << r.id << " " << r.ultrapassagens << "\n";
    
    return 0;
}