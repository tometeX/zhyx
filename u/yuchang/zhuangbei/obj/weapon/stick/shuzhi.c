#include <weapon.h>

inherit STICK;

void create()
{
        set_name("��֦", ({"shuzhi","stick"}));
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "wood");
        }
        init_stick(8);
        setup();
}

