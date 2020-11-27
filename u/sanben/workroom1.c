#include <ansi.h> 
#include <room.h>
//inherit ROOM; 

 inherit "/inherit/room/roomcode"; 

#define QINGTIAN    "/u/sanben/special/tianzi/qingtian.c"
#define SPECIAL     "/data/item/special/"


int is_chat_room() 
{ 
        return 1; 
} 

void create()
{       object ob;
        set("short", HIY "\n\n                大笨工作室" NOR);
        set("long", HIY "\n\n"
"这里想必就是传说中的笨蛋聚居所,\n"
"有道是：不是笨蛋不进来，进来就是大笨蛋。\n"
"所以欢迎你，笨蛋!\n\n" NOR
);

        set("exits", ([
                 "gc" : "/d/city/guangchang", 
                   "kd" : "/d/city/kedian",                
                //   "idl" : "/u/idle/workroom",
        ]));
        set("objects", ([
                "/clone/money/coin" : 1,
        ]));

        set("no_fight", 1);
        set("valid_startroom", 1);
        set("sleep_room", 1);
        set("chat_room",1);
        set("valid_startroom", 1);   
       restore();
        setup();               
                 "/clone/board/sanben_b"->foo();            
        
}

void init()
{

    add_action("do_ketou","ketou");

}

int do_ketou()
{

    object me, qingtian;
    string fn;
    string fc; 

    me = this_player();
    fc = read_file(QINGTIAN);

    fc = replace_string(fc, "LONG_DESCRIPTION",
                        HIW "这张护甲异乎寻常，周身散发出淡淡的雾气将其笼罩，"
                        "什么也看不清。\n" HIC
                        "护甲缘上刻着一行小字：众神赐于真命天子" + me->query("name") +
                         "(" + me->query("id") + ")。\n" NOR);
    fc = replace_string(fc, "ID",me->query("id"));

    fn = SPECIAL + me->query("id") + "/qingtian";

        if (file_size(fn + ".c") > 0)
        {
                if (qingtian = find_object(fn)) destruct(qingtian);
                rm(fn + ".c");
        }

        assure_file(fn);
        write_file(fn + ".c", fc);

        VERSION_D->append_sn(fn + ".c");
        qingtian = load_object(fn);
        qingtian->move(me, 1);
        me->set("can_summon/qingtian",fn);
        tell_object(me, HIY "你获得了一个结婚戒指。\n" NOR);

   
    return 1;

}


