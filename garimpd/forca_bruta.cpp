// solução de força bruta para o problema. feito para começar a desenvolver a lógica antes de implementar dp
// a versão com dp é basicamente essa lógica com memoização e menos estados envolvidos (ao invés das 3 flags que usei na função)

#include <iostream>
#include <vector>

using namespace std;

int solve(int dia_atual, int dias_totais, const vector<int>& valores, bool tem_passe, bool descansado, bool garimpou) {
    if (dia_atual == dias_totais) return 0; // caso base: acabaram os dias

    int resultado;

    if (garimpou && !descansado)  // acabou de garimpar, só pode descansar (avança um dia sem agir)
        resultado = solve(dia_atual + 1, dias_totais, valores, false, true, false);
    
    else if (tem_passe && descansado) { // pode escolher entre garimpar ou não fazer nada
        int op_garimpar = valores[dia_atual] + solve(dia_atual + 1, dias_totais, valores, false, false, true);
        int op_descansar = solve(dia_atual + 1, dias_totais, valores, true, true, false);
        resultado = max(op_garimpar, op_descansar);
    }

    else if (!tem_passe && descansado) { // pode escolher entre comprar o passe agora ou não fazer nada
    // obs.: por garantia que o resultado não vai ser lixo (nenhum if satisfeito), deixei o último if apenas como else
        int op_comprar = -valores[dia_atual] + solve(dia_atual + 1, dias_totais, valores, true, true, false);
        int op_nao_comprar = solve(dia_atual + 1, dias_totais, valores, false, true, false);
        resultado = max(op_comprar, op_nao_comprar);
    }

    /* obs.: na implementação com dp, basicamente tomo cada um dos if e transformo num estado na memoização */

    return resultado;
}

int main(void) {
    int casos_teste;
    cin >> casos_teste;

    for (int i = 0; i < casos_teste; i++) {
        int diamantes, dias;
        cin >> diamantes >> dias;

        vector<int> valores(dias);
        for (int j = 0; j < dias; j++) 
            cin >> valores[j];
        
        int ganho = solve(0, dias, valores, false, true, false); 
        cout << ganho + diamantes << endl;
    }
}