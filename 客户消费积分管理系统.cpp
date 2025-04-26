#include <iostream>
#include <string>

using namespace std;

// 客户类
class Customer {
public:
    int id;
    string name;
    string contactInfo;//联系方式
    double points;

    Customer(int id_A, string name_A, string contactInfo_A)
    {
        id = id_A;
        name = name_A;
        contactInfo = contactInfo_A;
        points = 0;
    }
    Customer()
    {
        id = -1;
    }

    void addPoints(double amount) {
        points += amount;
    }

    double getPoints() const {
        return points;
    }
    double getDiscount() const {//const关键字
        // 假设1000积分兑换9折优惠
        if (points >= 1000&&points<=2000) {
            return 0.9;
        }
        else if(points > 2000)
        {
            return 0.8;
        }
        else {
            return 1.0; // 无折扣
        }
    }
};

// 消费信息类
class Consumption {
public:
    int id;
    double amount;
    Customer* customer;

  
    Consumption(int id_A, double amount_A, Customer* customer_A)
    {
        id = id_A;
        amount = amount_A;
        customer = customer_A;
    }
    // 默认构造函数
    Consumption()
    {
        id = -1;
        amount = 0;
        customer = nullptr;
    }
    void calculatePoints() {
        // 假设每消费1元获得1积分
        if (customer != nullptr) {
            customer->addPoints(amount);
        }
    }
};

// 线性表类
template <typename T>
class LinearList {
private:
    T* data;          // 存储数据的数组
    int capacity;     // 线性表的容量
    int size;        // 线性表的当前大小

public:
    LinearList(int capacity_A) 
    {
        capacity = capacity_A;
        size = 0;
        data = new T[capacity];
    }

    LinearList(T* data1, int capacity1, int size1)
    {
        data = data1;
        capacity = capacity1;
        size = size1;
    }
    ~LinearList() 
    {
        delete[] data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }

    void add(const T& element) {
        if (isFull()) {
            cout << "线性表内存已满！" << endl;
            return;
        }
        data[size] = element;
        size++;
    }

    bool remove(int id) {
        for (int i = 0; i < size; ++i) {
            if (data[i].id == id) {
                for (int j = i; j < size - 1; ++j) {
                    data[j] = data[j + 1];
                }
                size--;
                return true;
            }
        }
        return false;
    }

    T& find(int id) {
        for (int i = 0; i < size; ++i) {
            if (data[i].id == id) {
                return data[i];
            }
        }
        static T temp; // 返回一个临时对象以避免 returning nullptr
        return temp;
    }

    bool update(int id, const T& element) {
        for (int i = 0; i < size; ++i) {
            if (data[i].id == id) {
                data[i] = element;
                return true;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            cout << "ID: " << data[i].id << ", Name: " << data[i].name << ", Contact: " << data[i].contactInfo << ", Points: " << data[i].points << endl;
        }
    }
};

// 客户管理系统
class CustomerManagementSystem {
private:
    LinearList<Customer> customers;  // 存储客户信息的线性表
    LinearList<Consumption> consumptions; // 存储消费信息的线性表

public:
    CustomerManagementSystem(int capacity): customers(capacity), consumptions(capacity) {}
  
    // 添加客户
    void addCustomer(int id, string name, string contactInfo) {
        Customer customer(id, name, contactInfo);
        customers.add(customer);
        cout << "客户成功添加！" << endl;
        system("pause");
        system("cls");
    }

    // 删除客户
    void removeCustomer(int id) {
        if (customers.remove(id)) {
            cout << "客户成功删除！" << endl;
        }
        else {
            cout << "该客户不存在" << endl;
        }
        system("pause");
        system("cls");
    }

    // 修改客户信息
    void updateCustomer(int id, string name, string contactInfo) {
        Customer customer(id, name, contactInfo);
        if (customers.update(id, customer)) {
            cout << "客户成功修改！" << endl;
        }
        else {
            cout << "该客户不存在" << endl;
        }
        system("pause");
        system("cls");
    }

    // 查询客户信息
    void queryCustomer(int id) {
        Customer& customer = customers.find(id);
        if (customer.id != -1) { // -1 是未找到时的标记
            cout << "客户信息：" << endl;
            cout << "ID: " << customer.id << endl;
            cout << "姓名: " << customer.name << endl;
            cout << "联系方式: " << customer.contactInfo << endl;
            cout << "积分: " << customer.points << endl;
        }
        else {
            cout << "客户不存在。" << endl;
        }
        system("pause");
        system("cls");
    }

    // 添加消费信息
    void addConsumption(int id, double amount, int customerId) {
        Customer& customer = customers.find(customerId);
        if (customer.id != -1) { // 检查是否找到了客户
            Consumption consumption(id, amount, &customer);
            consumption.calculatePoints(); // 更新积分
            consumptions.add(consumption);
            cout << "客户消费信息成功添加" << endl;
        }
        else {
            cout << "该客户不存在" << endl;
        }
        system("pause");
        system("cls");
    }

