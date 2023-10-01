#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <fstream>
#pragma comment(lib, "winmm.lib")

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define PAUSE 27

#define WHITE 7
#define LIGHT_BLUE 9
#define LIGHT_RED 12
#define LIGHT_YELLOW 14

using namespace std;
const int a = 20;

struct Player
{
    char name[11];
    char icon;
    int count;
    Player()
    {
        memset(name, 11, '\0');
        icon = ' ';
        count = 0;
    }
};

void Gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void print_horizontal_line(int bsize)
{
    for (int i = 0; i < bsize; i++)
        cout << " -------";
    cout << "\n";
}
void print_vertical_line(int bsize)
{
    cout << "|";
    for (int i = 0; i < bsize; i++)
        cout << "       |";
    cout << "\n";
}
void print_board(char board[][a], int bsize)
{
    for (int i = 0; i < bsize; i++)
    {
            print_horizontal_line(bsize);
            print_vertical_line(bsize);
            cout << "|";
            for (int j = 0; j < bsize; j++)
            {
                cout << "   " << board[i][j] << "   ";
                cout << "|";
            }
            cout << '\n';
        print_vertical_line(bsize);
    }
    print_horizontal_line(bsize);
}
void init_board(char board[][a], int bsize)
{
    for (int i = 0; i < bsize; i++)
    {
        for (int j = 0; j < bsize; j++)
            board[i][j] = ' ';
    }
}

void Save_game(Player player[], char board[][a], int bsize, int winsize , int turn, char music, int color)
{
    ofstream fout("save.txt");
    for(int i = 0; i < 2; ++i)
    {
        fout << player[i].name << " " << player[i].icon << " " << player[i].count << "\n";
    }
    fout << winsize << " " << bsize << " " << music << " " << color << " " << turn << "\n";
    for(int i = 0; i < bsize; ++i)
    {
        for(int j = 0; j < bsize; ++j)
        {
            if(board[i][j] == ' ') 
                fout << 0 << " ";
            else 
                fout << board[i][j] << " ";
        }
        fout << endl;
    }

    fout.close();
}
void Load_game(Player player[], char board[][a], int &bsize, int &winsize, int &turn, char &music, int &color)
{
    ifstream fin("save.txt");
    if(!fin.is_open())
    {
        int x = 30, y = 7;
	system("cls");
        Gotoxy(x, y);
        cout << "Dont have any save file";
        cin.get();
        return;
    }
    else 
    {
        for(int i = 0; i < 2; ++i)
            fin >> player[i].name >> player[i].icon >> player[i].count;
            
        fin >> winsize >> bsize >> music >> color >> turn;

        for(int i = 0; i < bsize; ++i)
        {
            for(int j = 0; j < bsize; ++j)
            {
                char temp = ' ';
                fin >> temp;
                if(temp == '0') 
                    board[i][j] = ' ';
                else 
                    board[i][j] = temp;
            }
        }
    }
    fin.close();
}

void Color(int &color) // chon mau cho background va text
{
    if(color > 0) goto COLOR_CHOSE;
    cout <<"Chose the color you want:"
         <<"\n1 Blue background and white text "
         <<"\n2 Black background and red text "
         <<"\n3 White background and cyan text "
         <<"\n4 white background and black text "
         <<"\n5 Red background and yellow text"
         <<"\nEnter your choice: ";
    cin >> color;
    COLOR_CHOSE:
    switch(color)
    {
        case(1): 
        {
            system("color 17");
            break;
        }
        case(2): 
        {
            system("color 04");
            break;
        }
        case(3): 
        {
            system("color FB");
            break;
        }
        case(4): 
        {
            system("color BA");
            break;
        }
        case(5): 
        {
            system("color 46");
            break;
        }
    }
}
void Sound(char &music) // tat mo nhac
{
    if(music == ' ')
    {
        cout << "Do you want to turn on music (Y/N) ? ";
        cin >> music;
    }
    else if (music == 'y' || music == 'Y') PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}
