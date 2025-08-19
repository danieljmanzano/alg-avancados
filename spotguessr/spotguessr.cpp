#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <iomanip>
#include <cmath>
#include <tuple>

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

    // ainda tenho que fazer a formula do barato

    return 0.0;
}

void printa(const map<string, double>& tentativas, const tuple<double, double>& resposta) {
    cout << "RANKING" << endl << "-------" << endl;
    int i = 1;
    for (const auto& tentativa : tentativas) {
        printf("%2d. %-20s: %7.3f km\n", i, tentativa.first.c_str(), tentativa.second); // print meio esquisito pra ficar formatado conforme esperado
        i++;
    }
    
}

int main(void) {
    map<string, double> tentativas;
    int jogadores = 0;
    cin >> jogadores;
    tuple<double, double> resposta;
    cin >> get<0>(resposta) >> get<1>(resposta); // resposta correta

    tuple<double, double> tentativa;
    string nome;
    double dist;
    double melhor = INFINITY;

    for (int i = 0; i < jogadores; i++) {
        cin >> nome >> get<0>(tentativa) >> get<1>(tentativa); // 'get<i>' pega o i-ésimo elemento da tupla
        dist = distancia(resposta, tentativa);
        auto res = tentativas.insert({nome, dist});

        if (dist < melhor) melhor = dist;
        cout << "> [AVISO] MELHOR PALPITE: " << fixed << setprecision(3) << melhor << "km" << endl;
    }

    printa(tentativas, resposta);

}