
#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIM "神兵卡" NOR, ({ "weapon card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "凭此卡可去天神处换取十级兵器一把。\n"NOR);			
                set("unit", "张");
                set("value", 100000000);
                set("weight", 10);
                set("material", "paper");	
                set("no_sell",1);	  		  
             }	         
        setup();
}

int query_autoload() 
     { return 1; } 
		
