// uquest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

string show_quest(mixed q);

int main(object me, string arg)
{
        string msg;
        mapping uq;
        
        if (! me->query("ultra_quest"))
                 return notify_fail("你目前没有领取任何宗师任务。\n");
                 
        uq = me->query("ultra_quest");
        
        msg = HIC "\n--------------------------------------------\n" NOR;        
        if (! me->query("ultra_quest/quest"))
        {
        	msg +=    sprintf("任务完成数：%-20d\n", uq["finish"]);
        	msg +=    sprintf("当前之任务：%-20s\n", "无任务");
        	msg +=    sprintf("提供线索者：%-20s\n", uq["next_npc"]);
        	msg +=    sprintf("线索人物地：%-20s\n", uq["npc_place"]);
        	msg += HIC "--------------------------------------------\n" NOR;
        	
        	write(msg);
        	return 1;
        }

        msg +=    sprintf("任务完成数：%-20d\n", uq["finish"]);
        msg +=    sprintf("当前之任务：%-20s\n", show_quest(uq));
        msg +=    sprintf("提供线索者：%-20s\n", uq["next_npc"]);
        msg +=    sprintf("线索人物地：%-20s\n", uq["npc_place"]);
        msg += HIC "--------------------------------------------\n" NOR;
        
        write(msg);                                               
       
        return 1;
}

string show_quest(mixed q)
{
	if (! mapp(q))return "error!";
	
	switch(q["quest"]["type"])
	{
		case "kill":
		      return "拿" HIY + q["quest"]["obj"] + NOR + "的人头给" + 
		             HIY + q["next_npc"] + NOR + "。";
                
                case "give":
                      return "帮" + HIY + q["next_npc"] + NOR + "把包裹送到" + 
                             HIY + q["quest"]["obj"] + NOR + "处。";
                      
                case "send":
                      return "帮" + HIY + q["next_npc"] + NOR + "把信送到" + 
                             HIY + q["quest"]["obj"] + NOR + "处。";

                case "find":
                      return "帮" HIY + q["next_npc"] + NOR + "找" + HIY + 
                             q["quest"]["obj"] + NOR + "。";
                      
                case "going":
                      return "护送" + HIY + q["next_npc"] + NOR + "到" + HIY + 
                             q["quest"]["obj"] + NOR + "。";
                             
                case "guard":
                      return "留在此处保护(guard)" HIY + q["quest"]["obj"] + NOR + "。";
                            
                case "mathematics":
                      return "和" + HIY + q["next_npc"] + NOR + "比试(accede)算术。";
                      
                case "literate":
                      return "跟" + HIY + q["next_npc"] + NOR + "吟诗对对(accede)。";
                      
                case "chess":
                      return "和" + HIY + q["next_npc"] + NOR + "对弈(accede)一局。";

                case "calligraphy":
                      return "帮" + HIY + q["next_npc"] + NOR + "写一副字(accede)。";
                      
                case "drawing":
                      return "帮" + HIY + q["next_npc"] + NOR + "画一副画(accede)。";
                      
                case "medical":
                      return "帮" + HIY + q["next_npc"] + NOR + "医治(accede)病痛。";
                
                default:
                      return HIR "error!";

	}
}

int help(object me)
{
        write(@HELP
指令格式 : uquest  这个指令可以查询你当前宗师任务的详细情况。

HELP );
        return 1;
}
