//update by xiner
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name( HIW"白虎战甲"NOR, ({ "tiger armor","armor","jia" }) );
	set_weight(1500);
	if( clonep() )
	set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("long", HIW"一张投射着奇异光芒的战甲。"NOR"
套装效果："HIW"临时增加空手伤害二百点。"NOR"\n");
		set("value", 150000);
		set("material", "feather");
		set("armor_prop/armor", 100 + random(100));
		set("armor_prop/dodge", 20 + random(50));
                set("armor_prop/parry", 20 + random(50));
		set("warm_cloth", 1);
		set("no_sell", 1 );
		set("no_steal", 1 );
	}
	setup();
}

int query_autoload()
{
	return 1;
}