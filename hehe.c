#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

typedef struct s_t
{
	sem_t	*sem;
	pthread_t	*th;
	int	i;
}	t_t;


void	*routine(void *params)
{
	t_t	*t;

	t = (t_t *) params;
	sem_wait(t->sem);
	t->i++;
	sem_post(t->sem);
	return (NULL);
}

int	main(void)
{
	int		i = 0;
	sem_t* sem = sem_open("my_semaphore", O_CREAT, 0644, 1);
	pthread_t	th[2];
	t_t	t;

	t.sem = sem;
	t.th = th;
	t.i = i;
	for (int i = 0; i < 2; i++)
	{
		pthread_create(&th[i], NULL, &routine, (void *) &t);
	}
	for (int i = 0; i < 2; i++)
	{
		pthread_create(&th[i], NULL, &routine, (void *) &t);
	}
	printf("%d\n", t.i);
	sem_close(t.sem);
	sem_unlink("my_semaphore");
	return (0);
}
