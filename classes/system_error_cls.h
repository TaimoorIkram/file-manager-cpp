#include<iostream>
#include"memory_cls.h"
using namespace std;

#define TOT_ERRORS 20

class system_error_cls : public exception
{
private:
    int error_code;
    string error_reasons[TOT_ERRORS] = {
        "INVALID_MEMORY_WRITE", // 0
        "DATA_STRUCTURE_CORRUPTION", // 1
        "FILE_DIR_PUSH_BACK_FAIL", // 2
        "", // 3
        "", // 4
        "", // 5
        "", // 6
        "", // 7
        "", // 8
        "", // 9
        "", // 10
    };
public:
    system_error_cls(int);
    ~system_error_cls();
    
    string get_error_details(int);
    int get_error_code();
    void display();
    void display(memory_cls*);
};

void system_error_cls::display(){
    system("cls");
    cout << "\t--------------------------------------" << endl;
    cout << "\tOops, that was not supposed to happen." << endl;
    cout << "\n\n\tCRITICAL ERROR: " + get_error_details(error_code) << endl;
    cout << "\n\tTerminating the operation helps, so try \n\tturning of the program and restarting. If \n\tthings still donot work out, get help at: \n\twww.google.com." << endl;
    cout << "\t--------------------------------------" << endl;
}

void system_error_cls::display(memory_cls* memory){
    system("cls");
    cout << "\t--------------------------------------" << endl;
    cout << "\tOops, that was not supposed to happen." << endl;
    cout << "\n\n\tCRITICAL ERROR: " + get_error_details(error_code) << endl;
    cout << "\n\tTerminating the operation helps, so try \n\tturning of the program and restarting. If \n\tthings still donot work out, get help at: \n\twww.google.com." << endl;
    cout << "\t--------------------------------------" << endl;
    memory->show();
}

string system_error_cls::get_error_details(int error_code){
    if(error_code < TOT_ERRORS){
        return error_reasons[error_code];
    }
    return "";
}

int system_error_cls::get_error_code(){
    return error_code;
}

system_error_cls::system_error_cls(int error_code)
{
    this->error_code = error_code;
}

system_error_cls::~system_error_cls()
{
}
