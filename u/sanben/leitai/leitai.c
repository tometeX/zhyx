#include <ansi.h>

inherit ROOM;
string look_tiaofu();
#define JINYONG   "/u/sanben/leitai/jinyong"

void create()
{
	set("short", HIY"华山论剑--五大高手封名擂台"NOR);
	set("long", 
HIW"此地便是挑战五大绝顶高手之所。有人若能在此处打\n"
"败五大高手便可取而代之。这里空无一物，只有墙上贴着\n"
"一块" NOR HIG"条幅(tiaofu)" NOR HIW"，大凡来此之人都会先看看这块条幅。\n"NOR);	
       set("biwutai",1);      
       set("no_sleep_room",1);
       set("no_steal",1);
       set("no_beg",1);
       set("no_get_from",1);
       
	set("item_desc", ([
		"tiaofu" : (: look_tiaofu :),
	]));

       set("exits", ([ 
               "down" : "/d/city/wumiao2", 
       ]));

	set("objects", ([
		__DIR__"jinyong": 1,
	]));
	setup();
}

string look_tiaofu()
{
    object jy;
    string msg;
    
    jy = find_object(JINYONG);
    if ( ! jy ) jy = load_object(JINYONG);

    msg = "===================================================\n";
    msg += HIR"想打擂者一次缴清五十两黄金给金庸大侠,\n";
    msg += "每次打擂限二十分钟，逾时不候。\n\n"NOR;

    msg += HIG"目前五大高手排行榜如下：\n";
    msg += "第一高手：中神通    " + jy->query("namelist/5") + 
           "(" + jy->query("idlist/5") + ")\n"; 
    msg += "第二高手：北  丐    " + jy->query("namelist/4") + 
           "(" + jy->query("idlist/4") + ")\n"; 
    msg += "第三高手：南  帝    " + jy->query("namelist/3") + 
           "(" + jy->query("idlist/3") + ")\n"; 
    msg += "第四高手：西  毒    " + jy->query("namelist/2") + 
           "(" + jy->query("idlist/2") + ")\n"; 
    msg += "第五高手：东  邪    " + jy->query("namelist/1") + 
           "(" + jy->query("idlist/1") + ")\n"NOR; 

    msg += HIY"\n若打赢擂台后可按如下格式设置替身\n"NOR;
    msg += HIC"为替身设置兵器格式为：\n";
    msg += "setwp 兵器类型\n";
    msg += "设置的兵器必须是\n"
           "「斧、刀、鞭、铁掌、锤、剑、棍、指套、杖」中的一种。\n"NOR;
    msg += HIW"为替身设置绝招的格式为：\n";
    msg += "setpfm 技能名称|技能类型|绝招名称\n";
    msg += "例如：setpfm taixuan-gong|unarmed|xuan\n"NOR;
    msg += "==================================================\n";
    return msg;
}

int no_die(object me)
{               
        message_vision (HIC"只见金大侠手指朝$N一指，$N顿时恢复了精神\n"NOR,me);
        me->remove_all_enemy(1);
        me->revive();
        me->set("eff_qi",me->query("max_qi")); 
        me->set("eff_jing",me->query("max_jing"));               
        me->set("qi",me->query("eff_qi"));
        me->set("jing",me->query("eff_jing")); 
        me->clear_condition("poison");
        return 1;
}
