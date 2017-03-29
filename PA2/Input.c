#include	"Input.h"
#include	<unistd.h>

Input::Input( int fdesc )
{
	fd = fdesc;
	used = 0;
	length = 0;
}

Input::~Input()
{
	close( fd );
}

int
Input::read()
{
	char		c;

	if ( used < length )
	{
		c = buffer[used++];
		return c;
	}
	else if ( (length = ::read( fd, buffer, sizeof(buffer) )) < 1 )
	{
		return -1;
	}
	else
	{
		c = buffer[0];
		used = 1;
		return c;
	}
}
