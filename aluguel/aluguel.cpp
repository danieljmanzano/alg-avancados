#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/*exercício para usar abordagem de algoritmo guloso
    dado um vetor de "alugueis" (com id, horário de início e fim, id do carro), aloco o máximo de alugueis possíveis
    pra isso, ordeno os alugueis de cada carro com base no horário de fim
    depois, aloco aqueles que não se sobrepõem*/

typedef struct horario {
    int h, m; // horas, minutos

    bool operator<(const struct horario& outra) const {
        if (h != outra.h) return h < outra.h;
        return m < outra.m;
    }
    bool operator==(const struct horario& outra) const {
        return h == outra.h && m == outra.m;
    }
} Horario;

typedef struct aluguel {
    Horario inicio;
    Horario fim;
    int id_aluguel;
    int id_carro;
} Aluguel;

// função para processar a entrada de um aluguel. a entrada é feita na própria chamada da função
Aluguel processa_aluguel() {
    // leitura
    int id_aluguel, id_carro;
    Horario inicio, fim;
    char dois_pontos; // para ler o caracter ':'
    cin >> id_aluguel;
    cin >> inicio.h >> dois_pontos >> inicio.m >> fim.h >> dois_pontos >> fim.m;
    cin >> id_carro;

    // armazenamento
    Aluguel aluguel;
    aluguel.id_aluguel = id_aluguel;
    aluguel.id_carro = id_carro; 
    aluguel.inicio = inicio;
    aluguel.fim = fim;
    return aluguel;
}

// função para ordenar os alugueis de um carro com base no horário de início
void ordena_alugueis(int quant_carros, map<int, vector<Aluguel>> &alugueis) {
    for (int id_carro = 1; id_carro <= quant_carros; id_carro++)
        sort(alugueis[id_carro].begin(), alugueis[id_carro].end(), 
            // lambda para comparar dois alugueis com base no horário de início
            [](const Aluguel &a, const Aluguel &b) {
                // se o fim for diferente, ordena pelo fim (teoricamente a ideia primordial desse sort)
                if (!(a.fim == b.fim)) return a.fim < b.fim;
                // caso os horários sejam iguais, ordena pelo id do aluguel
                if (a.inicio == b.inicio && a.fim == b.fim) return a.id_aluguel < b.id_aluguel;
                // último critério: caso apenas os fins sejam iguais, ordena pelo início 
                return a.inicio < b.inicio;
            });
}

// dados os horários de locação desejados para tal modelo, a função organiza os pedidos de aluguel de acordo com horários
void aloca_horarios(const vector<Aluguel> &alugueis) {
    if (alugueis.empty()) {cout << "0"; return;} 

    Horario inicio_atual, fim_atual;
    inicio_atual = {-1, -1};
    fim_atual = {-1, -1};
    vector<int> alocados;

    for (const Aluguel &a : alugueis) {
        if (a.inicio < fim_atual) continue; // se o horário de início do aluguel atual for menor que o fim do aluguel anterior, não aloca
        alocados.push_back(a.id_aluguel);
        fim_atual = a.fim;
    }

    cout << alocados.size() << " = ";
    for (int i = 0; i < alocados.size(); i++) {
        cout << alocados[i];
        if (i < alocados.size() - 1) cout << ", ";
    }
}

int main(void) {
    int casos_teste;
    int quant_carros;
    int solic_alugueis;
    map<int, vector<Aluguel>> alugueis; // mapeia id do carro para vetor de alugueis. funciona quase como uma matriz

    cin >> casos_teste;
    for (int i = 0; i < casos_teste; i++) {
        cin >> quant_carros;
        cin >> solic_alugueis;
        for (int j = 0; j < solic_alugueis; j++) {
            Aluguel atual = processa_aluguel();
            int id_carro = atual.id_carro;
            alugueis[id_carro].push_back(atual);
        }
        
        ordena_alugueis(quant_carros, alugueis);

        for (int a = 1; a <= quant_carros; a++) {
            cout << a << ": ";
            aloca_horarios(alugueis[a]);
            if (a < quant_carros) cout << " | ";
        }

        alugueis.clear();
        cout << endl;
    }
}