void Custom_Icon(Player player[], char PvE)
{
    char answer;
    cout << "Custom icon (Y/N)? ";
    cin >> answer;
    if(answer == 'Y' || answer == 'y')
    {
        if(PvE == 'Y' || PvE == 'y')
        {
            cout << "Enter the icon of player 1: ";
            cin >> player[0].icon;
        }
        else
        {
            cout << "Enter the icon of player 1: ";
            cin >> player[0].icon;
            cout << "Enter the icon of player 2: ";
            cin >> player[1].icon;
        }
        
    }else 
        {
            player[0].icon = 'X';
            player[1].icon = 'O';
        }
}
void Set_Color(int color)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}
void Animation_Loading()
{
    system("color 07");
	int x, y;
	x = 19, y = 10;
	Gotoxy(x, y);
	Set_Color(LIGHT_BLUE);
	cout << char(218);
	for (int i = 1; i <= 80; i++) cout << char(196);
	cout << char(191);
	Gotoxy(x, y + 1);
	cout << char(179);
	for (int i = 1; i <= 80; i++) cout << " ";
	cout << char(179);
	Gotoxy(x, y + 2);
	cout << char(192);
	for (int i = 1; i <= 80; i++) cout << char(196);
	cout << char(217);
	Set_Color(WHITE);

	Set_Color(LIGHT_YELLOW);
	Gotoxy(x + 1, y + 3);
	for (int i = 1; i <= 80; i++)
	{
		if (i == 1)
		{
			Gotoxy(x + 86, y + 1);
			cout << "%";
			Gotoxy(x + 31, y + 3);
			cout << ". . . LOADING . . .";
			Gotoxy(x + 1, y + 1);
		}
		cout << char(219);
		Gotoxy(x + 83, y + 1);
		cout << i + 20;
		Gotoxy(i + x + 1, y + 1);
		if (i + 20 == 100)
		{
			Gotoxy(x + 31, y + 3);
			Set_Color(LIGHT_RED);
			cout << ". . . COMPLETE . . .";
			Set_Color(WHITE);
		}
		Sleep(40);
	}
	Gotoxy(x + 87, y + 1);
	Sleep(1000);
	system("cls");
}
void Tictactoe()
{
    cout << "\t\t\t _____ _____ _____    _____ _____ _____    _____ _____ _____ \n";
    cout << "\t\t\t|_   _|     |     |  |_   _|  _  |     |  |_   _|     |   __|\n";
    cout << "\t\t\t  | | |-   -|   --|    | | |     |   --|    | | |  |  |   __|\n";
    cout << "\t\t\t  |_| |_____|_____|    |_| |__|__|_____|    |_| |_____|_____|\n";
}
void Intro(Player player[], char board[][a] ,int &bsize, int &winsize, int turn ,int &PvE, char &music, int &color)
{
    int x = 45, y = 7;
    int i = 1;
        Main_Menu:
        system("cls");
        Tictactoe();
        char move;
        Gotoxy(x, y);
        cout << "> RULE <";
        Gotoxy(x + 2, y + 2);
        cout << "CONTINUE";
        Gotoxy(x + 2, y + 4);
        cout << "PvP";
        Gotoxy(x + 2, y + 6);
        cout << "PvE";
    while(1)
    {
		move = _getch();
        if (move == UP && i > 1)
		{
            i--;
            if(i == 1)
            {
                Gotoxy(x, y);
                cout << "  CONTINUE  ";
                y -= 2;
                Gotoxy(x, y);
                cout << "> RULE <";
            }
            if(i == 2)
            {
                Gotoxy(x, y);
                cout << "  PvP  ";
                y -= 2;
                Gotoxy(x, y);
                cout << "> CONTINUE < ";
            } 
            if(i == 3)
            {
                Gotoxy(x, y);
                cout << "  PvE  ";
                y -= 2;
                Gotoxy(x, y);
                cout << "> PvP ";
            }
             
			
		}
		else if (move == DOWN && i < 5)
		{
            i++;
            if(i == 2)
            {
                Gotoxy(x, y);
                cout << "  RULE  ";
                y += 2;
                Gotoxy(x, y);
                cout << "> CONTINUE < ";
            }
            if(i == 3)
            {
                Gotoxy(x, y);
                cout << "  CONTINUE  ";
                y += 2;
                Gotoxy(x, y);
                cout << "> PvP < ";
            } 
            if(i == 4)
            {
                Gotoxy(x, y);
                cout << "  PvP  ";
                y += 2;
                Gotoxy(x, y);
                cout << "> PvE < ";
            } 
		}
        
        if(move == ' ' || move == '\r')
        {
            if(i == 1)
            {
                system("cls");
                x = 30, y = 7;
                Tictactoe();
                Gotoxy(x, y);
                cout << "- Tie game that's mean Player2 win";
                Gotoxy(x, y + 1);
                cout << "- Three or five same symbol on one line. You win";
                cin.get();
                x = 45; y = 7;
                goto Main_Menu;
            }
            if(i == 2)
            {
                Load_game(player, board, bsize, winsize, turn, music, color);
                system("cls");
                goto ANIMATION_LOADING;
            }
            if(i == 3)
            {
                PvE = 0;
                goto PvP;
            } 
            if(i == 4)
            {
                PvE = 1;
                goto PvE;
            } 
        }
    }
   
    //name
        PvE:
        system("cls");
        Tictactoe();
        Gotoxy(0, 7);
        cout << "Enter the name of the player 1: ";
        cin >> player[0].name;
        player[1].name[0] = 'B';
        player[1].name[1] = 'O';
        player[1].name[2] = 'T';
        player[1].name[3] = '\0';
        player[1].icon = 'O';
        goto Enter_Size;
        
        PvP:
        system("cls");
        Tictactoe();
        Gotoxy(0, 7);
        cout << "Enter the name of the player 1: ";
        cin >> player[0].name;
        cout << "Enter the name of the player 2: ";
        cin >> player[1].name;

    //setting
    Enter_Size:
		cout << "Enter the size of the board (3 -> 10) : ";
		cin >> bsize;
		if (bsize > 10 || bsize < 3)
		{
			cout << "\nYou have typed wrong format!";
			cout << "\nPlease enter again!";
			goto Enter_Size;
		}
        init_board(board, bsize);
	Enter_winsize:
		cout << "How many continuous point to win? (3 -> " << bsize << ") : ";
		cin >> winsize;
		if (winsize < 3 || winsize > bsize)
		{
			cout << "\nYou have typed wrong format!";
			cout << "\nPlease enter again!";
			goto Enter_winsize;
		}
        Color(color);
        cout << "\n";
        Sound(music);
        cout << "\n";
        Custom_Icon(player, PvE);
    system("cls");
    ANIMATION_LOADING:
    Animation_Loading();
    Color(color);
}

