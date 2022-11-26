# Sorting algorithms

Algoritmo de ordenação é um algoritmo que coloca os elementos de uma dada sequência em uma certa ordem. Ele efetua sua ordenação completa ou parcial. O objetivo da ordenação é facilitar a recuperação dos dados de uma lista.

Para este artigo foi escolhido o algoritmo de ordenação **Radix Sort** para serem estudado/analisado.

## Radix sort 
Para construção do radix é necessário previamente sabermos o conceito e funcionamento do **CoutingSort** para um melhor entendimento da nossa estrutura.
Com o counting sort usamos um vetor auxiliar de tamanho igual ao maior valor a ser ordenado, onde este vetor auxiliar é usado para contar a ocorrência de cada valor, assim o valor a ser ordenado irá ser tratado com um índice, ou seja, usaremos ele com índice no nosso vetor para fazermos a contagem. Assim posteriormente podemos percorrer o array auxiliar verificando quais valores existem e dessa forma gerar o vetor ordenado

Devemos levar em consideração algun pontos desse método, como:
- Não é recomendado para uso em grandes conjuntos de valores/dados.
- Possui um processamento simples.
- E é estável, ou seja, ele não altera a ordem de dados iguais.

#### Abaixo podemos analisar um exemplo desta implementação:
```c
#define MAX 100
void countingSort(int *v, int n){
  int i, j, k;
  int box[MAX];
  
  for( i = 0; i < MAX; i++){
    box[i] = 0;
    }
  for(i = 0; i < n; i++){
    box[v[i]]++;
  }
  for(i = 0, j = 0; j < MAX; j++){
    for(k = box[j]; k > 0; k--){
      v[i++] = j;
    }
  }
}
```

A ideia do Radix Sort é classificarmos dígito por dígito, sempre começando do dígito menos significativo para o mais significativo, neste algoritmo de ordenação usa-se a classificação por contagem como uma sub-rotina para classificar.
## Tem como características:
- Faz suposições de como os dados devem estar entre um intervalo de elementos.
- A matriz de entrada deve ter os elementos com a mesma raiz e largura.
- funciona na classificação com base em um dígito individual ou posição de letra.
- Começamos a classificação da posição mais à direita e é ideal usarmos um algoritmo estável para cada posição.
- Usa uma matriz de contagem temporária. 

Esse  algoritimo assume que todos os elementos de entrada são de base **d**. Isso significa que todos os números são **d** números de dígitos.
O que basicamente fazemos é, primeiro classificamos cada elemento com base no valor da sua unidade (*dígito menos significativo*). Em seguida, classificamos os valores com base no valor da décima casa (*ao lado do dígito menos significativo*). Este processo é feito até chegarmos aos dígitos mais significativos.
- Pegue o dígito menos significativo de cada elemento.
- Classifique a lista de elementos com base nesse dígito, e mantenha a ordem dos elementos com o mesmo dígito.
- Repita a classificação com cada dígito mais significativo.
## Exemplo: 
Vamos classificar a matriz de amostra usando esse algoritimo:

<div align="center">
  <img src="https://user-images.githubusercontent.com/114185919/202924149-3a54c706-f629-4189-9b33-ff270ef1d24f.png" width="600px" />
</div>

Para o tipo Radix, todos os elementos devem ser de **d** dígitos. Mas nesta matriz notamos que alguns elementos têm um total de dígito diferentes. Então, o que podemos fazer?

Podemos converter todos os elementos para o mesmo número de dígitos. 23 pode ser assumido como 023, e 1 como 001. *(obs: Isso não alterará o valor dos elementos)*. Uma vez que concluimos a converção dos elementos, nossa matriz se torna algo assim.

<div align="center">
  <img src="https://user-images.githubusercontent.com/114185919/202923888-3249e444-1079-4c8d-aa76-87981cc470ec.png" height="300px" />
</div>

Agora, classificamos todos esses números “no lugar” usando o dígito na casa da unidade, dezena e, finalmente, a casa da centena.

<div align="center">
  <img src="https://user-images.githubusercontent.com/114185919/202924547-405f88b3-6d0a-4363-b715-4cc717dc1c4b.png" height="300px" />
</div>

Primeiro precisamos saber qual a maior chave do vetor, usando a função max, para descobirmos quantas vezes iremos executar o procedimento do **coutsort** na próxima potência, podemos cria-lá em outro ponto do programa, seu papel será de recebe o vetor e a quantidade de elementos retornando o maior elemento desse vetor.

```c
void radix_sort(int *v, int n){
    int k, div = 1;
    k = max(v, n);
    int *temp = malloc(sizeof(int) * n);

    while (k > 0){
        counting_sort(v, n, div, 10, temp);
        div *= 10;
        k /= 10;
    }
    free(temp);
}

```
Note que definimos um vetor temporário chamado **temp** alocado dinamicamente e por fim liberamos a memória pela função **free()**, este será utilizado para montar a saída do countsorting antes de copiarmos de volta para o vetor principal **v**, .

**O próximo passo** é implementar esse **countsort** específico que irá contar a frequência  de um determinado dígito/posição, vejamos no código abaixo:  
```c
void counting_sort(int *v, int n, int div, int base, int *temp){
    int i, t, c[base], acum = 0;
    memset(c, 0, base * sizeof(int));

    #define DIGIT(x) (x / div) % base

    for(i = 0; i < n; i++){
        c[DIGIT(v[i])]++;
    }

    for(i = 0; i < base; i++){
        t = c[i];
        c[i] = acum;
        acum += t;
    }

    for (i = 0; i < n; i++){
        temp[c[DIGIT(v[i])]] = v[i];
        c[DIGIT(v[i])]++;
    }

    memcpy(v, temp, sizeof(int) * n);
    
}
```
Levamos em conta alguns aspectos para criação da função counting_sort como:
- variável temporária para a soma de prefixo.
- vetor para guardar a contagem de cada dígito.
- acumulador que será usado junto ao bloco de soma de prefixo.
- memset para zerar o vetor c.

Criamos uma macro chamada DIGIT recebendo a chave (x) que vai ser resolvida em tempo de compilação, sem chamadas de função.

Esta etapa do algoritimo, trata-se da contagem da frequência dos dígitos, onde passamos por todos os elementos do nosso vetor e incrementamos a posição no vetor **c** que corresponde ao dígito avaliado no dado momento na chave atual.
Em seguida é feito a soma de prefixo onde passamos por cada posição, e atualizamos o valor anterior de **c[i]**.
Por fim copiamos os elementos de *v* no vetor temporário obedecendo os índices de nosso vetor **c** que agora tem a soma de prefixos e atualizamos o vetor para não subscrevemos o valor que acabamos de colocar na posição correta, então por meio da função *memcpy* é copiado de volta para *v* os elementos de temp, que agora estão ordenados.












