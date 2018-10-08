#include<iostream>
#include<string>
#define INFINITY 65536
using namespace std;

int char_1st_appear_pos(string str, char chr){
    int ret = 9999;
    for(int i = 0; i < int(str.size()); i++){
        if(str[i] == chr){
            ret = i;
            break;
        }
    }
    return ret;
}

int get_char_num(string str, char chr){
    int ret = 0;
    for(int i = 0; i < int(str.size()); i++){
        if(str[i] == chr){
            ret++;
        }
    }
    return ret;
}

int main(){
    int time = 0;
//    bool judge = false;
    cin >> time;
    bool res[time];
    string str;
	for(int i = 0; i < time; i++){
        str = "";
//        cout << '\t' << str;
        cin >> str;
        bool judge = false;
        int pos_P = char_1st_appear_pos(str, 'P');
        int pos_T = char_1st_appear_pos(str, 'T');
        for(int j = 0; j < str.size(); j++){
            if(str[j] != 'P' && str[j] != 'A' && str[j] != 'T'){
                goto label1;
            }
        }

        if((get_char_num(str,'P') >= 2) || (get_char_num(str, 'T') >= 2)){
            judge = false;
        }
        else if((int(str.size()) - pos_T - 1) < pos_P){
            judge = false;
        }
        else{
            judge = true;
        }
        label1:
        res[i] = judge;

    }
    for(int i = 0; i < time; i++){
        if(res[i]){
            cout << "YES\n";
        }
        
        else{
            cout << "NO" << endl;
        }
    }
}