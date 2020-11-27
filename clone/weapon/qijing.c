//by xiner

#include <weapon.h>
#include <ansi.h>

inherit THROWING;
 
void create()
{
	set_name(HIR "四象气劲" NOR, ({ "qi jing" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "无数闪烁不定的光芒，汇成的一束" HIR "四象气劲" HIW "。\n" NOR);
		set("unit", "团");
		set("value", 0);
		set("base_unit", "束");
		set("base_weight", 1);
		set("base_value", 0);
		set("no_get", 1);
		set("no_put", 1); 
		set("no_steal", 1);
		set("no_drop", "这东西不能离开你的手心！\n"); 
	}
	set_amount(50);
	init_throwing(200);
	setup();
}
