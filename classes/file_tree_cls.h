#include "directory_cls.h"
#include <vector>

class file_tree_cls
{
private:
    const string ROOT_DIR = "root";
    directory_cls* root = new directory_cls(ROOT_DIR);
    memory_cls* memory;
public:
    file_tree_cls(memory_cls*);
    ~file_tree_cls();

    // general
    vector<string> process_f_path(string);
    directory_cls* get_root() const {return root;}

    // file functions
    bool add_f(string, string);
    int get_f_block(string);
    file_cls* search_f(string);
    bool update_f(file_cls*, string);

    
    // directory functions
    bool delete_f(string);
    bool remove_f(string);

    bool add_d(string);
    bool delete_d(string);
    directory_cls* search_d(string);

    void get_file_tree(directory_cls*, int);
};

bool file_tree_cls::add_f(string filepath, string data){
    vector<string> path_elements = process_f_path(filepath);
    file_cls* newfile = new file_cls(path_elements.back());
    try
    {
        directory_cls* directory = root;
        for(int iter = 1; iter < path_elements.size()-1; iter++){
            directory = root->find_directory(path_elements.at(iter));
            if(!directory) {
                throw system_error_cls(0);
                break;
            }
        }
        if(directory->add_file(newfile)){
            newfile->set_start_blk(memory->add_block(memory->get_head_block()));
            memory->write_to_block(newfile->get_start_blk(), data);
            return true;
        }
    }
    catch(system_error_cls &e)
    {
        e.display();
    }
    
    
    return false;
}

bool file_tree_cls::add_d(string path){
    vector<string> path_elements = process_f_path(path);
    directory_cls* newfile = new directory_cls(process_f_path(path).back());
    try
    {
        directory_cls* directory = root;
        for(int iter = 1; iter < path_elements.size()-1; iter++){
            directory = directory->find_directory(path_elements.at(iter));
            if(!directory) {
                throw system_error_cls(0);
                break;
            }
        }
        if(directory->add_directory(newfile)){
            return true;
        }
        
    }
    catch(system_error_cls &e)
    {
        e.display();
    }
    
    
    return false;
}

bool file_tree_cls::update_f(file_cls* file, string data){
    try{
        if(memory->write_to_block(file->get_start_blk(), data)) return true;
        throw system_error_cls(1);
    }catch(system_error_cls e){
        e.display();
    }
    return false;
}

bool file_tree_cls::delete_f(string filepath){
     vector<string> path_elements = process_f_path(filepath);
    try
    {
        directory_cls* directory = root, *prev_dir = root;
        file_cls* file = NULL;
        for(int iter = 1; iter < path_elements.size(); iter++){
            prev_dir = directory;
            directory = directory->find_directory(path_elements.at(iter));
            if(!directory) {
                file = prev_dir->find_file(path_elements.at(iter));
                if(!file){
                    throw system_error_cls(0);
                    break;
                }
            }
        }
        
        if(file->get_file_name() == path_elements.back()){
            prev_dir->delete_file(file->get_file_name());
            if(memory->cascade_delete(file->get_start_blk())){
                return true;
            }
            else throw system_error_cls(2);
        }
        
    }
    catch(system_error_cls &e)
    {
        e.display();
    }
    return false;
}

bool file_tree_cls::remove_f(string filepath){
     vector<string> path_elements = process_f_path(filepath);
    try
    {
        directory_cls* directory = root, *prev_dir = root;
        file_cls* file = NULL;
        for(int iter = 1; iter < path_elements.size(); iter++){
            prev_dir = directory;
            directory = directory->find_directory(path_elements.at(iter));
            if(!directory) {
                file = prev_dir->find_file(path_elements.at(iter));
                if(!file){
                    throw system_error_cls(0);
                    break;
                }
            }
        }
        
        if(file->get_file_name() == path_elements.back()){
            prev_dir->delete_file(file->get_file_name());
        }
        
    }
    catch(system_error_cls &e)
    {
        e.display();
    }
    return false;
}

int file_tree_cls::get_f_block(string filename){
    return search_f(filename)->get_start_blk();
}


vector<string> file_tree_cls::process_f_path(string filepath){
    char delimiter = '/';
    vector<std::string> parts;
    size_t start = 0, end = 0;

    while ((end = filepath.find(delimiter, start)) != std::string::npos) {
        std::string part = filepath.substr(start, end - start);
        parts.push_back(part);
        start = end + 1;
    }

    std::string part = filepath.substr(start);
    parts.push_back(part);

    return parts;
}

file_cls* file_tree_cls::search_f(string filepath){
    vector<string> path_elements = process_f_path(filepath);
    try
    {
        directory_cls* directory = root, *prev_dir = root;
        file_cls* file = NULL;
        for(int iter = 1; iter < path_elements.size(); iter++){
            prev_dir = directory;
            directory = directory->find_directory(path_elements.at(iter));
            if(!directory) {
                file = prev_dir->find_file(path_elements.at(iter));
                if(!file){
                    throw system_error_cls(0);
                    break;
                }
            }
        }
        if(file->get_file_name() == path_elements.back()){
            return file;
        }
        
    }
    catch(system_error_cls &e)
    {
        e.display();
    }
    return NULL;
}

directory_cls* file_tree_cls::search_d(string dirpath){
    vector<string> path_elements = process_f_path(dirpath);
    try
    {
        directory_cls* directory = root;
        for(int iter = 1; iter < path_elements.size(); iter++){
            directory = directory->find_directory(path_elements.at(iter));
            if(!directory) {
                throw system_error_cls(0);
                break;
            }
        }
        if(directory->get_dir_name() == path_elements.back()){
            return directory;
        }
        
    }
    catch(system_error_cls &e)
    {
        e.display();
    }
    return NULL;
}

string heirarchy_indent(int level){
    string indent = "\t";
    for(int iter = 0; iter < level; iter++){
        indent += " ";
    }
    return indent;
}

void file_tree_cls::get_file_tree(directory_cls* rootdir, int heir_level = 0){
    
    cout << heirarchy_indent(heir_level) << "" << rootdir->get_dir_name() << endl;
    list<file_cls*>* files = rootdir->get_files();
    if(files->size() != 0){
        for(file_cls* file : *files){
            if(file) cout << heirarchy_indent(heir_level+1) << "" << file->get_file_name() << "--blk " << file->get_start_blk() << endl;
        }
    }
    list<directory_cls*>* directories = rootdir->get_directories();
    if(directories->size() != 0){
        for(directory_cls* dir : *directories){
            get_file_tree(dir, heir_level+2);
        }
    }
}

file_tree_cls::file_tree_cls(memory_cls* memory)
{
    this->memory = memory; 
}

file_tree_cls::~file_tree_cls()
{
}
