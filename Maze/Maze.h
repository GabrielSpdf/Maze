#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define INTRODUCAO 5
#define MEDIO 10
#define DIFICIL 20 /*Nivel de dificuldade*/

/*Estrutura para armazenar a posicao do jogador no mapa*/
typedef struct
{
   int x;
   int y;
} Player;

/*Estrutura para armazenar a posicao da saida*/
typedef struct
{
   int x;
   int y;
} Escape;


/*Estrutura da arvore*/
typedef struct arvore
{
    int info;
    struct arvore *esq;
    struct arvore *dir;
} Tree;

/*Funcao para inicializar a arvore*/
Tree* initialize_tree ()
{
    return NULL;
}

/*Funcao para inserir elemento na arvore*/
Tree* insert_element (Tree* arvore, int num)
{
    if(arvore == NULL)
    {
        arvore = (Tree*) malloc (sizeof(Tree));
        arvore->info = num;
        arvore-> esq = NULL;
        arvore->dir = NULL;
    }

    else
    {
        if(num < arvore->info)
        {
            arvore->esq = insert_element(arvore->esq, num);
        }

        else
        {
            if(num > arvore->info)
            {
                arvore->dir = insert_element(arvore->dir, num);
            }

            else
            {
                arvore->info = num;
            }
        }
    }

    return arvore;
}

/*Funcao para liberar o espaco alocado da arvore*/
void free_tree (Tree* arvore)
{
    if (arvore != NULL)
    {
        free_tree(arvore->esq);
        free_tree(arvore->dir);
        free(arvore);
    }
}

/*Funcao para verificar a posicao inicial do jogador e armazena-la*/
Player player_start(int **mapa, int *modo, Player *jogador)
{
    printf("buu\n");
    for(int i=0; i<(*modo); i++)
    {
        printf("buu2\n");
        printf("modo: %d\n", *modo);
        for(int j=0; j<(*modo); j++)
        {
            printf("buu3\n");
            if(mapa[i][j] == -1)
            {
                printf("buu4\n");
                jogador->x = i;
                jogador->y = j;
            }
        }
    }
    printf("buu7\n");

    return *jogador;
}

/*Funcao para verificar a posicao da saida e armazena-la*/
Escape escape_pos(int **mapa, int modo, Escape *saida_pos)
{
    for(int i=0; i<modo; i++)
    {
        for(int j=0; j<modo; j++)
        {
            if(mapa[i][j] == -2)
            {
                saida_pos->x = i;
                saida_pos->y = j;
            }
        }
    }

    return *saida_pos;
}

void print_visible(int **mapa, int modo, Player *jogador, Escape *saida)
{
    for(int i=0; i<modo; i++)
    {
        for(int j=0; j<modo; j++)
        {
            if(i == jogador->x && j == jogador->y)
            {
                printf(" %c ", 207); /*Jogador*/
            }

            else if((i == jogador->x-1 && j == jogador->y) || (i == jogador->x+1 && j == jogador->y) || (i == jogador->x && j == jogador->y-1) || (i == jogador->x && j == jogador->y+1) || (i == jogador->x-1 && j == jogador->y-1) || (i == jogador->x+1 && j == jogador->y+1) || (i == jogador->x-1 && j == jogador->y+1) || (i == jogador->x+1 && j == jogador->y-1))
            {
                if(mapa[i][j] == -3)
                {
                    printf(" %c ", 178); /*Entrada*/
                }

                else if(i == saida->x && j == saida->y)
                {
                    printf(" %c ", 176); /*Saida*/
                }

                else if(mapa[i][j]>=1 || mapa[i][j] == -1)
                {
                    printf("   "); /*Caminho dispon??vel*/
                }

                else if(!(mapa[i][j]))
                {
                    printf(" %c ", 254); /*Parede*/
                }
            }

            else
            {
                printf(" %c ", 46);
            }

        }

        printf("\n");
    }
}

/*Funcao para ordenar os valores em pre-ordem*/
void pre_ordem (Tree* arvore)
{
    if(arvore != NULL)
    {
        printf("%d ", arvore->info);
        pre_ordem(arvore->esq);
        pre_ordem(arvore->dir);
    }
}

/*Funcao para ordenar os valores em in-ordem*/
void in_ordem (Tree* arvore)
{
    if(arvore != NULL)
    {
        in_ordem(arvore->esq);
        printf("%d ", arvore->info);
        in_ordem(arvore->dir);
    }
}

