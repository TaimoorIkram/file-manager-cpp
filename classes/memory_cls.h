#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
class memory_cls
{
private:
    const int BLK_SIZE = 10;
    int next_available = 0;
    struct memory_blk{
        int blk_id = -1;
        string data = "";
        memory_blk *next = NULL, *prev = NULL;
        int next_blk_to_read_id = -1;
    };
    memory_blk* head = NULL;
public:
    memory_cls(/* args */);
    ~memory_cls();

    // IMPLEMENTED
    int add_block(memory_blk*);
    bool write_to_block(int, string);
    bool check_full_block(memory_blk*);
    bool check_full_block(int);
    bool check_overflow_block(memory_blk*, string);
    memory_blk* get_block(int);
    memory_blk* get_head_block();
    void show();
    int next_available_blk();
    string read_block(int);
    string read_block(int, int, int);
    bool cascade_delete(int);
    memory_blk* get_least_available_block();
    int get_least_available_block_id();

    // NOT IMPLEMENTED
    memory_blk* get_block_size(int);
    memory_blk* delete_block(int);
};

int memory_cls::next_available_blk(){
    return next_available;
}

bool memory_cls::check_overflow_block(memory_blk* block, string data_to_enter){
    return block->data.length() + data_to_enter.length() > BLK_SIZE;
}

bool memory_cls::check_full_block(memory_blk* block){
    return block->data.length() == BLK_SIZE;
}

bool memory_cls::check_full_block(int block_id){
    return check_full_block(get_block(block_id));
}

bool memory_cls::cascade_delete(int start_blk){
    memory_blk* target_blk = get_block(start_blk);
    int next_to_read;
    if(!target_blk) return false;

    while(target_blk->next_blk_to_read_id != -1)
    {
        target_blk->data = "";
        next_to_read = target_blk->next_blk_to_read_id;
        target_blk->next_blk_to_read_id = -2;
        target_blk = get_block(next_to_read);
    }

    target_blk->data = "";
    target_blk->next_blk_to_read_id = -2;
    return true;
}

memory_cls::memory_blk* memory_cls::get_least_available_block(){
    memory_blk* block_ptr = head;
    while (block_ptr->next_blk_to_read_id != -2)
    {
        block_ptr = block_ptr->next;
    }
    return block_ptr;
}

int memory_cls::get_least_available_block_id(){
    memory_blk* block_ptr = head;
    while (block_ptr && block_ptr->next_blk_to_read_id != -2)
    {
        block_ptr = block_ptr->next;
    }
    if(block_ptr) {
        block_ptr->next_blk_to_read_id = -1;
        return block_ptr->blk_id;
    }
    else return -1;
}

memory_cls::memory_blk* memory_cls::get_head_block(){
    return head;
}

memory_cls::memory_blk* memory_cls::get_block(int block_id){
    memory_blk* block_ptr = head;
    while(block_ptr != NULL){
        if(block_ptr->blk_id == block_id) return block_ptr;
        block_ptr = block_ptr->next;
    }
    return NULL;
}

int memory_cls::add_block(memory_blk* headnode){
    memory_blk* new_blk = new memory_blk;
    new_blk->blk_id = next_available++;

    if(!head) {
        head = new_blk;
    }
    else{
        memory_blk* block_ptr = headnode, *previous_block_ptr;
        while(block_ptr->next){
            previous_block_ptr = block_ptr;
            block_ptr = block_ptr->next;
        }
        block_ptr->next = new_blk;
        new_blk->prev = block_ptr;
    }
    return new_blk->blk_id;
}

bool memory_cls::write_to_block(int block_id, string block_data){
    memory_blk* block = get_block(block_id);
    if(check_full_block(block)){    // if the block is full
        memory_blk* previous_block = block;
        int next_available = get_least_available_block_id();
        block = get_block(next_available == -1 ? add_block(this->head) : next_available);
        if(write_to_block(block->blk_id, block_data)){
            previous_block->next_blk_to_read_id = block->blk_id;
            return true;
        }
        else return false;
    }
    else{
        if(check_overflow_block(block, block_data)){    // if block data overflows
            string previous_block_data = block->data;
            string append_data1 = previous_block_data + (string)block_data.substr(0,abs((int)(BLK_SIZE-block->data.length())));
            {
                write_to_block(block->blk_id, append_data1);
                int newblk = get_least_available_block_id();
                if (newblk == -1) newblk = add_block(this->head);
                write_to_block(newblk, block_data.substr(BLK_SIZE, block_data.length()));
                block->next_blk_to_read_id = newblk;
                return true;
            }
        }
        else{ // if block data does not overflow
            block->data = block->data + block_data;
            block->next_blk_to_read_id = -1;
            return true;
        }
    }
    return false;
}

void memory_cls::show(){
    memory_blk* block_ptr = head;
    cout << '\t' << "BLOCK" << '\t' << "NEXT" << '\t' << "DATA" << endl;
    while(block_ptr != NULL){
        cout << '\t' << block_ptr->blk_id << '\t' << block_ptr->next_blk_to_read_id << '\t' << block_ptr->data << endl;
        block_ptr = block_ptr->next;
    }
}

string memory_cls::read_block(int start_block){
    memory_blk* block_ptr = get_block(start_block);
    string data = "";
    
    while(block_ptr->next_blk_to_read_id != -1)
    {
        data += block_ptr->data;
        block_ptr = get_block(block_ptr->next_blk_to_read_id);
    }

    data += block_ptr->data;
    return data;
}

string memory_cls::read_block(int start_block, int start, int length){
    memory_blk* block_ptr = get_block(start_block);
    string data = "";

    while(block_ptr->next_blk_to_read_id != -1)
    {
        data += block_ptr->data;
        block_ptr = get_block(block_ptr->next_blk_to_read_id);
    }

    data += block_ptr->data;

    return data.substr(start, length);
}


memory_cls::memory_cls(/* args */)
{
    add_block(head);
}

memory_cls::~memory_cls()
{
}
