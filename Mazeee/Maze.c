#include "Maze.h"

int main()
{
    char input; /*Comando do usuario*/
	Player jogador; 
	Escape saida;
	Tree* arvore;

    int escolher=0;
    int modo;
    int **mapa; 

    printf("Selecione a dificuldade: \n");
    printf("1 - Facil\n2 - Medio\n3 - Dificil\n");
    
    while(escolher != 1 && escolher != 2 && escolher != 3)
    {
        scanf("%d", &escolher);
        
        if(escolher == 1)
        {
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
            modo = MEDIO;
            mapa = (int**) malloc (MEDIO * sizeof(int*));
            for(int i=0; i<MEDIO; i++)
            {
                mapa[i] = (int*) malloc (MEDIO * sizeof(int));
            }

            for(int i=0; i<MEDIO; i++)
            {
                for(int j=0; j<MEDIO; j++)
                {
                    mapa[i][j] = mapa2[i][j];
                }
            }  
        }

        else if(escolher == 3)
        {
            modo = DIFICIL;
            mapa = (int**) malloc (DIFICIL * sizeof(int*));
            for(int i=0; i<DIFICIL; i++)
            {
                mapa[i] = (int*) malloc (DIFICIL * sizeof(int));
            }

            for(int i=0; i<DIFICIL; i++)
            {
                for(int j=0; j<DIFICIL; j++)
                {
                    mapa[i][j] = mapa3[i][j];
                }
            }
        }

        else
        {
            printf("Escolha uma dificuldade valida!\n");
        }
    }
    
    arvore = initialize_tree(); /*Inicializar arvore*/
	jogador = player_start(mapa, modo, &jogador); /*Encontrar posicao inicial do jogador dentro do mapa proposto*/
	saida = escape_pos(mapa, modo ,&saida); /*Encontrar posicao da saida dentro do mapa proposto*/

	arvore = insert_element(arvore, mapa[jogador.x][jogador.y]); /*Insere a posicao inicial na arvore*/

	while(check_end(&jogador, &saida, arvore) != 0) /*Enquanto o jogador não chegar na posição final*/
	{
		system("cls"); /*Limpar a tela*/
		print_maze(mapa, modo, &jogador, &saida); /*Imprimir labirinto*/

		fflush(stdin); /*Limpa o buffer para evitar erros de leitura*/
		input = getch(); /*Espera o comando do usuario*/

		/*Nota: Fiz uso das teclas padroes de movimentacao dentro dos jogos atuais. 
		O intuito foi por conta da familiarização da maioria das pessoas com as respectivas teclas:
		w = cima
		a = esquerda
		s = baixo
		d = direita*/

		if(input == 'w') /*Mover o jogador para cima*/
		{
			if(mapa[jogador.x-1][jogador.y] != 0 && mapa[jogador.x-1][jogador.y] != -3)
			{
				jogador.x--;
				arvore = insert_element(arvore, mapa[jogador.x][jogador.y]); /*Insere o valor na arvore, valor o qual o jogador acabou de passar por "cima"*/
			}
		}

		else if(input == 'a') /*Mover o jogador para esquerda*/
		{
			if(mapa[jogador.x][jogador.y-1] != 0 && mapa[jogador.x][jogador.y-1] != -3)
			{
				jogador.y--;
				arvore = insert_element(arvore, mapa[jogador.x][jogador.y]); /*Insere o valor na arvore, valor o qual o jogador acabou de passar por "cima"*/
			}
		}


		else if(input == 's') /*Mover o jogador para direita*/
		{
			if(mapa[jogador.x+1][jogador.y] !=0 && mapa[jogador.x+1][jogador.y] != -3)
			{
				jogador.x++;
				arvore = insert_element(arvore, mapa[jogador.x][jogador.y]); /*Insere o valor na arvore, valor o qual o jogador acabou de passar por "cima"*/
			}
		}

        else if(input == 'd') /*Mover o jogador para direita*/
		{
			if(mapa[jogador.x][jogador.y+1] != 0 && mapa[jogador.x][jogador.y+1] != -3)
			{
				jogador.y++;
				arvore = insert_element(arvore, mapa[jogador.x][jogador.y]); /*Insere o valor na arvore, valor o qual o jogador acabou de passar por "cima"*/
			}
		}
	}
}