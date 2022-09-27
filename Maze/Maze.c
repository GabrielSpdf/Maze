#include "Maze.h"

/*Adicionar texto para cada fase

Introdução -> Fácil -> Médio -> Difícil 
Sugestão: Deixar o mapa "cego" apenas no difícil

Implementar progressão de fase*/

int main()
{
    int escolher=0;
    int modo;
    int **mapa; 
    Player jogador;
    Escape saida;
    Tree* arvore;


    printf("Selecione a dificuldade: \n");
    printf("1 - Facil\n2 - Medio\n3 - Dificil\n");


    while(escolher != 1 && escolher != 2 && escolher != 3)
    {
        scanf("%d", &escolher);

        if(escolher == 1)
        {
            //fase_introducao(&modo, &mapa);
        modo = INTRODUCAO;
        mapa = (int**) malloc (INTRODUCAO * sizeof(int*));
        for(int i=0; i<INTRODUCAO; i++)
        {
            mapa[i] = (int*) malloc (INTRODUCAO * sizeof(int));
        }

        for(int i=0; i<INTRODUCAO; i++)
        {
            for(int j=0; j<INTRODUCAO; j++)
            {
                mapa[i][j] = mapa1[i][j];
            }
        }
        }

        else if(escolher == 2)
        {
            fase_media(&modo, mapa);
        }

        else if(escolher == 3)
        {
            fase_dificil(&modo, mapa);
        }

        else
        {
            printf("Escolha uma dificuldade valida!\n");
        }
    }

    printf("oi1\n");
    
    arvore = initialize_tree(); /*Inicializar arvore*/
    printf("oi2\n");
	jogador = player_start(mapa, &modo, &jogador); /*Encontrar posicao inicial do jogador dentro do mapa proposto*/
    printf("oi3\n");
	saida = escape_pos(mapa, modo ,&saida); /*Encontrar posicao da saida dentro do mapa proposto*/
    printf("oi4\n");
	arvore = insert_element(arvore, mapa[jogador.x][jogador.y]); /*Insere a posicao inicial na arvore*/


    
    while(check_end(&jogador, &saida, arvore)) /*Enquanto o jogador não chegar na posição final*/
	{
		system("cls"); /*Limpar a tela*/
		print_visible(mapa, modo, &jogador, &saida); /*Imprimir labirinto*/
        movimentacao(&jogador, arvore, mapa);
	}
}