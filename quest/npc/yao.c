// npc: for quest npc
// by sun..
#include <ansi.h>
inherit NPC;

string ask_job();
string ask_fail();

void create()
{
        set_name("姚岳玲", ({ "yao yueling","yueling","yao" }));
        set("title", HIM "倾城倾国" NOR);
        set("gender", "女性");
        set("age", 20);
        set("per",25);
        
        set("no_kill", 1);
        set("no_fight",1);
        set("no_get", 1);

        set("inquiry", ([
                "job" : ( :ask_job: ),
                "任务" : ( :ask_job: ),
                "fail" : ( :ask_fail: ),
                "失败" : ( :ask_fail: ),
        ])),

        setup();
}

#include "/quest/include/yao.h" 

