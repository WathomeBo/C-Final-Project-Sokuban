#include "Sokuban.h"

Object::Object(int type){
    this->type=type;
    this->grid=nullptr;

    this->id=object_cnt;
    object_cnt++;
}


