//非常重要！！！
//采用笛卡尔坐标系，即原点在左上角，水平为x轴，以右为正；纵向为y轴，以下为正。

#include <string>
#include <vector> //c++的vector相当于java的arraylist
const int UP=0;
const int DOWN=1;
const int LEFT=2;
const int RIGHT=3;

class Position{
    private:
        int x;
        int y;

    public:
        Position(){
            x=0;
            y=0;
        }
        Position(int x, int y){
            this->x=x;
            this->y=y;
        }
        Position(Position &pos){
            x=pos.getX();
            y=pos.getY();
        }

        void setX(int v){
            x=v;
        }

        void setY(int v){
            y=v;
        }

        int getX(){
            return x;
        }

        int getY(){
            return y;
        }

        void moveUp(){
            y--;
        }

        void moveDown(){
            y++;
        }

        void moveLeft(){
            x--;
        }

        void moveRight(){
            x++;
        }

        void sign(Position &pos){
            x=pos.getX();
            y=pos.getY();
        }

        
};

//所有可移动的东西，包括箱子，人的父类
class Object{
    private:
        //flag变量指示该物体的类型,id可随意设置，写在这里是为了万一以后要用
        int flag;
        int id;
        Position pos;

    public:
        static const int FLAG_PLAYER=0;
        static const int FLAG_BOX_NORMAL=1;
        static const int FLAG_BOX_INNER=2;
        
        Object(){
            flag=Object::FLAG_BOX_NORMAL;
            id=0;
            pos=Position(0,0);
        }
        
        Object(int x, int y,int flag ,int id){
            pos=Position(x,y);

            this->flag=flag;
            this->id=id;
        }

        Object(Position &pos,int flag, int id){
            this->pos=Position(pos);
            
            this->flag=flag;
            this->id=id;
        }

        Position getPosition(){
            return pos;
        }

        void setPosition(int x, int y){
            pos.setX(x);
            pos.setY(y);
        }

        void setPosition(Position &pos){
            this->pos.sign(pos);
        }
        
        int getId(){
            return id;
        }

        int getFlag(){
            return flag;
        }
};

//InnerBox和普通箱子的区别在于，多了一个入口和内部空间，内部空间即为gridboard
//注意：InnerBox在生命结束时会自动释放inner_space的内存
class InnerBox:public Object{
    private:
        int entrance;
        GridBoard *inner_space;
    
    public :
        InnerBox(int x, int y,int flag ,int id, int entrance):Object(x,y,flag,id){
            this->entrance=entrance;
        }

        InnerBox(Position &pos,int flag ,int id, int entrance):Object(pos,flag,id){
            this->entrance=entrance;
        }
        ~InnerBox(){
            delete inner_space;
        }

        void setInnerSpace(GridBoard *inner_space){ //浅拷贝
            this->inner_space=inner_space;
        }

        GridBoard* getInnerSpace(){
            return inner_space;
        }
};


class Grid{
    private:
        //type变量表示该地块的原生类型，object变量表示处于该地块上的可移动物体，如player和box。之所以不合并在type里是为了便于后续拓展复杂的规则。
        int type;
        Object *object;

    public:
        //如有需要可修改或添加新的常量
        static const int TYPE_EMPTY=0;
        static const int TYPE_WALL=1;
        static const int TYPE_STORAGE_POINT=2;
        static const int TYPE_CHECK_POINT=3;


        Grid(){
            type=Grid::TYPE_EMPTY;
            object=nullptr;
        }

        Grid(int t){
            type=t;
            object=nullptr;
        }
        
        Grid(int t, Object *object){
            type=t;
            this->object=object;
        }

        void setType(int t){
            type=t;
        }

        void setObject(Object *object){
            this->object=object;
        }

        int getType(){
            return type;
        }

        Object* getObject(){
            return object;
        }
};

//GridBoard不需要检测操作是否合法
class GridBoard{
    private:
    
    public:
        //todo:初始化函数，sizeX,sizeY指的是board的尺寸，pX,pY指的是玩家的初始位置。 需要初始化grid_board，默认每个grid为empty
        GridBoard(int sizeX, int sizeY, int pX, int pY);
        
        //todo：path为本地GridBoard文件的路径，从该文件中加载gridboard
        GridBoard(std::string &path);
        
        //todo:解构函数，用来释放内存
        ~GridBoard(); 

        //todo:返回指定位置的grid的引用
        Grid getGrid(int x, int y);
        Grid getGrid(Position &pos);

        //todo:设置grid的type
        void setGridType(int x, int y, int type);
        void setGridType(Position &pos, int type);

        //todo:添加一个可移动物体到棋盘上
        void addObject(Object &object);
        void addObject(int type, Position &pos);

        //todo:将start上的可移动物体移动到end上
        void moveObject(Position &start, Position &end);

        //todo:返回玩家当前位置
        Position getPlayerPosition();

        //todo:返回玩家当前所在grid
        Grid getPlayerGrid();

        //todo：保存当前GridBoard为本地文件
        void save(std::string &path);

};

class GameHandler{
    private:
        //gamemode用来表示当前所采用的规则
        int gamemode;
        GridBoard gridboard;

    public:
        static const int GAMEMODE_CLASSIC=0;
        static const int GMAEMODE_INNER_BOX=1;
        
        //do nothing
        GameHandler();
        GameHandler(int mode, GridBoard &board){
            gamemode=mode;
            gridboard=board;
        }

        //todo:判断游戏是否胜利
        bool isWin();



};