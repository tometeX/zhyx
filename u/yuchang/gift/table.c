#include <ansi.h>
#define LAST_PAR "sorry"
#define THIS_PAR "sorrysf"
inherit ITEM;
void create()
{
    set_name("茶几", ({ "table"}));
    set_weight(5000000);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "张");
        set("no_get","这个茶几是大家聊天用的，你好意思搬走？");
        set("long","一张小巧玲珑的茶几，上面放满了大家的礼物，大家快拿礼物(pick gift)啊！");
        set("value", 0);
        set("material", "stone");
    }
}
void init()
{
    add_action("do_pick", "pick");
}
 
int do_pick(string arg)
{
       object me,obj;
       me = this_player();
       if( !arg || arg!="gift" ) return notify_fail("你要拿什么？\n");


       if (me->query(THIS_PAR + "_pick")) {
tell_object(me,CYN "浪翻云突然出现在一阵烟雾之中。\n\n");	
tell_object(me,HIR "在你的手上轻轻一敲：每人只有一份礼物的哦~！\n\n");
tell_object(me,CYN "只见一阵烟雾过後，浪翻云已经不见了。\n" NOR)	;
       return 1;
       }
      obj = new (__DIR__"gift");
       obj->move(me);
       message_vision("$N从石桌上拿起一件礼物包。\n",me );
//每次拣礼物，都将上次的参数消除，增加本次拿的参数。 
       me->delete(LAST_PAR + "_pick");
       me->set(THIS_PAR + "_pick",1);
       me->start_busy(2);
       return 1;
}

