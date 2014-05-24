# The Claw

Projeto de Computação Gráfica na UFRN.

## Compilando
Há um Makefile incluído no projeto. Para compilar alterações, execute

``` bash
make
```

Em alguns casos, o compilador pode não detectar algumas mudanças. Para
recompilar tudo, execute

``` bash
make clean
make
```

Para adicionar novos arquivos ao projeto, insira uma nova linha ao Makefile com
o nome da classe seguido de `.o` na parte referente aos objetos. Não se esqueça
de adicionar uma `\` ao final da linha se o objeto não for o último da lista.

## Controles

Comando             | Ação
------------------- | ---------------------------
C + ← / ↑ / → / ↓   | Movimentação da câmera
← / →               | Rotacionar junta
↑ / ↓               | Alterar junta selecionada
