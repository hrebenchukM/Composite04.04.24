#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
 *  Паттерн проектирования, объединяет объекты в древовидную структуру для представления иерархии от частного к целому.
 *  Позволяет клиентам единообразно трактовать индивидуальные и составные объекты.
	Паттерн определяет иерархию классов, которые могут состоять из примитивных и сложных объектов, упрощает архитектуру клиента,
 *  делает процесс добавления новых видов объекта более простым.
 *
 * Одна из целей паттерна компоновщик - избавить клиентов от необходимости знать, работают ли они с листовым или составным объектом.
 * Для достижения этой цели класс Component должен сделать как можно больше операций общими для классов Composite и Leaf.
 * Обычно класс Component предоставляет для этих операций реализации по умолчанию, а подклассы Composite и Leaf замещают их.
 *
 * Результаты:
 * - определяет иерархии классов, состоящие из примитивных и составных объектов.
 * - упрощает архитектуру клиента.
 * - облегчает добавление новых видов компонентов.
 * - способствует созданию общего дизайна
*/

/*
 Component
	- объявляет интерфейс для компонуемых объектов;
	- предоставляет подходящую реализацию операций по умолчанию, общую для всех классов;
	- объявляет интерфейс для доступа к потомкам и управления ими;
	- определяет интерфейс для доступа к родителю компонента в рекурсивной структуре и при необходимости реализует его.
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
 *  - определяет поведение компонентов, у которых есть потомки;
	- хранит компоненты-потомки;
	- реализует относящиеся к управлению потомками операции в интерфейсе класса Component;
*/

class Composite : public Component//Приемная 
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
		cout << "Сумма всех предметов офиса: " << sum << endl;
	}

	


};
/*
 * Leaf
	- представляет листовые узлы композиции и не имеет потомков;
	- определяет поведение примитивных объектов в композиции;
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
	Component* root = new Composite("Приемная");
	root->Add(new Leaf("Должна быть выполнена в теплых тонах",200));
	Component* comp = new Composite("Журнальный столик",100);
	comp->Add(new Leaf("10-20 журналов типа компьютерный мир",200));
	root->Add(comp);
	root->Add(new Leaf("Мягкий диван",200));
	Component* comp2 = new Composite("Стол секретаря",1500);
	Component* comp3 = new Composite("Компьютер");
	comp3->Add(new Leaf("Важно наличие большого объема жесткого диска",100));
	comp2->Add(new Leaf("Офисный инструментарий",100));
	comp2->Add(comp3);
	root->Add(comp2);
	root->Add(new Leaf("Кулер с теплой и холодной водой",400));
	root->Display(1);
	cout << "\n\n";










	Component* root2 = new Composite("Аудитория 1");
	root2->Add(new Leaf("10 столов",1000));
	root2->Add(new Leaf("Доска",200));
	Component* comp4 = new Composite("Стол учителя",1300);
	comp4->Add(new Leaf("Компьютер",200));
	root2->Add(comp4);
	root2->Add(new Leaf("Плакаты великих математиков",200));
	root2->Display(1);
	cout << "\n\n";






	Component* root3 = new Composite("Аудитория 2");
	Component* comp5 = new Composite("20 столов",2000);
	comp5->Add(new Leaf("Столы черного цвета",1000));
	comp5->Add(new Leaf("Столы выставлены в овал или круг",1000));
	root3->Add(comp5);
	root3->Add(new Leaf("Доска",200));
	root3->Add(new Leaf("Мягкий диван",200));
	root3->Display(1);
	cout << "\n\n";





	Component* root4 = new Composite("Компьютерная аудитория");
	Component* comp6 = new Composite("10 компьютерных столов",1000);
	root4->Add(comp6);
	Component* comp7 = new Composite("Компьютер на каждом столе",100);
	comp6->Add(comp7);
	comp7->Add(new Leaf("Процессор 2.2ГРц",10));
	comp7->Add(new Leaf("Винчестер на 80ГБ",10));
	comp7->Add(new Leaf("Оперативная память 1024МБ",10));
	comp6->Add(new Leaf("Розетка возле каждого стола",10));
	Component* comp8 = new Composite("Доска",250);
	comp8->Add(new Leaf("Набор разноцветных маркеров",10));
	root4->Add(comp8);
	root4->Display(1);
	cout << "\n\n";





	Component* root5 = new Composite("Столовая");
	root5->Add(new Leaf("Кофейный автомат",500));
	Component* comp9 = new Composite("Стол",540);
	comp9->Add(new Leaf("4 стула",0));
	root5->Add(comp9);
	root5->Add(new Leaf("Холодильник",400));
	root5->Add(new Leaf("Умывальник",300));
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


