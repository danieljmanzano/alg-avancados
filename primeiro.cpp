/* código sem pé nem cabeça. só umas coisa basica de c++ pra lembrar depois */

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

// template: uma forma de evitar definir um tipo para aplicar uma função 
template <typename T>
T soma(T a, T b) {
    return a + b;
}

// struct aqui pode ter métodos e atributos, é como se fosse uma classe mas sem encapsulamento
struct Pessoa {
    int idade;

    bool operator<(Pessoa b) { 
        return this->idade < b.idade; // "this" é ponteiro, por isso a seta
    }
};

int main(void) {
    cout << "oi\n" << endl;

    float a = 2.3, b = 3;
    int c = 2, d = 3;
    cout << soma(a,b) << endl;
    cout << soma(c,d) << endl;
    cout << endl;

    list<int> lista; 
    lista.push_back(1);
    lista.push_front(2);
    lista.push_back(3);
    for (list<int>::iterator it = lista.begin(); it != lista.end(); it++) { // jeito paia de iterar 
        cout << *it << " ";
    }
    cout << endl;

    for (int x : lista) { // jeito facil de iterar
        cout << x << " ";
    }
    cout << endl;

    for (auto x : lista) { // jeito mais facil ainda de iterar (nao precisa pensar no tipo)
        cout << x << " ";
    }
    cout << endl;

    vector<int> vetor = {9, 2, 3, 7, 2};
    for (int i = 0; i < vetor.size(); i++) {
        cout << vetor[i] << " "; // acesso por indice
    }
    cout << endl;

    stack<string> pilha;
    pilha.push("primeiro");
    pilha.push("segundo");
    pilha.push("terceiro");
    while (!pilha.empty()) {
        cout << pilha.top() << " "; 
        pilha.pop(); 
    }
    cout << endl;

    map<string, int> mapa; // "map" funciona como o dicionario do python
    mapa.insert(make_pair("um", 1)); // jeito peba de inserir
    mapa["dois"] = 2; // jeito mais facil de inserir
    cout << mapa["um"] << " " << mapa["dois"] << endl; // acesso por chave
    cout << endl;

    sort(vetor.begin(), vetor.end(), [](int a, int b){
                                        return a < b; // lambda para ordenar a lista (sintaxe feia da gota)
                                        }); // aqui nao precisava do lambda (só pondo de exemplo, poderia só chamar o sort e por o begin e end)
    for (auto x : vetor) {
        cout << x << " ";
    }
    cout << endl;
    
}