#pragma once

class httplib::Client;
class Net
{
public:
	Net();
	virtual ~Net();

	virtual void setPlayer(const std::string& id) =0;

	httplib::Client* get_client()const { return client; }

protected:
	bool is_net_init = false;

	httplib::Client* client = nullptr;

};

