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

Primeiro precisamos saber qual a maior chave do vetor, usando a função max, para descobirmos quantas vezes iremos executar o procedimento do **coutsort** na próxima potência. usar uma função chamada **max** que podemos criar em outro ponto do programa,  que recebe o vetor e a quantidade de elementos retornando o maior elemento desse vetor.
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
Note que definimos um vetor temporário chamado **temp** , que será utilizado para montar a saída do countsorting antes de copiarmos de volta para o vetor principal **v**
