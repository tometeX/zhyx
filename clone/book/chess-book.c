// chess book.c

inherit ITEM;

void create()
{
        set_name("弈棋入门", ({ "chess book", "book" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"封面上写著「弈棋入门）」\n");
                set("value", 1000000);
                set("material", "paper");
                set("skill", ([
                        "name":         "chess",
                        "exp_required": 1000000,
                        "jing_cost":    100,
                        "difficulty":   100,
                        "max_skill":    199,
                ]));
        }
}

