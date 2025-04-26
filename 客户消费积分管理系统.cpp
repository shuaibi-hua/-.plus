#include <iostream>
#include <string>

using namespace std;

// �ͻ���
class Customer {
public:
    int id;
    string name;
    string contactInfo;//��ϵ��ʽ
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
    double getDiscount() const {//const�ؼ���
        // ����1000���ֶһ�9���Ż�
        if (points >= 1000&&points<=2000) {
            return 0.9;
        }
        else if(points > 2000)
        {
            return 0.8;
        }
        else {
            return 1.0; // ���ۿ�
        }
    }
};

// ������Ϣ��
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
    // Ĭ�Ϲ��캯��
    Consumption()
    {
        id = -1;
        amount = 0;
        customer = nullptr;
    }
    void calculatePoints() {
        // ����ÿ����1Ԫ���1����
        if (customer != nullptr) {
            customer->addPoints(amount);
        }
    }
};

// ���Ա���
template <typename T>
class LinearList {
private:
    T* data;          // �洢���ݵ�����
    int capacity;     // ���Ա������
    int size;        // ���Ա�ĵ�ǰ��С

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
            cout << "���Ա��ڴ�������" << endl;
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
        static T temp; // ����һ����ʱ�����Ա��� returning nullptr
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

// �ͻ�����ϵͳ
class CustomerManagementSystem {
private:
    LinearList<Customer> customers;  // �洢�ͻ���Ϣ�����Ա�
    LinearList<Consumption> consumptions; // �洢������Ϣ�����Ա�

public:
    CustomerManagementSystem(int capacity): customers(capacity), consumptions(capacity) {}
  
    // ��ӿͻ�
    void addCustomer(int id, string name, string contactInfo) {
        Customer customer(id, name, contactInfo);
        customers.add(customer);
        cout << "�ͻ��ɹ���ӣ�" << endl;
        system("pause");
        system("cls");
    }

    // ɾ���ͻ�
    void removeCustomer(int id) {
        if (customers.remove(id)) {
            cout << "�ͻ��ɹ�ɾ����" << endl;
        }
        else {
            cout << "�ÿͻ�������" << endl;
        }
        system("pause");
        system("cls");
    }

    // �޸Ŀͻ���Ϣ
    void updateCustomer(int id, string name, string contactInfo) {
        Customer customer(id, name, contactInfo);
        if (customers.update(id, customer)) {
            cout << "�ͻ��ɹ��޸ģ�" << endl;
        }
        else {
            cout << "�ÿͻ�������" << endl;
        }
        system("pause");
        system("cls");
    }

    // ��ѯ�ͻ���Ϣ
    void queryCustomer(int id) {
        Customer& customer = customers.find(id);
        if (customer.id != -1) { // -1 ��δ�ҵ�ʱ�ı��
            cout << "�ͻ���Ϣ��" << endl;
            cout << "ID: " << customer.id << endl;
            cout << "����: " << customer.name << endl;
            cout << "��ϵ��ʽ: " << customer.contactInfo << endl;
            cout << "����: " << customer.points << endl;
        }
        else {
            cout << "�ͻ������ڡ�" << endl;
        }
        system("pause");
        system("cls");
    }

    // ���������Ϣ
    void addConsumption(int id, double amount, int customerId) {
        Customer& customer = customers.find(customerId);
        if (customer.id != -1) { // ����Ƿ��ҵ��˿ͻ�
            Consumption consumption(id, amount, &customer);
            consumption.calculatePoints(); // ���»���
            consumptions.add(consumption);
            cout << "�ͻ�������Ϣ�ɹ����" << endl;
        }
        else {
            cout << "�ÿͻ�������" << endl;
        }
        system("pause");
        system("cls");
    }

    // ɾ��������Ϣ
    void removeConsumption(int id) {
        if (consumptions.remove(id)) {
            cout << "������Ϣ�ɹ�ɾ��" << endl;
        }
        else {
            cout << "��������Ϣ������" << endl;
        }
        system("pause");
        system("cls");
    }

    // �޸�������Ϣ
    void updateConsumption(int id, double amount) {
        Consumption& consumption = consumptions.find(id);
        if (consumption.id != -1) { // -1 ��δ�ҵ�ʱ�ı��
            consumption.amount = amount;
            consumption.calculatePoints();
            cout << "������Ϣ�޸ĳɹ���" << endl;
        }
        else {
            cout << "��������Ϣ������" << endl;
        }
        system("pause");
        system("cls");
    }

