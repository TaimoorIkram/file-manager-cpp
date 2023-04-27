#include<iostream>
using namespace std;

class file_cls
{
private:
    int start_blk_id;
    string filename;
public:
    file_cls(string);
    ~file_cls();

    int get_start_blk();
    string get_file_name() const {return filename;}
    void set_start_blk(int);
};

int file_cls::get_start_blk(){
    return start_blk_id;
}

void file_cls::set_start_blk(int block_id){
    start_blk_id = block_id;
}

file_cls::file_cls(string filename)
{
    this->filename = filename;
}

file_cls::~file_cls()
{
}
