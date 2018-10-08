#include<iostream>
#include<math.h>
#include<string>
#include<stack>
using namespace std;

// 4031.py
// east: 0
// north: 1
// west: 2
// south: 3
// positive_dir = east and north

class Ant{
// private:
public:
    int pos_x;
    int pos_y;
    int ori;

    Ant(){
        this -> pos_x = 0;
        this -> pos_y = 0;
        this -> ori = 0;
    }

    int get_cur_dis(){
        return abs(this -> pos_x) + abs(this -> pos_y);
    }

    void turn_right(){
        this->ori = (this -> ori - 1) % 4;
    }

    void turn_left(){
        this->ori = (this -> ori + 1) % 4;
    }

    void go_forward(){
        switch(this->ori){
            case 0: (this->pos_x)++; break;
            case 1: (this->pos_y)++; break;
            case 2: (this->pos_x)--; break;
            case 3: (this->pos_y)--; break;
            default: cerr << "error pos";
        }
    }


};

struct Pos{
    int x;
    int y;
};

int main(){
    Ant * a = new Ant();
    string S[50];
    int n = 0;
    cin >> n;
    cout << "n = " << n << endl;
    string temp_str_n;
    int temp_n = 0;
    int curr_len = 0;
    int max_num_ins = 0;
    for (int i = 0; i < n; i++){
        getline(cin, temp_str_n, ' ');
        temp_n = stoi(temp_str_n);
        if(temp_n > max_num_ins){
            max_num_ins = temp_n;
        }
        S[curr_len] = (char)(temp_n+48);
        curr_len++;
        // cout << "temp_n = " << temp_n << endl;
        for (int  j = 0; j < temp_n - 1; j++)
        {
            getline(cin, S[curr_len], ' ');
            curr_len++;
        }
        getline(cin, S[curr_len]);
        curr_len++;
    }

    // int n = 5;
    // int max_num_ins = 6;

    const int row = n;
    const int col = max_num_ins;

    string Mat[row][col];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            Mat[i][j] = "";
        }
    }
    // for(int i = 0; i < )
    int input_col_num = 0;
    int input_row_NUM = -1;
    for(int k = 0; k < curr_len; k++){
        // cout << S[k] << '\t';
        char m = (char)S[k][0];

//        int input_col_Num = -1;
        if(m >= '0' && m <= '9'){
            input_row_NUM++;
            input_col_num = 0;
            continue;
        }

        Mat[input_row_NUM][input_col_num] = S[k];
        input_col_num++;
    }

    Pos * pos;
    pos->x = 0;
    pos->y = -1;
    stack<Pos *> stk;
    int max_dis = 0;
//    for(int i = 0; i < input_row_NUM; i++){
    do{
//        Pos * temp_pos = pos;
        if(pos->y + 1 >= input_col_num || Mat[pos->x][pos->y + 1].empty()){
            if(stk.empty()){
                break;
            }
            pos = stk.top();
            stk.pop();

            continue;
        }
        else{
            pos -> y += 1;
            if(Mat[pos->x][pos->y][0] == 'F'){
                Pos * temp_pos = pos;
                stk.push(temp_pos);
//                p
                pos->x = (int)Mat[pos->x][pos->y][1] - 1;
                pos->y = -1;
            }
            else{
                if(Mat[pos->x][pos->y][0] == 'G'){
                    a->go_forward();
                }
                else if(Mat[pos->x][pos->y][0] == 'L'){
                    a->turn_left();
                }
                else if(Mat[pos->x][pos->y][0] == 'R'){
                    a->turn_right();
                }
            }
        }
        cout << a->get_cur_dis() << "\t";
    }while(true);
}
