import guloso
import diveconq

class sistema:
    x: float
    y: float
    nome: str
    def __init__(self, nome, x, y):
        self.nome = nome
        self.x = x
        self.y = y
        

def main():
    casos_teste = int(input())
    for i in range(casos_teste):
        n_total, n_importantes, tensao_max = map(int, input().split())
        sistemas = [] # lista com todos os sistemas
        sistemas_imp = [] # lista com apenas sistemas importantes

        for j in range(n_total):
            nome, x, y = input().split()
            sistemas.append(sistema(nome, float(x), float(y)))
            if j < n_importantes:
                sistemas_imp.append(sistemas[-1])

        guloso.malha_de_tuneis(sistemas_imp, tensao_max)
        diveconq.ponto_de_ressonancia(sistemas)
        print()

            
if __name__ == "__main__":
    main()