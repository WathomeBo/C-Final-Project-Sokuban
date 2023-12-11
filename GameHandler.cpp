#include "Sokuban.h"

GameHandler::GameHandler(GridBoard *board){
    loadGridBoard(board);
}

GameHandler::~GameHandler(){
    unloadGridBoard();
}

void GameHandler::loadGridBoard(GridBoard *gridboard){
    if(gridboard!=nullptr){
        gridboard->cnt++;
        this->gridboard=gridboard;
    }
}

void GameHandler::unloadGridBoard(){
    if(gridboard!=nullptr){
        gridboard->cnt--;
        if(gridboard->cnt<=0)delete gridboard;
        this->gridboard=nullptr;
    }
}

bool GameHandler::isWin(){
    if(gridboard->player->grid->type!=Grid::TYPE_CHECK_POINT)return false;
    int cnt=0;
    for(auto box:gridboard->boxes){
        if(box->grid->type==Grid::TYPE_STORAGE_POINT)cnt++;
    }
    return cnt==gridboard->storage_point_cnt;
}

bool GameHandler::moveUp(){
    Position direction(0,-1);
    return move(direction);
}

bool GameHandler::moveDown(){
    Position direction(0,1);
    return move(direction);
}

bool GameHandler::moveLeft(){
    Position direction(-1,0);
    return move(direction);
}

bool GameHandler::moveRight(){
    Position direction(1,0);
    return move(direction);
}

bool GameHandler::move(int direction){
    switch (direction){
    case UP:
        return moveUp();
    case DOWN:
        return moveDown();
    case LEFT:
        return moveLeft();
    case RIGHT:
        return moveRight();
    
    default:
        return false;
    }
}

bool GameHandler::move(Position &direction){
    if(gridboard->gamemode==GridBoard::GAMEMODE_CLASSIC){
        //target_pos为玩家朝direction前进一格后的位置
        Position target_pos=Position(gridboard->getPlayerPos());
        target_pos.move(direction);
        if(!gridboard->isPosValid(target_pos))return false;
        Grid target_grid=gridboard->getGrid(target_pos);
        
        //判断target_pos是否可以移动，若可以，则玩家移动到此位置，若不可以判断是否可以推箱子
        if(isGridMovable(target_grid)){
            gridboard->moveObject(*gridboard->player->grid,target_grid);
            cmds.push_back(direction2cmd(direction));
            return true;
        }else if(target_grid.getObjectType()==Object::TYPE_BOX_NORMAL){
            //extend_pos为target_pos再前进一格，即箱子被推到的位置
            Position extend_pos=Position(target_pos);
            extend_pos.move(direction);
            if(!gridboard->isPosValid(extend_pos))return false;
            Grid extend_grid=gridboard->getGrid(extend_pos);
            if(isGridMovable(extend_grid)){
                gridboard->moveObject(target_grid,extend_grid);
                gridboard->moveObject(*gridboard->player->grid,target_grid);
                return true;
            }else return false;
        }
    }
}


bool GameHandler::isGridMovable(Grid &grid){
    if(gridboard->gamemode==GridBoard::GAMEMODE_CLASSIC){
        return grid.object!=nullptr && grid.type!=Grid::TYPE_WALL;
    }
}

bool GameHandler::isGridMovable(Position &pos){
    Grid grid=gridboard->getGrid(pos);
    if(gridboard->gamemode==GridBoard::GAMEMODE_CLASSIC){
        return grid.object!=nullptr && grid.type!=Grid::TYPE_WALL;
    }
}

int GameHandler::direction2cmd(Position &direction){
    if(direction.x==0 &&direction.y==1)return DOWN;
    if(direction.x==0 &&direction.y==-1)return UP;
    if(direction.x==1 &&direction.y==0)return RIGHT;
    if(direction.x==-1 &&direction.y==0)return LEFT;
    return -1;
}