#include <iostream>
#include <vector>
#include <cstring> // usada apenas para memset

using namespace std;

/* estados */
#define LIVRE 0 // com passe e descansado
#define SEM_PASSE 1 // sem passe e descansado
#define CANSADO 2 // garimpou antes (sem passe), só pode descansar

int solve(int dia_atual, int dias_totais, const vector<int>& valores, int estado, int memo[][3]) {
    if (dia_atual == dias_totais) return 0; // caso base: acabaram os dias

    if (memo[dia_atual][estado] != -1) // antes de tudo, verifica memoização
        return memo[dia_atual][estado];

    int resultado;

    if (estado == CANSADO) // só pode descansar
        resultado = solve(dia_atual + 1, dias_totais, valores, SEM_PASSE, memo);

    else if (estado == LIVRE) { // pode escolher entre garimpar ou não fazer nada
        int op_garimpar = valores[dia_atual] + solve(dia_atual + 1, dias_totais, valores, CANSADO, memo);
        int op_descansar = solve(dia_atual + 1, dias_totais, valores, LIVRE, memo);
        resultado = max(op_garimpar, op_descansar);
    }

    else if (estado == SEM_PASSE) { // pode escolher entre comprar o passe agora ou não fazer nada
        int op_comprar = -valores[dia_atual] + solve(dia_atual + 1, dias_totais, valores, LIVRE, memo);
        int op_nao_comprar = solve(dia_atual + 1, dias_totais, valores, SEM_PASSE, memo);
        resultado = max(op_comprar, op_nao_comprar);
    }

    memo[dia_atual][estado] = resultado; // salva o estado antes de retornar
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
        
        int memo[dias][3];
        memset(memo, -1, sizeof(memo));

        int ganho = solve(0, dias, valores, SEM_PASSE, memo); 
        cout << ganho + diamantes << endl;
    }
}