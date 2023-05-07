#include "syntices_cls.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

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
    void main_screen_script_mode(string);
    void sys_msg(string, int);
    string get_sys_msg_sym(int);

    // undefined
};

void console_cls::main_screen(){
    sys_msg("Type 'help' for a list of available commands.", 0);
    while(true){
        cout << "\n\t" << syntax_processor->get_curr_dir_name() << "> "; getline(cin, user_command);
        try{
            syntax_processor->process_command(syntax_processor->to_command_args(user_command));
        }
        catch(system_error_cls &e)
        {
            if(e.get_error_code() == -1) {
                return;
            }
        }
    }
}

void console_cls::main_screen_script_mode(string script_path){
    ifstream script_file(script_path);

    if (script_file.is_open()) { // check if file is open
        string command;
        int read = 0;
        while (getline(script_file, command)) { // read file line by line
            try{
                if(command == "#fscript" && read == 0) read++;
                if(read == 0) throw system_error_cls(3);
            } catch(system_error_cls e){
                e.display();
                return;
            }
            cout << "\n\t" << syntax_processor->get_curr_dir_name() << "> " << command << endl;
            try{
                syntax_processor->process_command(syntax_processor->to_command_args(command));
            }
            catch(system_error_cls &e)
            {
                if(e.get_error_code() == -1) {
                    return;
                }
            }
            
        }
        script_file.close(); // close file
        return;
    }
    else {
        std::cout << "Unable to open file. Invalid format." << std::endl;
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
