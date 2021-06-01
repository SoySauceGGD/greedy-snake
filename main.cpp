#include<iostream>
#include<queue>
#include<set>
#include<random>
#include<ctime>
#include<windows.h>
#include<conio.h>

using namespace std;

const int N = 30;
const char WALL = '#';
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
                Map[0][i] = WALL;
                Map[i][0] = WALL;
                Map[N-1][i] = WALL;
                Map[i][N-1] = WALL;
            }
            for(int i=1; i<N-1; i++){
                for(int j=1; j<N-1; j++)
                    Map[i][j] = ' ';
            }
        }

        void print(){
            system("cls");
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++)
                    cout << Map[i][j] << " ";
                cout << "\n";
            }
            cout << flush;
        }

        void setXYC(int x, int y, char c){
            Map[x][y] = c;
        }
        void setXYC(pos p, char c){
            Map[p.first][p.second] = c;
        }

        char getXYChar(pos p){
            return Map[p.first][p.second];
        }
};

class Snake{
    private:
        queue<pos> snake;
        set<pos> snake_set;
        Screen map;
        random_device rd;
        char dire;
        pos food_pos;

    public:
        Snake(){
            map.init();

            int x = N / 2, y = N / 2;
            for(int i = 0; i < 4; i++){
                snake.push(make_pair(x + i, y));
                snake_set.insert(make_pair(x + i, y));
                map.setXYC(x + i, y, SNAKE_BODY);
            }
            map.setXYC(snake.back(), SNAKE_HEAD);
            dire = 'W';
            food_pos = GenFood();
            map.print();
        }

        bool oper(){
            if(!move()){
                return false;
            }
            map.print();
            return true;
        }

        bool move(){
            char in = getDire();
            pos old_head = snake.back(),
                new_head = snake.back();
            switch(in){
                case 'W':   case 'S':
                    dire = (in == 'W' ? 'S' : 'W');
                    new_head.first += (in == 'W' ? -1 : 1);
                    break;

                case 'A':   case 'D':
                    dire = (in == 'A' ? 'D' : 'A');
                    new_head.second += (in == 'A' ? -1 : 1);
                    break;
            }
            if(!isAlive(new_head))
                return false;

            if(new_head != food_pos){
                map.setXYC(snake.front(), ' ');
                snake_set.erase(snake.front());
                snake.pop();
            }else{
                GenFood();
            }

            snake.push(new_head);
            snake_set.insert(new_head);
            map.setXYC(old_head, SNAKE_BODY);
            map.setXYC(new_head, SNAKE_HEAD);
            return true;
        }

        char getDire(){
            char in;
            start:
            if(kbhit() != 0){
                in = toupper(_getch());
            }
            if(in != dire && (in == 'W' || in == 'S' || in == 'A' || in == 'D'))
                return in;
            else
                goto start;
        }

        bool isAlive(pos head){
            return map.getXYChar(head) != SNAKE_BODY && map.getXYChar(head) != WALL;
        }

        pos GenFood(){
            pos tmp = gen();
            auto it = snake_set.find(tmp);
            while(it != snake_set.end()){
                tmp = gen();
            }
            map.setXYC(tmp, FOOD);
            food_pos = tmp;
            return tmp;
        }
        
        pos gen(){
            mt19937 generator(rd() + time(NULL));
            uniform_int_distribution<> uid(1, N-2);
            return make_pair(uid(generator), uid(generator));
        }
};

int main(){
    ios::sync_with_stdio(false);
    system("mode con cols=62 lines=31");
    Snake snake;
    while(snake.oper());
    system("cls");
    cout << "You Are Dead! ;(" << endl;
    system("PAUSE");
}