inherit ROOM;

void create()
{
	set("short", "兵器铺");
	set("long", @LONG
这着是一家小小店面的兵器铺，可是所卖的兵器可大不寻
常。种类固然中土难得一见，能用的人更是稀少。掌柜的拿着
眼瞟得你直发毛。你转脸就看到墙上的招牌。
LONG );
	set("objects", ([
		__DIR__"npc/tanghuai" : 1,
	]));
	set("exits", ([
	    	"southeast" : __DIR__"northroad1",
	]));

	set("coor/x",-520);
	set("coor/y",-180);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

