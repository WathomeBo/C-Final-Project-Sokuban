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

    public:
        int x;
        int y;
        Position(){
            x=0;
            y=0;
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
        static const int FLAG_EMPTY=-1;
        static const int FLAG_PLAYER=0;
        static const int FLAG_BOX_NORMAL=1;
        static const int FLAG_BOX_INNER=2;
        
        //flag变量指示该物体的类型,id可随意设置，写在这里是为了万一以后要用
        int flag;
        int id;
        Position pos;

        Object(){
            flag=Object::FLAG_EMPTY;
            id=-1;
            pos=Position(-1,-1);
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

        bool isNull(){
            return Object::FLAG_EMPTY==this->flag;
        }

};

//InnerBox和普通箱子的区别在于，多了一个入口和内部空间，内部空间即为gridboard

class InnerBox:public Object{
    private:
        
    
    public :
        int entrance;
        GridBoard inner_space;
        
        InnerBox(int x, int y,int flag ,int id, int entrance):Object(x,y,flag,id){
            this->entrance=entrance;
        }

        InnerBox(Position &pos,int flag ,int id, int entrance):Object(pos,flag,id){
            this->entrance=entrance;
        }

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
        Object object;

        Grid(){
            type=Grid::TYPE_EMPTY;
            object=Object();
        }

        Grid(int t){
            type=t;
            object=Object();
        }
        
        Grid(int t, Object &object){
            type=t;
            this->object=object;
        }

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
        
        GridBoard():GridBoard(5,5,0,0,GridBoard::GAMEMODE_CLASSIC){

        }

        //todo:初始化函数，sizeX,sizeY指的是board的尺寸，pX,pY指的是玩家的初始位置。 需要初始化grid_board，默认每个grid为empty
        GridBoard(int sizeX, int sizeY, int pX, int pY,int gamemode);
        
        //todo：path为本地GridBoard文件的路径，从该文件中加载gridboard,若文件损坏，应有适当标志
        GridBoard(std::string &path);

        //todo：拷贝复制一个新的GridBoard
        GridBoard(GridBoard &gridboard);
        
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

        //todo：保存当前GridBoard为本地文件,path为文件路径
        //注意：innerbox的信息也要保存
        void save(std::string &path);

        //若当前棋盘为有效的，可用的棋盘，则返回true
        bool isValid();

};

class GameHandler{
    private:
        

    public:
        //add anything you want
        GameHandler();
        //todo: board为初始棋盘，instructors为初始的命令集，若instructors为nullptr，则表示玩家未进行任何移动
        GameHandler(GridBoard board,std::vector<int> instructors);

        //todo：path为本地文件夹的路径，从该文件夹中加载游戏进度,若文件损坏，应有适当标志
        GameHandler(std::string &path);

        //todo:判断游戏是否胜利
        bool isWin();

        //todo:在当前gamemode下，判断能否朝指定方向移动，若可以，则移动并返回true，若不行，则不进行任何操作，返回false
        //hint:若mode为inner_box, 将gridboard替换成inner_box所保存的gridboard即可视为进入了该inner_box
        bool moveUp();

        bool moveDown();

        bool moveLeft();

        bool moveRight();

        //todo:返回当前的指令集
        std::vector<int> instructors();

        //todo:当n为正数时，将当前棋局设置为第n步的状态，当n为负数时，表示悔棋n步。
        void stepTo(int n);

        //todo：保存当前游戏进度为本地文件，可以分为多个文件保存（如gridboard和instructors分开存），path为文件夹路径
        void save(std::string &path);

        //若当前游戏为有效的，可用的棋盘，则返回true
        bool isValid();
};
