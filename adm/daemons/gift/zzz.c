  // zzz.c 河豚

inherit ITEM;
inherit F_FOOD;

void create()
{
          set_name("河豚", ({"hetun", "fish"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
                  set("long", "一条肥头胖脑的河豚。\n");
                  set("unit", "条");
		set("value", 150);
		set("food_remaining", 3);
		set("food_supply", 60);
	}
}
