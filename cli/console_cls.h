#include "syntices_cls.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class console_cls
{
private:
    string user_command;
    syntices_cls* syntax_processor;

public:
    console_cls(memory_cls*, file_tree_cls*);
    ~console_cls();

    // defined
    void main_screen();
    void sys_msg(string, int);
    string get_sys_msg_sym(int);
    vector<string> to_command_args(string);    

    // undefined
};
vector<string> console_cls::to_command_args(string args){
    char delimiter = ' ';
    vector<std::string> parts;
    size_t start = 0, end = 0;

    while ((end = args.find(delimiter, start)) != std::string::npos) {
        std::string part = args.substr(start, end - start);
        parts.push_back(part);
        start = end + 1;
    }

    std::string part = args.substr(start);
    parts.push_back(part);

    return parts;
}

void console_cls::main_screen(){
    sys_msg("Type 'help' for a list of available commands.", 0);
    while(true){
        cout << "\n\t" << syntax_processor->get_curr_dir_name() << "> "; getline(cin, user_command);
        try{
            syntax_processor->process_command(to_command_args(user_command));
        }
        catch(system_error_cls &e)
        {
            if(e.get_error_code() == -1) {
                return;
            }
        }
    }
}

string console_cls::get_sys_msg_sym(int message_type){
    string symbols[] = {"?", "!", "-"};
    return symbols[message_type];
}

void console_cls::sys_msg(string message, int message_type){    
    cout << get_sys_msg_sym(message_type) << '\t' << message << endl;
    return;
}

console_cls::console_cls(memory_cls* mem, file_tree_cls* tr)
{
    syntax_processor = new syntices_cls(mem, tr);
}

console_cls::~console_cls()
{
}
