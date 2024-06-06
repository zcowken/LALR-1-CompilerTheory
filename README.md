设计文档

读入模块
Z -> a|Xgg|Y
会分解为
Z -> a
Z -> Xgg
Z -> Y

### 文法（production）存储结构

left 左部编号
right 右部数组

### 所有的文法左部（冗余段）

#### 文法的索引 ：实际上用不上

{文法左部，整体编号}
整体编号：对单个文法整体的编号

#### NullAble 空集合的计算

一个集合，如果在这个集合中的左部，不可以为空，是否可以为空

#### fist 集合结构

二维表
纵索引-文法整体的编号
横索引-无，直接存放 first 集合本身

#### follow 集合结构

二维表
纵索引-文法整体的编号
横索引-无，直接存放 follow 集合本身

#### 分割后的文法索引表--二级索引表

一级，文法 left
二级，文法右部
结果-顺序编号 i
直接存放分割后的文法右部的索引

#### first_s 集合

计算 first_s 的集合需要计算 follow 和 frist
由分割后的文法编号分类，然后由两类集合推演而来

### LR1 的 DFA 的构造

![image-20240603133256303](README.assets/image-20240603133256303.png)

### 获取任意的 select 集合

- betas：文法右部分（分割后）
- pos，当前走到右部的位置
- a，移进到当前文法的的文法的 first 集合
- left，文法左部
  \*/
  如果 β 中的所有元素可以为空，那么加入 a 集合，如果没有，那就是直接返回

### LR1 的 DFA 存储

DFA 表项是 int 编号
DFA 表项的内容：
int 编号
vector 的块数据的数据类型
一块含有的信息
int，文法的指针，指向 productions 的一个 int 位置
pos，当前走到该文法的那个位置
select，集合存放下一个可能位的符号集合，

#### DFA 表项的索引是 DFA 表项的编号

需要建立访问的索引

#### DFA 图的存储，二级索引广义表

第一个索引，DFA 表项的编号
第二个索引，string，下一个字符串，走哪一个字符
索引结果：下一个 DFA 的编号

#### DFA 表项的建立

读入开始文法，开始文法的下一个文法如果是非终结符，一会要对该终结符展开判断
然后建立当前文法的 select 集合，开始的时候，S'的 select 集合计算的时候，βa 中，a 是空的，表项中开始的第一个块，他的 select 继承移进产生他的 select

#### LALR 合并算法

从第一个项目开始，寻找所有可以合并的项目（文法的核心一样，认为可以合并，开始进行合并）

记录被选择未可以合并的项目

文法核心一样，后续的推到出的文法也一致，进行合并

合并之后，将所有项目的边关系进行补充，直接将同边的终点合并，使用 items 的 simply 函数进行化简

定义递归函数，
接受 dfaItem 的编号一共两个，
如果有一个是合并过的，返回
将两者进行合并
将 items 添加合并，之后简化，然后记录被合并的 id（大的被合并）
如果合并的 dfaItem 有边，将边到达的终点执行此递归函数

int func(int id1,int id2)
{
if(id1>id2)
{
swap
}

    // 递
    vector<pair<string,int>> edges1;
    vector<pair<string,int>> edges2;

    for(pair<string,int>:DFA[id1])
    {
        edges1.push
    }
    for(pair<string,int>:DFA[id2])
    {
        edges2.push
    }

    for(i in edges1)
    {
        for(j in edges2)
        {
            如果string相同
            递推处理
            int redId = func(i.second,j.second)
            break;
        }
        连接新边
        LALR1[id1][i.first] = retId
    }

    合并，化简
    返回合并后的id1
    hasMerged[id2] = true;
    return id1

}
