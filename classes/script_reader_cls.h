#include "../cli/console_cls.h"
#include <fstream>

class script_reader_cls
{
private:
    console_cls* decoder = NULL;
    syntices_cls* console = NULL;
public:
    script_reader_cls(console_cls*, syntices_cls*);
    ~script_reader_cls();

    bool run(string);
};

bool script_reader_cls::run(string script_path){
    ifstream script_file(script_path);

    if (script_file.is_open()) { // check if file is open
        string command;
        while (getline(script_file, command)) { // read file line by line
            console->process_command(console->to_command_args(command)); // print each line to console
        }
        script_file.close(); // close file
        return true;
    }
    else {
        std::cout << "Unable to open file. Invalid format." << std::endl;
    }
    return false;
}

script_reader_cls::script_reader_cls(console_cls* decoder, syntices_cls* console)
{
    this->decoder = decoder;
    this->console = console;
}

script_reader_cls::~script_reader_cls()
{
}
