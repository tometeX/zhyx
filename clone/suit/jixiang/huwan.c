// tianling huwan.c
// 天灵护腕 [吉祥]
// 成套装备
// by keinxin@sj2 2003.2
#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
	set_name( HIG"天灵护腕"NOR, ({ "tianling huwan", "huwan" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "双");
                set("long", HIG"这是一件玉质的护腕，晶莹剔透，闪闪发光"NOR"
防御指数：二十五
特殊效果："HIG"增加腕力(hand)"NOR"\n");
		set("value", 6000);
		set("material", "wrists");
		set("wear_msg", RED"$N拿出一双"HIG"天灵护腕"RED"戴在手上，顿时感到腕力有所增强。\n" NOR);
		set("armor_prop/hand", 100);
		set("armor_prop/armor", 25);
	}
	setup();
}
