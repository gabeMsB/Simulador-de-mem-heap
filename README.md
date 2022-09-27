## Simulador de manipulação de memória num heap
  
  - Nesta versão o programa recebe as instruções apenas por arquivo de texto.
  
  - As instruções tem o seguinte formato:
```
  <set_heap> ::= 'heap { 'first | 'best | 'worst | 'next }
  <new> ::= 'new <id> <number>
  <del> ::= 'del <id>
  <exibe> ::= 'exibe
  <atribui> ::= <id> '= <id>
```
