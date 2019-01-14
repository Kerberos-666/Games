#include<bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80


const int width=66;
const int height=30;
int turns_count=0;
int score=0;
int high_score=0;
bool inc=0;
int difficulty=150;
char plane[height][width];
pair<int ,int>tail=make_pair(1,1);
pair<int,int>head=make_pair(1,2);
pair<int,int> food;
vector< pair<int,int> > turns;
map<pair<int,int> , char> dir_of_turn;
char dir='d';
char dir_of_head='d' , dir_of_tail='d';
bool stop=0 , skip=0 , eaten=0 , leave=0 , restart=0;
void SetPlane(){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(i==0 || i==height-1)plane[i][j]='#';
            else if(j==0 || j==width-1)plane[i][j]='#';
            else plane[i][j]=' ';

        }
    }
}

void SetWindow(int Width, int Height)
    {
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
    }




void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }


void DrawPlane(){
    SetColor(10);
    srand((int)time(0));
    int x;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            x=rand();
            if(x%2==0)SetColor(2);
            else SetColor(10);
            if(i==head.first && j==head.second){
                SetColor(13);
                cout<<char(178);
            }
            else if(i==tail.first && j==tail.second){
                SetColor(13);
                cout<<char(219);
            }
            else cout<<plane[i][j];
        }
        cout<<endl;
    }
}
void TurnSnake(){

    switch(dir){
        case 'W':
        case 'w':
            dir_of_head='w';
            turns_count++;
            turns.push_back(head);
            dir_of_turn[head]='w';
            break;
        case 'S':
        case 's':
            dir_of_head='s';
            turns_count++;
            turns.push_back(head);
            dir_of_turn[head]='s';
            break;
        case 'A':
        case 'a':
            dir_of_head='a';
            turns_count++;
            turns.push_back(head);
            dir_of_turn[head]='a';
            break;
        case 'D':
        case 'd':
            dir_of_head='d';
            turns_count++;
            turns.push_back(head);
            dir_of_turn[head]='d';
            break;


    }



}
void SetCursorPosition(int x, int y){
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x,y};
    SetConsoleCursorPosition(output, pos);
}
void EditPlane(){
    SetColor(0);
    SetCursorPosition(tail.second , tail.first);
    cout<<' ';
    plane[tail.first][tail.second]=' ';
    SetCursorPosition(head.second , head.first);
    SetColor(13);
    cout<<char(219);
    plane[head.first][head.second]=char(219);
    if(dir_of_head=='d'){
        head.second++;
    }
    else if(dir_of_head=='s'){
        head.first++;
    }
    else if(dir_of_head=='a'){
        head.second--;
    }
    else if(dir_of_head=='w'){
        head.first--;
    }
    if(plane[head.first][head.second]=='#' || plane[head.first][head.second]==char(219)){
        stop=1;
        return;
    }
    if(plane[head.first][head.second]=='&'){
        SetCursorPosition(head.second , head.first);
        cout<<' ';
        plane[head.first][head.second]=' ';
        skip=1;
        eaten=1;
    }
    SetCursorPosition(head.second , head.first);
    cout<<char(178);
    plane[head.first][head.second]=char(178);
    if(dir_of_tail=='d' && skip==0){
        tail.second++;
    }
    else if(dir_of_tail=='s' && skip==0){
        tail.first++;
    }
    else if(dir_of_tail=='a' && skip==0){
        tail.second--;
    }
    else if(dir_of_tail=='w' && skip==0){
        tail.first--;
    }
    skip=0;
    if(turns.size()>0){
            if(tail==turns[0]){
            dir_of_tail=dir_of_turn[turns[0]];
            turns.erase(turns.begin());
            turns_count--;
        }
    }


}


