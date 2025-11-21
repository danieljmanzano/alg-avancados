import os

# função para limpar a tela do terminal
def limpar_tela():
    # se for Windows ('nt'), usa 'cls', senão usa 'clear'
    os.system('cls' if os.name == 'nt' else 'clear')

# função que printa um grid formatado, sem destaque para posição atual
def printa_grid(grid):
    tam_delimitador = len(grid) * 4

    print("-" * tam_delimitador)
    for i in range(len(grid)):
        linha = ""
        for j in range(len(grid[i])):
            linha += f" {grid[i][j]}  "
        print(linha)
    print("-" * tam_delimitador)

# função que printa um grid formatado, com destaque para posição atual
def printa_grid_pos(grid, pos_atual):
    tam_delimitador = len(grid) * 4

    print("-" * tam_delimitador)
    for i in range(len(grid)):
        linha = ""
        for j in range(len(grid[i])):
            if (i, j) == pos_atual:
                linha += f"[{grid[i][j]}] " # formatação para ficar alinhado
            else:
                linha += f" {grid[i][j]}  "
        print(linha)
    print("-" * tam_delimitador)

# função que gera um grid n x n com valores aleatórios entre 0 e 9
def gera_grid_aleatorio(n):
    from random import randint
    return [[randint(0, 9) for _ in range(n)] for _ in range(n)]
