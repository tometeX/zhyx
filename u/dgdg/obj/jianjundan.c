
//八一建军丹(加30万潜能)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "建军丹" NOR, ({ "jianjun dan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "六狼大神为庆祝八一建军节发放的礼物，有什么功能呢？吃吃看哦。\n" NOR);
                set("unit", "个");
                set("value", 10);
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
{       object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "jianjun dan" &&
             arg != "dan") )
        return 0;
        


        message_vision(HIW "$N" HIW "将巧克力一口吞了。\n" NOR, me);
        me->add("combat_exp", 300000);
        me->add("potential",300000);
        me->improve_neili(500); 
        me->improve_skill("martial-cognize", 1500000); 	   	    

        tell_object(me, HIG"恭喜你增加了三十万点经验和潜能，内力获得了提升，武学修养获得了提升。"
                    "希望你再接再厉！\n"NOR);

        destruct(this_object());
        return 1;    
}

