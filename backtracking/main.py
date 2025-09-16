from Trie import Trie

# possíveis direções em que se analisa o grid. lados e diagonais, para frente e trás
direcoes = [(-1,  1), ( 0,  1), ( 1,  1), 
            (-1,  0),           ( 1,  0), 
            (-1, -1), ( 0, -1), ( 1, -1)]


def resolve(grid, trie, linhas, colunas) -> list:
    solucao = []

    for i in range(linhas):
        for j in range(colunas):
            for direcao in direcoes: # percorro todas as 8 direções possíveis a partir da posição atual
                encontrada = trie.buscar(grid, i, j, linhas - 1, colunas - 1, direcao)
                if encontrada != "":
                    solucao.append(encontrada)
                    
    return solucao


def printa_resultado(resultado) -> None:
    encontradas = len(resultado)
    palavras = sorted(resultado)
    print(encontradas)
    for palavra in palavras:
        print(palavra)


def main():
    linhas, colunas = map(int, input().split())
    grid = {}

    for i in range(linhas):
        linha = input().strip()
        for j in range(colunas):
            grid[(i, j)] = linha[j]

    trie = Trie()
    n_palavras = int(input())
    for _ in range(n_palavras):
        palavra = input()
        trie.inserir(palavra)

    resultado = resolve(grid, trie, linhas, colunas)
    printa_resultado(resultado)


if __name__ == "__main__":
    main()