# PurrinhaPipe

Projeto utilizando pipe, com o tema de Purrinha, onde esse jogo é um clássico, o jogo consiste em adivinhar a soma de todos os palitinhos escondidos nas mãos dos participantes. O projeto tem como objetivo usar pipes para a comunicação entre os jogadores e threads.

## Autoria
Samuel Munhoz Tunes

## O que é?
O jogo consiste em adivinhar a soma de todos os palitinhos escondidos nas mãos dos participantes, pode ser jogado por 2 ou mais jogadores, porém no projeto terá apenas 2 jogadores. 

## Como jogar:
1) cada jogador recebe um palito e o divide em três partes iguais.
2) cada jogador coloca as mãos para trás e escolhe a quantidade de palitinhos a 
serem escondidos.
3) Em seguida, todos mostram as mãos fechadas.
4) cada jogador tenta adivinhar a soma de todos os palitinhos. Por exemplo: 3, 5, 7.
5) Depois de darem suas sugestões, todos abrem juntos as mãos.
6) O jogador que acertar, tira um palitinho das mãos
7) Ganha aquele que ficar sem nenhum palitinho primeiro

## Desenvolvimento
O projeto foi tomado como base o exemplo dado pelo professor Boca sobre pipe, chat_de_pobre.c, na qual o último é um projeto tutorial sobre a comunicação entre processos usando pipes. O projeto Purrinha usou inteiramente exemplo para a realização de tal, sendo a base fundamental dele.
Funciona de forma que a criação de dois pipes, em que com isso permite a comunicação escrita e leitura para ambos os jogadores, na qual o primeiro jogador 1fará sua jogada e as informações eram transmitidas ao jogador 2.


## Resultados

<img src="https://github.com/SamuelTunes/PurrinhaPipe/blob/main/imagens/pipe2.jpeg" alt="Jogo em andamento.">
Jogo em andamento


<img src="https://github.com/SamuelTunes/PurrinhaPipe/blob/main/imagens/pipe1.jpeg" alt="Resultado com um vencedor.">
Resultado com um vencedor



## REFERÊNCIAS
● chat_de_pobre.c
João Carlos de Moraes Morselli Junior. Disponível em: 
<https://pucminas.instructure.com/courses/115518/files/6587706?
module_item_id=2548126>. 

● PRACINHA, N.7 brincadeiras no restaurante com palitinhos – pra abrir mão 
do celular. Disponível em: <https://napracinha.com.br/2017/02/7-brincadeirasno-restaurante-com-palitinhos-pra-abrir-mao-do-celular/>. Acesso em: 15 dez.
2022