void Menu2(){
    SetCursorPosition(0 , 9);
    cout<<"                         ";
    SetCursorPosition(0 , 10);
    cout<<"                         ";
    SetCursorPosition(0 , 11);
    cout<<"                         ";
    SetCursorPosition(0,12);
    cout<<"          ";
    SetCursorPosition(0 , 9);
    cout<<"-Easy"<<endl;
    cout<<"-Normal"<<endl;
    cout<<"-Hard";
    SetCursorPosition(5 , 9);
    cout<<" <";
    char choice2;
    int enter2;
    int pos2=1;
    while(true){
        choice2=getch();
        enter2=choice2;
        if(choice2=='s' || choice2=='S'){
            if(pos2==1){
                SetCursorPosition(5 , 9);
                cout<<"  ";
                SetCursorPosition(7 , 10);
                cout<<" <";
                pos2=2;
            }
            else if(pos2==2){
                SetCursorPosition(7 , 10);
                cout<<"  ";
                SetCursorPosition(5 , 11);
                cout<<" <";
                pos2=3;
            }
            else if(pos2==3){
                SetCursorPosition(5 , 11);
                cout<<"  ";
                SetCursorPosition(5 , 9);
                cout<<" <";
                pos2=1;
            }


    }
    else if(choice2=='w' || choice2=='W'){
                if(pos2==1){
                SetCursorPosition(5 , 9);
                cout<<"  ";
                SetCursorPosition(5 , 11);
                cout<<" <";
                pos2=3;
            }
            else if(pos2==2){
                SetCursorPosition(7 , 10);
                cout<<"  ";
                SetCursorPosition(5 , 9);
                cout<<" <";
                pos2=1;
            }
            else if(pos2==3){
                SetCursorPosition(5 , 11);
                cout<<"  ";
                SetCursorPosition(7 , 10);
                cout<<" <";
                pos2=2;
            }


    }
    else if(enter2==13) {
        if(pos2==1){
            difficulty=150;
        }
        else if(pos2==2){
            difficulty=100;
        }
        else if(pos2==3){
            difficulty=50;
        }
        SetCursorPosition(0 , 9);
        cout<<"                         ";
        SetCursorPosition(0 , 10);
        cout<<"                         ";
        SetCursorPosition(0 , 11);
        cout<<"                         ";
        SetCursorPosition(0 , 9);
        SetColor(14);
        cout<<"-Start"<<endl;
        cout<<"-Select Difficulty"<<endl;
        cout<<"-Controls"<<endl;
        cout<<"-Exit";
        SetCursorPosition(6 , 9);
        cout<<" <";
        SetColor(10);
        SetCursorPosition(30 , 10);
        cout<<"                   ";
        SetCursorPosition(30 , 10);
        cout<<"Difficulty : ";
        if(difficulty==150)cout<<"EASY";
        else if(difficulty==100)cout<<"NORMAL";
        else if(difficulty==50)cout<<"HARD";
        SetCursorPosition(8 , 9);
        SetColor(14);
        return;


    }


}
}

void ControlsPage(){
    char x;
    SetCursorPosition(0,9);
    cout<<"          "<<endl;
    cout<<"                   "<<endl;
    cout<<"             "<<endl;
    cout<<"             "<<endl;
    cout<<"             "<<endl;
    SetCursorPosition(0,9);
    cout<<"-Move UP : w"<<endl;
    cout<<"-Move DOWN : s"<<endl;
    cout<<"-Move LEFT : a"<<endl;
    cout<<"-Move RIGHT : d"<<endl;
    cout<<"-PAUSE : p         =Controls Can't Be Changed="<<endl;
    x=getch();
    SetCursorPosition(0,9);
    cout<<"            "<<endl;
    cout<<"                  "<<endl;
    cout<<"               "<<endl;
    cout<<"               "<<endl;
    cout<<"                                                  "<<endl;
    SetCursorPosition(0 , 9);
    SetColor(14);
    cout<<"-Start"<<endl;
    cout<<"-Select Difficulty"<<endl;
    cout<<"-Controls"<<endl;
    cout<<"-Exit";
    SetCursorPosition(6 , 9);
    cout<<" <";
}




