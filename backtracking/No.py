class No:
    # valor é o caracter representado no nó
    def __init__(self, valor=None) -> None:
        self.valor = valor
        self.filhos = {}
        self.eh_fim_palavra = False # por padrão, todos os nós não são fim de palavra (nenhum método de No trata isso)
                                    # o tratamento é feito na Trie porque achei mais prático e lógico
                                    # isso teoricamente não é muito legal, mas como os códigos ficaram simples, mantive

    # filho é um nó (não apenas o caracter a ser inserido, mas a própria estrutura com um valor associado)
    def inserir(self, no_atual, filho) -> None:
        if filho.valor not in no_atual.filhos:
            no_atual.filhos[filho.valor] = filho


    