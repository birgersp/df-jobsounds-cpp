/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef JOBSOUNDS_APP_H
#define JOBSOUNDS_APP_H

#include "core.h"
#include "Socket_Server.h"

class Jobsounds_app
{
public:

	void run(const Vector<String>& arguments);

private:

	uint port = 56730;
	Socket_Server server;
	void parse_argument(String_ref argument);
	void process_connection(Socket_Connection& connection);
	void parse_message(String_ref message);

};

#endif /* JOBSOUNDS_APP_H */