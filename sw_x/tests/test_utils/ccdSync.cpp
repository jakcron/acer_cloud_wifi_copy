//
//  Copyright 2011 iGware Inc.
//  All Rights Reserved.
//
//  THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
//  TRADE SECRETS OF IGWARE INC.
//  USE, DISCLOSURE OR REPRODUCTION IS PROHIBITED WITHOUT
//  THE PRIOR EXPRESS WRITTEN PERMISSION OF IGWARE INC.
//

#include <ccdi.hpp>
#include <log.h>
#include <vpl_th.h>
#include <vpl_time.h>

#include <dirent.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <cstdio>
#include <cerrno>
#include <csignal>
#include <string>
#include <vector>

static int ownershipSync()
{
    int rv;
    rv = CCDIOwnershipSync();
    if (rv != CCD_OK) {
        LOG_ERROR("CCDIOwnershipSync: %d", rv);
    }
    return rv;
}

int main(int argc, char ** argv)
{
    LOG_DISABLE_LEVEL(LOG_LEVEL_DEBUG);

    int rv;
    std::string machine;

    if(argc != 2) {
        LOG_INFO("Usage: %s <machine> \n", argv[0]);
        LOG_INFO("Example: %s C1", argv[0]);
        return -1;
    }

    machine.assign(argv[1]);

    rv = ownershipSync();
    if(rv != 0) {
        LOG_ERROR("%s CCD sync failed: %d", machine.c_str(), rv);
        goto out;
    }
out:
    return rv;
}
