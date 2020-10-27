#include "addons.h"

int main(int argc, char **argv)
{
    const char *SERVER_NAME;
    int SERVER_PORT;
    if (argc !=3 || !(SERVER_PORT = atoi(argv[2])) || SERVER_PORT <= 0)
    {
	printf ("|CLIENT| Usage: %s Server_IP Server_PORT\n", argv[0]);
	return -1;
    }


    SERVER_NAME = argv[1];
    struct sockaddr_in server_addr;
    struct hostent *hostinfo;

    hostinfo = gethostbyname(SERVER_NAME);
    if (!hostinfo)
    {
	printf("|CLIENT| Unknown host name %s\n", SERVER_NAME);
	return -2;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(struct in_addr *)hostinfo->h_addr;

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
	printf("|CLIENT| Socket wasn't created\n");
	return -3;
    }

    int error = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(error < 0)
    {
	printf("|CLIENT| Can't connect\n");
	return -3;
    }

    printf("|CLIENT| Connected to server\n");

    char buff[BUFF_LEN];
    int ret;
    while(fgets (buff, BUFF_LEN, stdin))
    {
	for (ret = 0; buff[ret]; ret++)
	{
	    if (buff[ret] == '\n')
	    {
		buff[ret] = 0;
		break;
	    }
	}

	if (Printf(sock, buff) < 0)
	{
	    printf ("|CLIENT| Can't wrtie so server\n");
	}

	for(;;)
	{
	    error = Readf (sock, buff);
	    if(error < 0)
	    {
		switch(error)
		{
		    case ERROR_SERVER_CANNOT_READ_INCORRECT_SIZE:
			//printf ("|CLIENT| Can't read size of string\n");

			//break;
			return -1;
		    case ERROR_SERVER_CANNOT_READ:
			printf ("|CLIENT| Can't read\n");
			break;
		    case ERROR_SERVER_CLIPPED:
			printf ("|CLIENT| Read clipped\n");
			break;
		    case NOT_ERROR_SERVER_EMPTY_REQUEST:
			printf ("|CLIENT| Empty request\n");
			break;
		}
	    }
	    else
	    {
		if (strcmp (buff, "quit") == 0 || strcmp (buff, "stop") == 0 )
		{
		    close(sock);
		    printf("End of working\n");
		    return 0;
		}

		if (strcmp (buff, "Warning! Incorrect request!\n") == 0 || strcmp (buff, "Done!\n") == 0 )
		{
		    printf("%s\n", buff);
		    break;
		}
		printf("%s", buff);
	    }
	}
    }
    return 0;
}



