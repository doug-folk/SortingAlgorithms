# Sorting algorithms

Algoritmo de ordenação é um algoritmo que coloca os elementos de uma dada sequência em uma certa ordem. Ele efetua sua ordenação completa ou parcial. O objetivo da ordenação é facilitar a recuperação dos dados de uma lista.

Para este artigo foram escolhidos alguns algoritmos de ordenação para serem estudados que são: **Radix Sort e Shell Sort**.

## Radix sort 
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

# Shell sort
O Shellsort é um algoritmo de ordenação por comparação proveniente de uma generalização do algoritmo de ordenação por inserção (InsertionSort). A ordenação por Shellsort constitui-se de execuções sequenciais de InsertionSort sobre subconjuntos tomados dos *n* elementos do vetor de entrada, sendo que o último subconjunto é aquele de todos os elementos (ou seja, é uma execução padrão do InsertionSort). 

Esta estratégia tem potencial de obter melhor desempenho quando **(i)** as ordenações anteriores à última atuam sobre subconjuntos de elementos de tamanhos controlados, de modo que o custo do pior caso para estas execuções iniciais tenham peso reduzido no custo total; e **(ii)** os elementos escolhidos para serem pré-ordenados são tais que evitam o pior caso quadrático do último InsertionSort, de modo que a diminuição do custo na última execução compense as ordenações parciais anteriores.












