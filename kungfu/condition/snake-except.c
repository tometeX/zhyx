 // snake-except.c
 // by Plzw 2004-2-4  
       
#include <ansi.h>  
       
inherit F_CLEAN_UP;  
       
int dispel(object me, object ob, int duration)  
{  
        int n;  
        string force;
  
        if (me != ob)  
        {  
                if (me->query_skill_mapped("finger") != "sun-finger") 
                { 
                        tell_object(ob, "你发觉" + me->name() + "的内力源源涌进，但"  
                                    "丹田还是冰冷，毫无帮助。\n"); 
                        tell_object(me, "你试图帮助" + ob->name() + "化解其体内灵蛇剧毒，"  
                                    "却忽然发现灵蛇剧毒源源不断地传来，不由大惊，连"  
                                    "忙住手。\n"); 
                        return -1; 
                } 
                
                if (me->query("max_neili") < 2000)
                {
                	tell_object(me, "你的内力不够深厚，无法帮助" + ob->name() + "化解其体内灵蛇剧毒。\n");
                	return -1;
                }
  
        } else 
        { 
                tell_object(me, "你觉得丹田冰冷，无法凝聚内力。\n"); 
                return -1;  
        }  
       
        n = ob->query_condition("snake-except") - 
            (int)me->query_skill("sun-finger", 1); 
            
        force = me->query_skill_mapped("force");
 
        if (n < 1)  
        {
            ob->clear_condition("snake-except");  
            message_vision(HIY "$N默运" + to_chinese(force) + "，施展开一阳指法，"
				"瞬时点遍了$n身上诸要穴....\n\n" HIC "$N深吸一口气，头上隐隐冒出白雾。\n" + 
				"$n“哇”的一下吐出瘀血，脸色登时红润多了。\n" NOR, me, ob);  
         	me->add("max_neili", - (1000 + random(1000)));
        }        
        else  
        {
	        ob->apply_condition("snake-except", n);  
   	        message_vision(HIY "$N默默的运用一阳指诀，帮助$n化解体内的灵蛇剧毒。\n"NOR, me, ob);  
   	}
   	    
        return 1;  
}  
    
int update_condition(object me, int duration)  
{  
        int limit;  
   
        if (! living(me) && (me->query("eff_qi") < 20 || me->query("eff_jing") < 10))  
        {   
        	    me->set_temp("die_reason", "灵蛇剧毒发作身亡");
                me->die();  
                return 0;  
        } else  
        {  
                me->receive_wound("qi", 150 + random(50));  
                me->receive_wound("jing", 100 + random(20));  
                tell_object(me, HIG"你只觉得一股浑身一阵麻木，你中的灵蛇剧毒发作了！\n" NOR); 
                message("vision", HIG + me->name() + HIG "忽然倒在地上，脸色发紫，直打哆嗦。\n" NOR,  
                       environment(me), ({ me })); 
        }  
  
        return 1;  
}
