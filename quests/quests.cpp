#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

typedef struct quest_{
    int index;
    int tempo;
    vector<int> pendencias; // index de quests que são necessárias para realizar essa
} Quest;

typedef struct heroi_{
    string nome;
    string nivel; // Aprendiz, Cavaleiro, Aventureiro, Mestre, Lenda
    vector<Quest> quests; // quests que o herói realizou

    bool operator<(const struct heroi_ &outro) const {
        if (nivel != outro.nivel) {
            // ordem de níveis: Aprendiz < Cavaleiro < Aventureiro < Mestre < Lenda
            vector<string> ordem_niveis = {"Aprendiz", "Cavaleiro", "Aventureiro", "Mestre", "Lenda"};
            return find(ordem_niveis.begin(), ordem_niveis.end(), nivel) < find(ordem_niveis.begin(), ordem_niveis.end(), outro.nivel);
        }
        return false; // se os níveis forem iguais, o primeiro tem preferência
    }
} Heroi;



int main(void) {
    int casos_teste;
    cin >> casos_teste;

    for (int _ = 0; _ < casos_teste; _++) {
        int n_herois, n_quests;
        vector<Heroi> herois;
        map<int, Quest> quests;

        cin >> n_herois >> n_quests;

        for (int i = 0; i < n_herois; i++) {
            Heroi h;
            cin >> h.nome >> h.nivel;
            herois.push_back(h);
        }

        for (int i = 0; i < n_quests; i++) {
            Quest q;
            cin >> q.index >> q.tempo;

            // como a entrada pode ser 1 ou mais números, o resto da linha é lida inteira e depois divide em um vetor de pendências
            string resto_da_linha;
            getline(cin, resto_da_linha);
            int pendencia_atual;
            stringstream ss(resto_da_linha);
            while (ss >> pendencia_atual) {
                if (pendencia_atual == 0) break; // 0 indica que não há pendências
                q.pendencias.push_back(pendencia_atual);
            }
        }

        sort(herois.begin(), herois.end());
        /* logica de escolha dos herois - quests */
    }
}