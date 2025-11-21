import dp as dp
import guloso as guloso
import interativo as interativo
import utils

def main():
    utils.limpar_tela()
    print("Bem vindo ao labirinto de pontuação!")
    print("Escolha o modo de jogo:")
    print("1 - Modo Interativo")
    print("2 - Modo Guloso")
    print("3 - Modo Programação Dinâmica")
    modo = input("Digite o número correspondente ao modo desejado: ")
    if modo not in ['1', '2', '3']:
        print("Modo inválido! Por favor, escolha 1, 2 ou 3.")
        return

    utils.limpar_tela()
    print("Escolha o tamanho do labirinto")
    tamanho = int(input("Digite o tamanho 'n' do labirinto n x n: "))
    grid = utils.gera_grid_aleatorio(tamanho)
    
    # modo de jogo interativo
    if modo == '1':
        utils.limpar_tela()
        print(">>> Labirinto Gerado:")
        printa_grid(grid)
        print("\nTente chegar ao final do labirinto (canto inferior direito) somando a maior pontuação possível!\n")
        comecar = input("Pressione Enter para começar...")

        grid_original = [linha[:] for linha in grid]  # cópia do grid original para comparação
        interativo.resolver_labirinto(grid)
        
        print("Jogo encerrado! Você pode comparar seu desempenho com os modos automáticos.")
        ver_auto = input("Deseja ver os resultados dos modos automáticos? (s/n): ")
        if ver_auto.lower() == 's':
            print("\n>>> Labirinto Original:")
            printa_grid(grid_original)

            grid_guloso = [linha[:] for linha in grid_original]
            pontuacao_guloso, grid_guloso = guloso.resolver_labirinto(grid_guloso)
            print(f"\n>>> Pontuação do modo Guloso: {pontuacao_guloso}")
            printa_grid(grid_guloso)

            grid_dp = [linha[:] for linha in grid_original]
            pontuacao_dp, grid_dp = dp.resolver_labirinto(grid_dp)
            print(f"\n>>> Pontuação do modo Programação Dinâmica: {pontuacao_dp}")
            printa_grid(grid_dp)

        print("Obrigado por jogar!")

    # modo visualização guloso
    elif modo == '2':
        print("\n>>> Labirinto Gerado:")
        printa_grid(grid)
        pontuacao, grid_final = guloso.resolver_labirinto(grid)
        print(f"\n>>> Pontuação do modo Guloso: {pontuacao}")
        printa_grid(grid_final)

    # modo visualização programação dinâmica
    elif modo == '3':
        print("\n>>> Labirinto Gerado:")
        printa_grid(grid)
        pontuacao, grid_final = dp.resolver_labirinto(grid)
        print(f"\n>>> Pontuação do modo Programação Dinâmica: {pontuacao}")
        printa_grid(grid_final)

def printa_grid(grid):
    tam_delimitador = len(grid) * 4

    print("-" * tam_delimitador)
    for i in range(len(grid)):
        linha = ""
        for j in range(len(grid[i])):
            linha += f" {grid[i][j]}  "
        print(linha)
    print("-" * tam_delimitador)

if __name__ == "__main__":
    main()
