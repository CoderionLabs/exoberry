/*
 * Copyright (c) 2013 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */

#if defined(WITH_LIB_CONSOLE)
#include <lib/console.h>

#include <stdio.h>
#include <string.h>
#include <lwip/api.h>
#include <lwip/ip_addr.h>

static int net_cmd(int argc, const cmd_args *argv)
{
	if (argc < 2) {
		printf("%s commands:\n", argv[0].str);
usage:
		printf("%s lookup <hostname>\n", argv[0].str);
		goto out;
	}

	if (!strcmp(argv[1].str, "lookup")) {
		if (argc < 3)
			goto usage;

		ip_addr_t ip_addr;
		const char *hostname = argv[2].str;
		err_t err;

		err = netconn_gethostbyname(hostname, &ip_addr);
		if (err != ERR_OK) {
			printf("Failed to resolve host: %d\n", err);
		} else {
			printf("%s: %u.%u.%u.%u\n", hostname,
					ip4_addr1_16(&ip_addr),
					ip4_addr2_16(&ip_addr),
					ip4_addr3_16(&ip_addr),
					ip4_addr4_16(&ip_addr));
		}
	}

out:
	return 0;
}

STATIC_COMMAND_START
STATIC_COMMAND("net", "net toolbox", &net_cmd)
STATIC_COMMAND_END(net);

#endif

