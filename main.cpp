#include <iostream>
#include <getopt.h>
using namespace std;

int h_flag = 0;
int v_flag = 0;
int f_flag = 0;
int s_flag = 0;
int o_flag = 0;

int a_flag = 1;

int first = 0;
int second = 0;
char op;

void help();
void version();
void setFirst(char* value);
void setSecond(char* value);
void error(char c);


int main(int args, char *argv[]) {
//    setlocale(LC_ALL, NULL);

    char sOpt[] = "hvf:s:o:";
    static struct option lOpt[] = {
            {"help", no_argument, NULL, 'h'},
            {"version", no_argument, NULL, 'v'},
            {"first", required_argument, NULL, 'f'},
            {"second", required_argument, NULL, 's'},
            {"operator", required_argument, NULL, 'o'},
            {NULL, 0, NULL, 0}

    };

    int longindex = -1;


    char c;
    while((c = getopt_long(args, argv, sOpt, lOpt, &longindex)) != -1){
        switch(c){
            case 'h':
                help();
                break;
            case 'v':
                version();
                break;
            case 'f':
                setFirst(optarg);
                break;
            case 's':
                setSecond(optarg);
                break;
            case 'o':
                if(o_flag != 0) continue;
                op = optarg[0];
                o_flag = 1;
                break;
            case '?':
            default:
                error(c);
                break;
        }
        longindex = -1;
    }

    if(f_flag && s_flag && o_flag){
        double ans;
        switch (op) {
            case '+':
                ans = first + second;
                break;
            case '-':
                ans = first - second;
                break;
            case '*':
                ans = first * second;
                break;
            case '/':
                ans = first / second;
                break;
            case '|':
                ans = first | second;
                break;
            case '&':
                ans = first & second;
                break;
            case '%':
                ans = first % second;
                break;
            case '^':
                ans = first ^ second;
                break;
            default:
                a_flag = 0;
                break;

        }
        if(a_flag) {
            cout << first << " " << op << " " << second << " = " << ans << endl;
        }else{
            cout << "A cant calculate your expression because:" << endl;
            cout << "Unknown operation " << op;
        }
    }else if(f_flag || s_flag || o_flag){e
        cout << "A cant calculate your expression because:" << endl;
        if(!f_flag){
            cout << "Variable 'first' is not specified" << endl;
        }
        if(!s_flag){
            cout << "Variable 'second' is not specified" << endl;
        }
        if(!o_flag){
            cout << "No operand specified" << endl;
        }

    }
    return 0;
}


void help(){
    if(h_flag != 0) return;
    cout << " This is help message to mini calculator: " << endl;
    cout << " I can do something like: -f10 --second=5 -o+ out: 10 + 5 = 15" << endl;
    cout << " I can perform operations such as: + - * /(without fractional part) | & % ^" << endl;
    cout << " in:  -f10 --second=5 +" << endl;
    cout << " out: 10 + 5 = 15" << endl << endl;
    cout << " --help              -h         | to get this message" << endl;
    cout << " --version           -v         | program version" << endl;
    cout << " --first=[value]     -f[value]  | set first variable" << endl;
    cout << " --second=[value]    -s[value]  | set second variable" << endl;
    cout << " --operator=[value]  -o[value]  | set operator" << endl << endl;
    h_flag++;
}

void version(){
    if(v_flag != 0) return;
    cout << "mini calculator version 0.1" << endl;
    v_flag++;
}

void setFirst(char* value){
    if(f_flag != 0) return;
    first = atoi(value);
    f_flag++;
}

void setSecond(char* value){
    if(s_flag != 0) return;
    second = atoi(value);
    s_flag++;
}

void error(char c){
    cout << "Invalid argument " << c << endl;
}