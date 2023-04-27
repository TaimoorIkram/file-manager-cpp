#include"../cli/console_cls.h"
using namespace std;

int main(int argc, char const *argv[])
{   
    // tree-test
    memory_cls* memory = new memory_cls();
    file_tree_cls* tree = new file_tree_cls(memory);
    console_cls* console = new console_cls(memory, tree);
    console->main_screen();

    return 0;
}
