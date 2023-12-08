# C-Final-Project-Sokuban
Sokuban.h定义了类原型，函数原型，以及若干常量。具体每个类的实现应单独分为一个文件。
代码风格（类似PEP8，python的规范代码风格）：
        1)变量命名：
                  任何变量的名字应该具有含义。常量采用全大写加下划线分隔，如：const int GAMEMODE_CLASSIC=0。 类名采用首字母大写分隔，如class GameHandler, 方法名为第一个单词小写，后续单词首字母大写，如moveUp, loadMap。其他变量为全小写加下划线分隔，如img_player。
        2)采用缩进：
                  为了便于查看各代码块的层级关系，应采用缩进。且，左花括号'{'紧跟在提出代码块的语句之后，不单独成行，右花括号单独成行，缩进与提出该代码块的语句相同。如：
                  if(xxx){
                      do aaaa;
                  }else{
                      for(int i=0;i<n;i++){
                           do bbb;
                      }
                  }
        3)一行一句：
                  以';'号视为一句，一行至多存在一句代码。如：int a=10;long b=100; 应分2行书写
