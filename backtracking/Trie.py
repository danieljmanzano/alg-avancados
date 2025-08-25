from No import No

class Trie:
    def __init__(self) -> None:
        self.raiz = No(None) # nó raiz não contém valor

    def inserir(self, palavra) -> None:
        no_atual = self.raiz

        for char in palavra: # insiro caracter por caracter na trie. caso o caracter já exista, apenas sigo para o próximo nó
            if char not in no_atual.filhos:
                novo_no = No(char)
                no_atual.inserir(no_atual, novo_no) # esse método é referente ao inserir de No
            no_atual = no_atual.filhos[char]

        no_atual.eh_fim_palavra = True # ao invés de ter um tratamento de fim de palavra em algum método de "No",
                                       # é mais simples ter um único tratamento aqui (única parte do código que trata isso)

    # direção é uma tupla (i, j) que indica a direção a ser seguida. demais argumentos são autoexplicativos
    def buscar(self, grid, i, j, i_max, j_max, direcao) -> str:
        palavra = ""
        no_atual = self.raiz

        while (i <= i_max and i >= 0) and (j <= j_max and j >= 0):
            char = grid[(i, j)]

            if char not in no_atual.filhos:
                return "" # quase um "return False". como a função retorna uma string, retorno ""
            
            no_atual = no_atual.filhos[char]
            palavra += char

            if no_atual.eh_fim_palavra:
                return palavra
            
            i += direcao[0]
            j += direcao[1]

        return "" # caso tenha terminado o loop e não tenha retornado, montou apenas parte de uma palavra (não chegou ao fim)
        
