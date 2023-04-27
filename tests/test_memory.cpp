#include"../classes/file_cls.h"
#include"../classes/memory_cls.h"
#include"../classes/file_tree_cls.h"
// #include"../cli/syntices_cls.h"


using namespace std;

int main(int argc, char const *argv[])
{   
    // tree-test
    memory_cls* memory = new memory_cls();
    memory->write_to_block(0, "JGp#3FvDlPqz7t%mKx1cG9aEhW5eRs2rIiUy6YwHnMoNbTfXk0uQZ4SA8O");
    file_tree_cls* tree = new file_tree_cls(memory);
    tree->add_d("root/newdir");
    tree->add_d("root/newdir/newnew");
    tree->add_d("root/newdir1");
    tree->add_d("root/newdir2");
    tree->add_d("root/newdir2/file.txt");
    tree->add_d("root/newdir3");
    tree->add_d("root/newdir3/papers.txt");
    tree->add_d("root/newdir3/car.xlsx");
    tree->add_d("root/newdir3/lol.psd");
    tree->add_f("root/newdir/newfile.txt", "HELLOASOASaASJAJOIIOoauos03498-93493ipodpkop");
    tree->get_file_tree(tree->get_root());
    // tree->add_d("roo/newdir4/lol.psd");

    // directory-test
    // file_cls* file = new file_cls("hello.txt");
    // directory_cls* dir = new directory_cls("misc");
    // directory_cls* root = new directory_cls("root");
    // cout << root->add_file(file) << endl;
    // cout << root->add_directory(dir) << endl;
    // cout << memory->read_block(0) << endl;

    // syntices_cls syntaxer;
    // syntaxer.help();

    return 0;
}
