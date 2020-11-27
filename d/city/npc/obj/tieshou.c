// tieshou.c

#include <armor.h>

inherit HANDS;

void create()
{
	set_name( "铁手掌", ({ "iron hand", "hand" }) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "steel");
		set("unit", "块");
		set("long", "这是一块铁质的手掌形护具，用以保护手掌。\n");
		set("value", 900);
		set("armor_prop/armor", 5 );
              set("armor_prop/hand", 10);              
              set("armor_prop/unarmed_damage", 10); 
              set("armor_prop/strike", 10); 
	}
	setup();
}
