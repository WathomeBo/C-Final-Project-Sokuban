//非常重要！！！
//采用笛卡尔坐标系，即原点在左上角，水平为x轴，以右为正；纵向为y轴，以下为正。

#include <string>
#include <iostream>
#include <unordered_set>
#include <vector> //c++的vector相当于java的arraylist
const int UP=0;
const int DOWN=1;
const int LEFT=2;
const int RIGHT=3;

static int object_cnt=0;

class Position{
    private:

    public:
        int x;
        int y;
        Position(){
            x=-1;
            y=-1;
        }
        Position(int x, int y){
            this->x=x;
            this->y=y;
        }
        Position(const Position &pos){
            x=pos.x;
            y=pos.y;
        }

        void moveUp(){
            x--;
        }
        void moveDown(){
            x++;
        }
        void moveLeft(){
            y--;
        }
        void moveRight(){
            y++;
        }

        void extend(){
            x*=2;
            y*=2;
        }

        void move(Position &pos){
            x+=pos.x;
            y+=pos.y;
        }

        void asign(Position &pos){
            x=pos.x;
            y=pos.y;
        }

        void asign(int x, int y){
            this->x=x;
            this->y=y;
        }

        bool operator==(const Position &pos){
            return x==pos.x && y==pos.y;
        }

        friend std::ostream & operator << (std::ostream &out, const Position &pos){
            out<<"("<<pos.x<<", "<<pos.y<<") ";
        }

        
};

class Object;
class Grid;
class GridBoard;
class GameHandler;

//所有可移动的东西，包括箱子，人的父类
class Object{
    private:

    public:
        static const int TYPE_PLAYER=0;
        static const int TYPE_BOX_NORMAL=1;
        static const int TYPE_BOX_INNER=2;
        
        //type变量指示该物体的类型，id自动分配，保证每个object有唯一id，grid为object所在的grid
        int type;
        int id;
        Grid *grid;

        Object(int type);
        ~Object();


};

//InnerBox和普通箱子的区别在于，多了一个入口和内部空间，内部空间即为gridboard

class InnerBox:public Object{
    private:
        
    public :
        int entrance;
        GridBoard *inner_space;
        
        InnerBox(int flag, int entrance, GridBoard *inner_space);
        ~InnerBox();

        void loadInnerSpace(GridBoard *inner_space);
        void unloadInnerSpace();
};


class Grid{
    private:        

    public:
        //如有需要可修改或添加新的常量
        static const int TYPE_EMPTY=0;
        static const int TYPE_WALL=1;
        static const int TYPE_STORAGE_POINT=2;
        static const int TYPE_CHECK_POINT=3;

        Position pos;

        //type变量表示该地块的原生类型，object变量表示处于该地块上的可移动物体，如player和box。之所以不合并在type里是为了便于后续拓展复杂的规则。
        int type;
        Object *object;

        Grid();
        Grid(int type);
        Grid(int type, Object *object);

        Grid(Position &pos);
        Grid(int x, int y);

        Grid(Position &pos,int type);
        Grid(int x, int y,int type);

        Grid(Position &pos,int type, Object *object);
        Grid(int x, int y,int type, Object *object);

        void setPosition(int x, int y);
        void setPosition(Position &pos);

        //返回object的类型，若没有object则返回-1
        int getObjectType();

};

//GridBoard不需要检测操作是否符合游戏规则
class GridBoard{
    private:
        //gamemode用来表示当前所采用的规则,
        
    public:
        static const int INVALID=-1;
        static const int GAMEMODE_CLASSIC=0;
        static const int GMAEMODE_INNER_BOX=1;

        int gamemode;
        int size_x;
        int size_y;
        int storage_point_cnt;
        
        Grid *grids;
        Object *player;
        std::unordered_set<Object*> boxes;
        //类似向量计算那一题中的data，维护cnt表示引用次数，来判断是否需要释放。
        int cnt;
        GridBoard():GridBoard(10,10,0,0,GridBoard::GAMEMODE_CLASSIC){

        }

        //初始化函数，size_x,size_y指的是board的尺寸，player_pos指的是玩家的初始位置。 需要初始化grid_board，默认每个grid为empty
        GridBoard(int size_x, int size_y, Position &player_pos,int gamemode);
        GridBoard(int size_x, int size_y, int player_x, int player_y,int gamemode);
        
        //todo：path为本地GridBoard文件的路径，从该文件中加载gridboard,若文件损坏，将gamemode 设置为GridBoard::INVALID
        GridBoard(std::string &path);
        
        //解构函数，用来释放内存
        ~GridBoard(); 

        //若该位置越界，返回false
        bool isPosValid(int x, int y);
        bool isPosValid(Position &pos);
        
        //获取玩家位置
        Position& getPlayerPos();

        //返回指定位置的grid
        Grid* getGrid(int x, int y);
        Grid* getGrid(Position &pos);

        //设置grid的type
        void setGridType(int x, int y, int type);
        void setGridType(Position &pos, int type);

        //添加一个可移动物体到棋盘上，执行成功则返回true,否则返回false,目标位置已被占用算失败,该棋盘已存在该物体算失败
        bool addObject(Object *object, Position &pos);
        bool addObject(Object *object, int x, int y);

        //将可移动物体从from移动到to上,执行成功则返回true,否则返回false,to位置已有object算失败,from位置无object算失败
        bool moveObject(Position &from, Position &to);
        bool moveObject(Grid *from, Grid *eto);
        bool moveObject(Grid *from, Position &to);
        bool moveObject(Position &from, Grid *to);
        
        //将object从gridboard中删除，成功删除则返回true，若is_delete为true，还会delete该object，默认为false
        bool removeObject(Object *object);
        bool removeObject(Object *object, bool is_delete);

        //todo：保存当前GridBoard为本地文件,path为文件路径
        //注意：innerbox的信息也要保存
        void save(std::string &path);

        //若当前棋盘为有效的，可用的棋盘，则返回true
        bool isValid();

};

class GameHandler{
    private:

    public:
        GridBoard *gridboard;
        std::vector<int> cmds;

        GameHandler(GridBoard *board);

        //todo：path为本地文件夹的路径，从该文件夹中加载游戏进度,若文件损坏，将gridboard设置为nullptr
        GameHandler(std::string &path);

        //:解构函数，释放相关内存
        ~GameHandler();

        void loadGridBoard(GridBoard *gridboard);
        void unloadGridBoard();
        
        //判断游戏是否胜利
        bool isWin();

        //todo:在当前gamemode下，判断能否朝指定方向移动，若可以，则移动并返回true，若不行，则不进行任何操作，返回false
        //hint:若mode为inner_box, 将gridboard替换成inner_box所保存的gridboard即可视为进入了该inner_box
        bool moveUp();
        bool moveDown();
        bool moveLeft();
        bool moveRight();
        bool move(int direction);
        bool move(Position &direction);

        //返回在当前模式下，该地块是否可以移动上去
        bool isGridMovable(Grid *grid);
        bool isGridMovable(Position &grid);

        //todo:当n为正数时，将当前棋局设置为第n步的状态，当n为负数时，表示悔棋n步。执行成功则返回true，否则返回false
        bool stepTo(int n);

        //todo：保存当前游戏进度为本地文件，可以分为多个文件保存（如gridboard和instructors分开存），path为文件夹路径
        void save(std::string &path);

        //若当前游戏为有效的，可用的棋盘，则返回true
        bool isValid();

        //将direction转化为对应的cmd数字
        int direction2cmd(Position &direction);
};