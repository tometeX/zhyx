#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIY"光明顶大门"NOR);
        set("long",  "\n"
"这里是明教光明顶大门，由此上去便是通向"HIY"明教光明顶。\n"NOR 
 );
        set("exits",([
           "out" : "/d/wizard/skybook",
        ]));
        set("objects",([
        ]));
        setup();

}

void init()
{       mapping mine;
       object me;
        me = this_player();
        if ( me->query("skybook/tulong/tulongdao") > 0
        &&    me->query("skybook/tulong/winguangming") < 1)
        {
         message_sort(HIR"眼看六大门派已经攻上光明顶，明教万千教众生死存亡就在此\n"NOR
                        HIR"时，你愿意此时此刻挽救"HIW"(wanjiu)"HIR"明教于危难之中吗？\n"NOR, me);
        add_action("do_wanjiu", "wanjiu");
        }
}
int do_wanjiu()
{
    object me = this_player(), where = environment(me);

            if ( where->query_temp("temp/guangmingding", 1))
    {
       message_vision("别人正杀得过瘾呢，你还是等等吧。\n",me);
       return 1;
    }
        message_vision(HIC "\n$N" HIC "纵身一跃，飞上了光明顶顶峰，\n"
                       "只见明教弟子伤亡惨重，六大门派\n"
                       "一见到""$N""，便一齐向你围攻过来！"
                       "\n\n" NOR, me);
          where->set_temp("temp/guangmingding", 1);
        me->move(__DIR__"ding");

        me->start_busy(3); 

        return 1;
}

