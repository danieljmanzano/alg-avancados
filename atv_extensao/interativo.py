import readchar
from readchar import key
import utils

# função principal do modo interativo
def resolver_labirinto(grid):
    pos_atual = (0, 0)
    pos_final = (len(grid) - 1, len(grid) - 1)
    pontuacao = grid[0][0] # pontuação inicial na posição (0,0)

    utils.limpar_tela()
    print(f"Início! Pontuação: {pontuacao}")
    utils.printa_grid_pos(grid, pos_atual)

    while True:
        print("\nUse as setas (BAIXO ou DIREITA) para mover.")
        
        tecla = readchar.readkey() # 'readkey()' pausa o programa até receber uma tecla
        
        # mapeando a direção baseada na tecla pressionada
        direcao = None
        if tecla == key.DOWN:
            direcao = 'baixo'
        elif tecla == key.RIGHT:
            direcao = 'direita'
        elif tecla == key.CTRL_C: # opção para sair forçado
            print("Saindo...")
            break
        
        if direcao not in ['baixo', 'direita']:
            utils.limpar_tela()
            utils.printa_grid_pos(grid, pos_atual)
            print("Tecla inválida! Use apenas as setas BAIXO ou DIREITA.")
            continue

        pos_atual, pontuacao = andar(grid, pos_atual, direcao, pontuacao)
        utils.limpar_tela()
        utils.printa_grid_pos(grid, pos_atual)
        
        if pos_atual == pos_final:
            grid[pos_atual[0]][pos_atual[1]] = "X"  # marca a posição final
            utils.limpar_tela()
            utils.printa_grid_pos(grid, pos_atual)
            print(f"\nChegou ao fim! \n>>> Pontuação Final: {pontuacao}\n")
            break

def andar(grid, pos_atual, direcao, pontuacao):
    x, y = pos_atual
    novo_x, novo_y = x, y

    if direcao == 'baixo' and x < len(grid) - 1:
        grid[x][y] = "#"
        novo_x += 1
    elif direcao == 'direita' and y < len(grid) - 1:
        grid[x][y] = "#"
        novo_y += 1
    else:
        print(">>> Movimento inválido! Limite do labirinto.")
        return (x, y), pontuacao # retorna os valores originais sem alterar pontuação
    
    # atualiza pontuação
    pontuacao += grid[novo_x][novo_y]
    print(f">>> Movendo para {direcao}. Nova posição: ({novo_x}, {novo_y}). Pontuação: {pontuacao}")
    
    return (novo_x, novo_y), pontuacao

