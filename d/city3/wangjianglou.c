inherit ROOM;

void create()
{
	set("short", "����¥");
	set("long", @LONG
����¥�����������������Ľǣ�������˽ǣ���������
�̽Ƿ����������������������ϣ�Զ�����Ϻӣ�������棬��
����ʵΪʤ����¥�����⣬����ǧ�����죬ÿ��������
�������䣬�����������������ǡ�¥ǰѦ�ξ�����˵��ΪѦ��
Ưϴһ�ֺ�ɫʫ�������ǧ�ţ��޲��ž������أ���ɫ�ż��
���䡣��Ҳ����һ��Ů�Ĵ�����Ψһ����
LONG);
        set("outdoors", "chengdu");
	set("exits", ([
	    	"northwest" : __DIR__"eastroad3",
	]));
	set("no_clean_up", 0);
	set("coor/x",-485);
	set("coor/y",-195);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
