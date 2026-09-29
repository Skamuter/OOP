#include <iostream>
#include <string>
#include <vector>

class Student {
	std::string name;
	std::vector<int> grades;// оценки хранятся в самом объекте
public:
	Student(const std::string& name_) : name(name_) {}

	// добавление оценки (допустимы значения от 1 до 100)
	void add_grade(int grade) {
		if (grade < 1 || grade > 100) {
			std::cout << "Error: you may add points not below 0 and higher than 100\n";
			return;
		}
		grades.push_back(grade);
	}

	// просмотр оценок
	void show_grades() const {
		std::cout << "Student: " << name << "\nScore: ";
		if (grades.empty()) {
			std::cout << "Nothing";
		}
		for (int g : grades) {
			std::cout << g << ' ';
		}
		std::cout << '\n';
	}

	// средний балл
	int get_sum() const {
		int sum = 0;
		for (int g : grades) sum += g;
		return sum;
	}
};

int main() {

	Student st("Ivan");
	st.add_grade(6);
	st.add_grade(15);
	st.add_grade(4);
	st.add_grade(0);// будет отклонена
	st.show_grades();
	std::cout << "score: " << st.get_sum() << '\n';
}

/*
#include <iostream>
// создать класс Student с хранением информаци об оценках в объъекте
// предусмотреть методы для добавления оценок и их просмотра 
class Box {
	double length = 0.0;
	double width = 0.0;
	double height = 0.0;
public : // интерфейс
	Box(double len_, double wid_, double heig_) :
		length(len_), width(wid_), height(heig_)
		
	{}//lenght = len_; widht = wid_; height = heig_;
	//конструктор преоброзования
	Box(double side): length(side), width(side), height(side){}
	double get_volume() {
		return length * width * height;
	}
};

int main() {
	Box box1 = { 6, 5, 4 };
	std::cout << box1.get_volume();
}*/