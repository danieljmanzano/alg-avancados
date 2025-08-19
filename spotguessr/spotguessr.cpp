#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cmath>
#include <tuple>
#include <queue>
#include <vector>

using namespace std;

#define RAIO_TERRA 6371.0 // em km

// distancia calculada pela formula de haversine
double distancia(const tuple<double, double>& resposta, const tuple<double, double>& tentativa) {
    double lat1 = get<0>(resposta) * M_PI / 180.0;
    double lon1 = get<1>(resposta) * M_PI / 180.0;
    double lat2 = get<0>(tentativa) * M_PI / 180.0;
    double lon2 = get<1>(tentativa) * M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sqrt(sin(dlat / 2) * sin(dlat / 2) +
                    cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2));
    double res = 2 * asin(a) * RAIO_TERRA;

    return res;
}

/*void printa(const map<string, double>& tentativas, const tuple<double, double>& resposta) {
    cout << "RANKING" << endl << "-------" << endl;
    int i = 1;
    for (const auto& tentativa : tentativas) {
        printf("%2d. %-20s: %7.3f km\n", i, tentativa.first.c_str(), tentativa.second); // print meio esquisito pra ficar formatado conforme esperado
        i++;
    }
}*/

int main(void) {
    /* sintaxe da priority queue: <tipo, container, comparação>
        tipo: par de double e string, onde o primeiro é a distância e o segundo é o nome do jogador
        container: define como os elementos são armazenados, aqui usando vector
        comparação: menor distância primeiro (usando greater) - caso fosse usar a ordenação normal, poderia apenas omitir essa parte */
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> ranking;
    int jogadores = 0;
    cin >> jogadores;
    tuple<double, double> resposta;
    cin >> get<0>(resposta) >> get<1>(resposta); // resposta correta

    tuple<double, double> tentativa;
    string nome;
    double dist;

    for (int i = 0; i < jogadores; i++) {
        cin >> nome >> get<0>(tentativa) >> get<1>(tentativa); // 'get<i>' pega o i-ésimo elemento da tupla
        dist = distancia(resposta, tentativa);
        ranking.push({dist, nome});

        cout << "> [AVISO] MELHOR PALPITE: " << fixed << setprecision(3) << ranking.top().first << "km" << endl;
    }

    // printa(tentativas, resposta);
    // tenho que refazer o print
}