/*Funcao para ordenar os valores em pos-ordem*/
void pos_ordem (Tree* arvore)
{
    if(arvore != NULL)
    {
        pos_ordem(arvore->esq);
        pos_ordem(arvore->dir);
        printf("%d ", arvore->info);
    }
}

/*Funcao para verificar se o jogador chegou no final do labirinto*/
int check_end(Player *jogador, Escape *saida, Tree* arvore)
{
    if(jogador->x == saida->x && jogador->y == saida->y)
    {
        printf("Voce completou o labirinto. Parabens!\n\n\n");

        puts("NOTAS.");
        puts("O numero -1 se refere a posicao inicial do jogador, ou seja, onde ele comecou o labirinto");
        puts("O numero -2 se refere a porta de saida do labirinto, ou seja, onde o jogador terminou o labirinto\n\n");

        printf("Ordenacao Pre-Ordem: ");
        pre_ordem(arvore);
        puts("\n");

        printf("Ordenacao Pos-Ordem: ");
        pos_ordem(arvore);
        puts("\n");

        printf("Ordenacao In-Ordem: ");
        in_ordem(arvore);
        puts("\n");

        free_tree(arvore);

        printf("PARABENS! Voce passou de fase!\n");
    }
    else
        return 1;
}

    int mapa1[INTRODUCAO][INTRODUCAO] = {
    {0, -2, 0, 0, 0},
    {0, 10, 11, 12, 0},
    {0, 13, 0, 14, 0},
    {0, 15, 16, -1, 0},
    {0, 0, 0, -3, 0}
};

