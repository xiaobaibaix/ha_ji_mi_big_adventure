#pragma once

class httplib::Client;
class Net
{
public:
	Net();
	~Net();



private:

	httplib::Client* client = nullptr;

};

