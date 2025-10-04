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
# -----------------------------------------------------------------

# calcula a tensão (distância euclidiana) entre dois sistemas (pontos)
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
    tunnels_selecionados = []
    
    for tensao, nome1, nome2 in arestas:
        # tenta unir os conjuntos (se não forma ciclo)
        if dsu.union(nome1, nome2):
            tunnels_selecionados.append((nome1, nome2, tensao))
            
            # condição de parada: árvore tem V-1 arestas
            if len(tunnels_selecionados) == V - 1:
                break

    # formata e imprime a saída conforme especificado
    output = []
    for nome1, nome2, tensao in tunnels_selecionados:
        # saída em ordem alfabética de identificadores
        s1, s2 = sorted([nome1, nome2])
        output.append(f"{s1}, {s2}, {tensao:.2f}")

    print('\n'.join(output))
    return tunnels_selecionados

