"""
exercício para verificar quantas pessoas em uma árvore genealógica têm diabetes hereditária.
faço isso simulando uma árvore usando um dicionário de "Pessoa" (que, contendo os ids de pai e mãe, funciona como o nó de uma árvore)
"""

class Pessoa:
    def __init__(self, id=-1, pai=-1, mae=-1, tem_diabetes=False):
        self.id = id
        self.pai = pai
        self.mae = mae
        self.diabetes = tem_diabetes

# familiares == dicionário de pessoas, id_atual == int id usado para acessar a posição no dicionário
def verifica_arvore(familiares, id_atual): 
    if id_atual == -1 or id_atual not in familiares: # caso base: id é -1 ou não existe na árvore
        return 0

    pessoa_atual = familiares[id_atual]
    diabetes_pai = familiares[pessoa_atual.pai].diabetes if pessoa_atual.pai in familiares else 0
    diabetes_mae = familiares[pessoa_atual.mae].diabetes if pessoa_atual.mae in familiares else 0
    diabete_hereditaria = diabetes_pai + diabetes_mae # usada para analisar se algum dos pais tem diabetes
    contagem = 1 if pessoa_atual.diabetes and (diabete_hereditaria != 0) else 0

    contagem += verifica_arvore(familiares, pessoa_atual.pai) # recursão para o pai
    contagem += verifica_arvore(familiares, pessoa_atual.mae) # recursão para a mãe
    
    return contagem


def main():
    x = int(input()) # x == numero de casos teste
    familiares = {}

    for i in range(x):
        n = int(input()) # n == numero de familiares a analisar

        for j in range(n):
            id_str, diabetes, pai_str, mae_str = input().split()
            
            # acertar o tipo
            id = int(id_str)
            diabetes = diabetes.lower()
            pai = int(pai_str)
            mae = int(mae_str)

            pessoa = Pessoa(id, pai, mae, diabetes == 'sim')
            familiares[id] = pessoa

        print(verifica_arvore(familiares, 1))


if __name__ == "__main__":
    main()