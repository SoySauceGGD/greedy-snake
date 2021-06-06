#include<iostream>
#include<queue>
#include<set>
#include<random>
#include<windows.h>
#include<conio.h>

using namespace std;

const int N = 30;
const char WALL = '#';
const char FOOD = '+';
const char SNAKE_HEAD = '@';
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
        Screen screen;
        random_device rd;
        char dire;
        pos food_pos;
        int score;

    public:
        Snake(){
            screen.init();
            int x = N / 2, y = N / 2;
            for(int i = 0; i < 4; i++){
                snake.push(make_pair(x + i, y));
                snake_set.insert(make_pair(x + i, y));
                screen.setXYC(x + i, y, SNAKE_BODY);
            }
            screen.setXYC(snake.back(), SNAKE_HEAD);
            dire = 'S';
            food_pos = GenFood();
        }

        bool move(){
            if(kbhit() != 0){
                char tmp = toupper(getch());
                if(dire != revDirection(tmp) && revDirection(tmp) != ' ')
                    dire = tmp;
            }

            pos old_head = snake.back(),
                new_head = snake.back();
            switch(dire){
                case 'W':   case 'S':
                    new_head.first += (dire == 'W' ? -1 : 1);
                    break;

                case 'A':   case 'D':
                    new_head.second += (dire == 'A' ? -1 : 1);
                    break;
            }
            if(!isAlive(new_head))
                return false;

            if(new_head != food_pos){
                screen.setXYC(snake.front(), ' ');
                snake_set.erase(snake.front());
                snake.pop();
            }else{
                food_pos = GenFood();
                score++;
            }

            snake.push(new_head);
            snake_set.insert(new_head);
            screen.setXYC(old_head, SNAKE_BODY);
            screen.setXYC(new_head, SNAKE_HEAD);

            screen.print();
            cout << "  ! Press w/s/a/d to move\t! Score = " << score << endl;
            Sleep(250);
            return true;
        }

        char revDirection(char c){
            switch(c){
                case 'W': return 'S';
                case 'S': return 'W';
                case 'A': return 'D';
                case 'D': return 'A';
                default : return ' ';
            }
        }

        bool isAlive(pos head){
            return screen.getXYChar(head) != SNAKE_BODY && screen.getXYChar(head) != WALL;
        }

        pos GenFood(){
            pos tmp = gen();
            auto it = snake_set.find(tmp);
            while(it != snake_set.end()){
                tmp = gen();
                it = snake_set.find(tmp);
            }
            screen.setXYC(tmp, FOOD);
            return tmp;
        }
        pos gen(){
            mt19937 generator(rd());
            uniform_int_distribution<> uid(1, N-2);
            return make_pair(uid(generator), uid(generator));
        }
};

int main(){
    ios::sync_with_stdio(false);
    system("mode con cols=60 lines=34");
    Snake snake;
    while(snake.move());
    
    system("cls");
    cout << "You Are Dead! ;(" << endl;
    system("PAUSE");
}