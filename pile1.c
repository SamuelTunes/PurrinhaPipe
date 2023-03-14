#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int a[2] = {0, 0}, j1 = 3, j2 = 3;
void * placar(void * arg);

main() {

        inicio(); //Inicio do programa / Sobre e como jogar

        int descritor, // usado para criar o processo filho pelo fork
        pipe1[2], // comunicacao pai -> filho
                pipe2[2]; // comunicacao filho -> pai

        if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
                printf("Erro na chamada PIPE");
                exit(0);
        }
        //   Fork para criar o processo filho
        if ((descritor = fork()) < 0) {
                printf("Erro na chamada FORK");
                exit(0);
        } else if (descritor > 0) // PROCESSO PAI
        {
                close(pipe1[0]); // fecha leitura no pipe1
                close(pipe2[1]); // fecha escrita no pipe2
                jogador1(pipe2[0], pipe1[1]); // Chama JOGADOR 1 no PAI
                close(pipe1[1]); // fecha pipe1
                close(pipe2[0]); // fecha pipe2
                exit(0);
        } // FIM DO PROCESSO PAI
        else // PROCESSO FILHO
        {
                close(pipe1[1]); // fecha escrita no pipe1
                close(pipe2[0]); // fecha leitura no pipe2
                jogador2(pipe1[0], pipe2[1]); // Chama JOGADOR 2 no FILHO
                close(pipe1[0]); // fecha leitura no pipe1
                close(pipe2[1]); // fecha escrita no pipe2
                exit(0);
        } // FIM DO PROCESSO FILHO
} // FIM DO MAIN
/*
-----------------------------------------------------------------------------------
------------------------
Funcao jogador 1:  Executa no processo PAI
Envia as respostas do jogador 1 o FILHO(jogador 2)
Recebe os dados do FILHO e imprime na tela
-----------------------------------------------------------------------------------
------------------------ */
jogador1(readfd, writefd)
int readfd, // leitura do pipe2[0]
writefd; // escrita no pipe1[1]
{
        char buff[3][2];
        strcpy(buff[2], "n");
        while (1) {
                if (strcmp(buff[2], "n")) j1--;
                if ((j1 == 0)||(j2==0)) j1 = 3;
                printf("\n Jogador 1->");
                printf("\n Usará quantos palitos de 0 a %d->", j1);
                gets(buff[0]);
                while (1) {
                        if (strtol(buff[0], NULL, 10) <= j1) break;
                        printf(" \n A quantidade usada de palitos tem que ser menor ou igual ao que você ainda possui");
                        printf("\n Usará quantos palitos de 0 a %d->", j1);
                        gets(buff[0]);
                }
                printf(" Quantidade de palitos que terá no total->");
                gets(buff[1]);
                write(writefd, buff, 10);
                read(readfd, buff, 10);
        }
} // Fim da Funcao CLIENT
/*
-----------------------------------------------------------------------------------
------------------------
Funcao jogador-2:  Executa no processo FILHO
recebe as escolhas do jogador 1
chamará a função 'vencedor'
envia seu conteudo para o PAI
-----------------------------------------------------------------------------------
------------------------ */
jogador2(readfd, writefd)
int readfd, // leitura do pipe1[0]
writefd; // escrita no pipe2[1]
{
        char buff[3][2];
        pthread_t thread;
        strcpy(buff[2], "n");
        int n, fd;
        while (1) {
                read(readfd, buff, 10);
                a[0] = strtol(buff[0], NULL, 10);
                a[1] = strtol(buff[1], NULL, 10);

                printf(" \n Jogador 2->");
                printf("\n Usará quantos palitos de 0 a %d->", j2);
                gets(buff[0]);
                while (1) {
                        if (strtol(buff[0], NULL, 10) <= j2) break;
                        printf(" \n A quantidade usada de palitos tem que ser menor ou igual ao que você ainda possui");
                        printf("\n Usará quantos palitos de 0 a %d->", j2);
                        gets(buff[0]);
                }
                printf(" Quantidade de palitos que terá no total->");
                gets(buff[1]);
                while (1) {
                        if (strtol(buff[1], NULL, 10) != a[1]) break;
                        printf(" \n Não pode repetir a mesma resposta com a do Jogador-1");
                        printf(" \n Quantidade de palitos que terá no total->");
                        gets(buff[1]);
                }
                vencedor(buff, a);
                pthread_create( & thread, NULL, placar, NULL);
                pthread_join(thread, NULL);
                write(writefd, buff, 10);
        }
}

