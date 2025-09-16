#include <iostream>
#include <string>
#include <cmath>
#include <tuple>
#include <queue>
#include <vector>

using namespace std;

#define RAIO_TERRA 6371.0 // em km

// distancia calculada pela formula de haversine
double distancia(const pair<double, double>& resposta, const pair<double, double>& tentativa) {
    double lat1 = get<0>(resposta) * M_PI / 180.0;
    double lon1 = get<1>(resposta) * M_PI / 180.0;
    double lat2 = get<0>(tentativa) * M_PI / 180.0;
    double lon2 = get<1>(tentativa) * M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sqrt(sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2));
    double res = 2 * asin(a) * RAIO_TERRA;

    return res;
}

int main(void) {
    /*sintaxe da priority queue: <tipo, container, comparação>
        -tipo: par de double e string, onde o primeiro é a distância e o segundo é o nome do jogador
        -container: define como os elementos são armazenados, aqui usando vector
        -comparação: menor distância primeiro (usando greater) - caso fosse usar a ordenação normal, poderia apenas omitir essa parte */
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> ranking;
    int jogadores = 0;
    cin >> jogadores;
    pair<double, double> resposta;
    cin >> get<0>(resposta) >> get<1>(resposta); // coordenadas a serem adivinhadas

    pair<double, double> tentativa;
    string nome;
    double dist;

    for (int i = 0; i < jogadores; i++) {
        cin >> nome >> get<0>(tentativa) >> get<1>(tentativa); // 'get<i>' pega o i-ésimo elemento da tupla
        dist = distancia(resposta, tentativa); // distancia calculada com base nas tuplas resposta e tentativa
        ranking.push({dist, nome}); // acrescenta o jogador e a distância na fila

        printf("> [AVISO] MELHOR PALPITE: %.3lfkm\n", ranking.top().first);
    }

    cout << endl; 
    cout << "RANKING" << endl << "-------" << endl;
    int i = 1;
    while (!ranking.empty()) {
        pair<double, string> melhor_jogada = ranking.top();
        printf("%2d. %-21s: %6.3f km", i, melhor_jogada.second.c_str(), melhor_jogada.first); // print meio esquisto para estar formatado conforme o exercício
        if (melhor_jogada.first <= 0.050) cout << " [FANTASTICO]";
        cout << endl;
        ranking.pop(); // cada iteração retira a melhor tentativa da fila. assim, vai progredindo para printar todas ordenadamente
        i++;
    }

    return 0;
}