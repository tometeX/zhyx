//update by xiner
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name( HIG"东皇钟"NOR, ({ "donghuang zhong","zhong" }) );
	set_weight(1500);
	if( clonep() )
	set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("long", HIW"一个青铜大钟，相传为东皇太一的兵器。钟上刻着无数上古文字，散发着黄色的豪光。具有极强的防御能力。\n" NOR);
		set("value",10);
		set("material", "tian jing");
		set("armor_prop/armor", 500 + random(100));
		set("armor_prop/dodge", 200 + random(100));
                set("armor_prop/parry", 200 + random(100));
		set("warm_cloth", 1);
		set("no_sell", 1 );
		set("no_steal", 1 );
	}
	setup();
}

int query_autoload()
{
	return 1;
}

owner_is_killed()
{
	if (random(30)!=1)
	{
		message_vision(HIG"神物有灵，东皇钟向天外飞去，寻找他命中注定的主人。\n" NOR,this_player());
    destruct(this_object()); 
    return 1;
  }
  
  message_vision(HIG"恭喜你!你可以得到上古神物：东皇钟。\n" NOR,this_player());
  
	
}



 mixed valid_damage(object ob, object me, int damage, object weapon) 
     { 
             mapping result; 
             int ap, dp; 
             int cost,level,backdamage; 
      
                     level=(int)me->query_skill("martial-cognize", 1); 
                     if (level<100) backdamage=0; 
                     else if (level<299) backdamage=(int)damage/20 ; 
                     else if (level<499) backdamage=(int)damage/15 ; 
                       else backdamage=damage; 
     
             if ((int)me->query("neili") < 500)  
                     return; 
     
             cost = damage / 2; 
            if (cost > 1000) cost = 1000; 
      
             
             
             ap = ob->query_skill("force",1);
             dp = me->query_skill("force",1);

     
          if (ap * 2 / 5 + random(ap) < dp) 
             { 
                             if (random(4) == 1 ) 
                             { 
                     me->add("neili", -cost);                                 
                                     result = ([ "damage": -damage ]);        
                                     ob->receive_wound("qi", backdamage, me); 
                     
                             result += (["msg" : HIY "$n" HIY "默念东皇真诀，神灵护体上术，承下$N" + HIY "这一招，结果$N被$n以内力反震，「哇」地一声吐出一口鲜血！\n"NOR]);                         
                     return result; 
                             } 
                         else 
                             { 
                                     me->add("neili", -cost); 
                     result = ([ "damage": -damage ]);                
                             result += (["msg" : HIY "但见东皇钟发出层层豪光，把$n团团护住,混若无事的接下了$N这一招，却没有受到" 
                                                 "半点伤害。\n" NOR]);                        
                     return result; 
                             } 
      
             } 
     } 
      
