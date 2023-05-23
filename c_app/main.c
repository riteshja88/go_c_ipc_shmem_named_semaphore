//https://www.softprayog.in/programming/interprocess-communication-using-system-v-shared-memory-in-linux
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>




 #include <fcntl.h>
 #include <sys/stat.h>

 #include <semaphore.h>
 #include <time.h>
// sem_t* Go_sem_open(const char *name, int oflag, mode_t mode, unsigned int value)
// {
//      return sem_open(name, oflag, mode, value);
// }
// #endif

void error (char *msg);

int main (int argc, char **argv)
{
	sem_unlink("/testsem");
	sem_t *sem = sem_open("/testsem",
						 O_CREAT,
						 0644,
						 0);
	printf("Waiting\n");
	sem_wait(sem);
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
	sem_close(sem);
}

// Print system error and exit
void error (char *msg)
{
    perror (msg);
    exit (1);
}
