#pragma once

template <typename T>
class Manager
{
public:
	static T* instance(){
		if (!instance_mg)
			instance_mg = new T;
		return instance_mg;
	}

private:
	static T* instance_mg;

protected:
	Manager()=default;
	~Manager()=default;

	Manager(const T&) = delete;
	T& operator=(const T&) = delete;
};
template <typename T>
T* Manager<T>::instance_mg = nullptr;

