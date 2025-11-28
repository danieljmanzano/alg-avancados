#include <iostream>
#include <vector>
#include <string>

using namespace std;

// função para calcular o array pi (função de prefixo do KMP)
// retorna um vetor onde a posição i contém o tamanho do maior prefixo da substring s[0...i] que também é sufixo dessa substring
vector<int> computarFuncaoPrefixo(const string& s) {
    int m = s.length();
    vector<int> pi(m);
    
    // o primeiro elemento é sempre 0, pois um prefixo não pode ser ele mesmo
    pi[0] = 0;
    
    int j = 0; // comprimento do prefixo anterior
    
    // itera do segundo caractere até o final
    for (int i = 1; i < m; i++) {
        // enquanto não houver match e j > 0, voltamos j para o valor anterior no array pi
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        
        // se houver match, incrementa o tamanho do prefixo
        if (s[i] == s[j])
            j++;
        
        pi[i] = j;
    }
    
    return pi;
}

void solve(string s) {
    // calcula o array pi para toda a string
    vector<int> pi = computarFuncaoPrefixo(s);
    
    // o valor na última posição do array pi é o tamanho do maior prefixo que também é sufixo da string inteira (proper prefix)
    int tamanhoMaiorSegmento = pi[s.length() - 1];
    
    // imprime a substring correspondente
    cout << s.substr(0, tamanhoMaiorSegmento) << endl;
}

int main() {
    int x;
    cin >> x;

    while (x--) {
        string s;
        cin >> s;
        solve(s);
    }
    
    return 0;
}