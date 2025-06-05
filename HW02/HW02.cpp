#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

// Animal 기본 클래스 정의
class Animal {
public:
    // 순수 가상 함수: 각 동물은 고유한 소리를 낼 것입니다.
    virtual void makeSound() = 0;

    // 가상 소멸자: 파생 클래스의 소멸자가 올바르게 호출되도록 합니다.
    virtual ~Animal() {
        std::cout << "Animal destructor called." << std::endl;
    }
};

// Dog 클래스 정의
class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "멍멍!" << std::endl;
    }
    ~Dog() override {
        std::cout << "Dog destructor called." << std::endl;
    }
};

// Cat 클래스 정의
class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "야옹!" << std::endl;
    }
    ~Cat() override {
        std::cout << "Cat destructor called." << std::endl;
    }
};

// Cow 클래스 정의
class Cow : public Animal {
public:
    void makeSound() override {
        std::cout << "음메!" << std::endl;
    }
    ~Cow() override {
        std::cout << "Cow destructor called." << std::endl;
    }
};

// Zoo 클래스 요구사항
class Zoo {
private:
    // 동물 객체를 저장하는 포인터 배열 (최대 10마리)
    Animal* animals[10];
    int animalCount; // 현재 동물 수

public:
    // 생성자
    Zoo() : animalCount(0) {
        // 배열 초기화 (nullptr로)
        for (int i = 0; i < 10; ++i) {
            animals[i] = nullptr;
        }
    }

    // 동물을 동물원에 추가하는 함수
    void addAnimal(Animal* animal) {
        if (animalCount < 10) {
            animals[animalCount++] = animal;
            std::cout << "동물이 동물원에 추가되었습니다." << std::endl;
        }
        else {
            std::cout << "동물원에 더 이상 동물을 추가할 수 없습니다. (최대 10마리)" << std::endl;
            // 배열이 꽉 찼을 경우, 추가되지 않은 동물 객체의 메모리 해제
            delete animal;
        }
    }

    // 동물원에 있는 모든 동물의 행동을 수행하는 함수
    void performActions() {
        std::cout << "\n--- 동물들의 행동 시작 ---" << std::endl;
        for (int i = 0; i < animalCount; ++i) {
            if (animals[i] != nullptr) {
                animals[i]->makeSound();
            }
        }
        std::cout << "--- 동물들의 행동 종료 ---\n" << std::endl;
    }

    // Zoo 소멸자
    ~Zoo() {
        std::cout << "Zoo 소멸자 호출됨. 동적 할당된 동물 객체 메모리 해제 중..." << std::endl;
        for (int i = 0; i < animalCount; ++i) {
            delete animals[i]; // 동적 할당된 Animal 객체 메모리 해제
            animals[i] = nullptr; // 포인터를 nullptr로 설정하여 dangling pointer 방지
        }
    }
};

// 랜덤 동물을 생성하는 함수
Animal* createRandomAnimal() {
    // 현재 시간을 시드로 사용하여 난수 생성기 초기화
    // 이 함수는 프로그램 시작 시 한 번만 호출하는 것이 좋습니다.
    // 여기서는 매번 호출될 수 있으므로, main 함수에서 srand(time(0));을 호출하는 것이 더 적절합니다.
    // srand(time(0)); // 주석 처리: main에서 한 번만 호출

    int randomNum = rand() % 3; // 0, 1, 2 중 하나의 난수 생성

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
    // 난수 생성기 초기화
    srand(static_cast<unsigned int>(time(0)));

    Zoo myZoo;

    // Dog, Cat, Cow 자료형의 변수를 선언하고, 배열에 저장해봅니다.
    // createRandomAnimal() 함수를 사용하여 동물을 추가합니다.
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(createRandomAnimal());
    myZoo.addAnimal(new Dog()); // 직접 추가
    myZoo.addAnimal(new Cat()); // 직접 추가

    // Animal 배열을 반복문으로 순회하면서 각 동물의 울음소리를 내게 합니다.
    myZoo.performActions();

    // main 함수 종료 시 myZoo 객체의 소멸자가 호출되어 동적 할당된 동물 객체들이 해제됩니다.

    return 0;
}