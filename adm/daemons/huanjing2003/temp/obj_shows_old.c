//                标准描述长度示例                                   |
// 游戏内简易说明手册
// by naihe  2002-11-05  于茂名

inherit ITEM;

void create()
{
    set_name("「幻境·遥远传说之起缘」·玩家手册", ({"shou ce","ce"}));
    set_weight(10);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "这是一小本关于“幻境”游戏的玩家说明手册，你可以看看它的说明(shuoming)。\n");
        set("unit", "本");
        set("value", 0);
    }

    setup();
}

void init()
{
    add_action("do_shuoming","shuoming");
}

int do_shuoming(string arg)
{
    if(!arg) return notify_fail("你可以输入页数或类型来阅读这些说明。

第1页：背景及主线任务 <shuoming beijing>
第2页：游戏进程及指令 <shuoming zhiling>
第3页：支线任务简介   <shuoming zhixian>
第4页：战斗系统及相关 <shuoming zhandou>
第5页：各类NPC 简介   <shuoming npc>
第6页：各类道具简介   <shuoming daoju>
第7页：游戏内地图     <shuoming ditu> 或 <shuoming map>
第8页：最后的说明     <shuoming zuihou> 或 <shuoming last>

祝游戏愉快！ :) \n");

    if(arg == "1" || arg == "beijing")
    {
write("***************************************************************

幻境 · 遥远传说之起缘 · 剧情及主线任务介绍

    在此之前的一个未知的遥远年代，这大地上寂寞荒凉，除了仅有人
烟的四个国家，分驻在这大地的四方。它们有着各自的繁华、能力及令
人艳羡的宝物，一直都各自安居乐业，大地上平静而快乐着。

    但是终于有一天，它们之间爆发了战争，战争由宝物而起，我们却
无从知晓那根本的因缘……四个国家由于战争而消亡了，而它们的宝物，
也消散在这茫茫的大地之上。\n");
write("
    时光变迁，这四个国度不复存在；终于，到了你与我生存的年代。
一个偶尔的机会，你来到了神秘的“迷失之宝物隐匿之林”，传说这里
隐匿着那遥远年代时的四个国度的宝物，那些曾维持着它们在那荒凉土
地上安居的宝物，而又让它们因此而消亡的宝物……你渴望在这片渺无
边际的密林里寻得它们，以求能够得到它们所予你的启示，重见那已逝
的古老国度的神秘之光。

***************************************************************\n");
return 1; }

    if(arg == "2" || arg == "zhiling")
    {
write("***************************************************************
幻境 · 遥远传说之起缘 · 游戏进程、操作及各类介绍
    每一个进入幻境游戏的玩家，都会得到一个物品：七星灯。它不
允许丢弃或给别人，并且你所有的游戏内指令，都由它支持。

    你先要选择一个国度来进入游戏，每个国度的宝物不同。而它们都是
被分成了三个部分了的，你要一一找到，然后组合起来，才能够得到真正
的、完整的宝物。宝物的其中两部分散落在随机的各处，而最重要的一部
分在一个属于你的臣民(chen min)身上。你向他打听宝物的名字就知道了。\n");

write("
    游戏里以得分为主要目标。成功寻得属于自己的那件宝物会有3000分
的加分。与怪物战斗、解答各类游戏迷题、拾取各类游戏宝物，都是得
分的手段。但是如果你的气息已被攻击至零（无论是被玩家攻击或怪物
攻击），再多的游戏得分，也将全部作废，而要被迫退出游戏。
    游戏内操作指令十分简单，常规指令只有4个：
gk(或gkill)        game kill   之意，游戏内常规攻击指令
gsks(或gskills)    game skills 之意，游戏内常规技能指令");

write("
ghp                game hp     之意，游戏内查询气息指令
gheal              game heal   之意，游戏内恢复气息指令
    另外有1个特殊指令：
debug         用此指令，可以随时把你所遇到的有bug的物品
                  传送给开发巫师，以寻求更高效率的解决
在游戏内，可以随时用 help huanjing 指令，查询更明确的指令介绍。
***************************************************************\n");
return 1; }

    if(arg == "3" || arg == "zhixian")
    {
write("****************************************************************

幻境 · 遥远传说之起缘 · 支线任务详解

    在 幻境·遥远传说之起缘 里面，有一个十分重要的得分途径，这就
是支线任务。任务成功可获得游戏得分。

    支线任务之一：迷路孩童

    你只需要答应迷路的孩童<answer ok>，然后带她到相应的房间即可。
任务限制为 3 分钟。需要注意的是，不成功时会扣除你的游戏得分。\n");

write("
    支线任务之二：知识老人

    你同意接受问题之后 <huida 好> ，老人就会问你随机的问题，类型
都一样，是关于四个英雄的名字，而他给出一个特定的条件，你将根据条
件判断，应该选择来回答的是哪一个。回答问题失败、不回答、甚至逃跑，
你都会有相当长的忙时（基本上，够让一个普通NPC把你打死的了）。

****************************************************************\n");
return 1; }

    if( arg == "4" || arg == "zhandou")
    {
write("****************************************************************

幻境 · 遥远传说之起缘 · 战斗系统、怪物、力量气息及技能介绍

    在 幻境·遥远传说之起缘 里，战斗系统与我们习惯的方式不同。

1、每攻击一次，需要输入一次指令，并且会有忙时
2、你可以使用各种剑、或魔法水晶来辅助攻击 <gk 某人 with 道具>
3、你可以使用各种自身所会的技能来辅助攻击 <gk 某人 use 技能>
4、空手攻击：      <gk 某人>    恢复自身气息：<gheal> 
   恢复别人的气息：<gheal 某人> 准备常用技能：<gsks bei 技能>
   使用常用技能攻击： <gk 某人 !>\n");

write("
    游戏里的 力量 值十分重要，你的任何攻击行为，和它都有直接的
联系。但这是一项隐藏的数值，你无法知道具体它已经有多高。力量可
以空手攻击别人、使用特殊物品、或其他特殊方法得到提高。无上限。

    并非所有的NPC都准许攻击，请参看后文介绍。

****************************************************************\n");
return 1; }

    if( arg == "5" || arg == "npc")
    {
write("****************************************************************
幻境 · 遥远传说之起缘 · 非玩家操作类人物(NPC)介绍

    1、自己的NPC
    每个进入游戏的玩家都会对应一个不同的特殊npc，即臣民(chen min)。
他身上带着你要找的宝物的最重要的那部分，你要向他打听宝物的名字，
才能知道下一步该怎么做。一定的时间到达后（大概半个小时）他就会
消失，这样的话你只能靠特殊道具：召唤之盒，才有可能重新把他召来。
另外的两部分宝物，通过特殊道具：祈祷之石，也有机会获得。\n");

write("
    2、杀戮型NPC
    允许玩家攻击。不同等级的这类型NPC的攻击力不同，速度不同，气
息也不不同。攻击NPC能够得到游戏里的得分，杀死它们还有可能得到一
些很好的道具。但是若被它们攻击的话，将会损失你的游戏得分。

    3、小精灵
    游戏的奖励型NPC，有各种类型，能够随机予你不同的帮助。\n");

write("
    4、特殊类型
    小矮人，十分神秘的家伙……可以攻击。
    炼力老人，能够提升你在游戏里的力量！
    精灵商贩，可以向他购买一些道具。购买道具时，如果你身上没有
宝石，那么价格会是原价的两倍。

    除了本人NPC之外，所有的NPC都是随意移动的。
****************************************************************\n");
return 1; }

    if(arg == "6" || arg == "daoju")
    {
write("****************************************************************
幻境 · 遥远传说之起缘 · 各类道具使用详解
1、工具类道具
    定向水晶    可让你知道自己身在何方，误差 +-1
    飞翔水晶    可让你瞬间移动至某编号之房间，误差 +-1
    脱离水晶    奈何的至爱之一，逃命必不可少之道具，无忙时使用限制
    回归之镜    立刻退出游戏，得分有效（进入游戏时间太短时无法使用）
    祈祷之石    祈祷随机道具类物件，有机会获得属于自己的宝物的部分
    召唤之盒    召唤随机NPC类物件，有机会召来属于自己的NPC
    发呆之旗    相当搞笑的道具之一，热爱PK者必不可少
    驱逐之旗    相当搞笑的道具之一，也是奈何在这游戏里的至爱道具
    寻人水晶    输入玩家的ID，你可以知道他在哪个房间里
    窥探水晶    可以随机知道别人身上带着某样游戏内道具\n");
write("2、武器类道具 <gk 某人 with 道具>  时使用的道具
    各类剑  及 各类水晶  ，具体效果略
3、果品类道具
    各类常规果品  补充玩家在幻境里的气息
    试炼之果      可能增加力量或最大气息，也可能降低它们\n");
write("4、神秘石类道具
    领会 <linghui> 它们，可以让你学会技能或技能提升。
5、其他特殊类道具
     用途神秘，不一一介绍。
****************************************************************\n");
return 1; }

    if(arg=="7" || arg=="ditu" || arg=="map")
    {
write("****************************************************************

幻境 · 遥远传说之起缘 · 游戏地图(房间标记号)


         1   2   3   4   5   6   7   8   9   10

         11  12  13  14  15  16  17  18  19  20

         21  22  23  24  25  26  27  28  29  30

         31  32  33  34  35  36  37  38  39  40

         41  42  43  44  45  46  47  48  49  50

   允许横、竖、斜走。方向为 上北下南左西右东 。

****************************************************************\n");
return 1; }

    if(arg == "8" || arg=="zuihou" || arg=="last")
    {
write("****************************************************************

幻境 · 遥远传说之起缘 · 使用手册之最后说明

    本游戏由 神州巫师 奈何(naihe) 开发。如有建议或意见，
请 EMAIL TO :  lovesb@21cn.com  奈何 收，或在 神州 内
与奈何面谈。

    若想得到更详细的游戏介绍，或是感受奈何行事说话的作
风，请在 神州 内阅读新闻： 129 130 132 134 。

    游戏的奖励以 游戏内房间【回归现实之路】里公布的为准。

    奈何(naihe)   2002-11-05 于广东茂名

****************************************************************\n");
return 1; }

    write("输入有误。请直接输入 <shuoming> 查正再试。\n");
    return 1;
}
