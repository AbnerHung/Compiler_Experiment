【问题描述】

注：词法分析和语法分析实验都针对此文法，语法分析实验需在词法分析实验的基础上进行增量式开发。



【文法定义】:

＜标识符＞::=＜字母＞｛＜字母＞｜＜数字＞｝     //标识符和关键字都不区分大小写，比如if和IF均为关键字，不允许出现与关键字相同的标识符

＜字母＞::=＿｜a｜．．．｜z｜A｜．．．｜Z  

＜数字＞::=０｜１｜．．．｜９  

＜整数＞::=［＋｜－］＜无符号整数＞

＜无符号整数＞::=＜数字＞｛＜数字＞｝

＜字符＞::='＜加法运算符＞'｜'＜乘法运算符＞'｜'＜字母＞'｜'＜数字＞'  

＜加法运算符＞::=+｜- 

＜乘法运算符＞::=*｜/ 

＜字符串＞::="｛十进制编码为32,33,35-126的ASCII字符｝"         //字符串中要求至少有一个字符





【问题描述】

请根据给定的文法设计并实现词法分析程序，从源程序中识别出单词，记录其单词类别和单词值，输入输出及处理要求如下：

   （1）数据结构和与语法分析程序的接口请自行定义；类别码需按下表格式统一定义；

   （2）为了方便进行自动评测，输入的被编译源文件统一命名为testfile.txt（注意不要写错文件名）；输出的结果文件统一命名为output.txt（注意不要写错文件名），结果文件中每行按如下方式组织：

单词类别码 单词的字符/字符串形式(中间仅用一个空格间隔)

单词的类别码请统一按如下形式定义：

单词名称

类别码

单词名称

类别码

单词名称

类别码

单词名称

类别码

标识符

IDENFR

if

IFTK

-

MINU

= 

ASSIGN

整数

INTCON

else

ELSETK

*

MULT

;

SEMICN

字符

CHARCON

do

DOTK

/

DIV

,

COMMA

字符串

STRCON

while

WHILETK

< 

LSS

(

LPARENT

const

CONSTTK

for

FORTK

<=

LEQ

)

RPARENT

int

INTTK

scanf

SCANFTK

> 

GRE

[

LBRACK

char

CHARTK

printf

PRINTFTK

>=

GEQ

]

RBRACK

void

VOIDTK

return

RETURNTK

== 

EQL

{

LBRACE

main

MAINTK

+

PLUS

!= 

NEQ

}

RBRACE



【输入形式】testfile.txt中的符合文法要求的测试程序。
【输出形式】要求将词法分析结果输出至output.txt中。

【特别提醒】

（1）读取的字符串要原样保留着便于输出，特别是数字，这里输出的并不是真正的单词值，其实是读入的字符串，单词值需另行记录。

（2）本次作业只考核对正确程序的处理，但需要为今后可能出现的错误情况预留接口。

（3）在今后的错误处理作业中，需要输出错误的行号，在词法分析的时候注意记录该信息。

（4）单词的类别和单词值以及其他关注的信息，在词法分析阶段获取后，后续的分析阶段会使用，请注意记录；当前要求的输出只是为了便于评测，完成编译器中无需出现这些信息，请设计为方便打开/关闭这些输出的方案。

【样例输入】

const int const1 = 1, const2 = -100;
const char const3 = '_';
int change1;
char change3;
int gets1(int var1,int var2){
    change1 = var1 + var2;
    return (change1);
}
void main(){
    printf("Hello World");
    printf(gets1(10, 20));
}
【样例输出】

CONSTTK const
INTTK int
IDENFR const1
ASSIGN =
INTCON 1
COMMA ,
IDENFR const2
ASSIGN =
MINU -
INTCON 100
SEMICN ;
CONSTTK const
CHARTK char
IDENFR const3
ASSIGN =
CHARCON _
SEMICN ;
INTTK int
IDENFR change1
SEMICN ;
CHARTK char
IDENFR change3
SEMICN ;
INTTK int
IDENFR gets1
LPARENT (
INTTK int
IDENFR var1
COMMA ,
INTTK int
IDENFR var2
RPARENT )
LBRACE {
IDENFR change1
ASSIGN =
IDENFR var1
PLUS +
IDENFR var2
SEMICN ;
RETURNTK return
LPARENT (
IDENFR change1
RPARENT )
SEMICN ;
RBRACE }
VOIDTK void
MAINTK main
LPARENT (
RPARENT )
LBRACE {
PRINTFTK printf
LPARENT (
STRCON Hello World
RPARENT )
SEMICN ;
PRINTFTK printf
LPARENT (
IDENFR gets1
LPARENT (
INTCON 10
COMMA ,
INTCON 20
RPARENT )
RPARENT )
SEMICN ;
RBRACE }
【评分标准】 按与预期结果不一致的项数（每一行单词信息算一项）扣分，每项扣1%。
