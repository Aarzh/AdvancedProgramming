#include <iostream>

using namespace std;

int main()
{
	char a;
	char b;

	cout<<"Ingrese el primer numero: "<<endl;
	cin>>a;
	cout<<"Ingrese el segundo numero: "<<endl;
	cin>>b;

	if(a>b)
	{
		cout<<"Primer numero mas grande"<<endl;
	}
	else
	{
		cout<<"Segundo numero mas grande"<<endl;
	}

	return 0;
}