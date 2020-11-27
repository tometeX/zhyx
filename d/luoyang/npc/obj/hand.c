// jinshou.c

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
	set_name( HIY "黄金手掌" NOR, ({ "gold hand", "hand" }) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "steel");
		set("unit", "块");
		set("long", "这是一块黄金制成的掌套，可以加强手法和掌法的伤害力。\n");
		set("value", 50000);
              set("armor_prop/hand", 80);              
              set("armor_prop/unarmed_damage", 80); 
              set("armor_prop/strike", 80); 	
            }
	setup();
}
void owner_is_killed()
{
        destruct(this_object());
} 
int query_autoload() { return 1; }


