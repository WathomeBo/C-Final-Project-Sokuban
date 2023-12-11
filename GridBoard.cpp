#include "Sokuban.h"
GridBoard::GridBoard(int size_x, int size_y, int player_x, int player_y,int gamemode){
    //std::cout<<"GridBoard creating...\n";
    if(size_x<0||size_y<0||player_x<0||player_y<0||player_x>=size_x||player_y>=size_y||gamemode<0){
        this->gamemode=GridBoard::INVALID;
        return;
    }
    this->gamemode=gamemode;
    //初始化grids
    this->size_x=size_x;
    this->size_y=size_y;
    this->grids=new Grid[size_x*size_y];
    for(int x=0;x<size_x;x++){
        for(int y=0;y<size_y;y++){
            grids[y+x*size_y].setPosition(x,y);
        }
    }
    //std::cout<<"Grids created successfully,address="<<grids<<std::endl;

    //初始化player
    Object *p=new Object(Object::TYPE_PLAYER);
    Grid* g=getGrid(player_x,player_y);
    player=p;
    g->object=p;
    p->grid=g;
    //std::cout<<"Player created successfully,address="<<p<<std::endl;
    cnt=0;
    storage_point_cnt=0;
    //std::cout<<"GridBoad created successfully,address="<<this<<std::endl;;
}

GridBoard::GridBoard(int size_x, int size_y, Position &player_pos,int gamemode):GridBoard(size_x,size_y,player_pos.x,player_pos.y,gamemode){

}

GridBoard::~GridBoard(){
    delete[] grids;
    delete player;
    for(Object *o:boxes){
        delete o;
    }
}

Position& GridBoard::getPlayerPos(){
    return player->grid->pos;
}

Grid* GridBoard::getGrid(int x, int y){
    return grids+(x*size_y+y);
}

Grid* GridBoard::getGrid(Position &pos){
    return grids+(pos.x*size_y+pos.y);
}

void GridBoard::setGridType(int x, int y, int type){
    getGrid(x,y)->type=type;
    if(type==Grid::TYPE_STORAGE_POINT)storage_point_cnt++;
}

void GridBoard::setGridType(Position &pos, int type){
    setGridType(pos.x,pos.y,type);
}


bool GridBoard::addObject(Object *object, int x,int y){
    if(object==nullptr||!isPosValid(x,y))return false;
    Grid *g=getGrid(x,y);
    if(g->object!=nullptr)return false;
    else{
        auto result=boxes.emplace(object);
        if(result.second){
            g->object=object;
            object->grid=g;
        }
        return result.second;
    }
}

bool GridBoard::addObject(Object *object, Position &pos){
    return addObject(object,pos.x,pos.y);
}

bool GridBoard::isPosValid(int x, int y){
    return x>-1&&x<size_x&&y>-1&&y<size_y;
}

bool GridBoard::isPosValid(Position &pos){
    return pos.x>-1&&pos.x<size_x&&pos.y>-1&&pos.y<size_y;
}

bool GridBoard::moveObject(Position &from, Position &to){
    if(isPosValid(from)&&isPosValid(to))return moveObject(getGrid(from),getGrid(to));
    return false;
}

bool GridBoard::moveObject(Position &from, Grid *to){
    if(isPosValid(from))return moveObject(getGrid(from),to);
    return false;
}

bool GridBoard::moveObject(Grid *from, Position &to){
    if(isPosValid(to))return moveObject(from,getGrid(to));
    return false;
}

bool GridBoard::moveObject(Grid *from, Grid *to){
    if(from->object==nullptr||to->object!=nullptr)return false;
    to->object=from->object;
    to->object->grid=to;
    from->object=nullptr;
    return true;
}

bool GridBoard::removeObject(Object *object){
    return removeObject(object,false);
}

bool GridBoard::removeObject(Object *object, bool is_delete){
    if(object==player){
        player->grid->object=nullptr;
        player=nullptr;
        if(is_delete)delete object;
        return true;
    }else{
        auto result=boxes.erase(object);
        if(result>0){
            object->grid->object=nullptr;
            if(is_delete)delete object;
            return true;
        }else return false;
    }
}

bool GridBoard::isValid(){
    return gamemode!=GridBoard::INVALID;
}

