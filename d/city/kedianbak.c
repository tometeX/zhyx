#include <room.h>
#include <ansi.h>

inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "客店");
	set("long", @LONG
这是一家价钱低廉的客栈，生意却是非常兴隆。外地游客
多选择这里落脚，你可以在这里打听到各地的风土人情。店小
二里里外外忙得团团转，接待着南腔北调的客人。客店的主人
从不露面，他究竟是谁，有各种各样的猜测。客店的西墙上挂
着一个牌子(paizi)。
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
        set("no_sleep_room",1);
	set("item_desc", ([
		"paizi" : WHT "\n\n        ※※※※※※※※※※※※※※※※※\n"
                              "        ※                              ※\n"
                              "        ※   " NOR + HIW "地下室客店，免费提供住宿。" NOR + WHT " ※\n"
                              "        ※                              ※\n"
                              "        ※※※※※※※※※※※※※※※※※\n\n\n" NOR,
	]));
	set("objects", ([
                __DIR__"npc/xiaoer" : 1,             
	]));
	set("exits", ([
		"west" : __DIR__"beidajie1",
              "up":"/d/wizard/advice",
		"down"   : __DIR__"kedian2",
		"south": __DIR__"liaotian",
	]));
	
	setup();
	"/clone/board/kedian_b"->foo();
    "/adm/npc/beichou"->come_here();
}

void init()
{
        add_all_action();
}

