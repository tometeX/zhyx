
//春节礼包 打开后为无花果一粒或潜能药丸一个(加10万潜能)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "春节礼包" NOR, ({ "libao", "bag" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "赶快open libao看看你会得到什么吧。\n" NOR);
                set("unit", "个");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
{       
     add_action("do_open","open");     
}
                
int do_open( string arg )
{       object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "libao" &&
             arg != "bag") )
        return 0;

        message_vision(HIW "$N" HIW "将春节礼包打了开来。\n" NOR, me);

        if (random(3) == 1)
        {
           tell_object(me, HIG"恭喜你获得了一eat guo。\n\n"NOR); 
        }
        write(HIG"你指定了要获得" + arg + "的属性，现在请eat guo。\n\n"NOR); 
        return 1;    
}