void Menu1(){
SetColor(13);
cout<<" _______  _        _______  _        _______ "<<endl;
cout<<"(  ____ \\( (    /|(  ___  )| \\    /\\(  ____ \\"<<endl;
cout<<"| (    \\/|  \\  ( || (   ) ||  \\  / /| (    \\/"<<endl;
cout<<"| (_____ |   \\ | || (___) ||  (_/ / | (__    "<<endl;
cout<<"(_____  )| (\\ \\) ||  ___  ||   _ (  |  __)   "<<endl;
cout<<"      ) || | \\   || (   ) ||  ( \\ \\ | (      "<<endl;
cout<<"/\\____) || )  \\  || )   ( ||  /  \\ \\| (____/\\"<<endl;
cout<<"\\_______)|/    )_)|/     \\||_/    \\/(_______/"<<endl<<endl;
SetCursorPosition(46 , 0);
cout<<"       ---_ ......._-_--."<<endl;
SetCursorPosition(46 , 1);
cout<<"      (|\\ /      / /| \\  \\"<<endl;
SetCursorPosition(46 , 2);
cout<<"      /  /     .'  -=-'   `."<<endl;
SetCursorPosition(46 , 3);
cout<<"     /  /    .'             )"<<endl;
SetCursorPosition(46 , 4);
cout<<"   _/  /   .'        _.)   /"<<endl;
SetCursorPosition(46 , 5);
cout<<"  / o   o        _.-' /  .'"<<endl;
SetCursorPosition(46 , 6);
cout<<"  \\          _.-'    / .'*|"<<endl;
SetCursorPosition(46 , 7);
cout<<"   \\______.-'//    .'.' \\*|"<<endl;
SetCursorPosition(46 , 8);
cout<<"    \\|  \\ | //   .'.' _ |*|"<<endl;
SetCursorPosition(46 , 9);
cout<<"     `   \\|//  .'.'_ _ _|*|"<<endl;
SetCursorPosition(46 , 10);
cout<<"      .  .// .'.' | _ _ \\*|"<<endl;
SetCursorPosition(46 , 11);
cout<<"      \\`-|\\_/ /    \\ _ _ \\*\\"<<endl;
SetCursorPosition(46 , 12);
cout<<"       `/'\\__/      \\ _ _ \\*\\"<<endl;
SetCursorPosition(46 , 13);
cout<<"      /^|            \\ _ _ \*"<<endl;
SetCursorPosition(46 , 14);
cout<<"     '  `             \\ _ _ \\      "<<endl;
SetCursorPosition(46 , 15);
cout<<"                       \\_"<<endl;
SetCursorPosition(45 , 1);
SetColor(14);
cout<<"v3.2";
SetColor(10);
SetCursorPosition(30 , 9);
cout<<"High Score : "<<high_score;
SetCursorPosition(30 , 10);
cout<<"Difficulty : ";
    if(difficulty==150)cout<<"EASY";
    if(difficulty==100)cout<<"NORMAL";
    if(difficulty==50)cout<<"HARD";
int pos=1;
char choice;
int enter;
SetColor(14);
SetCursorPosition(0 , 9);
cout<<"-Start"<<endl;
cout<<"-Select Difficulty"<<endl;
cout<<"-Controls"<<endl;
cout<<"-Exit";
SetCursorPosition(6 , 9);
cout<<" <";

while(true){
    choice=getch();
    enter=choice;
    if(choice=='s' || choice=='S'){
            if(pos==1){
                SetCursorPosition(6 , 9);
                cout<<"  ";
                SetCursorPosition(18 , 10);
                cout<<" <";
                pos=2;
            }
            else if(pos==2){
                SetCursorPosition(18 , 10);
                cout<<"  ";
                SetCursorPosition(9 , 11);
                cout<<" <";
                pos=3;
            }
            else if(pos==3){
                SetCursorPosition(9 , 11);
                cout<<"  ";
                SetCursorPosition(5 , 12);
                cout<<" <";
                pos=4;
            }
            else if(pos==4){
                SetCursorPosition(5,12);
                cout<<"  ";
                SetCursorPosition(6,9);
                cout<<" <";
                pos=1;
            }


    }
    else if(choice=='w' || choice=='W'){
                if(pos==1){
                SetCursorPosition(6 , 9);
                cout<<"  ";
                SetCursorPosition(5,12);
                cout<<" <";
                pos=4;
            }
            else if(pos==2){
                SetCursorPosition(18 , 10);
                cout<<"  ";
                SetCursorPosition(6 , 9);
                cout<<" <";
                pos=1;
            }
            else if(pos==3){
                SetCursorPosition(9 , 11);
                cout<<"  ";
                SetCursorPosition(18 , 10);
                cout<<" <";
                pos=2;
            }
            else if(pos==4){
                SetCursorPosition(5,12);
                cout<<"  ";
                SetCursorPosition(9,11);
                cout<<" <";
                pos=3;
            }


    }
    else if(enter==13) {
        if(pos==1){
            system("cls");
            return;
        }
        else if(pos==4){
            leave=1;
            return;
        }
        else if(pos==2){
            Menu2();
            pos=1;
        }
        else if(pos==3){
            ControlsPage();
            pos=1;
        }


    }
}
}