char Chosepos(char board[][a], int bsize, char s, char player[], int &turn, char icon, int &posx , int &posy)
{
    print_board(board, bsize);
    int x, y, i, j;
	i = j = 1;
	Gotoxy(30 + (bsize / 2) * 7, 2);
	cout << "Turn: " << player;
    x = 4, y = 2;
    Gotoxy(x, y);
    while(1)
    {
        char move;
        move = _getch();
        if (move == UP && i > 1)
        {
            y -= 4;
            i--;
        }
        else if (move == DOWN && i < bsize)
        {
            y += 4;
            i++;
        }
        else if (move == RIGHT && j < bsize)
        {
            x += 8;
            j++;
        }
        else if (move == LEFT && j > 1)
        {
            x -= 8;
            j--;
        }
        else if (move == ' ' || move == '\r')
        {
            if(board[i-1][j-1] == ' ')
            {
                cout << icon;
                board[i-1][j-1] = icon;
                posx = j;
                posy = i;
                Gotoxy(x, y);
                break;
            }
            else
            {
                Gotoxy(30 + (bsize / 2) * 7, 3);
                cout << "This pos havs been taken!\n";
                Gotoxy(30 + (bsize / 2) * 7, 3);
                cout << player << " repick your pos (x y)";
            }
        }
        else if(move == PAUSE)
        {
            system("cls");
            int t = 1;
            int a = 45, b = 7;
            Gotoxy(a, b);
            cout << "> CONTINUE <";
            Gotoxy(a + 2, b + 2);
            cout << "QUIT";
            Gotoxy(a + 2, b + 4);
            cout << "SAVE AND QUIT";
            while(1)
            {
                move = _getch();
                if (move == UP && t > 1)
                {
                    t--;
                    if(t == 1)
                    {
                        Gotoxy(a, b);
                        cout << "  QUIT  ";
                        b -= 2;
                        Gotoxy(a, b);
                        cout << "> CONTINUE <";
                    } 
                    if(t == 2)
                    {
                        Gotoxy(a, b);
                        cout << "  SAVE AND QUIT  ";
                        b -= 2;
                        Gotoxy(a, b);
                        cout << "> QUIT <";
                    }
                }
                else if (move == DOWN && t < 4)
                {
                    t++;
                    if(t == 2)
                    {
                        Gotoxy(a, b);
                        cout << "  CONTINUE  ";
                        b += 2;
                        Gotoxy(a, b);
                        cout << "> QUIT <      ";
                    } 
                    if(t == 3)
                    {
                        Gotoxy(a, b);
                        cout << "  QUIT  ";
                        b += 2;
                        Gotoxy(a, b);
                        cout << "> SAVE AND QUIT < ";
                    } 
                }
                if(move == ' ' || move == '\r')
                {
                    if(t == 1) break;
                    if(t == 2) exit(0);
                    if(t == 3)
                    {
                        return 'q';
                    }
                }
            }
        }
        Gotoxy(x, y);
    }
    system("cls");
}
void Botchose(char board[][a], int bsize, int &posx, int &posy)
{
    int i, j;
    for(i = 1; i <= bsize; ++i)
    {
        for(j = 1; j <= bsize; ++j)
        {
             if(board[i-1][j-1] == ' ')
            {
                board[i-1][j-1] = 'O';
                posx = j;
                posy = i;
                break;
            }
        }
        if(board[i-1][j-1] == 'O') break;
    }
}

