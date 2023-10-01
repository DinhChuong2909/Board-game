#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
const int a = 100;
 
void print_horizontal_line(int bsize) // in duong ------ tren cung cua bang
{
    for (int i = 0; i < bsize; i++)
        cout << " -------";
    cout << "\n";
}
void print_vertical_line(int bsize) // in duong | cho bang
{
    cout << "|";    
    for (int i = 0; i < bsize; i++)
        cout << "       |";
    cout << "\n";
}

void init_board(char board[][a], int bsize) // khoi tao gia tri ban dau cho bang 
{
    for(int i = 0; i < bsize; i++)
    {
        for (int j = 0; j < bsize; j++) 
        board[i][j] = ' ';
    }
}
void init_pos(int pos[], int horse) // khoi tao vi tri ban dau cua n con ngu
{ 
    for(int i = 0; i < horse; i++)
        pos[i] = -1;
}
void init_row(int row[], int horse) // khoi tao hang ban dau cho n con ngua
{
    for (int i = 0; i < horse; i++)
        row[i] = 0;
}

void print_boardziczac(char board[][a], int bsize) // in ra bang ziczac
{
    for (int i = 0; i < bsize; i++)
    {
        print_horizontal_line(bsize);
        print_vertical_line(bsize);
        if (i % 2 == 0)
        {
            cout << '|';
            for (int j = 0; j < bsize; j++)
                cout << "   " << board[i][j] << "   |";
            cout << '\n';
        }
        if (i % 2 != 0)
        {
            cout << '|';
            for (int j = bsize - 1; j > -1; j--)
                cout << "   " << board[i][j] << "   |";
            cout << '\n';
        }
        print_vertical_line(bsize);
    }
    print_horizontal_line(bsize);
}

void cur_pos(int pos[], char board[][a], int bsize, char name, int horse, int sizeroll, int n[]) // ham thong bao vi tri hien tai cua con ngua
{   
    int move = rand() % sizeroll + 1;
    cout << "Dice roll: " << move;
    if(horse > 1)
    { 
        cout << "\nChose the horse of player "<< name <<" want to move: " ;
        cin >> horse;
        cout << "\nHorse " << horse << " of " << name << " move: " << move << endl;
        if (pos[horse - 1] + move > bsize * bsize - 1)
            cout << "Player " << name << " cannot move" << endl;
        else
        {
            board[n[horse - 1]][pos[horse - 1] - (n[horse - 1] * bsize)] = ' ';
            pos[horse - 1] += move;
        }
        while(pos[horse - 1] > bsize * (n[horse - 1] + 1)) n[horse - 1]++;
        for (int j = 0; j < bsize; j++)
            if (j == pos[horse - 1] - n[horse - 1] * bsize) board[n[horse - 1]][j] = name;
    }else
        {
            cout << "\nHorse " << horse << " of " << name << " move: " << move << endl;
            if (pos[horse - 1] + move > bsize * bsize - 1)
                cout << "Player " << name << " cannot move" << endl;
            else
            {
                board[n[horse - 1]][pos[horse - 1] - (n[horse - 1] * bsize)] = ' ';
                pos[horse - 1] += move;
            }
            while(pos[horse - 1] > bsize * (n[horse - 1] + 1)) n[horse - 1]++;
            for (int j = 0; j < bsize; j++)
                if (j == pos[horse - 1] - n[horse - 1] * bsize) board[n[horse - 1]][j] = name;
        }
}

char checkwin(int pos[], int horse, int bsize, char name) // ham kiem tra player da thang chua
{
    for (int i = 0; i < horse; i++)
    if(pos[i] == bsize * bsize - 1) 
    {
        cout << "Player " << name << " is the winner!!!" << endl;
        return name;
    }
}

void checkmove1(int pos1[],int pos2[] , int horse, int bsize, int n[], char name) // ham kiem tra vi tri cua player1
{   
        for(int j = 0; j < horse; j++)
        if(pos1[horse - 1] == pos2[j] && pos2[j] != -1) 
        {
            cout << "Player " << name << " is kicked " << endl;
            pos2[j] = -1;
            n[j] = 0;
        }
}   
void checkmove2(int pos1[],int pos2[] , int horse, int bsize, int n[], char name) // ham kiem tra vi tri cua player2
{   
        for(int j = 0; j < horse; j++)
        if(pos2[horse - 1] == pos1[j] && pos1[j] != -1) 
        {   
            cout << "Player " << name << " is kicked " << endl;
            pos1[j] = -1;
            n[j] = 0;
        }
}

