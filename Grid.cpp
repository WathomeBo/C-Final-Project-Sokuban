#include "Sokuban.h"

Grid::Grid(){
    pos=Position(-1,-1);
    type=Grid::TYPE_EMPTY;
    object=nullptr;
}

Grid::Grid(int type){
    pos=Position(-1,-1);
    this->type=type;
    object=nullptr;
}

Grid::Grid(int type, Object *object){
    this->type=type;
    this->object=object;
}

Grid::Grid(int x, int y){
    pos=Position(x,y);
    this->type=Grid::TYPE_EMPTY;
    object=nullptr;
}

Grid::Grid(Position &pos){
    this->pos=Position(pos);
    this->type=Grid::TYPE_EMPTY;
    object=nullptr;
}

Grid::Grid(int x, int y,int type){
    pos=Position(x,y);
    this->type=type;
    object=nullptr;
}

Grid::Grid(Position &pos,int type){
    this->pos=Position(pos);
    this->type=type;
    object=nullptr;
}

Grid::Grid(int x, int y,int type, Object *object){
    this->pos=Position(x,y);
    this->type=type;
    this->object=object;
}

Grid::Grid(Position &pos,int type, Object *object){
    this->pos=Position(pos);
    this->type=type;
    this->object=object;
}

int Grid::getObjectType(){
    if(object==nullptr)return -1;
    return object->type;
}

void Grid::setPosition(int x, int y){
    pos=Position(x,y);
}

void Grid::setPosition(Position &pos){
    this->pos=Position(pos);
}