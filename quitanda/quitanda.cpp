#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// explicando como funciona o argumento (comentários para eu mesmo entender posteriormente):
//   const garante que não haverá modificações em produtos. usar o "&" é quase o mesmo que usar ponteiro pelo que entendi
void compras(const map<string, float>& produtos) {
    string codigo;
    float peso;
    int itens_compra;

    while (true) {
        float valor_total = 0.0;
        
        cin >> itens_compra;
        if (itens_compra == -1) 
            break; 
        
        for (int i = 0; i < itens_compra; i++) {
            cin >> codigo >> peso;

            auto it = produtos.find(codigo); // busca o produto no mapa

            if (it != produtos.end()) valor_total += it->second * peso; // it->second é o preço
            else cout << "Produto com código " << codigo << " não cadastrado." << endl;
        }
        
        cout << "R$" << fixed << setprecision(2) << valor_total << endl;
    }
}

int main(void) {
    map<string, float> produtos;
    int cadastrados = 0;
    cin >> cadastrados;

    string codigo_aux;
    float preco_aux;

    for (int i = 0; i < cadastrados; i++) {
        cin >> codigo_aux >> preco_aux;

        // o método insert não adiciona se a chave já existir
        auto res = produtos.insert({codigo_aux, preco_aux});
        if (!res.second)  // res.second é false se a chave já existe
            cout << "Produto com código " << codigo_aux << " já cadastrado." << endl;
    }

    compras(produtos);

    return 0;
}