char playGame(char board[][a], int bsize, int pos1[], int pos2[], int horse, int sizeroll, char name1, char name2, int n1[], int n2[])
{ // Ham xet luot choi cho tung nguoi
    int turnval = 1;
    while(turnval <= bsize * bsize - sizeroll)
    {
        if(turnval % (horse * 2) == 1 || turnval % (horse * 2) == 3 || turnval % (horse * 2) == 5 )
        {
            cur_pos(pos1, board, bsize, name1, horse, sizeroll, n1);
            checkmove1(pos1, pos2, horse, bsize, n2, name2);
            print_boardziczac(board, bsize);
            if(checkwin(pos1, horse, bsize, name1) == name1)
            {
                return name1;
                break;
            }
            turnval++;
        }else
            {   
                cur_pos(pos2, board, bsize, name2, horse, sizeroll, n2);
                checkmove2(pos1, pos2, horse, bsize, n1, name1);
                print_boardziczac(board, bsize);
                checkmove2(pos1, pos2, horse, bsize, n1, name1);
                if(checkwin(pos2, horse, bsize, name2) == name2) 
                {
                    return name2;
                    break;
                }
                turnval++;
            }
    }
    if(turnval > bsize * bsize - sizeroll) 
    {
        cout << "DRAW\n";
        return name2;
    }
}  

void color() // chon mau cho background va text
{
    int color;
    cout <<"Chose the color you want:"
         <<"\n1 Blue background and white text "
         <<"\n2 Black background and red text "
         <<"\n3 Yellow background and green text "
         <<"\n4 white background and black text "
         <<"\n5 Red background and yellow text \n";
    cin >> color;
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
            system("color E2");
            break;
        }
        case(4): 
        {
            system("color FA");
            break;
        }
        case(5): 
        {
            system("color 46");
            break;
        }
    }
}

void sound() // tat mo nhac
{
    char music;
    cout << "Enter 'on' to turn on music or not enter 'no': ";
    cin >> music;
    if (music == 'o') PlaySound(TEXT("sound.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
}

int main()
{   
    srand((unsigned)time(NULL));
    char board[a][a];
    int bsize = 0; // kich thuoc cua bang
    int sizeroll; // kich thuoc cua xuc xac
    int pos1[a], pos2[a]; // Vi tri cua cac con ngua cua p1 va p2
    int n1[a], n2[a]; // Vi tri dong cua cac con ngua cua p1 va p2
    int horse; // So ngua cua moi nguoi choi
    char name1, name2; // ten cua hai nguoi choi
    int count1 = 0, count2 = 0; // Dem so luot thang cua p1 va p2
    int map; 
    char replay = 'y';
    color();
    sound();
    cout << "RULES:" ;
    cout << "\nIF DRAW PLAYER2 WIN."
         << "\nYOU WIN IF ONE OF YOUR HORSES FINISH"
         << "\nMUST USE OTHER HORSE IF HORSE GRATER THAN 1"
         << "\nREMEMBER YOUR HORSE";
    cout << "\nEnter player1's name: ";
    cin >> name1;
    cout << "Enter player2's name: ";
    cin >> name2;
    cout << "Enter the size of dice: ";
    cin >> sizeroll;
    cout << "Which map do you want ?"
         << "\n1.ZicZac 3x3"
         << "\n2.ZixZac 5x5"
         << "\n3.ZixZac 7x7"
         << "\n4. Random size\n";
    cin >> map;
    if(map == 1) bsize = 3;
    else if(map == 2) bsize = 5;
    else if(map == 3) bsize = 7;
    else bsize = rand()%6 + 3;
    while(replay == 'y' || replay == 'Y')
    {
        pos1[horse];
        pos2[horse];
        init_row(n1, horse);
        init_row(n2, horse);
        init_pos(pos1, horse);
        init_pos(pos2, horse);
        init_board(board, bsize);
        cout << "Enter amount of horse per player (LIMIT 3): ";
        cin >> horse;
        cout << "player " << name1 << " " << count1 << " win";
        cout << "\t\tplayer " << name2 << " " << count2 << " win\n";
        if ((playGame(board, bsize, pos1, pos2, horse, sizeroll, name1, name2, n1, n2) == name1)) count1++;
            else count2++;
        cout << "Do you want to play again?"
            << "\nEnter 'Yes' if you want to play again or not Enter 'No': ";
        cin >> replay;  
    }
    cout << "player " << name1 << " " << count1 << " win";
    cout << "\t\tplayer " << name2 << " " << count2 << " win\n";

    system("pause");
    return 0;
}   
