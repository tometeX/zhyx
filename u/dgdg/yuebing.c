
//火腿月饼(加50万潜能)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "火腿月饼" NOR, ({ "huotui yuebing", "bing" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "六狼大神为庆祝中秋、国庆节发放的月饼，愿大家心想事成。\n" NOR);
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
        
        if ( ! arg || (arg != "huotui yuebing" &&
             arg != "bing") )
        return 0;
        


        message_vision(HIW "$N" HIW "将月饼三口两口咬完吞下。\n" NOR, me);
        me->add("combat_exp", 500000);
        me->add("potential",500000);
        me->improve_neili(500); 
        me->improve_skill("martial-cognize", 1500000); 	   	    

        tell_object(me, HIG"恭喜你增加了五十万点经验和潜能，内力获得了提升，武学修养获得了提升。"
                    "恭祝你中秋、国庆愉快！\n"NOR);

        destruct(this_object());
        return 1;    
}

