#include "Sokuban.h"

Grid::Grid(){
    type=Grid::TYPE_EMPTY;
    object=nullptr;
}

Grid::Grid(int type){
    this->type=type;
    object=nullptr;
}

Grid::Grid(int type, Object *object){
    this->type=type;
    loadObject(object);
}

void Grid::loadObject(Object *object){
    this->object=object;
}

void Grid::unloadObject(){
    object=nullptr;
}