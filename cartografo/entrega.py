# como, por algum motivo, o runcodes não aceita zip nesse trabalho, esse código é só uma junção dos outros arquivos

"""
main.py -----------------------------------------------------------------------------------------------------------------------------
"""
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
        sistemas = [] 
        sistemas_imp = [] 

        for j in range(n_total):
            nome, x, y = input().split()
            sistemas.append(sistema(nome, float(x), float(y)))
            if j < n_importantes:
                sistemas_imp.append(sistemas[-1])

        malha_de_tuneis(sistemas_imp, tensao_max)
        ponto_de_ressonancia(sistemas)
        print()


"""
guloso.py ---------------------------------------------------------------------------------------------------------------------------
"""
import math

class UnionFind:
    def __init__(self, elementos):
        self.pai = {e: e for e in elementos}
        self.rank = {e: 0 for e in elementos}

    def find(self, i):
        if self.pai[i] == i:
            return i
        self.pai[i] = self.find(self.pai[i])
        return self.pai[i]

    def union(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)

        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:
                self.pai[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.pai[root_j] = root_i
            else:
                self.pai[root_j] = root_i
                self.rank[root_i] += 1
            return True
        return False

def calcular_tensao(p1, p2):
    dx = p1.x - p2.x
    dy = p1.y - p2.y
    return math.sqrt(dx*dx + dy*dy)

def malha_de_tuneis(sistemas_importantes, tensao_max):
    V = len(sistemas_importantes)
    
    arestas = []
    for i in range(V):
        for j in range(i + 1, V):
            p1 = sistemas_importantes[i]
            p2 = sistemas_importantes[j]
            tensao = calcular_tensao(p1, p2)

            if tensao <= tensao_max:
                arestas.append((tensao, p1.nome, p2.nome))

    arestas.sort(key=lambda x: x[0])

    nomes_sistemas = [s.nome for s in sistemas_importantes]
    dsu = UnionFind(nomes_sistemas)
    tunnels_selecionados = []
    
    for tensao, nome1, nome2 in arestas:
        if dsu.union(nome1, nome2):
            tunnels_selecionados.append((nome1, nome2, tensao))
            
            if len(tunnels_selecionados) == V - 1:
                break

    output = []
    for nome1, nome2, tensao in tunnels_selecionados:
        s1, s2 = sorted([nome1, nome2])
        output.append(f"{s1}, {s2}, {tensao:.2f}")

    print('\n'.join(output))
    return tunnels_selecionados

"""
diveconq.py -------------------------------------------------------------------------------------------------------------------------
"""
def forca_bruta(pontos):
    min_dist = float('inf') 
    melhor_par = None

    N = len(pontos)
    for i in range(N):
        for j in range(i + 1, N):
            dist = calcular_tensao(pontos[i], pontos[j])
            if dist < min_dist:
                min_dist = dist
                melhor_par = (pontos[i], pontos[j])
                
    return min_dist, melhor_par

def faixa_central(pontos_faixa_ordenados_y, delta, par_minimo_atual):
    min_dist = delta
    melhor_par = par_minimo_atual

    for i in range(len(pontos_faixa_ordenados_y)):
        for j in range(i + 1, len(pontos_faixa_ordenados_y)):
            p1 = pontos_faixa_ordenados_y[i]
            p2 = pontos_faixa_ordenados_y[j]

            if (p2.y - p1.y) >= min_dist:
                break
            
            dist = calcular_tensao(p1, p2)
            if dist < min_dist:
                min_dist = dist
                melhor_par = (p1, p2)

    return min_dist, melhor_par

def closest_pair_recursive(Px, Py):
    N = len(Px)
    if N <= 3:
        return forca_bruta(Px)

    mid = N // 2
    Lx = Px[:mid]
    Rx = Px[mid:]
    linha_central_x = Lx[-1].x

    Ly = [p for p in Py if p.x <= linha_central_x]
    Ry = [p for p in Py if p.x > linha_central_x]

    delta_L, par_L = closest_pair_recursive(Lx, Ly)
    delta_R, par_R = closest_pair_recursive(Rx, Ry)

    if delta_L < delta_R:
        delta = delta_L
        par_minimo = par_L
    else:
        delta = delta_R
        par_minimo = par_R

    Sy = [p for p in Py if abs(p.x - linha_central_x) < delta]

    return faixa_central(Sy, delta, par_minimo)

def ponto_de_ressonancia(sistemas_totais):
    if len(sistemas_totais) < 2:
        return None

    Px = sorted(sistemas_totais, key=lambda p: p.x)
    Py = sorted(sistemas_totais, key=lambda p: p.y)

    min_dist, (p1, p2) = closest_pair_recursive(Px, Py)

    id1, id2 = sorted([p1.nome, p2.nome])
    
    print("Ponto de Ressonância:", end=' ')
    print(f"{id1}, {id2}, {min_dist:.2f}")

    return min_dist, id1, id2



if __name__ == "__main__":
    main()