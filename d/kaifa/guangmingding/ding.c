#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIY"光明顶"NOR);
        set("long", @LONG
这里是明教光明顶，现在正是江湖六大门派围攻光明顶的时候，而此
刻明教的四大法王和左右护法遭“霹雳手”成昆的暗算，正在运功
疗伤。眼看六大门派即将攻上光明顶，明教的生死存亡系于这电光
火石的一瞬间了。
LONG );
        set("exits",([
            "down" : __DIR__"to_ding",
        ]));
        set("objects",([
            __DIR__"npc/xuan-ci":1,
            __DIR__"npc/miejue":1,
            __DIR__"npc/song":1,
            __DIR__"npc/hetaichong":1,
            __DIR__"npc/yuebuqun":1,
            __DIR__"npc/chengkun":1,
        ]));
                
        
        setup();

}


void init()
{
        add_action ("do_fight","fight");
        add_action ("do_fight","kill");
        add_action ("do_fight","hit");
        add_action ("do_work","quit");
        add_action ("do_work","halt");
}

int do_work()
{
        write("这里不能使用这个指令！\n");
        return 1;
}

int do_fight()
{
        write("这里不能使用这个指令！\n");
        return 1;
}

