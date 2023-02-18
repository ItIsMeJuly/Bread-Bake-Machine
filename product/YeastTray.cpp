#include "YeastTray.h"

YeastTray::YeastTray(Log& log)
    : log(log)
{
}

void YeastTray::Drop(uint64_t time)
{
    log.Debug(">> %s::%s: %d minutes", __FILE__, __FUNCTION__, time / 1000);
}

void YeastTray::Cancel()
{
    log.Trace(">> %s::%s", __FILE__, __FUNCTION__);
}