void Pause(){
    char resume;
    SetColor(14);
    SetCursorPosition(66,6);
    cout<<"                                               ";
    SetCursorPosition(66,2);
    cout<<"                                                 ";
    SetCursorPosition(66,4);
    cout<<"                                                ";
    SetCursorPosition(66,5);
    cout<<" _______  _______           _______  _______  ______  ";
    SetCursorPosition(66,6);
    cout<<"(  ____ )(  ___  )|\\     /|(  ____ \\(  ____ \\(  __  \\";
    SetCursorPosition(66,7);
    cout<<"| (    )|| (   ) || )   ( || (    \\/| (    \\/| (  \\  )";
    SetCursorPosition(66,8);
    cout<<"| (____)|| (___) || |   | || (_____ | (__    | |   ) |";
    SetCursorPosition(66,9);
    cout<<"|  _____)|  ___  || |   | |(_____  )|  __)   | |   | |";
    SetCursorPosition(66,10);
    cout<<"| (      | (   ) || |   | |      ) || (      | |   ) |";
    SetCursorPosition(66,11);
    cout<<"| )      | )   ( || (___) |/\\____) || (____/\\| (__/  )";
    SetCursorPosition(66,12);
    cout<<"|/       |/     \\|(_______)\\_______)(_______/(______/ ";
    while(true){
        resume=getch();
        if(resume=='P' || resume=='p'){
            SetCursorPosition(66,5);
            cout<<"                                                    ";
            SetCursorPosition(66,6);
            cout<<"                                                     ";
            SetCursorPosition(66,7);
            cout<<"                                                      ";
            SetCursorPosition(66,8);
            cout<<"                                                      ";
            SetCursorPosition(66,9);
            cout<<"                                                      ";
            SetCursorPosition(66,10);
            cout<<"                                                      ";
            SetCursorPosition(66,11);
            cout<<"                                                      ";
            SetCursorPosition(66,12);
            cout<<"                                                      ";
            SetColor(14);
            SetCursorPosition(68 , 2);
            cout<<"SCORE : "<<score;
            SetCursorPosition(68 , 4);
            cout<<"HIGHEST SCORE : "<<high_score;
            SetCursorPosition(68 , 6);
            cout<<"DIFFICULTY : ";
            if(difficulty==150)cout<<"EASY";
            if(difficulty==100)cout<<"NORMAL";
            if(difficulty==50)cout<<"HARD";
            break;
        }

    }

}


void GameOver(){
    char x;
    SetColor(12);
    SetCursorPosition(66,6);
    cout<<"                                                     ";
    SetCursorPosition(66,2);
    cout<<"                                                     ";
    SetCursorPosition(66,4);
    cout<<"                                                      ";
    SetCursorPosition(74,0);
    cout<<" _______  _______  _______  _______    "<<endl;
    SetCursorPosition(74,1);
    cout<<"(  ____ \\(  ___  )(       )(  ____ \\  "<<endl;
    SetCursorPosition(74,2);
    cout<<"| (    \\/| (   ) || () () || (    \\/  "<<endl;
    SetCursorPosition(74,3);
    cout<<"| |      | (___) || || || || (__      "<<endl;
    SetCursorPosition(74,4);
    cout<<"| | ____ |  ___  || |(_)| ||  __)     "<<endl;
    SetCursorPosition(74,5);
    cout<<"| | \\_  )| (   ) || |   | || (         "<<endl;
    SetCursorPosition(74,6);
    cout<<"| (___) || )   ( || )   ( || (____/\\  "<<endl;
    SetCursorPosition(74,7);
    cout<<"(_______)|/     \\||/     \\|(_______/  "<<endl;
    SetCursorPosition(74,8);
    cout<<" _______           _______  _______ "<<endl;
    SetCursorPosition(74,9);
    cout<<"(  ___  )|\\     /|(  ____ \\(  ____ )"<<endl;
    SetCursorPosition(74,10);
    cout<<"| (   ) || )   ( || (    \\/| (    )|"<<endl;
    SetCursorPosition(74,11);
    cout<<"| |   | || |   | || (__    | (____)|"<<endl;
    SetCursorPosition(74,12);
    cout<<"| |   | |( (   ) )|  __)   |     __)"<<endl;
    SetCursorPosition(74,13);
    cout<<"| |   | | \\ \\_/ / | (      | (\\ ( "<<endl;
    SetCursorPosition(74,14);
    cout<<"| (___) |  \\   /  | (____/\\| ) \\ \\__"<<endl;
    SetCursorPosition(74,15);
    cout<<"(_______)   \\_/   (_______/|/   \\__/"<<endl;
    SetCursorPosition(107,25);
    cout<<"X";
    SetColor(14);
    SetCursorPosition(74,17);
    cout<<"            High Score : ";
    if(score>high_score)cout<<score;
    else cout<<high_score;
    SetCursorPosition(74,18);
    cout<<"            Score : "<<score;
    SetCursorPosition(74,19);
    cout<<"            Press any key";
    restart=true;
    x=getch();
    system("cls");
}

void CheckHighScore(){
    if(inc){
        ofstream write;
        write.open("HighestScore.txt");
        write<<score;
        write.close();
    }
}



