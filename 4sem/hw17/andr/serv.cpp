#include "database.h"


int serv (int PORT, database &bas, char *alf, command &com)
{
	int i, err, ret, opt = 1;
	int sock, new_sock;
	fd_set active_set, read_set;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	char buf[LEN];
	socklen_t size;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) return -1;
	setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

	addr.sin_family = AF_INET;
	addr.sin_port = htons (PORT);
	addr.sin_addr.s_addr = htonl (INADDR_ANY);
	err = bind (sock, (struct sockaddr *)&addr, sizeof(addr));
	if(err < 0) return -1;

	err = listen (sock, 12);
	if(err < 0) return -1;

	FD_ZERO (&active_set);
	FD_SET (sock, &active_set);
	com.destroy();
	printf("it's alive!\n");
	while(true)
	{
		read_set = active_set;
		if (select (FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0)
			return -4;

		for (i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET (i, &read_set))
			{
				if(i == sock)
				{
					size = sizeof(client);
					new_sock = accept (sock, (struct sockaddr *)&client, &size);
					if(new_sock < 0) return -5;

					printf ( "SERVER: connect from host %s, port %d.\n",	inet_ntoa(client.sin_addr), (unsigned int)ntohs(client.sin_port));
					FD_SET (new_sock, &active_set);
				}
				else
				{
					err = ReadfromClient (i, buf);
					if(err < 0)
					{
						printf("something bad or Client left\n");
						close(i);
						FD_CLR(i, &active_set);
					}
					else
					{
						ret = com.parser(buf,alf);	
						if (ret < 0)
				        {  	
							if(ret==-243)
							{
								PrinttoClient(i, "stop;");
				        		close (i);
				        		FD_CLR (i, &active_set);
				        		printf ( "SERVER: close\n");
				        		return close (sock), 0;
							}
							PrinttoClient (i, "bad_command");
							com.destroy();
							
						}
				        else
				        {
				            bas.docommand (com, i);
							PrinttoClient(i, "done");
							com.destroy();
							
				        }
					}
				}
			}
		}
	}
}


