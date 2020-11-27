// zhujidan.c 筑基丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "筑基丹" NOR, ({ "zhuji dan", "zhuji", "dan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "一颗紫中泛黄的精致奇丹，具有着神话般的功效，传说吃了之后\n"
                                "能平增数十年的功力,神丹妙药。适合武林新手筑基使用\n" NOR);
                set("value", 10);
                set("unit", "颗");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
      me=this_player();
      //  int effect;
     //   int neili;

       if (me->query("combat_exp")>800000)
       	{
       	message_vision(HIY "你已经功力深厚，以后要靠自己努力提升了。\n" NOR, me);
       	return 1;
       	}

        	me->add("combat_exp", 100000 + random(50000));
        	me->add("potential", 30000);
            me->improve_neili(500);
          message_vision(HIY "你的经验提升了！你的潜能提升了！你的内力提升了！\n" NOR, me); 
          
           
   /*     	mapsk = me->query_skill_mapped("force");
        	if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
*/
    destruct(this_object());
        return 1;    	
        
	}
        


int query_autoload()
{
        return 1;
}