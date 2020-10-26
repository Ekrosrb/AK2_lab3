#include <iostream>
#include <cstring>
#include <getopt.h>
using namespace std;

int h_flag = 0;
int v_flag = 0;
int f_flag = 0;
int s_flag = 0;
int o_flag = 0;
int l_flag = 0;
int e_flag = 0;
int a_flag = 1;

int first = 0;
int second = 0;
char op;

void list(char* args);
void help();
void version();
void setFirst(char* value);
void setSecond(char* value);


int main(int args, char *argv[]) {

    char sOpt[] = "hvf:s:o:l:";
    static struct option lOpt[] = {
            {"help", no_argument, nullptr, 'h'},
            {"version", no_argument, nullptr, 'v'},
            {"first", required_argument, nullptr, 'f'},
            {"second", required_argument, nullptr, 's'},
            {"operator", required_argument, nullptr, 'o'},
            {"list", required_argument, nullptr, 'l'},
            {nullptr, 0, nullptr, 0}

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
                if(o_flag) continue;
                if(strlen(optarg) > 1){
                    cout << "Parameters are incorrect: " << optarg << endl;
                    return 0;
                }
                op = optarg[0];
                o_flag = 1;
                break;
            case 'l':
                list(optarg);
                break;
            case '?':
            default:
                cout << "Invalid argument!" << c << endl;
                e_flag = 1;
                break;
        }
        longindex = -1;
    }
    if(e_flag) return 0;

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
            cout << "Unknown operation " << op << endl;
            return 0;
        }
    }else if(f_flag || s_flag || o_flag){
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
        return 0;

    }
    return 0;
}

void list(char* args){
    if(l_flag) return;
    l_flag = 1;
    int size = strlen(args);
    int c = 0;
    string buffer = "";
    for(int i = 0; i < size; i++){
        if(args[i] != ','){
            buffer += args[i];
        }else{
            switch (c) {
                case 0:
                    first = atoi(buffer.c_str());
                    f_flag = 1;
                    break;
                case 1:
                    second = atoi(buffer.c_str());
                    s_flag = 1;
                    break;
                default:
                    cout << "Parameters are incorrect: " << optarg << endl;
                    f_flag = 1;
                    break;
            }
            c++;
            buffer = "";
        }
    }
    if(buffer.length() > 1 ){
        cout << "Invalid operator: " << buffer << endl;
        f_flag = 1;
    }
    o_flag = 1;
    op = buffer.c_str()[0];

}

void help(){
    if(h_flag != 0) return;
    cout << " This is help message to mini calculator: "                                    << endl;
    cout << " I can do something like:"                                                     << endl;
    cout << R"( in:  -f10 --second=5 -o"+"  or  -list=10,5,"+")"                            << endl;
    cout << " out: 10 + 5 = 15"                                                     << endl << endl;
    cout << R"( I can perform operations such as: + - * /(without fractional part) "|" "&" % ^)"<< endl;
    cout << " For correct operation, operators & and | MUST be specified in double quotes!" << endl;
    cout << " --help              -h            | to get this message"                      << endl;
    cout << " --version           -v            | program version"                          << endl;
    cout << " --first=<value>     -f<value>     | set first variable"                       << endl;
    cout << " --second=<value>    -s<value>     | set second variable"                      << endl;
    cout << " --operator=<value>  -o<value>     | set operator"                             << endl;
    cout << " --list=<f>,<s>,<o>  -l<f>,<s>,<o> | set all values, but with this"            << endl;
    cout << "                                     command, -f -s -o have no effect" << endl << endl;
    h_flag++;
}

void version(){
    if(v_flag != 0) return;
    cout << "mini calculator version 0.2" << endl;
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