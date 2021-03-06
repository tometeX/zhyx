#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(MAG "九霄环佩琴·盛唐" NOR, ({ "jiuxiao qin", "jiuxiao", "qin" }));
        set_weight(600);

	if (clonep())
		set_default_object(__FILE__);
	else {
                set("unit", "把");
                set("long", HIW "这历史最悠久的传世之琴，盛唐开元之器。此琴\n"
                                "形体饱满，上髹紫漆，间杂朱砂后补之色，贵在\n"
                                "声形俱佳，为传世之器的极品。\n" NOR);

		set("value", 400000);
		set("material", "wood");
	}
	setup();
}

void init()
{
        add_action("play_qin", "play");
}
