#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Employee class
class Employee
{
private:
    int empId;
    string empName;
    string position;
    string startDate;
    float basicSalary;
    float hourlyWage;

public:
    Employee() : empId(0), empName(""), position(""), startDate(""), basicSalary(0), hourlyWage(0) {}

    string getEmpName()
    {
        return empName;
    }

    void Hourly_wage_cal()
    {
        hourlyWage = (basicSalary / 30 / 8);
    }
    float get_hourlyWage() { return hourlyWage; }
    float get_basicSalary() { return basicSalary; }

    void setdata()
    {
        cout << "Enter employee id: ";
        cin >> empId;
        cin.ignore();
        cout << "Enter employee name: ";
        getline(cin, empName);
        cout << "Enter employee position \n(Barista,Cashier,Spervisor,Kitchen Staff,Cleaner,Waiter/Waitress): ";
        getline(cin, position);

        if (position == "Barista")
        {
            basicSalary = 1920;
        }
        else if (position == "Cashier")
        {
            basicSalary = 1790;
        }
        else if (position == "Supervisor")
        {
            basicSalary = 2400;
        }
        else if (position == "Kitchen Staff")
        {
            basicSalary = 1850;
        }
        else if (position == "Cleaner")
        {
            basicSalary = 1400;
        }
        else if (position == "Waiter" || position == "Waitress")
        {
            basicSalary = 1700;
        }
        else
        {
            cout << "Invalid position" << endl;
        }

        cout << "Enter employee Start date (dd/mm/yyyy): ";
        getline(cin, startDate);

        Hourly_wage_cal(); // Calculate hourly wage
    }

    void display_data()
    {
        cout << left << setw(10) << empId
             << setw(20) << empName
             << setw(15) << position
             << setw(15) << startDate
             << setw(15) << basicSalary
             << setw(15) << hourlyWage;
    }

    int getEmpId()
    {
        return empId;
    }
};

// Full-Time Employee class
class Full_Time : public Employee
{
private:
    int leaveDay, overTime;
    float bonus, netSalary;

public:
    Full_Time() : leaveDay(0), overTime(0), bonus(0), netSalary(0) {}

    void set_fulltime_data()
    {
        setdata();
        cout << "Enter leave day: ";
        cin >> leaveDay;
        cout << "Enter over time hours: ";
        cin >> overTime;
        Cal_bonus_and_netSalary();
    }

    void display_fulltime_data()
    {
        display_data();
        cout << setw(15) << leaveDay
             << setw(15) << bonus
             << setw(15) << netSalary << endl;
    }

    void Cal_bonus_and_netSalary()
    {
        // Calculate bonus for leave days
        if (leaveDay == 0)
            bonus += 300;
        else if (leaveDay == 1)
            bonus += 200;
        else if (leaveDay == 2)
            bonus += 100;

        // Calculate bonus for overtime
        bonus += (get_hourlyWage() * 2) * overTime;

        // Calculate net salary
        netSalary = get_basicSalary() + bonus - ((get_basicSalary() * 0.02) + 10);
    }
};

// Part-Time Employee class
class Part_Time : public Employee
{
private:
    int workingHour;
    float netPartTimeFee;

public:
    Part_Time() : workingHour(0), netPartTimeFee(0) {}

    void set_parttime_data()
    {
        setdata();
        cout << "Enter working hours (monthly): ";
        cin >> workingHour;
        Cal_netpartTime_fee();
    }

    void display_parttime_data()
    {
        display_data();
        cout << setw(15) << workingHour
             << setw(15) << netPartTimeFee << endl;
    }

    void Cal_netpartTime_fee()
    {
        netPartTimeFee = ((get_hourlyWage() * workingHour) - (((get_hourlyWage() * workingHour) * 0.02) + 10));
    }
};

vector<Full_Time> fullTimeEmployee;
vector<Part_Time> partTimeEmployee;

