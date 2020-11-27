#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + CYN "镇龙石" NOR, ({"zhenlong shi", "zhenlong", "shi"}));
        set_weight(15000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "传说此石乃是历代皇朝用于镇住龙脉所用，大非寻常。\n"
				                 "可以打造锤，杖，棍。基础伤害：60~90。\n"NOR);
                set("unit", "块");
                set("value", 9000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + CYN "镇龙石" NOR);
                set("can_make", ({ "锤","棍", "杖" }));
                set("power_point", 60);
        }
}

int query_autoload()
{
        return 1;
}

