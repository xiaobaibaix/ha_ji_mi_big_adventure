#include "pch.h"
#include "Net.h"

Net::Net()
{
	client = new httplib::Client("100.66.45.102:25565");





}

Net::~Net()
{
	delete client;
}
