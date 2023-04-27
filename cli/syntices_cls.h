#include<iostream>
#include<vector>

// prerequisite system files
#include"../classes/file_cls.h"
#include"../classes/file_tree_cls.h"

using namespace std;

#define TOTAL_COMMANDS 14

class syntices_cls
{
private:
    memory_cls* memory;
    file_tree_cls* tree;
    directory_cls* current_dir;
    file_cls* open_file = NULL;

    string commands[14] = {
        "help",
        "create",
        "write", 
        "read", 
        "delete", 
        "mkdir", 
        "cd", 
        "move", 
        "movec", 
        "open", 
        "close", 
        "mmap",
        "quit",
        "memory",
    };

    string descriptions[20] = {
        "list all commands",
        "create a new file",
        "write data to a file", 
        "read data from a file", 
        "delete a file or directory", 
        "make a new directory", 
        "choose a directory to work from", 
        "move file into another directory", 
        "move content within a file", 
        "open a file", 
        "close a file being editied", 
        "show the entire memory map",
        "close the software",
        "show the memory data",
    };

    string syntices[20][14] = {
        {"help"},
        {"create", "f|d", "<../dir/name>"},
        {"write", "<filepath>", "a|o", "<data>"},
        {"read", "<filepath>", "f|l", "<if-l:start/length>"},
        {"delete", "<filepath>"},
        {"mkdir", "<dirpath>"},
        {"cd", "<dirpath>"},
        {"move", "<filepath>", "<../newdirpath>"},
        {"movec"},      // TBD
        {"open", "<filepath>"},
        {"close"},
        {"mmap"},
        {"quit"},
        {"memory"},
    };

public:
    syntices_cls(memory_cls*, file_tree_cls*);
    ~syntices_cls();

    void process_command(vector<string>);
    int find_command_by_name(string);
    void help();
    void shelp(string);
    string get_curr_dir_name();
    
    // void create_directory(string);
    // void create_file(string);
    // void add_to_directory(string);
    // void move(string);
    // void delete_file();
    // void delete_directory();
    // void change_directory(string);
    // void open_file(string);
    // void show_mem_map();
};

string syntices_cls::get_curr_dir_name(){
    return current_dir->get_dir_name();
}

void syntices_cls::process_command(vector<string> args){
    for (int cmd = 0; cmd < TOTAL_COMMANDS; cmd++)
    {
        if (args.at(0) == commands[cmd]){
            switch(cmd){
                case 0:
                    if(args.size() == 1) help();
                    else if(args.size() != 1) shelp(args.at(1));
                    break;
                case 1:
                    if(args.size() == 3){
                        bool successful;
                        if(args.at(1) == "f"){
                            string data;
                            cout << "\twrite something to the file: "; getline(cin, data);
                            tree->add_f(args.at(2), data);
                        }
                        else if(args.at(1) == "d"){
                            tree->add_d(args.at(2));
                        }
                    }
                    break;
                case 2:
                    if(args.size() == 4){
                        file_cls* tmp_file = tree->search_f(args.at(1));
                        if(args.at(2) == "o") memory->write_to_block(tmp_file->get_start_blk(), args.at(3));
                        else if(args.at(2) == "a"){
                            string old_data = memory->read_block(tmp_file->get_start_blk());
                            string new_data = old_data + args.at(3);
                            memory->write_to_block(tmp_file->get_start_blk(), new_data);
                        }
                        cout << endl;
                    }
                    break;
                case 3:
                    if(args.size() >= 3){
                        file_cls* tmp_file = tree->search_f(args.at(1));
                        if(args.at(2) == "f") cout << '\t' << memory->read_block(tmp_file->get_start_blk());
                        else if(args.at(2) == "l"){
                            vector<string> limits = tree->process_f_path(args.at(3));
                            cout << '\t' << memory->read_block(tmp_file->get_start_blk(), stoi(limits.at(0)), stoi(limits.at(1)));
                        }
                        cout << endl;
                    }
                    break;
                case 4:
                    if(args.size() == 2){
                        if(tree->delete_f(args.at(1))) cout << "\tdelete successful" << endl;
                        else throw system_error_cls(0);
                    }
                    break;
                case 5:
                    if(args.size() == 2){
                        directory_cls* _dir = new directory_cls(args.at(1));
                        current_dir->add_directory(_dir);
                        cout << "\tadded new directory" << endl;
                    }
                    break;
                case 6:
                    if(args.size() == 1) current_dir = tree->get_root();
                    else if(args.size() != 1) current_dir = tree->search_d(args.at(1));
                    break;
                case 7:
                    if(args.size() == 3){
                        file_cls* tmp_file = tree->search_f(args.at(1));
                        directory_cls* tmp_dir = tree->search_d(args.at(2));
                        tmp_dir->add_file(tmp_file);
                        
                        vector<string> _command;
                        _command.push_back("delete");
                        _command.push_back(args.at(1));
                        process_command(_command);
                    }
                    break;
                case 9:
                    if(args.size() == 2){
                        file_cls* tmp_file = tree->search_f(args.at(1));
                        open_file = tmp_file;
                        cout << memory->read_block(open_file->get_start_blk());
                    }
                    break;
                case 10:
                    if(args.size() == 1){
                        file_cls* tmp_file = open_file;
                        open_file = NULL;
                        cout << "\t"<< tmp_file->get_file_name() << " closed" << endl;
                    }
                    break;
                case 11:
                    tree->get_file_tree(current_dir);
                    break;
                case 12:
                    throw system_error_cls(-1);
                    break;
                case 13:
                    memory->show();
                    break;
                default:
                    cout << "\tinvalid command " << args.at(0) << endl;
                    break;
            }
        }
    }
    
}

int syntices_cls::find_command_by_name(string command){
    for(int iter = 0; iter < TOTAL_COMMANDS; iter++){
        if(commands[iter] == command) return iter;
    }
    return -1;
}

void syntices_cls::help(){
    cout << "\tCOMMAND" << "\t\t" << "DESCRIPTION" << endl;
    for(int iter = 0; iter < TOTAL_COMMANDS; iter++){
        
        cout << "\t" << commands[iter] << "\t\t" << descriptions[iter] << endl;
    }
}

void syntices_cls::shelp(string command){
    int cmd_idx = find_command_by_name(command);
    cout << "\t";
    for(int cmd = 0; cmd < sizeof(syntices[cmd_idx])/sizeof(string); cmd++){
        cout << syntices[cmd_idx][cmd] << ' ';
    }
    cout << endl;
    return;
}

syntices_cls::syntices_cls(memory_cls* mem, file_tree_cls* tr)
{
    memory = mem;
    tree = tr;
    current_dir = tree->get_root();
    memory->write_to_block(0, "JGp#3FvDlPqz7t%mKx1cG9aEhW5eRs2rIiUy6YwHnMoNbTfXk0uQZ4SA8O");
}

syntices_cls::~syntices_cls()
{
}
