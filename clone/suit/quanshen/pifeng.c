// jinjin pifeng.c
// 金锦披风 [吉祥]
// 成套装备
// by yuchang                                                                        

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
	set_name( HIY"金锦披风"NOR, ({ "jinjin pifeng", "pifeng" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
                set("long", HIY"这是一件金丝织成的披风，价值连城。"NOR"
防御指数：三十
成套装备："HIC"[天祥防具]"NOR" "HIR"龙凤战甲"NOR" "YEL"锦云护心"NOR" "HIG"天灵护腕"NOR" "HIY"金锦披风"NOR" "HIW"云盘护腰"NOR"
特殊效果："HIG"无"NOR"\n");
		set("value", 60000);
		set("material", "silk");
		set("armor_prop/armor", 30);
		
	}
	setup();
}