bool checkhorizontal(char board[][a], int bsize, int posy, int icon, int winsize)
{   
    int sum = 0;
    for (int i = 0; i <= bsize - winsize; i++)
    {
        if (board[posy-1][i] == icon)
        {
            for (int j = i; j < bsize; j++)
            {
                if(board[posy-1][j] == icon)
                {
                    sum++;
                    if(sum == winsize) return true;
                }else 
                    {
                        i = j;
                        sum = 0;
                        break;
                    }
            } 
        }
    }
    return false;
}
bool checkvertical(char board[][a], int bsize, int posx, int icon, int winsize)
{
    int sum = 0;
    for (int i = 0; i <= bsize - winsize; i++)
    {
        if (board[i][posx-1] == icon)
        {
            for (int j = i; j < bsize; j++)
            {
                if(board[j][posx-1] == icon)
                {
                    sum++;
                    if(sum == winsize) return true;
                }else  
                    {
                        i = j;
                        sum = 0;
                        break;
                    }
            } 
        }
    }
    return false;
}
bool checkmaindiagonal(char board[][a], int bsize, int posy, int posx, int icon, int winsize) 
{
    int sum = 0;
    int i = 0;
    int temp = 0;
    if(posy >= posx)
    {
        temp = posy - posx;
        i = 0;
    }
    else
    {
        i = posx - posy;
        temp = 0;
    } 
    for(; i <= bsize - winsize; i++, temp++)
    {
        if(board[temp][i] == icon)
        {
            for (int j = i; j < bsize; j++)
            {
                if(board[temp][j] == icon)
                {
                    sum++;
                    temp++;
                    if(winsize == sum) return true;
                }else 
                    {
                        i = j;
                        sum = 0; 
                        break;
                    }
            }
        }
    }
    return false;
}
bool checksubdiagonal(char board[][a], int bsize, int posy, int posx, int icon, int winsize)
{
    int temp = 0;
    int sum = 0;
    int i = 0;
    if(posx + posy > bsize)
    {
        temp = posx + posy - bsize - 1;
        i = bsize - 1; 
        for(; i > bsize - winsize; i--, temp++)
        {
            if(board[temp][i] == icon)
            {
                for(int j = i; j >= 0; j--)
                {
                    if(board[temp][j] == icon)
                    {
                        sum++;
                        temp++;
                        if(sum == winsize) return true;
                    }else  
                        {
                            i = j;
                            sum = 0;
                            break;
                        }
                }
            }
        }
        return false;
    }
    else
    {
        temp = posx + posy - 2;
        i = 0;
        for(; i <= bsize - winsize; i++, temp--)
        {
            if(board[i][temp] == icon)                 
            {                                           
                for(int j = i; j < bsize; j++)
                {
                    if(board[j][temp] == icon)
                    {
                        sum++;
                        temp--;
                        if(sum == winsize) return true;
                    }else  
                        { 
                            i = j;
                            sum = 0;
                            break;
                        }
                } 
            }
        } 
        return false;
    }
}

