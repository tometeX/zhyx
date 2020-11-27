//update by xiner

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
	set_name(BLK"玄武"HIW"披风"NOR,({"xuanwu coat","coat"}));
	set_weight(1500);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","件");
		set("long",HIW"这是一件带有玄武图腾的披风。"NOR"
套装效果："HIW"玄武套装拥有最强的防御能力。"NOR"\n");
		set("value",200000);
		set("material","feather");
		set("armor_prop/armor", 50 + random(100));
		set("armor_prop/parry", 20 + random(20));
		set("armor_prop/dodge", 20 + random(20));
		set("no_sell",1);
		set("no_steal",1);
	}
	setup();
}

int query_autoload()
{
	return 1;
}