
//五一礼物巧克力 (特殊force,force,dodge,parry)各加1级


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "五一巧克力" NOR, ({ "qiao keli", "chocolate" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "五一巧克力，几项技能加一级。\n" NOR);
                set("unit", "块");
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
        {
                add_action("do_eat","eat");
        }
                

int do_eat( string arg )
{       
        if (arg == "qiao keli" || arg == "chocolate" )

        {
         string mapsk;   
         object me;
        
         me = this_player();

        if ( me->query("liwu/wuyi2005/eat") )
        {write(HIR"今年的五一你已经吃过礼物了呀！\n"NOR);return 1;}

        message_vision(HIY "$N将巧克力一口吞了，“哈喇子”顺着嘴角就流了出来，\n" +
                                "还一个劲儿连说:“味道好极了哟，还有吗？再来一个!\n" NOR, me);

         log_file("static/wuyi", sprintf("%s(%s) eat 巧克力 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        me->set("liwu/wuyi2005/eat", 1);

         me->add("combat_exp", 50000);
         mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                destruct(this_object());
                return 1;
        }
else {  return 0;}
}
                
