// File(/data/room/dgdg/key.c) of dgdg's key
// Create by LUBAN written by Doing Lu

#include <ansi.h>

inherit ITEM;

string query_autoload() { return "1"; }

void create()
{
	set_name(YEL "杨六狼家的钥匙" NOR, ({ "key", "1 of dgdg" }));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把用来开启喜来登(xld)的钥匙。
这是原配钥匙。
LONG );
		set("unit", "把");
		set("no_pawn", 1);
                set("no_sell", 1);
		set("item_make", 1);
		set("value", 1);
	}
}
