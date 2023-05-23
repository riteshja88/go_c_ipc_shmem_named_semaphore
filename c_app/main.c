//https://www.softprayog.in/programming/interprocess-communication-using-system-v-shared-memory-in-linux
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 

void error (char *msg);

int main (int argc, char **argv)
{
    key_t s_key = 1234; 
    int shm_id;
    if((shm_id = shmget(s_key,
						4096,
						0660 | IPC_CREAT)) == -1) {
        error ("shmget");
	}

	char *shared_mem_ptr = NULL;
    if((shared_mem_ptr = (char *) shmat(shm_id,
										NULL,
										0)) == (char *) -1) {
        error ("shmat");
	}
	printf("%s\n",shared_mem_ptr);
}

// Print system error and exit
void error (char *msg)
{
    perror (msg);
    exit (1);
}
