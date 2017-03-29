#ifndef Input_h
#define Input_h

class Input {
	int	fd;
	int	length;
	int	used;
	char	buffer[2048];
public:
		Input( int );
		~Input();

	int	read();
};

#endif
