# Projeto de Extensão

Este projeto tem como objetivo introduzir o conceito de Programação Dinâmica (PD) de forma lúdica, visual e interativa, focada em um público não familiarizado com computação.

# Apresentação ao Público

A metodologia de apresentação da atividade é centrada na analogia do "Labirinto do Tesouro":

- Introdução do Problema: É apresentado um "labirinto" (um grid/tabuleiro) onde cada célula possui um valor (ex: "moedas"). O objetivo é encontrar o caminho do início (canto superior esquerdo) ao fim (canto inferior direito), movendo-se apenas para baixo e para a direita, de forma a maximizar o total de moedas coletadas.

- Tentativa "Gulosa": Inicialmente, o público é convidado a sugerir um caminho. A tendência natural será usar uma estratégia "gulosa" (escolher a célula vizinha com mais moedas). Anota-se o resultado (subótimo) obtido por essa abordagem.

- Solução "Inteligente" (PD): Em seguida, é demonstrada a abordagem da Programação Dinâmica. Apresenta-se o conceito de "criar um mapa" (a tabela de memoização) que guarda a melhor pontuação possível para se chegar a cada célula. O "mapa" é preenchido, mostrando visualmente o caminho verdadeiramente ótimo traçado pelo algoritmo.

- Conclusão: Ao final, o "mapa" da PD dá o valor máximo garantido. Por fim, os resultados são comparados, demonstrando de forma prática e visual por que a PD é uma ferramenta poderosa para encontrar a melhor solução.

# Códigos

- ```main.py```: Centraliza as operações dos demais códigos (é o script a ser executado para jogar).
- ```interativo.py```: Contém as operações que possibilitam ao usuário traçar sua tentativa no jogo.
- ```guloso.py```: Implementa o algorimto guloso de resolução do problema.
- ```dp.py```: Implementa o algorimto de programação dinâmica de resolução do problema.
- ```utils.py```: Contém funções auxiliares necessárias para visualização adequada do jogo.
- ```Makefile```: Executa os códigos com ```make run``` e limpa o executável gerado com ```make clean```.
