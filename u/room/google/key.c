// File(/data/room/google/key.c) of google's key
// Create by LUBAN written by Doing Lu

#include <ansi.h>

inherit ITEM;

string query_autoload() { return "1"; }

void create()
{
	set_name(YEL "狗狗家的钥匙" NOR, ({ "key", "1 of google" }));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把用来开启豆芽居(dyj)的钥匙。
这是原配钥匙。
LONG );
		set("unit", "把");
		set("no_pawn", 1);
                set("no_sell", 1);
		set("item_make", 1);
		set("value", 1);
	}
}