int main()
{
    int food_color;
    while(true){
    //SetWindow(150 , 40);
    ifstream read;
    read.open("HighestScore.txt");
    read>>high_score;
    read.close();
    restart=false;
    turns_count=0;
    tail=make_pair(1,1);
    head=make_pair(1,2);
    turns.clear();
    stop=0;
    skip=0;
    eaten=0;
    leave=0;
    dir_of_head='d';
    dir_of_tail='d';
    dir='d';
    high_score=max(high_score,score);
    score=0;
    Menu1();
    if(leave==1){
            ofstream write;
            write.open("HighestScore.txt");
            write<<high_score;
            write.close();
            return 0;
    }
    srand((int)time(0));
    while(true){
        restart=false;
        food.first=rand()%height;
        food.second=rand()%width;
        if(food.first==0)food.first++;
        if(food.second==0)food.second++;
        if(food.first==height-1)food.first--;
        if(food.second==width-1)food.second--;
        if(plane[food.first][food.second]!=char(219) && plane[food.first][food.second]!=char(178))break;
    }
    SetPlane();
    DrawPlane();
    SetCursorPosition(68 , 2);
    SetColor(14);
    cout<<"SCORE : "<<score;
    SetCursorPosition(68 , 4);
    cout<<"HIGHEST SCORE : "<<high_score;
    SetCursorPosition(68 , 6);
    cout<<"DIFFICULTY : ";
    if(difficulty==150)cout<<"EASY";
    if(difficulty==100)cout<<"NORMAL";
    if(difficulty==50)cout<<"HARD";
    SetColor(13);
            SetCursorPosition(66,20);
            cout<<"                __    __    __    __"<<endl;
            SetCursorPosition(66,21);
            cout<<"               /  \\  /  \\  /  \\  /  \\"<<endl;
            SetCursorPosition(66,22);
            cout<<"______________/  __\\/  __\\/  __\\/  __\\_______________"<<endl;
            SetCursorPosition(66,23);
            cout<<"_____________/  /__/  /__/  /__/  /__________________"<<endl;
            SetCursorPosition(66,24);
            cout<<"             | / \\   / \\   / \\   / \\  \\____"<<endl;
            SetCursorPosition(66,25);
            cout<<"             |/   \\_/   \\_/   \\_/   \\    o \\"<<endl;
            SetCursorPosition(66,26);
            cout<<"                                     \\_____/--<"<<endl;

    SetCursorPosition(100 , 0);
    char dir2='d';
    while(!restart){
        Sleep(difficulty);
        EditPlane();
        if(eaten==1){
            score+=10;
            SetCursorPosition(68 , 2);
            SetColor(14);
            cout<<"SCORE : "<<score;
            if(score>high_score)
                CheckHighScore();
            while(true){
                food.first=rand()%height;
                food.second=rand()%width;
                if(food.first==0)food.first++;
                if(food.second==0)food.second++;
                if(food.first==height-1)food.first--;
                if(food.second==width-1)food.second--;
                if(plane[food.first][food.second]!=char(219) && plane[food.first][food.second]!=char(178))
                    break;
            }
            eaten=0;
        }
        SetCursorPosition(food.second , food.first);
        while(true){
            food_color=rand()%20;
            if(food_color!=0)break;
        }
        SetColor(food_color);
        cout<<'&';
        if(score>high_score){
                    if(!inc){
                        inc=1;
                    }
                    SetCursorPosition(68 , 2);
                    cout<<"SCORE : "<<score;
            }

        plane[food.first][food.second]='&';
        SetCursorPosition(100 , 0);
        if(stop){
            GameOver();
            inc=0;
            continue;
        }
        if(_kbhit()){
                dir=_getch();
                if(dir!='a' && dir!='A' && dir!='s' && dir!='S' && dir!='d' && dir!='D' && dir!='w' && dir!='W' && dir!='p' && dir!='P')
                        dir=dir2;
                else if(dir=='A' && dir=='S'  && dir=='D'  && dir=='W' && dir=='P')
                        dir+='a'-'A';
        }
        if(dir=='p'){
            Pause();
            dir=dir2;
            continue;
        }
        else if(dir=='d' && dir2=='a'){
                dir=dir2;
                continue;
        }
        else if(dir=='a' && dir2=='d'){
                dir=dir2;
                continue;
        }
        else if(dir=='w' && dir2=='s'){
                dir=dir2;
                continue;
        }
        else if(dir=='s' && dir2=='w'){
                dir=dir2;
                continue;
        }
        dir2=dir;
        TurnSnake();
    }


    }

    return 0;
}
