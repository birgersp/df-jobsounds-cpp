#include "TCP_Connection.h"
#include "util.h"

#include <cpputil/errorhandling.hpp>

TCP_Connection::TCP_Connection(SOCKET socket) : socket(socket)
{
}

TCP_Connection::~TCP_Connection()
{
	closesocket(socket);
}

void TCP_Connection::readline(Mutable_String_Ref string)
{
	if (is_closed())
		throw functionException("Connection closed");

	int n;
	bool done = false;
	while (not done)
	{
		n = recv(socket, buffer, BUFFER_SIZE, 0);
		if (n < 0)
			throw functionException("Read error: " + get_wsa_error_string());
		else if (n == 0)
		{
			connection_open = false;
			done;
		}
		else
		{
			string += std::string(buffer, n);
			if (buffer[n - 1] == '\0')
				done = true;
		}
	}
}

bool TCP_Connection::is_closed() const
{
	return !connection_open;
}