//Função Vencedor que irá ver se houve um vencedor da rodada e/ou final.
int vencedor(char buff[3][2], int jog1[2]) {
        int resultado;
        resultado = jog1[0] + strtol(buff[0], NULL, 10);
        printf("\n------------------------------------------\n");
        if (jog1[1] == resultado) {
                j1--;
                if (j1 == 0) {
                        j1 = 3, j2 = 3;
                        strcpy(buff[2], "s");
                        system("clear");
                        printf("\n\t\t\t------------------------------------------\n");
                        printf("\n\t\t\t\t\tJogador 1 Win\n");
                        printf("\n\t\t\t------------------------------------------\n");
                        printf("Reiniciando Jogo...\n");
                        inicio();
                } else {
                        printf("\nJogador 1 venceu essa rodada\n");
                        strcpy(buff[2], "s");
                        printf("Total de palito -> %d\nResposta do Jogador 1 -> %d\nResposta do Jogador 2 -> %s\n", resultado, a[1], buff[1]);
                        printf("\n------------------------------------------\n");
                }
        } else if (strtol(buff[1], NULL, 10) == resultado) {
                j2--;
                if (j2 == 0) {
                        j1 = 3;
                        j2 = 3;
                        system("clear");
                        printf("\n\t\t\t------------------------------------------\n");
                        printf("\n\t\t\t\t\tJogador 2 Win\n");
                        printf("\n\t\t\t------------------------------------------\n");
                        printf("Reiniciando Jogo...\n");
                        inicio();
                } else {
                        printf("\nJogador 2 venceu essa rodada\n");
                        strcpy(buff[2], "n");
                        printf("Total de palito -> %d\nResposta do Jogador 1 -> %d\nResposta do Jogador 2 -> %s\n", resultado, a[1], buff[1]);
                        printf("\n------------------------------------------\n");
                }
        } else {
                printf("\nNinguém acertou");
                printf("Total de palito -> %d\nResposta do Jogador 1 -> %d\nResposta do Jogador 2 -> %s\n", resultado, a[1], buff[1]);
                printf("\n------------------------------------------\n");
        }
}

void inicio() {
        printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
        printf("\nAluno: Samuel Munhoz Tunes\n");
        printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n\t\t\t\t\tIniciando o jogo Purrinha ou jogo do palitinho...\n");
        printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n Clássico dos clássicos, o jogo consiste em adivinhar a soma de todos os palitinhos escondidos nas mãos dos participantes.\n");
        printf("\nComo funciona:\n");
        printf("\n1) cada jogador recebe um palito e o divide em três partes iguais.");
        printf("\n2) cada jogador coloca as mãos para trás e escolhe a quantidade de palitinhos a serem escondidos.");
        printf("\n3) Em seguida, todos mostram as mãos fechadas.");
        printf("\n4) cada jogador tenta adivinhar a soma de todos os palitinhos. Por exemplo: 3, 5, 7.");
        printf("\n5) Depois de darem suas sugestões, todos abrem juntos as mãos.");
        printf("\n6) O jogador que acertar, tira um palitinho das mãos");
        printf("\n7) Ganha aquele que ficar sem nenhum palitinho primeiro");
        printf("\n------------------------------------------\n");
}

//Thread que mostra o placar do jogo
void * placar(void * arg) {
        printf("\nPlacar -> %d,%d \n", j1, j2);
        pthread_exit(NULL);
}
