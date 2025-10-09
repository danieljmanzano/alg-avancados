# como, por algum motivo, o runcodes não aceita zip nesse trabalho, esse código é só uma junção dos outros arquivos que usei para resolver o problema
# à propósito, também para adequar ao runcodes, tem muita maracutaia aqui para conseguir printar na ordem de entrada. partes confusas provavelmente são por isso

"""
main.py -----------------------------------------------------------------------------------------------------------------------------
"""
class sistema:
    x: float
    y: float
    nome: str
    index: int # campo usado unicamente para printar os sistemas conforme foram lidos
    def __init__(self, nome, x, y, index):
        self.nome = nome
        self.x = x
        self.y = y
        self.index = index


def main():
    casos_teste = int(input())
    for i in range(casos_teste):
        n_total, n_importantes, tensao_max = map(int, input().split())
        sistemas = [] # lista com todos os sistemas
        sistemas_imp = [] # lista com apenas sistemas importantes

        for j in range(n_total):
            nome, x, y = input().split()
            sistemas.append(sistema(nome, float(x), float(y), j))
            if j < n_importantes:
                sistemas_imp.append(sistemas[-1])

        malha_de_tuneis(sistemas_imp, tensao_max)
        ponto_de_ressonancia(sistemas)
        print()


"""
guloso.py ---------------------------------------------------------------------------------------------------------------------------
"""
import math

# implementação da classe Union-Find (Disjoint Set Union - DSU) para aplicar algoritmo de Kruskal
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

# calcula a tensão (distância euclidiana) entre dois sistemas (pontos) - usado tanto no guloso quanto no div&conq
def calcular_tensao(p1, p2):
    dx = p1.x - p2.x
    dy = p1.y - p2.y
    return math.sqrt(dx*dx + dy*dy)

# função principal que implementa o algoritmo guloso (Kruskal) para encontrar a árvore geradora mínima
def malha_de_tuneis(sistemas_importantes, tensao_max):
    V = len(sistemas_importantes)
    
    arestas = []
    for i in range(V):
        for j in range(i + 1, V):
            p1 = sistemas_importantes[i]
            p2 = sistemas_importantes[j]
            tensao = calcular_tensao(p1, p2)

            # aresta é considerada apenas se a tensão for menor ou igual ao máximo permitido
            if tensao <= tensao_max:
                arestas.append((tensao, p1.nome, p2.nome))

    # ordenar arestas pelo custo (tensão)
    arestas.sort(key=lambda x: x[0])

    # inicializa UnionFind e processa as arestas (Kruskal)
    nomes_sistemas = [s.nome for s in sistemas_importantes]
    dsu = UnionFind(nomes_sistemas)
    tuneis_selecionados = []
    
    for tensao, nome1, nome2 in arestas:
        # tenta unir os conjuntos (se não forma ciclo)
        if dsu.union(nome1, nome2):
            tuneis_selecionados.append((nome1, nome2, tensao))
            
            # condição de parada: árvore tem V-1 arestas
            if len(tuneis_selecionados) == V - 1:
                break

    # formata e imprime a saída conforme especificado
    output = []
    sistema_map = {s.nome: s for s in sistemas_importantes} 
    for nome1, nome2, tensao in tuneis_selecionados:
        s1 = sistema_map[nome1]
        s2 = sistema_map[nome2]
        if s1.index < s2.index: output.append(f"{s1.nome}, {s2.nome}, {tensao:.2f}")
        else: output.append(f"{s2.nome}, {s1.nome}, {tensao:.2f}")

    print('\n'.join(output))
    return tuneis_selecionados

"""
diveconq.py -------------------------------------------------------------------------------------------------------------------------
"""

# resolve o caso base da recursão (2 ou 3 pontos)
def forca_bruta(pontos):
    min_dist = float('inf') # infinito
    melhor_par = None

    N = len(pontos)
    for i in range(N):
        for j in range(i + 1, N):
            dist = calcular_tensao(pontos[i], pontos[j])

            # lógica abaixo feita para garantir a ordem correta dos pontos no par (especificamente para garantir o print correto)
            # minha lógica original era mais simples, mas tive que complicar para garantir a ordem correta
            p_atual_i, p_atual_j = pontos[i], pontos[j]
            if p_atual_i.index > p_atual_j.index:
                p_atual_i, p_atual_j = p_atual_j, p_atual_i # ordena por index

            if dist < min_dist:
                min_dist = dist
                melhor_par = (p_atual_i, p_atual_j)
            elif dist == min_dist: # caso distâncias sejam iguais, verifica a ordem dos índices
                if p_atual_i.index < melhor_par[0].index:
                    melhor_par = (p_atual_i, p_atual_j)
                elif p_atual_i.index == melhor_par[0].index:
                    if p_atual_j.index < melhor_par[1].index:
                        melhor_par = (p_atual_i, p_atual_j)

    return min_dist, melhor_par

