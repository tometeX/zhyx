inherit ROOM;

void create()
{
	set("short", "��Ȥͤ");
	set("long", @LONG
ͤ�ڸ߸�����������д�ġ���Ȥ����һ�顣ͤ��װ�ξ���
��̻Ի͡����ܡ�Χ����ȹ���ϵ�̵��������ͼ��Ω��Ω
Ф���ڴ˿��Ի���ȫ԰��ɫ��
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"  : __DIR__"wenmeige",
		"north" : __DIR__"yanyutang",
	]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x",215);
	set("coor/y",-176);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

