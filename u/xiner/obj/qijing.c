#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIR "四象气劲" NOR, ({ "sixiang qijing", "qijing" }) );
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("base_unit", "丝");
                set("base_weight", 1);
                set("base_value", 0);
//              set("material", "paper");  
                set("long", HIW "无数闪烁不定的光芒，汇成的一束" HIR "四象气劲" HIW "。\n" NOR); 
	    	set("no_put", 1); 
        	set("no_steal", 1); 
//	        set("no_drop", 1); 
	        set("no_get", 1); 

        }
        set_amount(1);
        init_throwing(100);
        setup();
}
