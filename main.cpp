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

        /*char getXYChar(int x, int y){
            return Map[x][y];
        }
        char getXYChar(pos p){
            return Map[p.first][p.second];
        }*/
};

class RamdomGen{
    private:
        random_device rd;

    public:
        pos gen(){
            mt19937 generator(rd() + time(NULL));
            uniform_int_distribution<int> uid(1, N-2);
            return make_pair(uid(generator), uid(generator));
        }

};

class Snake{
    private:
        queue<pos> snake;
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
                snake.push(make_pair(x + i, y));
                snake_set.insert(make_pair(x + i, y));
                map.setXYC(x + i, y, SNAKE_BODY);
            }
            map.setXYC(x + 3, y, SNAKE_HEAD);
            dire = 'W';

            food_pos = GenFood();
            map.print();
        }

        bool oper(){
            move1();
            /*if(!isAlive()){
                return false;
            }*/
            map.print();
            return true;
        }

        void move1(){
            char in;
            start:
            cin >> in; in = toupper(in);
            if(in != dire && (in == 'W' || in == 'S' || in == 'A' || in == 'D'))
                move2(in);
            else
                goto start;
        }

        void move2(char in){
            pos old_head = snake.back();
            pos new_head = old_head;
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
            food_pos = tmp;
            return tmp;
        }
};

int main(){
    Snake snake;
    while(snake.oper());

    system("PAUSE");
}