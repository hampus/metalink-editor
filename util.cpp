#include "util.hpp"
#include "config.h"

wxStandardPaths get_stdpaths()
{
    wxStandardPaths stdp;
#ifdef __UNIX__
    stdp.SetInstallPrefix(wxT(CMAKE_INSTALL_PREFIX));
#endif
    return stdp;
}
