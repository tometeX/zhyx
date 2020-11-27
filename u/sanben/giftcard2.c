
#include <ansi.h>
 
inherit ITEM;

int is_head() { return 1; }

void create()
{
        set_name(HIW "银卡兑奖劵" NOR, ({ "silver card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "凭这张银卡可以在武庙的浪翻云那里兑换五点奖励点数。\n"NOR);			
                set("unit", "张");
                set("value", 10);
                set("gft_pt",5);
                set("weight", 1);
                set("material", "paper");		  		  
             }	         
        setup();
}

void init()
{
     remove_call_out("dest");
     call_out("dest", 600);     

}

void dest()
{
     tell_room(environment(), HIR"奖劵突然不见了。\n"NOR);
     destruct(this_object());

}
