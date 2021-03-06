//Room: gaotai.c 南岩宫高台
//Date: Sep 29 1997
//Modified by haiyan

#include <ansi.h>
inherit ROOM;

string *zhen = ({
"你手持$w，前进中一阵急骤，手中$w劈空猛然刺出。\n", 
"你着地一滚，手中$w向上斜斜刺出。\n",  
"你反手握住$w，化出一道白弧，手中$w铮铮作响。\n", 
"你向前一纵，略退半步，突然一个急进，手中$w直刺过去。\n", 
"你与$w合而为一，飞身而起，人剑合一，向下疾刺。\n", 
"你左手捻一个剑诀，手中$w忽而向下刺出。\n",  
"你纵身一跃，手中$w叮叮作响，唰唰唰连刺三剑。\n",  
"你手中$w疾挥，划出道道剑光，身形一转，手中$w向后刺出。\n" 
}); 

int do_caoyan(); 
int do_exit(); 
int caoyan(object me); 
int halt_caoyan(object me); 

void create()
{
      set("short","南岩宫高台");
      set("long",@LONG
这里是就是南岩宫高台。高台孤悬崖侧，四望临渊，深不可测。山风夹
耳，松清涤面，顿觉心窍大开。
    武当真武剑阵就在这里。真武剑阵由五名五行弟子按东西南北中的木、
金、火、水、土方位，八名八卦弟子按乾、坤、坎、离、巽、震、艮、兑八
方天、地、水、火、风、雷、山、泽排列。
LONG);
      set("objects", ([
           CLASS_D("wudang") +"/wuxing": 5,
           CLASS_D("wudang") +"/bagua": 8,
           CLASS_D("wudang") +"/yan": 1,
      ]));
      set("exits",([ /* sizeof() == 1 */
          "northdown" : __DIR__"nanyangong",
      ]));
      set("outdoors", "wudang");
      setup();
}

void init()   
{  
      add_action("do_caoyan", "caoyan");
      add_action("do_exit", "quit");
      add_action("do_exit", "exit");
}   

int do_caoyan() 
{
     object me, weapon; 
     me = this_player(); 
     weapon = me->query_temp("weapon"); 
     if (!me->query_temp("lianzhen")) 
        return notify_fail("俞岱岩伸手拦住你：“你是不是想试试剑阵的威力？”\n");

     if (me->query_temp("lianzhen") > 1) 
        return notify_fail("你不是正在练嘛！\n");

     if (!objectp(weapon) || (string)weapon->query("skill_type") != "sword") 
        return notify_fail("你手中无剑，怎么练剑阵？\n"); 

     me->add_temp("lianzhen", 1);
     message_vision("$N将手中" + weapon->name() + "一抖，纵身跃入剑阵，开始操演阵法。\n", me); 
     me->set_short_desc("手执" + weapon->name() + "，正在操演真武剑阵。"); 
     me->start_busy((:call_other, __FILE__, "caoyan" :), 
                    (:call_other, __FILE__, "halt_caoyan" :)); 
     return 1; 
}

int caoyan(object me) 
{ 
    string msg; 
    object weapon; 
    int i, lvl; 

    weapon = me->query_temp("weapon");
    lvl = me->query_skill("zhenwu-array");

    if (!objectp(weapon) || (string)weapon->query("skill_type") != "sword")
    {
       halt_caoyan(me); 
       return 0;
    }
    for( i = 0; i <= 8; i++ ) 
    {
        if (random(10) == 0) 
        {  
            msg = zhen[random(sizeof(zhen))]; 
            msg = replace_string(msg,"$w",weapon->name()); 
            write(msg); 
        } 
    }
    if (me->can_improve_skill("zhenwu-array")) 
       me->improve_skill("zhenwu-array", 500); 
    return 1; 
} 

int halt_caoyan(object me) 
{ 
    object ob, weapon;
    ob = present("yu daiyan"); 
    weapon = me->query_temp("weapon"); 
    message_vision( HIY "$N" HIY "将手中" + weapon->name() +  
                    HIY "一荡，跃出了剑阵。抱拳道：在下有事在身，先行告退。\n" NOR, me); 
    tell_object(me, "你中止了操演。\n");  
    me->delete_temp("lianzhen"); 
    me->set_short_desc(0); 
    ob->add_temp("count", -1);
    return 1; 
} 

int valid_leave(object me, string dir)  
{  
    if (objectp(present("yu daiyan", environment(me))) && 
        dir == "northdown" && me->query_temp("lianzhen"))
            return notify_fail("俞岱岩一把拦住你：“好好在这操演阵法，不要乱跑。”\n"); 
    return ::valid_leave(me, dir); 
}  

int do_exit() 
{
     object me; 
     me = this_player(); 
     if (me->query_temp("lianzhen")) 
     {
        tell_object(me, "你必须操演结束后才能离开。\n");  
        return 1;
     }
     return 0; 
}

