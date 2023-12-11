#include "Sokuban.h"

InnerBox::InnerBox(int flag ,int entrance, GridBoard *inner_space):Object(flag){
    this->entrance=entrance;
    loadInnerSpace(inner_space);
}

InnerBox::~InnerBox(){
    unloadInnerSpace();
}

void InnerBox::loadInnerSpace(GridBoard *inner_space){
    unloadInnerSpace();
    if(inner_space!=nullptr){
        inner_space->cnt++;
        this->inner_space=inner_space;
    }
}

void InnerBox::unloadInnerSpace(){
    if(inner_space!=nullptr){
        inner_space->cnt--;
        if(inner_space->cnt==0)delete inner_space;
        inner_space==nullptr;
    }
}