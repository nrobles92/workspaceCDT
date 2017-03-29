#include	<signal.h>
#include	<stdio.h>
#include	<unistd.h>
//#include	<sys/siginfo.h>
#include	<sys/time.h>
//#include	"printBlocked.h"

// Timer demonstration signal handling.  How to set a timer.

static void
start_timer( int first_quantum, int next_quantum )
{
	struct itimerval		interval;

	interval.it_interval.tv_sec = next_quantum;
	interval.it_interval.tv_usec = 0;		/* microseconds */
	interval.it_value.tv_sec = first_quantum;
	interval.it_value.tv_usec = 0;
	setitimer( ITIMER_REAL, &interval, 0 );
}

static void
timeout_handler( int signo, siginfo_t * info , void * p )
{
	printf( "timeout_handler() invoked.  errno is %d\n", info->si_errno );
	//printBlocked( "timeout handler" );
}

static void
signal_handler( int signo )
{
	printf( "--Dang.  Cntl-C hit.  signo is %d, exit()ing.\n", signo );
	//printBlocked( "SIGINT handler" );
	_exit( 0 );
}

int
main()
{
	struct sigaction	action;

	printf( "main() invoked in process %d.\n", getpid() );
	//printBlocked( "main()" );

	action.sa_flags = SA_SIGINFO | SA_RESTART;
	action.sa_sigaction = timeout_handler;		/* long form */
	sigemptyset( &action.sa_mask );			/* no additional signals blocked */
	sigaction( SIGALRM, &action, 0 );

	action.sa_flags = 0;
	action.sa_handler = signal_handler;		/* short form */
	sigemptyset( &action.sa_mask );			/* no additional signals blocked */
	sigaction( SIGINT, &action, 0 );

	start_timer( 5, 2 );
	while( pause() == -1 );				/* wait for a signal, any signal */
	printf( "Normal end.\n" );
	return 0;
}
