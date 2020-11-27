//update by xiner

#include <ansi.h>
#include <armor.h>
inherit BOOTS;

void create()
{
	set_name(HIR"夔龙之足"NOR,({"seraphim foots","foots","zu"}));
	set_weight(1200);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("long",HIW"《山海经·大荒东经》：“状如牛，苍身而无角，一足，出入水则必有风雨，其光如日月，其声如雷，其名曰夔。”"NOR"
套装效果："HIW"临时增加武器伤害二百点。"NOR"\n");
		set("unit","双");
		set("value",5000);		
		set("material","boots");
		set("armor_prop/armor",30+random(20));
		set("armor_prop/dodge",50+random(20));
		set("no_sell",1);
		set("no_steal",1);
		}
	setup();
}

int query_autoload()
{
	return 1;
}