    // ��ѯ������Ϣ
    void queryConsumption(int id) {
        Consumption& consumption = consumptions.find(id);
        if (consumption.id != -1) { // -1 ��δ�ҵ�ʱ�ı��
            cout << "ID: " << consumption.id << ", Amount: " << consumption.amount << ", Customer ID: " << consumption.customer->id << endl;
        }
        else {
            cout << "��������Ϣ������" << endl;
        }
        system("pause");
        system("cls");
    }
    //��ʾ�ۿ���Ϣ
    void showCustomerDiscount(int id) {
        Customer& customer = customers.find(id);
        if (customer.id != -1) { // ����Ƿ��ҵ��˿ͻ�
            double discount = customer.getDiscount();
            cout << "�ͻ�ID: " << customer.id << ", ����: " << customer.name
                << ", ��ϵ��ʽ: " << customer.contactInfo << ", ����: " << customer.points
                << ", �ۿ�: " << discount * 100 << "%" << endl;
        }
        else {
            cout << "�ͻ������ڡ�" << endl;
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
        cout << "*******************��ӭ�ͻ����ѻ��ֹ���ϵͳ*****************" << endl;
        cout << "************************1. ����û�����*********************" << endl;
        cout << "************************2. ɾ���û�����*********************" << endl;
        cout << "************************3. �޸��û���Ϣ*********************" << endl;
        cout << "************************4. ��ѯ�û���Ϣ*********************" << endl;
        cout << "************************5. ���������Ϣ*********************" << endl;
        cout << "************************6. ɾ��������Ϣ*********************" << endl;
        cout << "************************7. �޸�������Ϣ*********************" << endl;
        cout << "************************8. ��ѯ������Ϣ*********************" << endl;
        cout << "************************9. ��ѯ�����Ż�*********************" << endl;
        cout << "************************0.   ��  ��    *********************" << endl;
        cout << "*********************����������Ҫ���еĲ���*****************" << endl;
        cout << "************************************************************" << endl;
        cout << endl;
        
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "������1.�û�ID   2.�û�����  3.�û���ϵ��ʽ " << endl;
            while (!(cin >> id)) {
                cout << "�������������������Ϊ�û�ID: "<<endl;
                cin.clear(); // �������״̬
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Դ�������
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ����ID��Ļ��з�
            getline(cin, name); // ��ȡ����
            getline(cin, contactInfo); // ��ȡ��ϵ��ʽ
            cms.addCustomer(id, name, contactInfo);
            break;
        case 2:
            cout << "��������Ҫɾ���û���ID " << endl;;
            cin >> id;
            cms.removeCustomer(id);
            break;
        case 3:
            cout << "��������Ҫ�޸ĵ��û�ID�������޸ĺ���û���Ϣ "<<endl;
            cin >> id >> name >> contactInfo;
            cms.updateCustomer(id, name, contactInfo);
            break;
        case 4:
            cout << "��������Ҫ��ѯ���û�ID " << endl;
            cin >> id;
            cms.queryCustomer(id);
            break;
        case 5:
            cout << "���������Ѽ�¼��ID�����Ϳͻ�ID " << endl;
            cin >> id >> amount >> customerId;
            cms.addConsumption(id, amount, customerId);
            break;
        case 6:
            cout << "������Ҫɾ�������Ѽ�¼��ID" << endl;
            cin >> id;
            cms.removeConsumption(id);
            break;
        case 7:
            cout << "������Ҫ���µ����Ѽ�¼��ID���µĽ�� " << endl;
            cin >> id >> amount;
            cms.updateConsumption(id, amount);
            break;
        case 8:
            cout << "������Ҫ��ѯ�����Ѽ�¼��ID "<<endl;
            cin >> id;
            cms.queryConsumption(id);
            break;
        case 9:
            cout << "������Ҫ��ʾ�ۿ���Ϣ�Ŀͻ�ID: ";
            cin >> id;
            cms.showCustomerDiscount(id);
            break;

        case 0:
            return 0;
        default:
            cout << "����ѡ����������������Ҫ���еĲ���" << endl;
        }
    }

    return 0;
}