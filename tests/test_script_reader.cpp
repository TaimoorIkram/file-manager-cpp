#include"../classes/script_reader_cls.h"
using namespace std;

int main(int argc, char const *argv[])
{   
    // tree-test
    memory_cls* memory = new memory_cls();
    file_tree_cls* tree = new file_tree_cls(memory);
    console_cls* console = new console_cls(memory, tree);
    
    console->main_screen_script_mode("../scripts/test_script.fscript");    
    // reader->run("../scripts/test_script.fscript");
    return 0;
}
