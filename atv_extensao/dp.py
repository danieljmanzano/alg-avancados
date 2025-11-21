# função que resolve o labirinto usando programação dinâmica
def resolver_labirinto(grid):
    linhas = len(grid)
    cols = len(grid[0])
    
    # matriz de momização que guarda a pontuação máxima acumulada até aquela posição
    dp = [[0] * cols for _ in range(linhas)]
    
    for i in range(linhas):
        for j in range(cols):
            # caso base: a célula inicial (0,0)
            if i == 0 and j == 0:
                dp[i][j] = grid[i][j]
            
            # primeira linha: só pode vir da esquerda
            elif i == 0:
                dp[i][j] = dp[i][j-1] + grid[i][j]
            
            # primeira coluna: só pode vir de cima
            elif j == 0:
                dp[i][j] = dp[i-1][j] + grid[i][j]
            
            # caso geral: vem de cima ou da esquerda (o que for maior)
            else:
                melhor_anterior = max(dp[i-1][j], dp[i][j-1])
                dp[i][j] = melhor_anterior + grid[i][j]
    
    # a pontuação máxima estará na última célula (inferior direita)
    pontuacao_maxima = dp[linhas-1][cols-1]
    grid_visual = reconstruir_caminho(grid, dp)
    return pontuacao_maxima, grid_visual


# função que faz o backtracking no grid dp para reconstruir o caminho visualmente
def reconstruir_caminho(grid, dp):
    rows = len(grid)
    cols = len(grid[0])
    
    grid_visual = [[str(val) for val in row] for row in grid]
    
    i, j = rows - 1, cols - 1 # começa no fim
    grid_visual[i][j] = "#"
    
    while i > 0 or j > 0:
        # caso esteja na primeira linha, só pode vir da esquerda
        if i == 0: 
            j -= 1
        # caso esteja na primeira coluna, só pode vir de cima
        elif j == 0: 
            i -= 1
        # caso geral: olha para a tabela dp para ver quem tem o valor maior
        else:
            valor_cima = dp[i-1][j]
            valor_esquerda = dp[i][j-1]
            
            if valor_cima >= valor_esquerda:
                i -= 1
            else:
                j -= 1
        
        # marca a posição escolhida
        grid_visual[i][j] = "#"
        
    return grid_visual