# função que resolve o labirinto usando abordagem gulosa
def resolver_labirinto(grid):
    n = len(grid)
    x, y = 0, 0
    pontuacao = grid[x][y]

    while (x, y) != (n - 1, n - 1):
        grid[x][y] = "#" # marca o caminho percorrido

        direita = grid[x][y + 1] if y + 1 < n else -1
        baixo = grid[x + 1][y] if x + 1 < n else -1

        if direita >= baixo:
            y += 1
            pontuacao += direita
        else:
            x += 1
            pontuacao += baixo

    grid[n - 1][n - 1] = "#" # marca a posição final
    return pontuacao, grid