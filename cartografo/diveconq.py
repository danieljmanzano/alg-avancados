import math

# calcula a tensão (distância euclidiana) entre dois sistemas (pontos)
def calcular_tensao(p1, p2):
    dx = p1.x - p2.x
    dy = p1.y - p2.y
    return math.sqrt(dx*dx + dy*dy)

# resolve o caso base da recursão (2 ou 3 pontos)
def forca_bruta(pontos):
    min_dist = float('inf') # infinito
    melhor_par = None

    N = len(pontos)
    for i in range(N):
        for j in range(i + 1, N):
            dist = calcular_tensao(pontos[i], pontos[j])
            if dist < min_dist:
                min_dist = dist
                melhor_par = (pontos[i], pontos[j])
                
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
            if dist < min_dist:
                min_dist = dist
                melhor_par = (p1, p2)

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

    # garante a ordem alfabética para a saída
    id1, id2 = sorted([p1.nome, p2.nome])
    
    print("Ponto de Ressonância:", end=' ')
    print(f"{id1}, {id2}, {min_dist:.2f}")

    return min_dist, id1, id2