#include "Sokuban.h"
#include <unordered_map>
#include <iostream>
using namespace std;

unordered_map<string,string> DENOTATION;

void init(){
    DENOTATION.insert({"P","Player"});
    DENOTATION.insert({"p","Player on checkpoint"});
    DENOTATION.insert({"O","Box without inner space"});
    DENOTATION.insert({"o","Box with inner space"});
    DENOTATION.insert({"=","Check point"});
    DENOTATION.insert({"_","Storage point"});
    DENOTATION.insert({"#","Wall"});
    DENOTATION.insert({".","Empty"});
}

char Grid2Char(Grid &grid){
    if(grid.object==nullptr){
        switch (grid.type){
        case Grid::TYPE_CHECK_POINT:
            return '=';
        case Grid::TYPE_STORAGE_POINT:
            return '_';
        case Grid::TYPE_WALL:
            return '#';
        case Grid::TYPE_EMPTY:
            return '.';
        }
    }else{
        if(grid.object->type==Object::TYPE_PLAYER && grid.type==Grid::TYPE_CHECK_POINT)return 'p';
        else if(grid.object->type==Object::TYPE_PLAYER) return 'P';
        else if(grid.object->type==Object::TYPE_BOX_INNER) return 'o';
        else if(grid.object->type==Object::TYPE_BOX_NORMAL) return 'O';
    }
}

void printGridboard(GridBoard *gridboard){
    if(gridboard==nullptr){
        cout<<"gridboard is null"<<endl;
        return;
    }else{
        cout<<"----------DENOTATION---------\n";
        for(auto &i:DENOTATION){
            cout<<i.first<<": "<<i.second<<endl;
        }
        cout<<"----------DENOTATION---------\n";
        for(int x=0;x<gridboard->size_x;x++){
            for(int y=0;y<gridboard->size_y;y++){
                cout<<Grid2Char(gridboard->getGrid(x,y))<<" ";
            }
            cout<<endl;
        }
    }
}

GridBoard* makeMap1(){
    GridBoard *gridboard=new GridBoard(11,11,1,1,GridBoard::GAMEMODE_CLASSIC);
    for(int i=0;i<11;i++){
        gridboard->setGridType(0,i,Grid::TYPE_WALL);
        gridboard->setGridType(10,i,Grid::TYPE_WALL);
        gridboard->setGridType(i,0,Grid::TYPE_WALL);
        gridboard->setGridType(i,10,Grid::TYPE_WALL);
    }
    gridboard->setGridType(7,9,Grid::TYPE_STORAGE_POINT);
    gridboard->setGridType(7,8,Grid::TYPE_STORAGE_POINT);
    gridboard->setGridType(7,7,Grid::TYPE_STORAGE_POINT);
    gridboard->setGridType(1,9,Grid::TYPE_CHECK_POINT);

    Object *box;
    box=new Object(Object::TYPE_BOX_NORMAL);
    gridboard->addObject(box,4,4);

    box=new Object(Object::TYPE_BOX_NORMAL);
    gridboard->addObject(box,3,3);

    box=new Object(Object::TYPE_BOX_NORMAL);
    gridboard->addObject(box,2,2);
}

int main(){
    init();
    GridBoard *map1=makeMap1();
    GameHandler gh(map1);
    printGridboard(map1);
    char cmd;
    cout<<"enter w,s,a,d to move, p to quit";
    while(cin>>cmd){
        switch (cmd)
        {
        case 'w':
            gh.moveUp();
            break;
        case 's':
            gh.moveDown();
            break;
        case 'a':
            gh.moveLeft();
            break;
        case 'd':
            gh.moveRight();
            break;
        case 'p':
            return 0;
            break;
        }
        if(gh.isWin()){
            cout<<"You win!!!\nEnter any key to quit.."<<endl;
            break;
        }
    }
    cin>>cmd;
    
}