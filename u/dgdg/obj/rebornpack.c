//转世奖励礼包


#include <ansi.h>
inherit ITEM;


void create()
{
        set_name(NOR + HIY "转世奖励礼包" NOR, ({ "reborn pack" ,"pack" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这是杨六郎亲自发放的转世奖励礼包，"
                            "这可是限量版的哦。\n");                
                set("no_put", "这样东西不能离开你。\n");
                set("no_sell", "这样东西不能离开你。\n");
        }
        setup();
}

void init()
{
     add_action("do_open","open");    
}

int do_open( string arg )
{
    object me, gift; 
    object where; 


    if ( !arg || arg != "reborn pack")
    return notify_fail("你要打开什么？\n");


    me = this_player(); 
    where = environment(me); 
    gift = new("/clone/fam/max/noname");
    gift->move(me);
    tell_object(me, HIY"恭喜你获得了转世礼物。\n"NOR);  

    destruct(this_object());   
    return 1;

}

