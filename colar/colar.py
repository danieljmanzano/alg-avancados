from math import atan2 # função que calcula o ângulo em radiano de um ponto em relação ao eixo X

class Ponto:
    x: float
    y: float
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

# determina a orientação de três pontos. faz isso usando um produto vetorial e classificando seu resultado
# obs.: positivo == sentido horário, negativo == sentido anti-horário, 0 == colineares
def orientacao(p, q, r):
    val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y)

    if val == 0: return 0  # colinear
    return 1 if val > 0 else -1 # horário ou anti-horário

# função principal que inicia o algoritmo do "quickhull"
def encontrar_fecho(pontos):
    pontos_unicos = list(set(pontos)) # garante que não há pontos repetidos (por isso "únicos")
    if len(pontos_unicos) < 3:
        pontos_unicos.sort(key=lambda p: (p.x, p.y))
        return pontos_unicos
    
    # verifica se todos os pontos são colineares (caso particular que o algoritmo original não trata)
    primeiro = pontos_unicos[0]
    segundo = pontos_unicos[1]
    todos_colineares = all(orientacao(primeiro, segundo, p) == 0 for p in pontos_unicos[2:])
    if todos_colineares:
        # retorna todos os pontos ordenados por x (e depois y)
        return sorted(pontos_unicos, key=lambda p: (p.x, p.y))

    # encontra os pontos extremos no eixo X
    min_x_ponto = min(pontos_unicos, key=lambda p: (p.x, p.y))
    max_x_ponto = max(pontos_unicos, key=lambda p: p.x)

    # o fecho é construído em duas metades ordenadas
    borda_superior = []
    borda_inferior = []
    
    # divide os pontos em dois grupos
    for p in pontos_unicos:
        o = orientacao(min_x_ponto, max_x_ponto, p)
        if o < 0: # anti-horário
            borda_superior.append(p)
        elif o > 0: # horário
            borda_inferior.append(p)

    # contrói as duas metades do fecho recursivamente
    fecho_sup_final = [min_x_ponto, max_x_ponto]
    fecho_inf_final = [min_x_ponto, max_x_ponto]
    encontrar_parte_do_fecho(borda_superior, min_x_ponto, max_x_ponto, fecho_sup_final)
    encontrar_parte_do_fecho(borda_inferior, max_x_ponto, min_x_ponto, fecho_inf_final)

    # combina as duas metades para formar o fecho final em ordem anti-horária
    resultado = list(set(fecho_inf_final + fecho_sup_final))
    return resultado

# função recursiva que encontra os pontos mais distantes
def encontrar_parte_do_fecho(sub_pontos, p1, p2, fecho_parcial):
    if not sub_pontos:
        return

    # encontra o ponto mais distante da linha p1-p2
    ponto_mais_distante = max(sub_pontos, key=lambda p: abs((p1.y - p.y) * (p2.x - p1.x) - (p1.x - p.x) * (p2.y - p1.y)))
    
    # adiciona o ponto ao fecho parcial correspondente
    fecho_parcial.append(ponto_mais_distante)

    # pontos que estão "à esquerda" das novas bordas formadas
    s1 = [p for p in sub_pontos if orientacao(p1, ponto_mais_distante, p) < 0]
    s2 = [p for p in sub_pontos if orientacao(ponto_mais_distante, p2, p) < 0]

    # chama recursivamente para as duas novas bordas
    encontrar_parte_do_fecho(s1, p1, ponto_mais_distante, fecho_parcial)
    encontrar_parte_do_fecho(s2, ponto_mais_distante, p2, fecho_parcial)


# função que ordena os pontos do fecho conforme esperado no exercício
def ordenar_resultado_final(fecho_desordenado, pontos_todos):
    # encontra o ponto de partida (menor (Ei, Vi))
    ponto_inicial_correto = pontos_todos[0]

    # ordena os pontos do fecho em sentido anti-horário em relação a esse ponto inicial
    # a função atan2 calcula o ângulo de cada ponto, permitindo uma ordenação circular
    fecho_em_ordem_ccw = sorted( # obs. meio bobeira: ccw == counter-clockwise
        fecho_desordenado,
        key=lambda p: (atan2(p.y - ponto_inicial_correto.y, p.x - ponto_inicial_correto.x))
    )
    
    idx_inicial = fecho_em_ordem_ccw.index(ponto_inicial_correto)

    # "gira" a lista para que ela comece efetivamente no ponto inicial mantendo a ordem anti-horária
    return fecho_em_ordem_ccw[idx_inicial:] + fecho_em_ordem_ccw[:idx_inicial]

def main():
    casos_teste = int(input())
    for k in range(1, casos_teste + 1):
        n_pedras = int(input())
        pedras = []

        for _ in range(n_pedras):
            e, v = map(float, input().split())
            pedras.append(Ponto(e, v))

        # ordena as pedras pelas coordenadas (necessário para o algoritmo)
        pedras.sort(key=lambda p: (p.x, p.y))

        # chama o algoritmo quickhull para encontrar o conjunto de pontos do fecho, ordenado geometricamente
        fecho_em_ordem_geometrica = encontrar_fecho(pedras)

        ponto_inicial = pedras[0]

        # calcula o centroide do fecho para usar como referência
        # definição de centroide: é o centro geométrico de uma forma ou figura, e é um ponto onde se pode considerar que toda a massa está concentrada para fins de cálculos mecânicos
        centro_x = sum(p.x for p in fecho_em_ordem_geometrica) / len(fecho_em_ordem_geometrica)
        centro_y = sum(p.y for p in fecho_em_ordem_geometrica) / len(fecho_em_ordem_geometrica)

        # ordena os pontos do fecho em sentido anti-horário em relação ao centroide
        fecho_em_ordem_ccw = sorted(
            fecho_em_ordem_geometrica,
            key=lambda p: atan2(p.y - centro_y, p.x - centro_x)
        )

        # rotaciona a lista para começar no ponto inicial
        if ponto_inicial in fecho_em_ordem_ccw:
            idx_inicial = fecho_em_ordem_ccw.index(ponto_inicial)
            fecho_ordenado_final = fecho_em_ordem_ccw[idx_inicial:] + fecho_em_ordem_ccw[:idx_inicial]
        else:
            fecho_ordenado_final = fecho_em_ordem_ccw

        print(f"Caso {k}:")
        print(f"Tamanho do colar: {len(fecho_ordenado_final)}") 
        
        # formata a lista de pontos como strings a partir da lista ordenada final
        pedras_formatadas = [f"({p.x:.4f},{p.y:.4f})" for p in fecho_ordenado_final]
        print("Pedras ancestrais: " + ",".join(pedras_formatadas)) 
    
        print() # quebra linha


if __name__ == "__main__":
    main()
