def entrada():
    conexoes = []
    atomos, ligacoes = map(int, input().split())
    for _ in range(ligacoes):
        conexao = tuple(map(int, input().split()))
        conexoes.append(conexao)
    return atomos, conexoes

# função que, dado o número de átomos e uma lista de conexões, retorna o número de moléculas distintas
def conta_moleculas(atomos, conexoes):
    
    # inicializa lista de adjacência para o grafo
    adj = {i: [] for i in range(1, atomos + 1)}
    
    # constrói o grafo a partir das conexões (como não é direcionado, adiciona em ambos os sentidos)
    for u, v in conexoes:
        adj[u].append(v)
        adj[v].append(u)

    # 'visitados' guarda os átomos que já foram contados em alguma molécula
    visitados = set()
    contador_moleculas = 0

    # itera por todos os átomos
    for i in range(1, atomos + 1):
        
        # checar se o átomo pertence a alguma molécula que já contamos
        if i not in visitados:
            # se encontramos um átomo novo, significa que encontramos uma nova molécula
            contador_moleculas += 1
            
            # inicia a BSF para encontrar todos os vizinhos deste átomo
            # a fila guarda os átomos que ainda precisam ser explorados que estão conectados ao átomo inicial
            fila = [i]
            visitados.add(i) # marca o primeiro átomo como visitado
            
            while fila:
                # pega o próximo átomo da fila
                atual = fila.pop(0) 
                
                # olha todos os vizinhos do átomo 'atual'
                for vizinho in adj[atual]:
                    if vizinho not in visitados:
                        # se o vizinho é novo, marca ele e adiciona à fila
                        visitados.add(vizinho)
                        fila.append(vizinho)
                        
    # retorna o número de vezes que uma busca foi iniciada
    return contador_moleculas

def main():
    casos_teste = input()
    for i in range(int(casos_teste)):
        conexoes = []
        atomos, conexoes = entrada()
        resultado = conta_moleculas(atomos, conexoes)
        print(resultado)
    
if __name__ == "__main__":
    main()
