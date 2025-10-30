#include <iostream>
#include <cmath>

using namespace std;

// lógica O(sqrt(n)) para verificar um número como primo ou não
// obs.: apenas essa lógica é suficiente para o problema (não estoura limite de tempo)
bool testa_primo(long long n) {
    for (long long i = 2; i * i <= n; i++) 
        if (n % i == 0) return false;

    return true;
}

// função auxiliar para multiplicação modular sem overflow
unsigned long long multiply(unsigned long long a, unsigned long long b, unsigned long long mod) {
    unsigned long long res = 0;
    a %= mod;

    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % mod;
        
        a = (a * 2) % mod;
        b >>= 1;
    }
    return res;
}

// implementação de exponenciação modular (forma específica de resolver o esperado do exercício sem estourar memória ou tempo)
// seria possível apenas usar um pow e depois calcular o módulo do resultado, mas o tamanho da variável estoura
long long power(long long base, long long mod, long long exp) {
    unsigned long long res = 1;
    unsigned long long u_base = (base % mod + mod) % mod; // garante base positiva
    unsigned long long u_mod = mod;

    while (exp > 0) {
        // se o expoente é ímpar, multiplica o resultado pela base atual
        if (exp % 2 == 1)
            res = multiply(res, u_base, u_mod); 

        // divide o expoente por 2
        exp >>= 1; 

        // eleva a base ao quadrado
        u_base = multiply(u_base, u_base, u_mod); 
    }
    return res;
}

// função principal que resolve o problema
long long solve(long long n, long long t) {

    // (a*t) mod p = 1
    // p == próximo primo após n
    // encontrar 'a' com base no escrito acima

    long long p = n + 1;
    for (long long i = p;; i++) {
        if (testa_primo(i)) {
            p = i;
            break;
        }
    }

    /*
    explicação do algoritmo:
    usando o pequeno teorema de fermat, sabemos que:
        t^(p-1) ≡ 1 (mod p)
    assim, usando que t^(p-1) = t * t^(p-2), temos que:
        t * t^(p-2) ≡ 1 (mod p)
    o que queremos encontrar é:
        a * t ≡ 1 (mod p)
    então, devemos apenas encontrar um valor de a tal que:
        a ≡ t^(p-2) (mod p)
    */

    long long a = 1;
    a = power(t, p, p - 2); // a função, basicamente, aplica a ideia acima
    return a;
}


int main(void) {
    long long n, t;
    cin >> n >> t;

    long long a = solve(n, t);
    cout << a << endl;
}