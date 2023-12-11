#include "Sokuban.h"

Object::Object(int x, int y,int flag){
    pos=Position(x,y);

    this->flag=flag;
    this->id=object_cnt;
    object_cnt++;
}

Object::Object(Position &pos,int flag){
    this->pos=Position(pos);
    
    this->flag=flag;
    this->id=object_cnt;
    object_cnt++;
}

void Object::setPosition(int x, int y){
    pos=Position(x,y);
}

void Object::setPosition(Position &pos){
    this->pos=Position(pos);
}