# busca o par mais próximo na faixa central menor que delta
def faixa_central(pontos_faixa_ordenados_y, delta, par_minimo_atual):
    min_dist = delta
    melhor_par = par_minimo_atual

    # a verificação é limitada a 7 vizinhos próximos em y para manter O(N)
    for i in range(len(pontos_faixa_ordenados_y)):
        for j in range(i + 1, len(pontos_faixa_ordenados_y)):
            p1 = pontos_faixa_ordenados_y[i]
            p2 = pontos_faixa_ordenados_y[j]

            # otimização: se a diferença em y for muito grande, não verifica p2 nem os seguintes pois estão ordenados por y
            if (p2.y - p1.y) >= min_dist:
                break
            
            # calcula a distância, que é O(1)
            dist = calcular_tensao(p1, p2)
            
            # lógica semelhante à do forca_bruta para garantir a ordem correta dos pontos no par
            p_novo1, p_novo2 = p1, p2
            if p_novo1.index > p_novo2.index:
                p_novo1, p_novo2 = p_novo2, p_novo1

            if dist < min_dist:
                min_dist = dist
                melhor_par = (p_novo1, p_novo2)
            elif dist == min_dist:
                if p_novo1.index < melhor_par[0].index:
                    melhor_par = (p_novo1, p_novo2)
                elif p_novo1.index == melhor_par[0].index:
                    if p_novo2.index < melhor_par[1].index:
                        melhor_par = (p_novo1, p_novo2)

    return min_dist, melhor_par

# função recursiva principal. Px é a lista de pontos ordenados por x, Py por y
def closest_pair_recursive(Px, Py):
    N = len(Px)
    if N <= 3:
        # caso base: resolve por força bruta
        return forca_bruta(Px)

    # divisão
    mid = N // 2
    Lx = Px[:mid]
    Rx = Px[mid:]
    linha_central_x = Lx[-1].x

    # dividir Py em Ly e Ry
    Ly = [p for p in Py if p.x <= linha_central_x]
    Ry = [p for p in Py if p.x > linha_central_x]

    # chama recursivamente para os dois lados
    delta_L, par_L = closest_pair_recursive(Lx, Ly)
    delta_R, par_R = closest_pair_recursive(Rx, Ry)

    # encontrar a menor distância e o par associado
    if delta_L < delta_R:
        delta = delta_L
        par_minimo = par_L
    elif delta_R < delta_L:
        delta = delta_R
        par_minimo = par_R
    else: # lógica para garantir, denovo, ordem correta para o print
        if par_L[0].index < par_R[0].index:
            delta = delta_L
            par_minimo = par_L
        else:
            delta = delta_R
            par_minimo = par_R

    # cria a lista de pontos 'Sy' (pontos dentro de delta da linha central, ordenados por y)
    Sy = [p for p in Py if abs(p.x - linha_central_x) < delta]

    # procurar por um par ainda mais próximo na faixa (O(N))
    return faixa_central(Sy, delta, par_minimo)

# função principal do algoritmo
def ponto_de_ressonancia(sistemas_totais):
    if len(sistemas_totais) < 2:
        return None # caso não haja sistemas suficientes

    # lista com todos sistemas ordenada por x
    Px = sorted(sistemas_totais, key=lambda p: p.x)
    # lista com todos sistemas ordenada por y
    Py = sorted(sistemas_totais, key=lambda p: p.y)

    # chama a função de recursão principal (com o resultado final)
    min_dist, (p1, p2) = closest_pair_recursive(Px, Py)
    
    print("Ponto de Ressonância:", end=' ')
    print(f"{p1.nome}, {p2.nome}, {min_dist:.2f}")

    return min_dist, p1.nome, p2.nome


if __name__ == "__main__":
    main()