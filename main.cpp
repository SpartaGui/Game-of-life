#include <iostream>
#include <chrono>
#include <windows.h>
using namespace std;

const int tela_y = 100;
const int tela_x = 100;
char tela[tela_y][tela_x];
char tela2[tela_y][tela_x];

string coisos = " #";

void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

bool pode_desenhar(int x, int y){
    if(x >= 0 && x < tela_x-1 && y >= 0 && y < tela_y-1)
        return true;
    return false;
}

int pegar_vizinhos(int x, int y, char vizinho){
    int contagem = 0;
    for(int i = -1;i<2;i++){
        for(int j = -1;j<2;j++){
            if(i+y != y || j+x != x){
                if(pode_desenhar(x+j, y+i)){
                //tela[i+y][j+x] = '&';
                if(tela[i+y][j+x] == vizinho)
                    contagem++;
            }
            }
        }
    }
    return contagem;
}

void reset(){
    for(int i = 0;i<tela_y;i++){
        for(int j = 0;j<tela_x;j++){
            tela[i][j] = coisos[rand()%coisos.length()];
        }
    }
}

int main(){
    srand(time(NULL));
    for(int i = 0;i<tela_y;i++){
        for(int j = 0;j<tela_x;j++){
            tela[i][j] = coisos[rand()%coisos.length()];
        }
    }
    for(int i = 0;i<tela_y;i++){
        for(int j = 0;j<tela_x;j++){
            tela2[i][j] = ' ';
        }
    }
    int frames = 0;
    string tela_buffer = "";
    gotoxy(0, 0);
    for(int i = 0;i<tela_y;i++){
        for(int j = 0;j<tela_x;j++){
            tela_buffer += tela[i][j];
        }
        tela_buffer += "\n";
    }
    cout<<tela_buffer;

    system("pause");
    while(true){
    frames++;
    Sleep(10);
    //logica
    for(int i = 0;i<tela_y;i++){
        for(int j = 0;j<tela_x;j++){
            switch(tela[i][j]){
        case '#':
            tela2[i][j] = '#';
            if(pegar_vizinhos(j, i, '#') >= 4 || pegar_vizinhos(j, i, '#') <= 1)
                tela2[i][j] = ' ';
            break;
        case ' ':
            tela2[i][j] = ' ';
            if(pegar_vizinhos(j, i, '#') == 3){
                tela2[i][j] = '#';
            }
            break;
            }
        }
    }

    //renderizar
    string tela_buffer = "";
    gotoxy(0, 0);
    for(int i = 0;i<tela_y;i++){
        for(int j = 0;j<tela_x;j++){
            tela_buffer += tela[i][j];
        }
        tela_buffer += "\n";
    }
    cout<<tela_buffer;

    cout<<frames<<endl;
    for(int i = 0;i<tela_y;i++){
        for(int j = 0;j<tela_x;j++){
            tela[i][j] = tela2[i][j];
        }
    }

    }
    return 0;
}
