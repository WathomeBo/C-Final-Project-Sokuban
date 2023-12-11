//非常重要！！！
//采用笛卡尔坐标系，即原点在左上角，水平为x轴，以右为正；纵向为y轴，以下为正。

#include <string>
#include <vector> //c++的vector相当于java的arraylist
const int UP=0;
const int DOWN=1;
const int LEFT=2;
const int RIGHT=3;

int object_cnt=0;

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
        Position(Position &pos){
            x=pos.x;
            y=pos.y;
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
            x=pos.x;
            y=pos.y;
        }

        
};

//所有可移动的东西，包括箱子，人的父类
class Object{
    private:

    public:
        static const int FLAG_PLAYER=0;
        static const int FLAG_BOX_NORMAL=1;
        static const int FLAG_BOX_INNER=2;
        
        //flag变量指示该物体的类型
        int flag;
        int id;
        Position pos;

        Object(int x, int y,int flag);
        Object(Position &pos,int flag);

        ~Object();

        void setPosition(int x, int y);
        void setPosition(Position &pos);

};

//InnerBox和普通箱子的区别在于，多了一个入口和内部空间，内部空间即为gridboard

class InnerBox:public Object{
    private:
        
    public :
        int entrance;
        GridBoard *inner_space;
        
        InnerBox(int x, int y,int flag ,int id, int entrance, GridBoard *inner_space);
        InnerBox(Position &pos,int flag ,int id, int entrance, GridBoard *inner_space);

        ~InnerBox();
};


class Grid{
    private:        

    public:
        //如有需要可修改或添加新的常量
        static const int TYPE_EMPTY=0;
        static const int TYPE_WALL=1;
        static const int TYPE_STORAGE_POINT=2;
        static const int TYPE_CHECK_POINT=3;

        //type变量表示该地块的原生类型，object变量表示处于该地块上的可移动物体，如player和box。之所以不合并在type里是为了便于后续拓展复杂的规则。
        int type;
        Object *object;

        Grid();
        Grid(int type);
        Grid(int type, Object *object);

        void loadObject(Object *object);
        void unloadObject();

};

//GridBoard不需要检测操作是否合法
class GridBoard{
    private:
        //gamemode用来表示当前所采用的规则,
        
    public:
        static const int GAMEMODE_CLASSIC=0;
        static const int GMAEMODE_INNER_BOX=1;

        int gamemode;
        int sizeX;
        int sizeY;
        
        Object player;
        std::vector<Object> boxes;
        //类似向量计算那一题中的data，维护cnt表示引用次数，来判断是否需要释放。
        int cnt;
        GridBoard():GridBoard(5,5,0,0,GridBoard::GAMEMODE_CLASSIC){

        }

        //todo:初始化函数，sizeX,sizeY指的是board的尺寸，pX,pY指的是玩家的初始位置。 需要初始化grid_board，默认每个grid为empty
        GridBoard(int sizeX, int sizeY, int pX, int pY,int gamemode);
        
        //todo：path为本地GridBoard文件的路径，从该文件中加载gridboard,若文件损坏，应有适当标志
        GridBoard(std::string &path);
        
        //todo:解构函数，用来释放内存
        ~GridBoard(); 

        //todo:返回指定位置的grid的
        Grid* getGrid(int x, int y);
        Grid* getGrid(Position &pos);

        //todo:设置grid的type
        void setGridType(int x, int y, int type);
        void setGridType(Position &pos, int type);

        //todo:添加一个可移动物体到棋盘上，执行成功则返回true,否则返回false
        bool addObject(Object &object, Position &pos);

        //todo:将可移动物体移动到pos上,执行成功则返回true,否则返回false
        bool moveObject(Object &object, Position &pos);
        
        //todo:将object从gridboard中删除
        bool removeObject(Object &object);

        //todo：保存当前GridBoard为本地文件,path为文件路径
        //注意：innerbox的信息也要保存
        void save(std::string &path);

        //当gridboard被挂载或卸载时，应调用load或unload函数，当引用次数减为0时，gridboard应该被释放
        void load();
        void unload();

        //若当前棋盘为有效的，可用的棋盘，则返回true
        bool isValid();

};

class GameHandler{
    private:

    public:
        GridBoard *gridboard;
        std::vector<int> cmds;

        GameHandler();
        //todo: board为初始棋盘
        GameHandler(GridBoard *board);

        //todo：path为本地文件夹的路径，从该文件夹中加载游戏进度,若文件损坏，应有适当标志
        GameHandler(std::string &path);

        //todo:解构函数，释放相关内存
        ~GameHandler();

        //todo:判断游戏是否胜利
        bool isWin();

        //todo:在当前gamemode下，判断能否朝指定方向移动，若可以，则移动并返回true，若不行，则不进行任何操作，返回false
        //hint:若mode为inner_box, 将gridboard替换成inner_box所保存的gridboard即可视为进入了该inner_box
        bool moveUp();
        bool moveDown();
        bool moveLeft();
        bool moveRight();

        //todo:当n为正数时，将当前棋局设置为第n步的状态，当n为负数时，表示悔棋n步。执行成功则返回true，否则返回false
        bool stepTo(int n);

        //todo：保存当前游戏进度为本地文件，可以分为多个文件保存（如gridboard和instructors分开存），path为文件夹路径
        void save(std::string &path);

        //若当前游戏为有效的，可用的棋盘，则返回true
        bool isValid();
};