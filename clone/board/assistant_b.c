
inherit BULLETIN_BOARD;

void create()
{
	set_name("玩家代表室留言版", ({ "board" }) );
	set("location", "/u/viremploy/assistant");
	set("board_id", "assistant_b");
	set("long", "请认真记录。\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
