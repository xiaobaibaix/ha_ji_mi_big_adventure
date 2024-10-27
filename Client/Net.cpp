#include "pch.h"
#include "Net.h"

Net::Net()
{
	client = new httplib::Client("localhost:25565");





}

Net::~Net()
{
	delete client;
}
