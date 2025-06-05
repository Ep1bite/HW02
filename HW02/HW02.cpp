#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime>  

class Animal {
public:
    virtual void makeSound() = 0;

    virtual ~Animal() {
        std::cout << "Animal destructor called." << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "멍멍!" << std::endl;
    }
    ~Dog() override {
        std::cout << "Dog destructor called." << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "야옹!" << std::endl;
    }
    ~Cat() override {
        std::cout << "Cat destructor called." << std::endl;
    }
};

class Cow : public Animal {
public:
    void makeSound() override {
        std::cout << "음메!" << std::endl;
    }
    ~Cow() override {
        std::cout << "Cow destructor called." << std::endl;
    }
};

class Zoo {
private:
    Animal* animals[10];
    int animalCount;

public:
    // 생성자
    Zoo() : animalCount(0) {
        for (int i = 0; i < 10; ++i) {
            animals[i] = nullptr;
        }
    }

    void addAnimal(Animal* animal) {
        if (animalCount < 10) {
            animals[animalCount++] = animal;
            std::cout << "동물이 동물원에 추가되었습니다." << std::endl;
        }
        else {
            std::cout << "동물원에 더 이상 동물을 추가할 수 없습니다. (최대 10마리)" << std::endl;
            delete animal;
        }
    }

    void performActions() {
        std::cout << "\n--- 동물들의 행동 시작 ---" << std::endl;
        for (int i = 0; i < animalCount; ++i) {
            if (animals[i] != nullptr) {
                animals[i]->makeSound();
            }
        }
        std::cout << "--- 동물들의 행동 종료 ---\n" << std::endl;
    }

    ~Zoo() {
        std::cout << "Zoo 소멸자 호출됨. 동적 할당된 동물 객체 메모리 해제 중..." << std::endl;
        for (int i = 0; i < animalCount; ++i) {
            delete animals[i];
            animals[i] = nullptr;
        }
    }
};

Animal* createRandomAnimal() {

    int randomNum = rand() % 3; 

    if (randomNum == 0) {
        std::cout << "Dog 생성" << std::endl;
        return new Dog();
    }
    else if (randomNum == 1) {
        std::cout << "Cat 생성" << std::endl;
        return new Cat();
    }
    else {
        std::cout << "Cow 생성" << std::endl;
        return new Cow();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Zoo myZoo;

    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(new Dog());
    myZoo.addAnimal(new Cat());

    myZoo.performActions();


    return 0;
}
