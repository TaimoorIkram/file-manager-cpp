#include<list>
#include<iostream>
#include"system_error_cls.h"
using namespace std;

class directory_cls
{
private:
    string directory_name = "";
public:
    directory_cls(string);
    ~directory_cls();

    list<file_cls*> files;
    list<directory_cls*> directories;

    string get_dir_name() const {return directory_name;}

    bool add_file(file_cls*);
    bool add_directory(directory_cls*);

    directory_cls* find_directory(string);
    file_cls* find_file(string);
    bool delete_file(string); // ALMOST FIXED
    bool delete_file(file_cls*); // NEEDS ATTENTION

    list<file_cls*>* get_files();
    list<directory_cls*>* get_directories();
};

list<file_cls*>* directory_cls::get_files(){
    return &files;
}

list<directory_cls*>* directory_cls::get_directories(){
    return &directories;
}

directory_cls* directory_cls::find_directory(string dir_name){
    for(auto &dir : directories){
        if(dir->directory_name == dir_name) return dir;
    }
    return NULL;
}

file_cls* directory_cls::find_file(string file_name){
    for(auto &file : files){
        if(file->get_file_name() == file_name) return file;
    }
    return NULL;
}

bool directory_cls::delete_file(string file_name){
    int i = 0;
    for(auto &file : files){
        if(file->get_file_name() == file_name) break;
        i++;
    }

    auto it = files.begin();
    std::advance(it, i);
    files.erase(it);

    return true;
}

bool directory_cls::delete_file(file_cls* file){
    files.remove(file);
    return true;
}

bool directory_cls::add_file(file_cls* file){
    try{
        files.push_back(file);
        return true;
    }
    catch(exception e){
        throw system_error_cls(2);
    }
    return false;
}

bool directory_cls::add_directory(directory_cls* directory){
    try{
        directories.push_back(directory);
        return true;
    }
    catch(exception e){
        throw system_error_cls(2);
    }
    return false;
}

directory_cls::directory_cls(string directory_name)
{
    this->directory_name = directory_name;
}

directory_cls::~directory_cls()
{
}
