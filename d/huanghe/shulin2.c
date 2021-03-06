#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "树林");
    set("long", @LONG
树林里光线暗淡，只能听见头顶传来一些鸟儿的啼鸣。偶
而从茂密的叶间透过的一线光伴着落叶在飞舞。朽木腐烂的气
味和身後传来野兽的啸声使人不觉犹豫了前进的脚步。草丛中
隐约有一个洞穴(cave)。
LONG);
    set("item_desc", ([
          "cave" : WHT "\n这是一个黑不溜湫的大洞，里面不知道"
                   "有些什么古怪。\n" NOR,
    ]));
    set("exits", ([
        "east"  : __DIR__"shulin1",
        "north" : __DIR__"shulin4",
    ]));
    set("quarrys", ([
            "tu"        : 100000,
            "ji"        : 80000,
            "pao"       : 50000,
            "caihuashe" : 50000,
            "dushe"     : 20000,
            "hu"        : 5000,
            "bao"       : 2000,
            "laohu"     : 2000,
    ]));
    set("outdoors", "huanghe");
    setup();
    //replace_program(ROOM);
}

void init()
{
    add_action("do_enter", "enter");
}

int do_enter(string arg)
{
    int n;
    object *inv;
    object me;
    me = this_player();

    if (!arg || arg == "")
        return 0;

    inv = deep_inventory(me);

    for (n = 0; n < sizeof(inv); n++)

    {
        if (!playerp(inv[n]))
            continue;

        else
        {
            message_vision(CYN "\n空中神灵喝道：你个妖人？圣人之地"
                               "可由不得你嚣张！你身上藏着什么!且速速退下\n" NOR,
                           me);

            return 1;
        }
    }

    if (arg == "cave")
    {
        if (me->query_skill("force", 1) > 600 || me->query_skill("dodge", 1) > 600 ||
            me->query_skill("parry", 1) > 600 || me->query_skill("sword", 1) > 600 ||
            me->query_skill("unarmed", 1) > 600 || me->query_skill("martial-cognize", 1) > 600 ||
            me->query("max_qi") > 50000)

        {
            message_vision(CYN "\n空中神灵喝道：你个妖人？圣人之地"
                               "可由不得你嚣张！且速速退下\n" NOR,
                           me);
            return 1;
        }

        return me->move("/u/dgdg/fuben/room/wolfcave");
    }
}