    // 删除消费信息
    void removeConsumption(int id) {
        if (consumptions.remove(id)) {
            cout << "消费信息成功删除" << endl;
        }
        else {
            cout << "该消费信息不存在" << endl;
        }
        system("pause");
        system("cls");
    }

    // 修改消费信息
    void updateConsumption(int id, double amount) {
        Consumption& consumption = consumptions.find(id);
        if (consumption.id != -1) { // -1 是未找到时的标记
            consumption.amount = amount;
            consumption.calculatePoints();
            cout << "消费信息修改成功！" << endl;
        }
        else {
            cout << "该消费信息不存在" << endl;
        }
        system("pause");
        system("cls");
    }

    // 查询消费信息
    void queryConsumption(int id) {
        Consumption& consumption = consumptions.find(id);
        if (consumption.id != -1) { // -1 是未找到时的标记
            cout << "ID: " << consumption.id << ", Amount: " << consumption.amount << ", Customer ID: " << consumption.customer->id << endl;
        }
        else {
            cout << "该消费信息不存在" << endl;
        }
        system("pause");
        system("cls");
    }
    //显示折扣信息
    void showCustomerDiscount(int id) {
        Customer& customer = customers.find(id);
        if (customer.id != -1) { // 检查是否找到了客户
            double discount = customer.getDiscount();
            cout << "客户ID: " << customer.id << ", 姓名: " << customer.name
                << ", 联系方式: " << customer.contactInfo << ", 积分: " << customer.points
                << ", 折扣: " << discount * 100 << "%" << endl;
        }
        else {
            cout << "客户不存在。" << endl;
        }
        system("pause");
        system("cls");
    }
}; 

int main() {
    const int capacity = 100;
    CustomerManagementSystem cms(capacity);
    int choice, id, customerId;
    string name, contactInfo;
    double amount;

    while (true) {
        cout << "************************************************************" << endl;
        cout << "*******************欢迎客户消费积分管理系统*****************" << endl;
        cout << "************************1. 添加用户操作*********************" << endl;
        cout << "************************2. 删除用户操作*********************" << endl;
        cout << "************************3. 修改用户信息*********************" << endl;
        cout << "************************4. 查询用户信息*********************" << endl;
        cout << "************************5. 添加消费信息*********************" << endl;
        cout << "************************6. 删除消费信息*********************" << endl;
        cout << "************************7. 修改消费信息*********************" << endl;
        cout << "************************8. 查询消费信息*********************" << endl;
        cout << "************************9. 查询打折优惠*********************" << endl;
        cout << "************************0.   退  出    *********************" << endl;
        cout << "*********************请输入您想要进行的操作*****************" << endl;
        cout << "************************************************************" << endl;
        cout << endl;
        
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "请输入1.用户ID   2.用户姓名  3.用户联系方式 " << endl;
            while (!(cin >> id)) {
                cout << "输入错误，请输入数字作为用户ID: "<<endl;
                cin.clear(); // 清除错误状态
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略ID后的换行符
            getline(cin, name); // 读取姓名
            getline(cin, contactInfo); // 读取联系方式
            cms.addCustomer(id, name, contactInfo);
            break;
        case 2:
            cout << "请输入想要删除用户的ID " << endl;;
            cin >> id;
            cms.removeCustomer(id);
            break;
        case 3:
            cout << "请输入想要修改的用户ID并输入修改后的用户信息 "<<endl;
            cin >> id >> name >> contactInfo;
            cms.updateCustomer(id, name, contactInfo);
            break;
        case 4:
            cout << "请输入想要查询的用户ID " << endl;
            cin >> id;
            cms.queryCustomer(id);
            break;
        case 5:
            cout << "请输入消费记录的ID、金额和客户ID " << endl;
            cin >> id >> amount >> customerId;
            cms.addConsumption(id, amount, customerId);
            break;
        case 6:
            cout << "请输入要删除的消费记录的ID" << endl;
            cin >> id;
            cms.removeConsumption(id);
            break;
        case 7:
            cout << "请输入要更新的消费记录的ID和新的金额 " << endl;
            cin >> id >> amount;
            cms.updateConsumption(id, amount);
            break;
        case 8:
            cout << "请输入要查询的消费记录的ID "<<endl;
            cin >> id;
            cms.queryConsumption(id);
            break;
        case 9:
            cout << "请输入要显示折扣信息的客户ID: ";
            cin >> id;
            cms.showCustomerDiscount(id);
            break;

        case 0:
            return 0;
        default:
            cout << "错误选择，请重新输入您想要进行的操作" << endl;
        }
    }

    return 0;
}