int mapa2[MEDIO][MEDIO] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 500, 501, 502, 0, 0, 0, 0},
    {0, 503, 0, 504, 0, 505, 0, 0, 506, 0},
    {0, 507, 508, 509, 0, 510, 0, 0, 511, 0},
    {0, 0, 0, 512, 0, 513, 514, 0, 515, 0},
    {0, 0, 516, 517, 0, 0, 518, 519, -1, -3},
    {0, 520, 521, 0, 0, 0, 0, 0, 524, 0},
    {0, 525, 0, 526, 527, 528, 0, 529, 605, 0},
    {-2, 530, 531, 0, 0, 532, 533, 534, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int mapa3[DIFICIL][DIFICIL] = {
{0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 300, 299, 280, 281, 290, 283, 284, 285, 0, 287, 288, 289, 290, 291, 292, 293, 294, 295, 0},
{0, 0, 0, 0, 0, 284, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 277, 0},
{0, 270, 0, 272, 0, 273, 274, 187, 184, 185, 178, 186, 187, 0, 190, 191, 192, 193, 194, 0},
{0, 269, 0, 190, 0, 0, 0, 0, 183, 0, 0, 0, 189, 0, 188, 0, 0, 0, 0, 0},
{0, 267, 0, 266, 265, 264, 263, 0, 182, 0, 177, 0, 161, 160, 159, 158, 157, 156, 155, 0},
{0, 259, 260, 261, 0, 0, 262, 0, 181, 0, 176, 0, 162, 0, 0, 0, 0, 0, 154, 0},
{0, 258, 0, 0, 0, 257, 256, 0, 180, 179, 175, 0, 163, 0, 151, 152, 153, 0, 255, 0},
{0, 246, 0, 247, 248, 249, 250, 251, 252, 0, 174, 0, 164, 0, 150, 0, 253, 0, 254, 0},
{0, 245, 0, 244, 0, 0, 0, 0, 0, 0, 173, 0, 165, 0, 149, 0, 243, 0, 242, 0},
{0, 232, 233, 234, 235, 236, 237, 238, 239, 172, 171, 170, 166, 0, 148, 0, 240, 0, 241, 0},
{0, 231, 0, 0, 0, 230, 0, 229, 0, 0, 0, 169, 167, 228, 147, 0, 227, 226, 225, 0},
{0, 220, 221, 222, 0, 223, 0, 0, 0, 224, 0, 0, 168, 0, 146, 0, 0, 0, 0, 0},
{0, 0, 0, 219, 0, 140, 141, 142, 143, 144, 0, 145, 218, 0, 217, 216, 215, 214, 213, 0},
{0, 137, 138, 139, 0, 0, 0, 0, 0, 210, 0, 0, 211, 0, 0, 0, 0, 0, 212, 0},
{0, 136, 0, 0, 0, 120, 119, 118, 0, 114, 111, 112, 113, 0, 103, 209, 208, 0, 207, 0},
{0, 135, 0, 123, 122, 121, 0, 117, 116, 115, 110, 0, 0, 0, 102, 0, 205, 0, 206, 0},
{0, 134, 0, 124, 0, 125, 0, 0, 130, 0, 109, 0, 105, 104, 101, 0, 203, 0, 204, 0},
{0, 133, 132, 131, 0, 127, 126, 128, 129, 0, 108, 107, 106, 0, -1, 0, 200, 201, 202, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0}};

void desalocar(int **mapa, int modo)
{
    for(int i=0; i<modo; i++)
    {
        free(mapa[i]);
    }
    free(mapa);
}

void movimentacao(Player *jogador, Tree* arvore, int **mapa)
{
    char input;
    fflush(stdin); /*Limpa o buffer para evitar erros de leitura*/
    input = getch(); /*Espera o comando do usuario*/

    /*Nota: Fiz uso das teclas padroes de movimentacao dentro dos jogos atuais. 
    O intuito foi por conta da familiariza????o da maioria das pessoas com as respectivas teclas:
    w = cima
    a = esquerda
    s = baixo
    d = direita*/

    if(input == 'w') /*Mover o jogador para cima*/
    {
        if(mapa[jogador->x-1][jogador->y] != 0 && mapa[jogador->x-1][jogador->y] != -3)
        {
            jogador->x--;
            arvore = insert_element(arvore, mapa[jogador->x][jogador->y]); /*Insere o valor na arvore, valor o qual o jogador acabou de passar por "cima"*/
        }
    }

    else if(input == 'a') /*Mover o jogador para esquerda*/
    {
        if(mapa[jogador->x][jogador->y-1] != 0 && mapa[jogador->x][jogador->y-1] != -3)
        {
            jogador->y--;
            arvore = insert_element(arvore, mapa[jogador->x][jogador->y]); /*Insere o valor na arvore, valor o qual o jogador acabou de passar por "cima"*/
        }
    }


    else if(input == 's') /*Mover o jogador para direita*/
    {
        if(mapa[jogador->x+1][jogador->y] !=0 && mapa[jogador->x+1][jogador->y] != -3)
        {
            jogador->x++;
            arvore = insert_element(arvore, mapa[jogador->x][jogador->y]); /*Insere o valor na arvore, valor o qual o jogador acabou de passar por "cima"*/
        }
    }

    else if(input == 'd') /*Mover o jogador para direita*/
    {
        if(mapa[jogador->x][jogador->y+1] != 0 && mapa[jogador->x][jogador->y+1] != -3)
        {
            jogador->y++;
            arvore = insert_element(arvore, mapa[jogador->x][jogador->y]); /*Insere o valor na arvore, valor o qual o jogador acabou de passar por "cima"*/
        }
    }
}

    void fase_introducao (int *modo, int **mapa)
    {
        *modo = INTRODUCAO;
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

    void fase_media (int *modo, int **mapa)
    {
        *modo = MEDIO;
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

    void fase_dificil (int *modo, int **mapa)
    {
        *modo = DIFICIL;
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


/*Funcao para imprimir o labirinto*/
/*Nota: Fiz uso da tabela ASCII para ficar esteticamente mais agradavel a visualizacao do labirinto*/
/*void print_maze(int **mapa, int modo, Player *jogador, Escape *saida)
{
	for(int i=0; i<modo; i++)
   	{
		for(int j=0; j<modo; j++)
		{
			if(i == jogador->x && j == jogador->y)
			{
				printf(" %c ", 207); /*Jogador
			}

			else if(mapa[i][j] == -3)
			{
				printf(" %c ", 178); /*Entrada
			}

			else if(i == saida->x && j == saida->y)
			{
				printf(" %c ", 176); /*Saida
			}

			else if(mapa[i][j]>=1 || mapa[i][j] == -1)
			{
				printf("   "); /*Caminho dispon??vel
			}

			else if(!(mapa[i][j]))
			{
				printf(" %c ", 254); /*Parede
			}
		}

		printf("\n");
   	}
}*/

    


