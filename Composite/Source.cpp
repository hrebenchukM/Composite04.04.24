#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
 *  ������� ��������������, ���������� ������� � ����������� ��������� ��� ������������� �������� �� �������� � ������.
 *  ��������� �������� ������������ ���������� �������������� � ��������� �������.
	������� ���������� �������� �������, ������� ����� �������� �� ����������� � ������� ��������, �������� ����������� �������,
 *  ������ ������� ���������� ����� ����� ������� ����� �������.
 *
 * ���� �� ����� �������� ����������� - �������� �������� �� ������������� �����, �������� �� ��� � �������� ��� ��������� ��������.
 * ��� ���������� ���� ���� ����� Component ������ ������� ��� ����� ������ �������� ������ ��� ������� Composite � Leaf.
 * ������ ����� Component ������������� ��� ���� �������� ���������� �� ���������, � ��������� Composite � Leaf �������� ��.
 *
 * ����������:
 * - ���������� �������� �������, ��������� �� ����������� � ��������� ��������.
 * - �������� ����������� �������.
 * - ��������� ���������� ����� ����� �����������.
 * - ������������ �������� ������ �������
*/

/*
 Component
	- ��������� ��������� ��� ����������� ��������;
	- ������������� ���������� ���������� �������� �� ���������, ����� ��� ���� �������;
	- ��������� ��������� ��� ������� � �������� � ���������� ���;
	- ���������� ��������� ��� ������� � �������� ���������� � ����������� ��������� � ��� ������������� ��������� ���.
 */

class Component abstract
{
protected:
	string name;
	int price;
public: 
	Component(string name)
	{
		this->name = name;
	}
	Component(string name, int price)
	{
		this->name = name;
		this->price = price;
	}

	int GetPrice()
	{
		return price;
	}
	

	virtual  void Add(Component *c) abstract;
	virtual  void Remove(Component *c) abstract;
	virtual  void Display(int depth) abstract;
	
};

/*
 * Composite
 *  - ���������� ��������� �����������, � ������� ���� �������;
	- ������ ����������-�������;
	- ��������� ����������� � ���������� ��������� �������� � ���������� ������ Component;
*/

class Composite : public Component//�������� 
{
	vector<Component*> components;

public:
	Composite(string name):Component(name){	}
	Composite(string name,int price) :Component(name, price) {	}

	void Add(Component * component) override
	{
		components.push_back(component);
	}
	void Remove(Component *component) override
	{
		auto iter = find(components.begin(), components.end(), component);
		components.erase(iter);
	}
	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << " Price :" << price << endl;
		int sum=0;

		for(Component *component : components)
		{
			
			component->Display(depth + 1);
			sum = sum + component->GetPrice();
		}
		cout << "����� ���� ��������� �����: " << sum << endl;
	}

	


};
/*
 * Leaf
	- ������������ �������� ���� ���������� � �� ����� ��������;
	- ���������� ��������� ����������� �������� � ����������;
 */
class Leaf : public Component
{
public:
	Leaf(string name,int price): Component(name,price){	}
	Leaf(string name) : Component(name) {	}
	void Add(Component *c) override
	{
		cout << "Cannot add to file\n";
	}
	void Remove(Component *c) override
	{
		cout << "Cannot remove from file\n";
	}
	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name <<" Price :" <<price << endl;
		
	}

	



};




int main()
{
	setlocale(LC_ALL, "Russian");
	Component* root = new Composite("��������");
	root->Add(new Leaf("������ ���� ��������� � ������ �����",200));
	Component* comp = new Composite("���������� ������",100);
	comp->Add(new Leaf("10-20 �������� ���� ������������ ���",200));
	root->Add(comp);
	root->Add(new Leaf("������ �����",200));
	Component* comp2 = new Composite("���� ���������",1500);
	Component* comp3 = new Composite("���������");
	comp3->Add(new Leaf("����� ������� �������� ������ �������� �����",100));
	comp2->Add(new Leaf("������� ��������������",100));
	comp2->Add(comp3);
	root->Add(comp2);
	root->Add(new Leaf("����� � ������ � �������� �����",400));
	root->Display(1);
	cout << "\n\n";










	Component* root2 = new Composite("��������� 1");
	root2->Add(new Leaf("10 ������",1000));
	root2->Add(new Leaf("�����",200));
	Component* comp4 = new Composite("���� �������",1300);
	comp4->Add(new Leaf("���������",200));
	root2->Add(comp4);
	root2->Add(new Leaf("������� ������� �����������",200));
	root2->Display(1);
	cout << "\n\n";






	Component* root3 = new Composite("��������� 2");
	Component* comp5 = new Composite("20 ������",2000);
	comp5->Add(new Leaf("����� ������� �����",1000));
	comp5->Add(new Leaf("����� ���������� � ���� ��� ����",1000));
	root3->Add(comp5);
	root3->Add(new Leaf("�����",200));
	root3->Add(new Leaf("������ �����",200));
	root3->Display(1);
	cout << "\n\n";





	Component* root4 = new Composite("������������ ���������");
	Component* comp6 = new Composite("10 ������������ ������",1000);
	root4->Add(comp6);
	Component* comp7 = new Composite("��������� �� ������ �����",100);
	comp6->Add(comp7);
	comp7->Add(new Leaf("��������� 2.2���",10));
	comp7->Add(new Leaf("��������� �� 80��",10));
	comp7->Add(new Leaf("����������� ������ 1024��",10));
	comp6->Add(new Leaf("������� ����� ������� �����",10));
	Component* comp8 = new Composite("�����",250);
	comp8->Add(new Leaf("����� ������������ ��������",10));
	root4->Add(comp8);
	root4->Display(1);
	cout << "\n\n";





	Component* root5 = new Composite("��������");
	root5->Add(new Leaf("�������� �������",500));
	Component* comp9 = new Composite("����",540);
	comp9->Add(new Leaf("4 �����",0));
	root5->Add(comp9);
	root5->Add(new Leaf("�����������",400));
	root5->Add(new Leaf("����������",300));
	root5->Display(1);
	cout << "\n\n";







	
	


	/*Component* root = new Composite("root");

	root->Add(new Leaf("File A"));
	root->Add(new Leaf("File B"));

	Component* comp = new Composite("Folder X");

	comp->Add(new Leaf("File XA"));
	comp->Add(new Leaf("File XB"));
	root->Add(comp);

	Component* comp2 = new Composite("Folder Y");

	comp2->Add(new Leaf("File YA"));
	comp2->Add(new Leaf("File YB"));

	Component* comp3 = new Composite("Folder Z");
	comp3->Add(new Leaf("File YZA"));
	comp3->Add(new Leaf("File YZB"));
	comp2->Add(comp3);

	root->Add(comp2);

	root->Add(new Leaf("File C"));

	Component* leaf = new Leaf("File D");
	root->Add(leaf);
	root->Display(1);
	cout << "\n\n";

	root->Remove(leaf);
	root->Display(1);

	cout << "\n\n";
	comp2->Remove(comp3);
	root->Display(1);*/

	system("pause");
}


