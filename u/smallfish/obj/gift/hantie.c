// hantie.c ��������

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "��������" NOR, ({"ice steel", "han tie", "tie"}));
	set_weight(9000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���������Ľ�������˵�����Ϲ��������������ĺ�����\n");
		set("unit", "��");
		set("value", 10000);
                set("item_origin", 1);
                set("material_attrib", "steel");
                set("material_name", WHT "�Ϲź���" NOR);
                set("can_make", "all");
                set("not_make", ({ "��", "��"}));
                set("power_point", 70);
	}
}

