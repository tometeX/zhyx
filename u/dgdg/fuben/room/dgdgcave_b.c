// /u/dgdg/fuben/room/dgdgcave_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("远古通道留言板", ({ "board" }) );
	set("location", "/u/dgdg/fuben/room/wolfcave");
	set("board_id", "sdgdgcave_b");
	set("long", "这是一个供打宝游侠交流的留言板。\n" );
	setup();
	set("capacity", 1200);
	replace_program(BULLETIN_BOARD);
}
