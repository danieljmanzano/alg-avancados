#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream> // usada para fazer a entrada (uma entrada específica pode ser única ou de mais de um número)
#include <set>
#include <limits>
#include <cstdio>
#include <queue> 
#include <iomanip>

using namespace std;

typedef struct quest_{
    int index;
    int tempo;
    vector<int> pendencias;
} Quest;

typedef struct heroi_{
    string nome;
    string nivel;
    vector<Quest> quests;
    int id; // id baseado na ordem de entrada
} Heroi;

// função que ordena as quests de acordo com suas pendências
vector<int> ordenacao_topologica(const map<int, Quest>& quests_map) {
    map<int, vector<int>> adjacencias; // lista de adjacência para o grafo de quests
    map<int, int> grau_entrada; // quantas pendências cada quest tem

    for (const auto& par : quests_map) grau_entrada[par.first] = 0; // inicializa grau de entrada
    
    for (const auto& par : quests_map) { // constrói o grafo e calcula o grau de entrada de cada quest
        int quest_id = par.first;
        for (int pendencia_id : par.second.pendencias) {
            adjacencias[pendencia_id].push_back(quest_id);
            grau_entrada[quest_id]++;
        }
    }

    // fila de quests que não têm mais pendências
    queue<int> fila;
    for (const auto& par : grau_entrada) 
        if (par.second == 0) fila.push(par.first);

    vector<int> ordem_final;
    while (!fila.empty()) {
        int id_atual = fila.front();
        fila.pop();
        ordem_final.push_back(id_atual);

        // para cada quest que dependia da atual, diminui seu grau de entrada
        if (adjacencias.count(id_atual)) {
            for (int vizinho_id : adjacencias.at(id_atual)) {
                grau_entrada[vizinho_id]--;
                if (grau_entrada[vizinho_id] == 0) 
                    fila.push(vizinho_id);
            }
        }
    }
    return ordem_final;
}

// função que aloca heróis para as quests
double aloca_herois(vector<Heroi>& herois, const map<int, Quest>& quests_map, const map<string, float>& eficiencia) {
    vector<int> ordem_execucao = ordenacao_topologica(quests_map);
    
    double tempo_total = 0.0;
    vector<double> herois_tempo_livre(herois.size(), 0.0);
    map<int, double> quests_tempo_conclusao;

    // itera sobre a ordem encontrada e aloca o melhor herói para cada iteração
    for (int quest_id : ordem_execucao) {
        const Quest& quest_atual = quests_map.at(quest_id);
        
        double melhor_tempo_final = numeric_limits<double>::max();
        int melhor_heroi_id = -1;

        // calcula quando as pendências desta quest estarão prontas
        double tempo_deps_prontas = 0.0;
        for (int p_idx : quest_atual.pendencias) 
            tempo_deps_prontas = max(tempo_deps_prontas, quests_tempo_conclusao.at(p_idx));
        
        // encontra o herói que termina essa quest o mais cedo possível
        for (int i = 0; i < herois.size(); i++) {
            double tempo_inicio = max(herois_tempo_livre[i], tempo_deps_prontas);
            double tempo_necessario = (double)quest_atual.tempo / eficiencia.at(herois[i].nivel);
            double tempo_final_calculado = tempo_inicio + tempo_necessario;

            if (tempo_final_calculado < melhor_tempo_final) {
                melhor_tempo_final = tempo_final_calculado;
                melhor_heroi_id = herois[i].id;
            } else if (tempo_final_calculado == melhor_tempo_final) 
                // desempate: prefere o herói de menor id
                if (herois[i].id < melhor_heroi_id) 
                    melhor_heroi_id = herois[i].id;
            
        }
        
        // atribui a quest ao herói encontrado
        herois_tempo_livre[melhor_heroi_id] = melhor_tempo_final;
        herois[melhor_heroi_id].quests.push_back(quest_atual);
        quests_tempo_conclusao[quest_id] = melhor_tempo_final;
        tempo_total = max(tempo_total, melhor_tempo_final);
    }
    
    return tempo_total;
}

void resultado(vector<Heroi>& herois, double tempo) {
    for (int i = 0; i < herois.size(); i++) {
        cout << herois[i].nome << " = {";
        for (int j = 0; j < herois[i].quests.size(); j++) {
            cout << herois[i].quests[j].index;
            if (j < herois[i].quests.size() - 1) cout << ",";
        }
        cout << "}" << endl;
    }

    cout << "Tempo mínimo: " << fixed << setprecision(2) << tempo << endl;
}

int main(void) {
    const map<string, float> eficiencia = {
        {"Aprendiz", 0.75},
        {"Aventureiro", 1.0}, 
        {"Cavaleiro", 1.2},
        {"Mestre", 1.5},
        {"Lenda", 2.0}
    };

    int casos_teste;
    cin >> casos_teste;

    for (int conta_teste = 0; conta_teste < casos_teste; conta_teste++) {
        int n_herois, n_quests;
        vector<Heroi> herois;
        map<int, Quest> quests_map;

        cin >> n_herois >> n_quests;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa o buffer

        for (int i = 0; i < n_herois; i++) {
            Heroi h;
            h.id = i;
            string linha;
            getline(cin, linha);
            stringstream ss(linha);
            ss >> h.nome >> h.nivel;
            herois.push_back(h);
        }

        for (int i = 0; i < n_quests; i++) {
            Quest q;
            string linha_quest;
            getline(cin, linha_quest);
            stringstream ss(linha_quest);
            ss >> q.index >> q.tempo;
            int pendencia_atual;
            while (ss >> pendencia_atual) {
                if (pendencia_atual == 0) break;
                q.pendencias.push_back(pendencia_atual);
            }
            quests_map[q.index] = q;
        }

        double tempo_total = aloca_herois(herois, quests_map, eficiencia);
        resultado(herois, tempo_total);

        if (conta_teste < casos_teste - 1) cout << endl;
    }
    return 0;
}