#include<iostream>

using namespace std;

const int N = 30;

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
};

int main(){
    Screen sc;
    sc.init();
    sc.print();
}