bool checkwin(char board[][a], int bsize, char s, char player[], int posx, int posy, int winsize)
{
    if (checkhorizontal(board, bsize, posy, s, winsize) == true) return true;
    if (checkvertical(board, bsize, posx, s, winsize) == true) return true;
    if (checkmaindiagonal(board, bsize, posy, posx, s, winsize) == true) return true;
    if (checksubdiagonal(board, bsize, posy, posx, s, winsize) == true) return true;
    return false;
}

bool Playgame(char board[][a], int bsize, int turn, int posx, int posy, int winsize, Player player[], char music, int color)
{
    char winner = ' ';
    while(turn <= bsize * bsize)
    {   
        if(turn % 2 == 1)
        {
            system("cls");
            if(Chosepos(board, bsize, player[1].icon, player[0].name, turn, player[0].icon, posx, posy) == 'q')
            {
                Save_game(player, board, bsize, winsize, turn, music, color);
                exit(0);
            }
            print_board(board, bsize);
            if(checkwin(board, bsize, player[0].icon, player[0].name, posx, posy, winsize) == true) 
            {
                cout << player[0].name << " win\n";
                return true;
            }
        }
        else 
        {
            system("cls");
            if(Chosepos(board, bsize, player[0].icon, player[1].name, turn, player[1].icon, posx, posy) == 'q')
            {
                Save_game(player, board, bsize, winsize, turn, music, color);
                exit(0);
            }
            print_board(board, bsize);
            if(checkwin(board, bsize, player[1].icon, player[1].name, posx, posy, winsize) == true)
            {
                cout << player[1].name << " win\n";
                return false;
            }
        }
        turn++;
    }
    if(turn > bsize * bsize)
    {
        cout << "TIE!";
        return false;
    } 
}
bool PvE(char board[][a], int bsize, int turn, int posx, int posy, int winsize, Player player[], char music, int color)
{
    char winner = ' ';
    while(turn <= bsize * bsize)
    {   
        if(turn % 2 == 1)
        {
            system("cls");
            if(Chosepos(board, bsize, player[1].icon, player[0].name, turn, player[0].icon, posx, posy) == 'q')
            {
                Save_game(player, board, bsize, winsize, turn, music, color);
                exit(0);
            };
            print_board(board, bsize);
            if(checkwin(board, bsize, player[0].icon, player[0].name, posx, posy, winsize) == true) 
            {
                cout << player[0].name << " win\n";
                return true;
            }
        }
        else 
        {
            system("cls");
            Botchose(board, bsize, posx, posy);
            print_board(board, bsize);
            if(checkwin(board, bsize, player[1].icon, player[1].name, posx, posy, winsize) == true)
            {
                cout << player[1].name << " win\n";
                return false;
            }
        }
        turn++;
    }
    if(turn > bsize * bsize)
    {
        cout << "TIE!";
        return false;
    } 
}

int main()
{
    char board[a][a];
    int posx = 0 , posy = 0;
    int bsize = 5, winsize = 0, turn = 1, map = 0, bot = 0, color = 0;
    char replay = 'y', music = ' ';
    Player player[2];
    Intro(player, board, bsize, winsize, turn, bot, music, color);

    while(replay == 'y' || replay == 'Y')
    {
        if(bot == 0) 
        {
            if(Playgame(board, bsize, turn, posx, posy, winsize, player, music, color) == true) player[0].count++;
            else player[1].count++;
            cout << "Play again? (Y/N) ";
            cin >> replay;
        }
        else
        {
            if(PvE(board, bsize, turn, posx, posy, winsize, player, music, color) == true) player[0].count++;
            else player[1].count++;
            cout << "Play again? (Y/N) ";
            cin >> replay;
        }
    }

    cout << "player " << player[0].name << " " << player[0].count << " win";
    cout << "\t\tplayer " << player[1].name << " " << player[1].count << " win\n";
    Save_game(player, board, bsize, winsize, turn, music, color);

    system("pause");
    return 0;
}