int main()
{
    int con;
    do
    {
        cout << "************************************\n";
        cout << "***** Employee Payroll Manager *****\n";
        cout << "************************************\n";
        cout << "1. Insert new employee Data \n";
        cout << "2. Update Employee Information \n";
        cout << "3. View Full-time employee information \n";
        cout << "4. View Part-time employee information \n";
        cout << "5. View all Employee information \n";
        cout << "6. Exit \n";
        cout << "Choose option: ";
        cin >> con;
        cin.ignore();

        switch (con)
        {
        case 1:
        {
            int e_num;
            cout << "Enter the number of employees to input: ";
            cin >> e_num;
            cin.ignore();

            for (int i = 0; i < e_num; i++)
            {
                string empType;
                cout << "Enter Employee type (Full-Time / Part-Time): ";
                cin >> empType;

                if (empType == "Full-Time")
                {
                    Full_Time f;
                    f.set_fulltime_data();
                    fullTimeEmployee.push_back(f);
                    cout << endl;
                }
                else if (empType == "Part-Time")
                {
                    Part_Time p;
                    p.set_parttime_data();
                    partTimeEmployee.push_back(p);
                    cout << endl;
                }
                else
                {
                    cout << "Invalid input. Skipping this employee.\n";
                }
            }
            break;
        }
        case 2:
        {
            int upd_id;
            string empType;
            bool found = false;

            cout << "Enter Employee type to update (Full-Time / Part-Time): ";
            cin >> empType;
            cout << "Enter employee id to update: ";
            cin >> upd_id;

            if (empType == "Full-Time")
            {
                for (int i = 0; i < fullTimeEmployee.size(); i++)
                {
                    if (upd_id == fullTimeEmployee[i].getEmpId())
                    {
                        fullTimeEmployee[i].set_fulltime_data();
                        found = true;
                        break;
                    }
                }
            }
            else if (empType == "Part-Time")
            {
                for (int i = 0; i < partTimeEmployee.size(); i++)
                {
                    if (upd_id == partTimeEmployee[i].getEmpId())
                    {
                        partTimeEmployee[i].set_parttime_data();
                        found = true;
                        break;
                    }
                }
            }
            if (!found)
            {
                cout << "Invalid ID" << endl;
            }
            break;
        }

        case 3:
        {
            cout << "\n***** ( Full-Time Employees ) *****\n";
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Start Date"
                 << setw(15) << "Basic Salary"
                 << setw(15) << "Hourly Wage"
                 << setw(15) << "Leave Days"
                 << setw(15) << "Bonus"
                 << setw(15) << "Net Salary" << endl;

            // Sort Full-Time Employees by Name (A-Z)
            sort(fullTimeEmployee.begin(), fullTimeEmployee.end(), [](Full_Time &a, Full_Time &b)
                 { return a.getEmpName() < b.getEmpName(); });

            for (int i = 0; i < fullTimeEmployee.size(); i++)
            {
                fullTimeEmployee[i].display_fulltime_data();
            }
            break;
        }
        case 4:
        {
            cout << "\n***** ( Part-Time Employees ) *****\n";
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Start Date"
                 << setw(15) << "Basic Salary"
                 << setw(15) << "Hourly Wage"
                 << setw(15) << "Work Hours"
                 << setw(15) << "Net Income" << endl;

            // Sort Part-Time Employees by Name (A-Z)
            sort(partTimeEmployee.begin(), partTimeEmployee.end(), [](Part_Time &a, Part_Time &b)
                 { return a.getEmpName() < b.getEmpName(); });

            for (int i = 0; i < partTimeEmployee.size(); i++)
            {
                partTimeEmployee[i].display_parttime_data();
            }
            break;
        }
        case 5:
        {
            cout << "\n***** All Employees *****\n";

            // Sort Full-Time Employees by Name (A-Z)
            sort(fullTimeEmployee.begin(), fullTimeEmployee.end(), [](Full_Time &a, Full_Time &b)
                 { return a.getEmpName() < b.getEmpName(); });

            cout << setw(25) << "Full-Time\n"
                 << endl;
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Start Date"
                 << setw(15) << "Basic Salary"
                 << setw(15) << "Hourly Wage"
                 << setw(15) << "Leave Days"
                 << setw(15) << "Bonus"
                 << setw(15) << "Net Salary" << endl;

            for (int i = 0; i < fullTimeEmployee.size(); i++)
            {
                fullTimeEmployee[i].display_fulltime_data();
            }

            // Sort Part-Time Employees by Name (A-Z)
            sort(partTimeEmployee.begin(), partTimeEmployee.end(), [](Part_Time &a, Part_Time &b)
                 { return a.getEmpName() < b.getEmpName(); });

            cout << setw(25) << "Part-Time\n"
                 << endl;
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Start Date"
                 << setw(15) << "Basic Salary"
                 << setw(15) << "Hourly Wage"
                 << setw(15) << "Work Hours"
                 << setw(15) << "Net Income" << endl;

            for (int i = 0; i < partTimeEmployee.size(); i++)
            {
                partTimeEmployee[i].display_parttime_data();
            }
            break;
        }

        case 6:
            cout << "Exiting program.\n";
            break;
        default:
        {
            cout << "Invalid option. Please try again.\n";
        }
        }
        }
        while (con != 6)
            ;
        return 0;
    }
