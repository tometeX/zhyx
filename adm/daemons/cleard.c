// #pragma optimize
// #pragma save_binary

inherit F_DBASE;

#include <ansi.h>

void create()
{
    seteuid(ROOT_UID);
    set("name", HIR "系统精灵" NOR);
    set("channel_id", "系统精灵");
    CHANNEL_D->do_channel(this_object(), "sys", "\n清除程序已经启动。\n");
    call_out("auto_clear", 30);
}

void auto_clear()
{
    CHANNEL_D->do_channel(this_object(), "sys", HIY "清除程序运行中。\n" NOR);
    if (random(3) == 1)
        rm("/log/usage");

    cp("/log/debug.log", "/driver/system.log"); //备份debug.log为systerm.log为程序查错
    remove_call_out("auto_clear");
    call_out("auto_clear", 1800); //30分钟清理一次
}
