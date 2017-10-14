#include <iostream>
#include <Windows.h>

using namespace std;

#define N 10
HANDLE H[2];


DWORD WINAPI f_even(void *p)
{
	int buf[N];

	for(int i=0;i<N;i++) buf[i] = 2*i+1;

	HANDLE hodd  = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"odd");
	HANDLE heven = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"even");
	HANDLE vlapa = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"vlapa");

	for(int i=0;i<N;i++)
	{
		WaitForSingleObject(hodd,INFINITE);
		cout<<buf[i]<<"-";
		ReleaseSemaphore(heven,1,0);
	}

	return 0;
}

DWORD WINAPI f_odd(void *p)
{
	int buf[N];

	for(int i=0;i<N;i++) buf[i] = 2*i;

	HANDLE hodd  = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"odd");
	HANDLE heven = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"even");
	HANDLE vlapa = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"vlapa");


	for(int i=0;i<N;i++)
	{
		WaitForSingleObject(heven,INFINITE);
		cout<<buf[i]<<".";
		ReleaseSemaphore(hodd,1,0);
	}

	return 0;
}

DWORD WINAPI pavla(void *p)
{
	int buf[N];

	for(int i=0;i<N;i++) buf[i] = 2*i;

	HANDLE hodd  = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"odd");
	HANDLE heven = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"even");
	HANDLE vlapa = OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,"vlapa");


	for(int i=0;i<N;i++)
	{
		WaitForSingleObject(heven,INFINITE);
		cout<<buf[i]<<"-";
		ReleaseSemaphore(vlapa,1,0);
	}

	return 0;
}


int main(int argc, char *argv[])
{
	CreateSemaphore(NULL,1,1,"even");
	CreateSemaphore(NULL,0,1,"odd");
	CreateSemaphore(NULL,0,0,"vlapa");

	DWORD d1,d2,d3;

	H[0] = CreateThread(NULL,0,f_even,NULL,0,&d1);
	H[1] = CreateThread(NULL,0,f_odd,NULL,0,&d2);
	H[2] = CreateThread(NULL,0,pavla,NULL,0,&d3);

	WaitForMultipleObjects(2,H,true,INFINITE);

	cout<<endl;

	int k;
	cin>>k;

	return 0;
}
