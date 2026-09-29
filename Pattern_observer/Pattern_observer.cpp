#include <iostream>
#include <list>
#include <string>
#include <windows.h>



// 1. Спільний інтерфейс для всіх смарт-пристроїв (Спостерігач)
class Device {
public:
    virtual void update(int temperature) = 0;
    virtual std::string getName() = 0;
};

// 2. Центральний хаб розумного дому (Суб'єкт)
class SmartHub {
private:
    std::list<Device*> devices; // Список підключених пристроїв
    int currentTemp = 20;

public:
    // Підключити пристрій
    void attach(Device* device) {
        devices.push_back(device);
        std::cout << "[+] Підключено: " << device->getName() << "\n";
    }

    // Відключити пристрій
    void detach(Device* device) {
        devices.remove(device); // std::list дозволяє дуже легко видаляти
        std::cout << "[-] Відключено: " << device->getName() << "\n";
    }

    // Сповістити всі підключені пристрої про зміну
    void notify() {
        std::cout << "\n--- Увага! Нова температура: " << currentTemp << "°C ---\n";
        for (Device* device : devices) {
            device->update(currentTemp);
        }
    }

    // Встановити нову температуру на сенсорі
    void setTemperature(int temp) {
        currentTemp = temp;
        notify(); // Як тільки температура змінилась - повідомляємо всіх
    }
};

// 3. Конкретні смарт-пристрої
class AirConditioner : public Device {
public:
    void update(int temperature) override {
        if (temperature > 25) {
            std::cout << " -> Кондиціонер: УВІМКНЕНО (охолодження)\n";
        }
    }
    std::string getName() override { return "Кондиціонер"; }
};

class Heater : public Device {
public:
    void update(int temperature) override {
        if (temperature < 18) {
            std::cout << " -> Обігрівач: УВІМКНЕНО (нагрівання)\n";
        }
    }
    std::string getName() override { return "Обігрівач"; }
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    SmartHub hub;

    // Створюємо пристрої
    AirConditioner ac;
    Heater heater;

    // Підключаємо їх до хаба (передаємо адреси об'єктів через &)
    hub.attach(&ac);
    hub.attach(&heater);

    // Імітація 1: Стало спекотно
    hub.setTemperature(30);

    // Імітація 2: Стало холодно
    hub.setTemperature(10);

    // Відключаємо кондиціонер
    hub.detach(&ac);

    // Імітація 3: Знову спекотно, але кондиціонер відключений і не зреагує
    hub.setTemperature(28);

    return 0;
}