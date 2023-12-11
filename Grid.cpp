#include "Sokuban.h"

Grid::Grid():Grid(-1,-1,Grid::TYPE_EMPTY,nullptr){
}

Grid::Grid(int type):Grid(-1,-1,type,nullptr){
}

Grid::Grid(int type, Object *object):Grid(-1,-1,type,object){
}

Grid::Grid(int x, int y):Grid(x,y,Grid::TYPE_EMPTY,nullptr){
}

Grid::Grid(Position &pos):Grid(pos.x,pos.y,Grid::TYPE_EMPTY,nullptr){
}

Grid::Grid(int x, int y,int type):Grid(x,y,type,nullptr){
}

Grid::Grid(Position &pos,int type):Grid(pos.x,pos.y,type,nullptr){
}

Grid::Grid(int x, int y,int type, Object *object){
    this->pos.asign(x,y);
    this->type=type;
    this->object=object;
}

Grid::Grid(Position &pos,int type, Object *object):Grid(pos.x,pos.y,type,object){

}

int Grid::getObjectType(){
    if(object==nullptr)return -1;
    return object->type;
}

void Grid::setPosition(int x, int y){
    pos.asign(x,y);
}

void Grid::setPosition(Position &pos){
    this->pos=Position(pos);
}