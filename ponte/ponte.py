import heapq
from collections import defaultdict

# N == número de acampamentos (vértices), adj == lista de adjacência do grafo
def prim(N, adj):
    
    visited = set() # conjunto para rastrear nós já incluídos na MST
    mst_edges = [] # lista para armazenar as arestas (pontes) da MST na ordem em que são adicionadas
    
    total_cost = 0 # custo total da MST
    
    # fila de prioridade (min-heap) para armazenar as arestas candidatas
    min_heap = [] # formato: (custo, nó_destino, nó_origem)

    # começa pelo acampamento 1
    # custo 0 para alcançar o primeiro nó, -1 indica que é o nó inicial (sem origem)
    heapq.heappush(min_heap, (0, 1, -1))

    while min_heap:
        cost, u, parent = heapq.heappop(min_heap) # pega a aresta de menor custo da fila
        if u in visited: # se o nó 'u' (destino) já foi visitado, pula (evita ciclos)
            continue
        
        visited.add(u) # marca o nó 'u' como visitado
        total_cost += cost # adiciona o custo à soma total

        # se não for o nó inicial (parent != -1), adiciona a ponte à lista
        # isso garante a ordem de adição pedida no enunciado 
        if parent != -1:
            mst_edges.append((cost, parent, u))

        # adiciona todas as arestas que saem de 'u' para nós ainda não visitados
        for edge_cost, v in adj[u]:
            if v not in visited:
                heapq.heappush(min_heap, (edge_cost, v, u))

    # após o loop, verifica se todos os N acampamentos foram visitados
    # se len(visited) != N, o grafo é desconexo (saída específica)
    if len(visited) != N:
        return None, None

    return total_cost, mst_edges

def main():
    casos_teste = int(input())
    
    for i in range(int(casos_teste)):
        
        n_acampamentos, n_pontes = map(int, input().split())
        
        # uso de defaultdict(list) para criar a lista de adjacência
        adj = defaultdict(list)
        
        # conjunto para verificar custos únicos 
        costs = set()
        duplicate_cost = False
        
        # lista temporária para armazenar arestas
        all_edges = []

        # lê todas as pontes (e verifica custos duplicados)
        for _ in range(n_pontes):
            u, v, c = map(int, input().split())
            all_edges.append((u, v, c))
            
            if c in costs:
                duplicate_cost = True
            costs.add(c)

        # caso de entrada com custo duplicado 
        if duplicate_cost:
            print("Esse nao e o caminho correto para a Cidade Perdida de Z.\n")
            continue # pula para o próximo caso de teste

        for u, v, c in all_edges:
            # armazena (custo, vizinho) para a min-heap funcionar corretamente
            adj[u].append((c, v))
            adj[v].append((c, u))

        total_cost, mst_edges = prim(n_acampamentos, adj)

        # caso de grafo desconexo
        if total_cost is None:
            print("O vale nao pode ser completamente atravessado.")
        else:
            print(f"Custo minimo: {total_cost}")
            print("Pontes reconstruidas:")
            
            mst_edges.sort()

            for cost, u, v in mst_edges:
                # menor vértice primeiro
                if u < v:
                    print(f"{u} - {v}")
                else:
                    print(f"{v} - {u}")

        print()

if __name__ == "__main__":
    main()