//update by xiner

#include <ansi.h>
#include <armor.h>
inherit BOOTS;

void create()
{
	set_name(HIW"白虎战靴"NOR,({"tiger shoes","shoes","xie"}));
	set_weight(1200);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("long",GRN"这是一双布满诡异鳞片的鞋子。"NOR"
套装效果："HIW"临时增加空手伤害二百点。"NOR"\n");
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