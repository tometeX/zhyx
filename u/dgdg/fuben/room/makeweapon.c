// makeweapon.c

inherit ROOM;

#define GANJIANG        "/adm/npc/ganjiang"
#define MOYE            "/adm/npc/moye"

void create()
{
	set("short","远古炼造室");
	set("long",@LONG
这里就是传说中的远古炼造室，不远处的一男一女正是传说中的
干将、莫邪夫妻，旁边的火炉正燃烧着熊熊大火。
LONG
	);

	set("exits", ([
		"down" : "/d/city/kedian",
	]));

        GANJIANG->come_here();
        MOYE->come_here();


        set("no_fight", 1);
        set("no_sleep_room", 1);

	setup();
	//replace_program(ROOM);
}