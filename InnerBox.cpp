#include "Sokuban.h"

InnerBox::InnerBox(int x, int y,int flag ,int id, int entrance, GridBoard *inner_space):Object(x,y,flag){
    this->entrance=entrance;
    this->inner_space=inner_space;
    inner_space->load();
}

InnerBox::InnerBox(Position &pos,int flag ,int id, int entrance, GridBoard *inner_space):Object(pos,flag){
    this->entrance=entrance;
    this->inner_space=inner_space;
    inner_space->load();
}

InnerBox::~InnerBox(){
    if(inner_space!=nullptr)inner_space->unload();
}