inherit ROOM;

void create()
{
	set("short", "�Ÿ�����");
	set("long", @LONG
�����ǶŸ���Ԣ�ɶ��Ĺʾӡ���������ˮ���ӣ�С�Ź���
������ӳ���Եü�ׯ�����£����ӵ��ţ��ֲ�ʧ����ף���
�����ʡ�
LONG);
        set("outdoors", "chengdu");
	set("no_clean_up", 0);
	set("exits", ([
		"south"  : __DIR__"path2",
	]));
	setup();
	//replace_program(ROOM);
}
