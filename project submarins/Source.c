#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//
#include <stdlib.h>
#include <time.h>
//functions
#define ff printf

//const varibles

#define MinBoredSize 5
#define MaxBoredSize 99
#define MinCellW 2
#define MinCellH 1
#define SUBMARINS 2


//colors
#define	YELLOW	"\033[0;33m"
#define	GREEN	"\033[0;32m"
#define WHITE	"\033[0;37m"
#define BLUE	"\033[0;34m"
#define L_BLUE	"\033[1;34m"
#define RED		"\033[1;31m"
#define BLACK	"\033[0;30m"


//BG colors
#define	BGYELLOW	"\033[0;43m"
#define	BGGREEN		"\033[0;42m"
#define BGWHITE		"\033[0;47m"
#define BGBLUE		"\033[0;44m"
#define BGL_BLUE	"\033[1;44m"
#define BGRED		"\033[1;41m"
#define BGBLACK		"\033[0;40m"


//------------------------------


//Functions - decleration

//messeges and printing

//messeges for the player
void welcome_massege();
void print_bored_rules();
void pass_the_computer_messege(int player);
void win_messege(int player);



//bored printing
void drow_bored(int boredSize, int cellW, int cellH, int bored[2][MaxBoredSize][MaxBoredSize], int player, int showBoredTwo);
void drow_line(int boredSize, int cellW);
void drow_numbers(int boredSize, int cellW);
void drow_line_of_cells(int boredSize, int cellW, int cellH, int bored[2][MaxBoredSize][MaxBoredSize], int index, int player, int showBoredTwo);
void drow_cells(int boredSize, int cellW, int bored[MaxBoredSize], int showSubmarin);
void drow_cell(int cellW, int value, int showSubmarin);
void drow_border();
//
void drow_submarins(int size);
void drow_submarin(int size, int or );



//colors
void yellow();
void green();
void white();
void blue();
void Lblue();
void red();
void black();


//BG colors
void bg_yellow();
void bg_green();
void bg_white();
void bg_blue();
void bg_Lblue();
void bg_red();
void bg_black();

//sound
void ball();


//------------------------------


//player interaction
void set_bored(int* boredSizeDef, int* cellWDef, int* cellHDef, int bored[2][MaxBoredSize][MaxBoredSize], int player);
int set_boredSize();
void set_cellSize(int* cellW, int* cellH);
void set_submarins(int boredSize, int cellW, int cellH, int bored[2][MaxBoredSize][MaxBoredSize], int player);
int choos_oraintation(int size);
void choos_red_dot_placement(int size, int or , int boredSize, int bored[2][MaxBoredSize][MaxBoredSize], int player);
void place_submarin(int x, int y, int size, int or , int boredSize, int bored[MaxBoredSize][MaxBoredSize]);
void correct_submarin(int boredSize, int bored[MaxBoredSize][MaxBoredSize]);
void bombing(int boredSize, int cellW, int cellH, int bored[2][MaxBoredSize][MaxBoredSize], int player);


//------------------------------


//convertion
int str_to_int(char str[]);


//------------------------------


//chacking
int is_submarin_placement_good(int x, int y, int size, int or , int boredSize, int bored[MaxBoredSize][MaxBoredSize]);
int is_bombing_valid(int x, int y, int boredSize, int bored[MaxBoredSize][MaxBoredSize]);
int check_victory(int bored[MaxBoredSize][MaxBoredSize], int boredSize);


//------------------------------


//convenience
void pause();
void clear();
//
int random(int Nmin, int Nmax);


//------------------------------



//the main function
int main()
{
	//Start of test erea - you can run code lines hear to test them, BUT remember to delete them

	
	
	//End of test erea
	
	//varibles
	int isGameover = 0, player = 0;

	int boredSize, cellW , cellH;

	int bored[2][MaxBoredSize][MaxBoredSize] = { 0 };

	for (int i = 0; i < MaxBoredSize; i++)
	{
		for (int j = 0; j < MaxBoredSize; j++)
		{
			bored[0][i][j] = 1;
			bored[1][i][j] = 1;

		}
	}

	//the program
	welcome_massege();
	set_bored(&boredSize, &cellW, &cellH, bored, player);
	clear();

	pass_the_computer_messege(player);

	do
	{
		set_submarins(boredSize, cellW, cellH, bored, player);
		player = !player;
		pass_the_computer_messege(player);
	} while (player);

	//main game
	while (!isGameover)
	{
		bombing(boredSize, cellW, cellH, bored, player);
		pause();
		isGameover = check_victory(bored[!player], boredSize);
		if (!isGameover)
		{
		player = !player;
		pass_the_computer_messege(player);
		}
		else
		{
			win_messege(player);
		}
		clear();
	}

	return 0;
}
//------------------------------


