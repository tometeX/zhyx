// 弈棋之道提升弹琴技艺，kasumi
#include <ansi.h>
inherit SKILL;

void skill_improved(object me)
{
        int lvl;
        int layer;

        lvl = me->query_skill("chess", 1);
        layer = lvl / 200;
        

        if (! layer)
        {
                tell_object(me, HIM "你潜心领悟弈棋之道，若有所悟。\n" NOR);
        } else
        if ((lvl % 200) == 0)
        {
			if (me->can_improve_skill("tanqin-jifa")&& me->query_skill("tanqin-jifa", 1) <= lvl)
	            me->improve_skill("tanqin-jifa", 1500000);
                tell_object(me, HIM "你领悟了第" + chinese_number(layer) +
                            "层境界的弈棋之道的奥妙。\n" NOR);
        } else
		{
			if (me->can_improve_skill("tanqin-jifa")&& me->query_skill("tanqin-jifa", 1) <= lvl)
	            me->improve_skill("tanqin-jifa", 1500000);
                tell_object(me, HIM "你对第" + chinese_number(layer) +
                            "层境界的弈棋之道又加深了一点了解。\n" NOR);
		}
}