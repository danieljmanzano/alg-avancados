#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <cmath>
#include <tuple>

using namespace std;

#define RAIO_TERRA 6371.0 // em km

// distancia calculada pela formula de haversine
float distancia(const tuple<float, float>& resposta, const tuple<float, float>& tentativa) {
    float lat1 = get<0>(resposta) * M_PI / 180.0;
    float lon1 = get<1>(resposta) * M_PI / 180.0;
    float lat2 = get<0>(tentativa) * M_PI / 180.0;
    float lon2 = get<1>(tentativa) * M_PI / 180.0;

    float dlat = lat2 - lat1;
    float dlon = lon2 - lon1;

    // aqui falta montar a propria equacao (ô bagulho feio, depois vejo)

    return 0.0;
}

void printa(const map<string, float>& tentativas, const tuple<float, float>& resposta) {
    // tenho que arranjar um jeito de formatar a saída conforme ta no exercicio (meio peba)
    cout << "RANKING" << endl << "-------" << endl;
    int i = 1;
    for (const auto& tentativa : tentativas) {
        cout << i << ". " << tentativa.first << " ";
        cout << fixed << setprecision(2) << tentativa.second << " km" << endl;
        i++;
    }

}   

int main(void) {
    map<string, float> tentativas;
    int jogadores = 0;
    cin >> jogadores;
    tuple<float, float> resposta;
    cin >> get<0>(resposta) >> get<1>(resposta); // resposta correta

    tuple<float, float> tentativa;
    string nome;
    float dist;
    float melhor = INFINITY;

    for (int i = 0; i < jogadores; i++) {
        cin >> nome >> get<0>(tentativa) >> get<1>(tentativa); // 'get<i>' pega o i-ésimo elemento da tupla
        dist = distancia(resposta, tentativa);
        auto res = tentativas.insert({nome, dist});

        if (dist < melhor) melhor = dist;
        cout << "> [AVISO] MELHOR PALPITE: " << fixed << setprecision(3) << melhor << "km" << endl;
    }

    printa(tentativas, resposta);

}