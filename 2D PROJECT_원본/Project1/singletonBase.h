#pragma once

template <typename T>

class singletonBase
{
protected:
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};

public:
	static T* getSingleton();
	void releaseSingleton();
};

// 싱글톤을 초기화한다
template <typename T>
T* singletonBase<T>::singleton = 0;

// 싱글톤 값을 가져온다
template <typename T>
T* singletonBase<T>::getSingleton()
{
	if (!singleton)	singleton = new T;
	return singleton;
}

// 싱글톤 메모리를 해제한다
template <typename T>
void singletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}