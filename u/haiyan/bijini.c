// bijini.c

inherit EQUIP;

void create()
{
        set_name("比基尼泳衣", ({ "bijini", "cloth", }) );
        set("long","这是一件名贵的泳装，穿上它可以尽显女性的曲线美。\n");
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("armor_type", "cloth");
                set("value", 2500);
                set("no_get",1);
                set("no_put",1);
                set("only_do_effect",1);
                set("armor_prop/dodge", 6);
                set("armor_prop/armor", 1);
        }
}