//Functions - realization (im hoping that i writed it right)

//messeges and printing

//messeges for the player
void welcome_massege()
{
	clear();
	ff("%s", GREEN);
	ff("\t\t\t\t\t###############################\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#     %sWelcome to my game!%s     #\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t###############################\n");
	//
	ff("\n\n\t\t\t\t\t");
	yellow();
	pause();
	clear();
	green();
	//
	ff("\t\t\t\t\t###############################\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#            %sStart:%s           #\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 1: Set boared size          %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 2: Set submarins placement  %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 3: pass to the other player %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    the computer - so he     %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    could set his submarins  %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t# %s4: Enjoy!%s                   #\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t###############################\n");
	//
	ff("\n\n\t\t\t\t\t");
	yellow();
	pause();
	clear();
	green();
	//
	ff("\t\t\t\t\t###############################\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s            Rules:           %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 1: in each turn choos spot  %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    to bomb.                 %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 2: the program will show    %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    diffrent color if its a  %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    blank space or an        %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    ocupied space.           %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 3: pass the computer to the %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    other player and rpeat   %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 4: the game end when one    %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    player disroy all the    %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    other player submarin.   %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t###############################\n");
	//
	ff("\n\n\t\t\t\t\t");
	yellow();
	pause();
	clear();
	green();
	//
	white();
}
//
void print_bored_rules()
{
	green();
	ff("\t\t\t\t\t###############################\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s          Bored rules:       %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 1: define the %sbored %ssize -  %s#\n", YELLOW, WHITE, YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    the minimum has to be %s%2d %s#\n", YELLOW, RED, MinBoredSize, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s 2: define the %scells %ssize -  %s#\n", YELLOW, WHITE, YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    the with and height dont %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    has to match - but the   %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    minimum width has to     %s#\n", YELLOW,  GREEN);
	ff("\t\t\t\t\t#    %sbe %s%d.                    %s#\n",YELLOW,RED,MinCellW,GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#%s    the recomended size is:  %s#\n", YELLOW, GREEN);
	ff("\t\t\t\t\t#%s    bored: %s25                %s#\n", YELLOW, RED, GREEN);
	ff("\t\t\t\t\t#%s    cell width: %s3            %s#\n", YELLOW, RED, GREEN);
	ff("\t\t\t\t\t#%s    cell height: %s1           %s#\n", YELLOW, RED, GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t###############################\n");
	//
	ff("\n\n\t\t\t\t\t");
	yellow();
	pause();
	clear();
	green();
}
//
void pass_the_computer_messege(int player)
{
	clear();
	ball();
	ball();
	ff("%s", RED);
	ff("\t\t\t\t\t###############################\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#      %sPass the compoter%s      #\n", YELLOW, RED);
	ff("\t\t\t\t\t#         %sto player %s%d%s         #\n", YELLOW, WHITE, player + 1, RED);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t###############################\n");
	//
	ff("\n\n\t\t\t\t\t");
	red();
	pause();
	clear();
	green();
}
//
void win_messege(int player)
{
	clear();
	ball();
	ball();
	ff("%s", GREEN);
	ff("\t\t\t\t\t###############################\n");
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t#       %sPlayer %s%d %swon!!        %s#\n", YELLOW,WHITE,player + 1,YELLOW ,GREEN);
	ff("\t\t\t\t\t#                             #\n");
	ff("\t\t\t\t\t###############################\n");
	//
	ff("\n\n\t\t\t\t\t");
	yellow();
	pause();
	clear();
	green();
}


//bored printing
void drow_bored(int boredSize, int cellW, int cellH, int bored[2][MaxBoredSize][MaxBoredSize], int player, int showBoredTwo)
{
	int i = 0, j = 0;

	drow_numbers(boredSize, cellW);
	if (showBoredTwo)
	{
		ff("\t\t%s   your bored",YELLOW);
		
	}
	ff("\n");

	drow_line(boredSize, cellW);

	if (showBoredTwo)
	{
		ff("\t");
		drow_line(boredSize, cellW);
	}
	ff("\n");
	for (; i < boredSize; i++)
	{
		green();
		(ff("%6d", i + 1));

		drow_line_of_cells(boredSize,cellW,cellH, bored,i, player, showBoredTwo);

		drow_line(boredSize, cellW);

		if (showBoredTwo)
		{
			ff("\t");
			drow_line(boredSize, cellW);
		}

		ff("\n");
	}
}
//
void drow_line(int boredSize, int cellW)
{
	int i = 0;
	blue();
	ff("\t");
	for (; i < (boredSize * cellW) + boredSize + 1; i++)
	{
		ff("-");
	}
	white();
}
//
void drow_numbers(int boredSize, int cellW)
{
	int i = 0;
	red();
	ff("\t");
	for (; i < boredSize; i++)
	{
		ff("%*d", cellW + 1, i + 1);
	}
	white();
}
//
void drow_line_of_cells(int boredSize, int cellW, int cellH, int bored[2][MaxBoredSize][MaxBoredSize], int index, int player, int showBoredTwo)
{
	int i = 0;
	for (; i < cellH; i++)
	{
		drow_cells(boredSize, cellW, bored[player][index], 0);
		if (showBoredTwo)
		{
			ff("\t");
			drow_cells(boredSize, cellW, bored[!player][index], showBoredTwo);
		}
		ff("\n");
	}
}
//
void drow_cells(int boredSize, int cellW, int bored[MaxBoredSize], int showSubmarin)
{
	int i = 0;
	ff("\t");
	drow_border();
	for (; i < boredSize; i++)
	{
		drow_cell(cellW, bored[i], showSubmarin);
		drow_border();
	}
}
//
void drow_cell(int cellW, int value, int showSubmarin)
{
	int i = 0;

	switch (value)
	{
	case 0:
		bg_black();
		break;
	case 1:
		bg_Lblue();
		break;
	case 2:
		showSubmarin ? bg_green() : bg_black();
		break;
	case 3:
		bg_red();
		break;
	default:
		bg_yellow();
		break;
	}

	for (; i < cellW; i++)
	{

		ff(" ");
	}
	bg_white();
}
//
void drow_border()
{
	blue();
	ff("|");
	white();
}
//
void drow_submarins(int size)
{
	int i = 0;
	yellow();
	ff("1:\n");
	drow_submarin(size, 1);
	ff("\n");
	ff("\n");
	yellow();
	ff("2:\n");
	drow_submarin(size, 2);
	ff("\n");

}
//
void drow_submarin(int size, int or )
{
	int i = 0;
	switch (or )
	{
	case 1:
		red();
		for (; i < size; i++)
		{
			ff("*");
			green();
		}
		break;
	case 2:
		red();
		for (i = 0; i < size; i++)
		{
			ff("*\n");
			green();
		}
		break;
	}
	ff("\n");
	ff("\n");
}



//colors
void yellow() { printf(YELLOW); }
//
void green() { printf(GREEN); }
//
void white() { printf(WHITE); }
//
void blue() { printf(BLUE); }
//
void Lblue() { printf(L_BLUE); }
//
void red() { printf(RED); }
//
void black() { printf(BLACK); }


//BG colors
void bg_yellow() { printf(BGYELLOW); }
void bg_green() { printf(BGGREEN); }
void bg_white() { printf(BGWHITE); }
void bg_blue() { printf(BGBLUE); }
void bg_Lblue() { printf(BGL_BLUE); }
void bg_red() { printf(BGRED); }
void bg_black() { printf(BGBLACK); }


//sound
void ball() { ff("\a"); }


//------------------------------


//player interaction
void set_bored(int* boredSizeDef, int* cellWDef, int* cellHDef, int bored[2][MaxBoredSize][MaxBoredSize], int player)
{
	int boredSize = boredSizeDef, cellW = cellWDef, cellH = cellHDef;
	int isOK, isGood;
	char choos;

	print_bored_rules();

	do
	{

		boredSize = set_boredSize();

		set_cellSize(&cellW, &cellH);
		clear();
		drow_bored(boredSize, cellW, cellH, bored, player, 0);
		do
		{
			isOK = 1;
			printf("\n\n\t\t\t\t\t%sis that good? (y/n): ", YELLOW);
			scanf(" %c", &choos);
			if (!(choos == 'y' || choos == 'n'))
			{
				isOK = 0;
				printf("\t\t\t\t\t%sinvalid char\n\n", RED);
			}
		} while (!isOK);
	} while (choos != 'y');
	*boredSizeDef = boredSize;
	*cellWDef = cellW;
	*cellHDef = cellH;
}
//
int set_boredSize()
{
	int isOK = 1;
	int boredSize;
	char temp[5];
	clear();
	do
	{
		isOK = 1;
		ff("\t\t\t\t\t%senter bored size (minimum %s%d%s maximum %s%d%s): ", YELLOW, RED, MinBoredSize, YELLOW, RED, MaxBoredSize, YELLOW);
		red();
		scanf("%4s", temp);
		boredSize = str_to_int(temp);
		if (boredSize < MinBoredSize)
		{
			isOK = 0;
			clear();
			red();
			ff("\t\t\t\t\ttoo small\n\n");
		}
		else if (boredSize > MaxBoredSize)
		{
			isOK = 0;
			clear();
			red();
			ff("\t\t\t\t\ttoo big\n\n");
		}
		else
		{
			clear();
		}
	} while (!isOK);
	return boredSize;
}
//
void set_cellSize(int* cellWSorce, int* cellHSorce)
{
	int isOk;
	int cellW, cellH;
	char temp[3];
	clear();
	do
	{
		isOk = 1;
		ff("\t\t\t\t\t%senter cell width (minimum %s%d%s): ", YELLOW, RED, MinCellW, YELLOW);
		red();
		scanf("%2s", temp);
		cellW = str_to_int(temp);
		white();
		if (cellW < MinCellW)
		{
			isOk = 0;
			clear();
			red();
			ff("\t\t\t\t\ttoo small\n\n");
		}
	} while (!isOk);
	clear();
	do
	{
		isOk = 1;
		ff("\t\t\t\t\t%senter cell height (minimum %s%d%s): ", YELLOW, RED, MinCellH, YELLOW);
		red();
		scanf("%2s", temp);
		cellH = str_to_int(temp);
		white();
		if (cellH < MinCellH)
		{
			isOk = 0;
			clear();
			red();
			ff("\t\t\t\t\ttoo small\n\n");
		}
	} while (!isOk);

	*cellHSorce = cellH;
	*cellWSorce = cellW;
}
//
void set_submarins(int boredSize, int cellW, int cellH, int bored[2][MaxBoredSize][MaxBoredSize], int player)
{
	int size, j;
	int or, isGood;
	int x, y;


	for (size = SUBMARINS; size > 0; size--)
	{
		for (j = 1; j <= SUBMARINS - (size - 1); j++)
		{
			yellow();
			ff("submarine size %d number %d/%d\n\n", size, j, SUBMARINS - (size - 1));
			if (size > 1)
			{
				or = choos_oraintation(size);
			}
			clear();

			yellow();
			drow_submarin(size, or );
			drow_bored(boredSize, cellW, cellH, bored, player, 0);
			yellow();

			choos_red_dot_placement(size, or , boredSize, bored,player);
			
			clear();
		}
	}
	correct_submarin(boredSize,bored[player]);
}
//
int choos_oraintation(int size)
{
	int choos;
	char temp[2];
	drow_submarins(size);

	yellow();

	ff("\nwhat oriantetion do you want? (1/2)\n");
	do
	{
		scanf("%1s", temp);
		choos = str_to_int(temp);
		if (choos != 1 && choos != 2)
		{
			red();
			ff("not valid oriantetion\n");
			yellow();
		}
	} while (choos != 1 && choos != 2);

	return choos;
}
//
void choos_red_dot_placement(int size, int or , int boredSize, int bored[2][MaxBoredSize][MaxBoredSize], int player)
{
	int isGood,x,y;
	char temp[2][3];
	ff("where to place the red dote of the submarin (%sx%s/%sy%s)? ", RED, YELLOW, GREEN, YELLOW);
	do
	{
		isGood = 1;
		scanf("%2s%2s", temp[0], temp[1]);
		x = str_to_int(temp[0]) -1;
		y = str_to_int(temp[1]) - 1;
		isGood = is_submarin_placement_good(x, y, size, or , boredSize, bored[player]);
		if (!isGood)
		{
			red();
			ff("not a valid placement\n");
			yellow();
		}
	} while (!isGood);
	place_submarin(x, y, size, or , boredSize, bored[player]);
}
//
void place_submarin(int x, int y, int size, int or , int boredSize, int bored[MaxBoredSize][MaxBoredSize])
{
	int i = y, j = x;
	switch (or )
	{
	case 1:
		(j > 0 && i > 0) && (bored[i - 1][j - 1] = 0);
		(j > 0) && (bored[i][j - 1] = 0);
		(j > 0 && i < boredSize - 1) && (bored[i + 1][j - 1] = 0);
		for (; j < x + size; j++)
		{
			bored[i][j] = 3;
			(i < boredSize - 1) && (bored[i + 1][j] = 0);
			(i > 0) && (bored[i - 1][j] = 0);
			(j < boredSize - 1 && i < boredSize - 1) && (bored[i + 1][j + 1] = 0);
			(j < boredSize - 1 && i > 0) && (bored[i - 1][j + 1] = 0);
			(j < boredSize - 1) && (bored[i][j + 1] = 0);
		}

		break;
	case 2:
		(j > 0 && i > 0) && (bored[i - 1][j - 1] = 0);
		(i > 0) && (bored[i - 1][j] = 0);
		(j < boredSize - 1 && i > 0) && (bored[i - 1][j + 1] = 0);
		for (; i < y + size; i++)
		{
			bored[i][j] = 3;
			(j < boredSize - 1) && (bored[i][j + 1] = 0);
			(j > 0) && (bored[i][j - 1] = 0);
			(j < boredSize - 1 && i < boredSize - 1) && (bored[i + 1][j + 1] = 0);
			(j > 0 && i < boredSize - 1) && (bored[i + 1][j - 1] = 0);
			(i < boredSize - 1) && (bored[i + 1][j] = 0);
		}

		break;
	}
}
//
void correct_submarin(int boredSize, int bored[MaxBoredSize][MaxBoredSize])
{
	int i, j;
	for (i = 0; i < boredSize ; i++)
	{
		for (j = 0; j < boredSize; j++)
		{
			bored[i][j] -= bored[i][j] % 2;
		}
	}
}
//
void bombing(int boredSize, int cellW, int cellH, int bored[2][MaxBoredSize][MaxBoredSize], int player)
{
	int x, y, isGood;
	char temp[2][2];
	clear();
	drow_bored(boredSize, cellW, cellH, bored, !player,1);
	yellow();
	ff("\nwhere do you want to bomb (%sx%s/%sy%s)? ", RED, YELLOW, GREEN, YELLOW);
	do
	{
		scanf("%2s%2s", temp[0], temp[1]);
		x = str_to_int(temp[0]) - 1;
		y = str_to_int(temp[1]) - 1;
		isGood = is_bombing_valid(x, y,boredSize,bored[!player]);
		if (!isGood)
		{
			red();
			ff("you cant bomb that place\n");
			yellow();
		}
	} while (!isGood);

	bored[!player][y][x] += 1;

	if (bored[!player][y][x] == 3)
	{
		green();
		ff("\n\n\t\tGood hit!\n\n");
	}
	else
	{
		red();
		ff("\n\n\t\tYou missed!\n\n");
	}
	ff("\n");
	yellow();
}


//------------------------------


//convertion
int str_to_int(char str[])
{
	int sum = 0,i;
	for (i = 0; str[i] != '\0'; i++)
	{
		sum *= 10;
		sum += str[i] - '0';
	}
	return sum;
}


//------------------------------


//chacking
int is_submarin_placement_good(int x, int y, int size, int or , int boredSize, int bored[MaxBoredSize][MaxBoredSize])
{
	int i = y, j = x, isGood = 1;

	if (i >= 0 && j >= 0)
	{
		switch (or )
		{
		case 1:
			if (i < boredSize && j < boredSize - (size - 1))
			{

				for (; j < x + size && isGood; j++)
				{
					(bored[i][j] != 1) && (isGood = 0);
				}
			}
			else
			{
				isGood = 0;
			}
			break;
		case 2:
			if (i < boredSize - (size - 1) && j < boredSize)
			{
				for (; j < x + size && isGood; j++)
				{
					(bored[i][j] != 1) && (isGood = 0);
				}
			}
			else
			{
				isGood = 0;
			}
			break;
		}
	}
	else
	{
		isGood = 0;
	}
	return isGood;
}
int is_bombing_valid(int x, int y, int boredSize,int bored[MaxBoredSize][MaxBoredSize])
{
	int ret = 1;
	if (x < 0 || y < 0 || x >= boredSize || y >= boredSize)
		ret = 0;
	else
		ret = !(bored[y][x] % 2);

	return ret;
}
int check_victory(int bored[MaxBoredSize][MaxBoredSize], int boredSize)
{
	int i, j, ret = 1;

	for (i = 0; i < boredSize; i++)
	{
		for (j = 0; j < boredSize; j++)
		{
			if (bored[i][j] == 2)
			{
				ret = 0;
			}
		}
	}
	return ret;
}



//------------------------------


//convenience
void pause() { system("pause"); }
//
void clear() { 
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}
//


int random(int Nmin, int Nmax) 
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	srand((time_t)ts.tv_nsec);
	int min = Nmin, max = Nmax;
	int RUN = rand() % (max - min + 1) + min;
	return RUN;
}
