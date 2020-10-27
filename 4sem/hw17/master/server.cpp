#include "addons.h"
#include "dataBase.h"

int server(DataBase &Db, int PORT)
{
    char buff2[BUFF_LEN];
    char espace[ESCAPE_LEN] = {'\n', '\t',' '};
    int space[SPACE_LEN] = {0};
    for (int i = 0; i < ESCAPE_LEN; ++i)
    {
	space[int(espace[i])] = 1;
    }

    fd_set active_set, read_set;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    socklen_t size;

    int Socket = socket(PF_INET, SOCK_STREAM, 0);
    if (Socket < 0)
    {
	return ERROR_SERVER_CANNOT_CREATE_SOCKET;
    }

    int flag = 1;
    setsockopt (Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&flag, sizeof(flag));

    addr.sin_family = AF_INET;
    addr.sin_port = htons (PORT);
    addr.sin_addr.s_addr = htonl (INADDR_ANY);

    int error = bind (Socket, (struct sockaddr *)&addr, sizeof(addr));
    if(error < 0)
    {
	return ERROR_SERVER_CANNOT_BIND_SOCKET;
    }

    error = listen (Socket, 30);
    if(error < 0)
    {
	return ERROR_SERVER_CANNOT_LISTEN_QUEUE;
    }

    FD_ZERO (&active_set);
    FD_SET (Socket, &active_set);

    printf ( "|SERVER| Start working !\n");

    int i, ret, newSocket;
    char buff[BUFF_LEN];
    Command current;
    for(;;)
    {
	read_set = active_set;
	if (select (FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0)
	{
	    return ERROR_SERVER_CANNOT_SELECT_SOCKET;
	}

	for (i = 0; i < FD_SETSIZE; i++)
	{
	    if (FD_ISSET (i, &read_set))
	    {
		if(i == Socket)
		{
		    size = sizeof(client);
		    newSocket = accept (Socket, (struct sockaddr *)&client, &size);
		    if(newSocket < 0)
		    {
			return ERROR_SERVER_WASNOT_ACCEPTED;
		    }

		    printf ( "|SERVER| Connected with new client, port: %d.\n", (unsigned int)ntohs(client.sin_port));
		    FD_SET (newSocket, &active_set);
		}
		else
		{
		    error = Readf (i, buff);
		    if(error < 0)
		    {
			switch(error)
			{
			    case ERROR_SERVER_CANNOT_READ_INCORRECT_SIZE:
				printf ("|Server| Can't read size of string\n");
				break;
			    case ERROR_SERVER_CANNOT_READ:
				printf ("|Server| Can't read\n");
				break;
			    case ERROR_SERVER_CLIPPED:
				printf ("|Server| Package was clipped\n");
				break;
			    case NOT_ERROR_SERVER_EMPTY_REQUEST:
				printf ("|Server| Empty request\n");
				break;
			}
			close(i);
			FD_CLR(i, &active_set);
		    }
		    else
		    {
			current.clear();
			printf("|SERVER| Request's long %d bytes, message: %s\n", error, buff);
			if(current.parse(buff, space, buff2) == 0)
			{
			    printf("Warning! Incorrect request!\n");
			    Printf(i, "Warning! Incorrect request!\n");

			}
			else
			{
			    ret = Db.requestExecute(current, i);
			    if(ret  < 0)
			    {
				switch (ret)
				{
				    case END_OF_WORKING_QUIT:
					Printf(i, "quit");
					close(i);
					FD_CLR (i, &active_set);
					break;
				    case END_OF_WORKING_STOP:
					Printf(i, "stop");
					printf("|SERVER| Stop Working!\n");
					close(Socket);
					return 0;
				    default: break;
				}
			    }
			    else
			    {
				Printf(i, "Done!\n");
			    }
			}
		    }
		}
	    }
	}
    }
}


