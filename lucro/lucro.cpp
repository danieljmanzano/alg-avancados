#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct data {
    int ano;
    int mes;
    int dia;

    bool operator<(const struct data& outra) const {
        if (ano != outra.ano) return ano < outra.ano;
        if (mes != outra.mes) return mes < outra.mes;
        return dia < outra.dia;
    }
} Data;


/* funçao que pega a "melhor" (menor) combinação de lucros/dias que ultrapassa a soma dos lucros dos demais dias
   retorna os índices que formam a melhor combinação em "lucros" */
vector<int> melhor_combinacao(vector<pair<Data, float>> lucros, float lucro_total) {
    vector<int> resultado;

    pair<float, int> maior = make_pair(0.0, -1);
    float valor_acumulado = 0;
    for (int i = 0; i < lucros.size(); i++) {
        maior = make_pair(0.0, -1); 
        for (int j = 0; j < lucros.size(); j++) {
            if (lucros[j].second == 0.0) continue; // posicao do vetor ja foi usada (ou nao tem valor)
            if (lucros[j].second > maior.first) {
                maior.first = lucros[j].second; // guarda valor
                maior.second = j; // guarda index
            }
        }
        lucros[maior.second].second = 0.0; // marca posicao do vetor como usada
        valor_acumulado += maior.first;
        lucro_total -= maior.first;
        resultado.push_back(maior.second);
        if (valor_acumulado > lucro_total) break; // quando consigo mais valor que o restante dos dias, para
    }

    return resultado;
}


/* função para print da saída */
void saida(const vector<pair<Data, float>> &lucros, const float lucro_total) {
    vector<int> resultado_indices = melhor_combinacao(lucros, lucro_total);

    vector<pair<Data, float>> dias_selecionados; // vetor de pares de data e valor referentes aos dias selecionados na combinação
    for (int index : resultado_indices) dias_selecionados.push_back(lucros[index]);
    sort(dias_selecionados.begin(), dias_selecionados.end()); // ordena por data (sort de um pair considera o primeiro elemento)

    if (dias_selecionados.size() > 1) cout << dias_selecionados.size() << " dias (";
    else cout << dias_selecionados.size() << " dia (";
    
    float soma_combinacao = 0;
    for (int i = 0; i < dias_selecionados.size(); i++) {
        const auto& dia_info = dias_selecionados[i]; 
        soma_combinacao += dia_info.second;
        printf("%02d/%02d/%04d", dia_info.first.dia, dia_info.first.mes, dia_info.first.ano);
        
        if (i < dias_selecionados.size() - 1) cout << ", ";
    }

    printf(") | soma=%.2f | ", soma_combinacao);

    float fracao_do_total = (float(dias_selecionados.size()) / float(lucros.size())) * 100.0;
    printf("%.2f%% dos dias totais\n", fracao_do_total); // curiosidade: para printar o literal "%" precisa escrever "%%" no printf
}

int main(void) {
    Data data; // usado para leitura de uma data
    float valor; // usado para leitura de um valor
    char barra; // usado para ler a barra entre dia, mes e ano
    int casos_teste, dias; // dias são quantos dados serão passados como entrada a cada caso teste
    vector<pair<Data, float>> lucros; // vetor de pares de data e valor referentes ao lucro de um dia específico
    float lucro_total;

    /* entrada */
    cin >> casos_teste;
    for (int i = 0; i < casos_teste; i++) {
        cin >> dias;
        lucro_total = 0;
        for (int j = 0; j < dias; j++) {
            cin >> data.dia >> barra >> data.mes >> barra >> data.ano >> valor; // entrada tipo dd/mm/aaaa
            lucros.push_back(make_pair(data, valor)); 
            lucro_total += valor;
        }
        saida(lucros, lucro_total);
        lucros.clear(); // limpa o vetor para o próximo caso de teste
    }

    return 0;
}