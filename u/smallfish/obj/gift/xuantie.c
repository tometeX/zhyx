// xuantie.c ����ʯ

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(CYN "����ʯ" NOR, ({"xuan tie", "tie"}));
	set_weight(50000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���������Щ����ʯͷ���������ие���Ϊ���أ���ʤͭ����\n");
		set("unit", "��");
		set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "steel");
                set("material_name", CYN "����" NOR);
                set("can_make", "all");
                set("not_make", ({ "��", "��"}));
                set("power_point", 70);
	}
}
