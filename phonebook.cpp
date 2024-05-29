#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class PhoneBook
{
private:
    string *names;
    string *phones;
    int phoneBookSize;
    int phoneBookEntries = 0;

public:
    void setSize(int);                 // 1
    bool addEntry(string, string);     // 2
    bool displayEntryAtIndex(int);     // 3
    void displayEntryAtIndices(int *); // 4
    void displayAll();                 // 5
    int *findByName(string);           // 6
    string findByPhone(string);        // 7
    bool updateNameAt(string, int);    // 8
    bool updatePhoneAt(string, int);   // 9
    void copyPB(const PhoneBook &);    // 10
    void clear();                      // 11
};

// 1
inline void PhoneBook::setSize(int size) // 1
{
    if (size > 0)
    {
        phoneBookSize = size;
        names = new string[size];
        phones = new string[size];
    }
    else
        cout << "Invalid size" << endl;
}
// 2
inline bool PhoneBook::addEntry(string name, string phoneNumber) // 2
{
    if (phoneNumber.length() != 11)
        return false;

    if (phoneBookEntries <= phoneBookSize)
    {
        names[phoneBookEntries] = name;

        for (int i = 0; i < 11; ++i)
        {
            if (!isdigit(phoneNumber[i]))
            {
                return false;
            }
            else
            {
                phones[phoneBookEntries] = phoneNumber;
            }
        }
    }
    else
        return false;
    phoneBookEntries++;
    return true;
}
// 3
inline bool PhoneBook::displayEntryAtIndex(int index) // 3
{
    if (index > phoneBookEntries)
        return false;

    cout << names[index - 1] << setw(30 - (names[index - 1].length())) << phones[index - 1] << endl;

    return true;
}
// 4
inline void PhoneBook::displayEntryAtIndices(int *indices) // 4
{
    for (int i = 0; i < phoneBookSize; i++)
    {
        if (indices[i] == 1)
            displayEntryAtIndex(i + 1);
    }
}
// 5
inline void PhoneBook::displayAll() // 5
{
    for (int i = 1; i <= phoneBookEntries; i++)
    {
        displayEntryAtIndex(i);
    }
}
// 6
inline int *PhoneBook::findByName(string searchName) // 6
{
    int *namesFound;
    namesFound = new int[phoneBookSize];
    for (int i = 0; i < phoneBookSize; i++)
    {
        namesFound[i] = 1;
        for (int j = 0; j < size(searchName) - 1; j++)
        {
            if (searchName[j] == names[i][j])
                continue;
            else
                namesFound[i] = 0;
            break;
        }
    }
    return namesFound;
}
// 7
inline string PhoneBook::findByPhone(string wantedPhone)
{
    string wantedName = " Invalid Phone Number";
    for (int i = 0; i < phoneBookEntries; i++)
    {
        if (phones[i] == wantedPhone)
            wantedName = names[i];
    }
    return wantedName;
}
// 8
inline bool PhoneBook::updateNameAt(string updatedName, int index)
{
    if (index <= phoneBookSize && index != 0)
    {
        names[index - 1] = updatedName;
    }
    else
        return false;
    if (updatedName == names[index - 1])
        return true;
    return false;
}
// 9
inline bool PhoneBook::updatePhoneAt(string updatedPhone, int index)
{
    for (int i = 0; i < updatedPhone.length(); i++)
    {
        if ((isdigit(updatedPhone[i])) == 0)
            return false;
    }

    if (updatedPhone.length() != 11)
        return false;
    if (index <= phoneBookSize && index != 0)
    {
        phones[index - 1] = updatedPhone;
    }
    else
        return false;
    if (updatedPhone == phones[index - 1])
        return true;
    return false;
}
// 10
inline void PhoneBook::copyPB(const PhoneBook &pb2)
{
    phoneBookSize = pb2.phoneBookSize;
    phoneBookEntries = pb2.phoneBookEntries;
    names = new string[phoneBookSize];
    phones = new string[phoneBookSize];
    for (int i = 0; i < phoneBookSize; ++i)
    {
        names[i] = pb2.names[i];
        phones[i] = pb2.phones[i];
    }
}
// 11
inline void
PhoneBook::clear()
{
    delete[] names;
    delete[] phones;
}

int main()
{
    PhoneBook myPhonebook;
    int size, choices;

    cout << "Enter the size of your phone book: ";
    cin >> size;
    myPhonebook.setSize(size);
    cin.ignore();
    for (int i = 0; i < size; ++i)
    {
        string name, phone;
        cout << "Enter name " << i + 1 << ": ";

        getline(cin, name);
        cout << "Enter phone " << i + 1 << ": ";
        getline(cin, phone);
        if (myPhonebook.addEntry(name, phone) == false)
        {
            cout << "Invalid input.\n";
            --i;
            continue;
        };
    }

    int exitCode = 1;
    while (exitCode != 0)
    {
        cout << endl
             << "Enter your choice \n"
             << "1- Display all phone book\n2- Search for entry/entries by name\n";
        cout << "3- Search for entry/entries by phone\n4- Find an entry by index\n5- Update name by index\n6- Update phone by index\n";
        cout << "7- Copy phone book to another and display entries of the new phone book\n8- Exit\nChoice:";
        cin >> choices;

        switch (choices)
        {
        default:
            cout << "\n Invalid Choice ";
            break;
        case 1:
            myPhonebook.displayAll();
            break;

        case 2:
        {
            string wantedName;
            cout << "\nEnter wanted name : ";
            cin.ignore();
            getline(cin, wantedName);

            for (int i = 0; i < size; ++i)
            {

                if ((myPhonebook.findByName(wantedName))[i] == 1)
                {
                    myPhonebook.displayEntryAtIndex(i + 1);
                }
            }
        }

        break;
        case 3:
        {
            string wantedPhone;
            cout << "\nEnter wanted phone : ";
            cin.ignore();
            getline(cin, wantedPhone);
            cout << endl
                 << (myPhonebook.findByPhone(wantedPhone));
            break;
        }

        case 4:
            int index;
            cout << "\nEnter index of the wanted person's info : ";
            cin.ignore();
            cin >> index;
            myPhonebook.displayEntryAtIndex(index);
            break;
        case 5:
        {
            int reqIndex;

            cout << "\nEnter index of the wanted person : ";
            cin >> reqIndex;

            string updatedName;
            cout << "\nEnter wanted name : ";
            cin.ignore();
            getline(cin, updatedName);

            myPhonebook.updateNameAt(updatedName, reqIndex);
            break;
        }

        case 6:
        {
            int reqIndex2;

            cout << "\nEnter index of the wanted person : ";
            cin >> reqIndex2;
            if (reqIndex2 > size && reqIndex2 <= 0)
                cout << "Invalid index.\n";

            string updatedPhone;
            cout << "\nEnter wanted phone : ";
            cin.ignore();
            getline(cin, updatedPhone);

            if (myPhonebook.updatePhoneAt(updatedPhone, reqIndex2) == 0)
                cout << "Invalid phone number.\n";
            break;
        }

        case 7:
        {
            PhoneBook newPhoneBook;
            newPhoneBook.copyPB(myPhonebook);
            newPhoneBook.displayAll();
            break;
        }
        case 8:
            exitCode = 0;
            myPhonebook.clear();
            break;
        }
    }

    return 0;
}
