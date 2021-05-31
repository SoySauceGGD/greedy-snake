#include<iostream>
#include<queue>
#include<set>
#include<random>
#include<ctime>

using namespace std;

const int N = 30;
const char FOOD = '@';
const char SNAKE_HEAD = '+';
const char SNAKE_BODY = '*';

typedef pair<int, int> pos; // x y coordinates

class Screen{
    private:
        char Map[N][N];

    public:
        void init(){
            for(int i=0; i<N; i++){
                Map[0][i] = '#';
                Map[i][0] = '#';
                Map[N-1][i] = '#';
                Map[i][N-1] = '#';
            }
            for(int i=1; i<N-1; i++){
                for(int j=1; j<N-1; j++)
                    Map[i][j] = ' ';
            }
        }

        void print(){
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++)
                    cout << Map[i][j] << " ";
                cout << "\n";
            }
        }

        void setXYC(int x, int y, char c){
            Map[x][y] = c;
        }
        void setXYC(pos p, char c){
            Map[p.first][p.second] = c;
        }

        char **getXYC(int x, int y){
            return (char**)Map[x][y];
        }

        char getXYChar(int x, int y){
            return Map[x][y];
        }
        char getXYChar(pos p){
            return Map[p.first][p.second];
        }
};

class RamdomGen{
    private:
        random_device rd;

    public:
        pos gen(){
            mt19937 gen(rd() + time(NULL));
            uniform_int_distribution<int> uid(1, N-2);
            return make_pair(uid(gen), uid(gen));
        }

};

class Snake{
    private:
        queue<pair<char**, pos>> snake;
        set<pos> snake_set;
        Screen map;
        RamdomGen ramdom;
        char dire;
        pos food_pos;

    public:
        Snake(){
            map.init();

            int x = N / 2, y = N / 2;
            for(int i = 0; i < 4; i++){
                snake.push(make_pair(map.getXYC(x + i, y), make_pair(x + i, y)));
                snake_set.insert(make_pair(x + i, y));
                map.setXYC(x + i, y, SNAKE_BODY);
            }
            map.setXYC(x, y, SNAKE_HEAD);
            dire = 'W';

            food_pos = GenFood();
            map.print();
        }

        bool oper(){/*
            move();
            if(!isAlive()){
                return false;
            }
            map.print();
        */}

        void move1(){
            char in;
            start:
            cin >> in; in = toupper(in);
            if(in != dire && (in == 'W' || in == 'S' || in == 'A' || in == 'D'))
                move2(in);
            else
                goto start;
        }

        void move2(char c){
            int x = snake.front().second.first,
                y = snake.front().second.second;

            switch(c){
                case 'W':
                    if(map.getXYChar(x - 1, y) != FOOD){
                        snake_set.erase(snake.back().second);
                        snake.pop();
                    }
                    //snake.front().second;
                    break;
            }
        }

        bool isAlive(){

        }

        pos GenFood(){
            pos tmp = ramdom.gen();
            auto it = snake_set.find(tmp);
            while(it != snake_set.end()){
                tmp = ramdom.gen();
            }
            map.setXYC(tmp, FOOD);
            return tmp;
        }
};

int main(){
    Snake snake;

    while(snake.oper()){
    }
    system("PAUSE");
}