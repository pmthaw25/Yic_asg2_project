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
    double basicSalary;
    double hourlyWage;

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
    double get_hourlyWage() { return hourlyWage; }
    double get_basicSalary() { return basicSalary; }

    void setdata()
    {
        cout << "Enter employee id: ";
        cin >> empId;
        cin.ignore();
        cout << "Enter employee name: ";
        getline(cin, empName);
        cout << "Enter employee position \n((Full-Time) Barista,Cashier,Supervisor,(Part-Time) Kitchen Staff,Cleaner,Waiter/Waitress): ";
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
    double bonus, netSalary;

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
        double total;
        // Calculate bonus for leave days
        if (leaveDay == 0)
            bonus += 300;
        else if (leaveDay == 1)
            bonus += 200;
        else if (leaveDay == 2)
            bonus += 100;
        else
        {
            bonus += 0;
        }

        // Calculate bonus for overtime
        bonus += (get_hourlyWage() * 2) * overTime;

        // Calculate net salary
        if (leaveDay >= 4 && overTime > 0)
        {
            total = get_basicSalary() + bonus;
            netSalary = total - (((get_basicSalary() * 0.01) + ((total * 0.02))) + 10);
        }
        else
        {
            total = get_basicSalary() + bonus;
            netSalary = total - ((total * 0.02) + 10);
        }
    }

    double getNetSalary() const
    {
        return netSalary;
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

    double getNetPartTimeFee() const
    {
        return netPartTimeFee;
    }
};

void mergeFullTime(vector<Full_Time> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Full_Time> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<Full_Time> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].getEmpId() <= R[j].getEmpId())
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortFullTime(vector<Full_Time> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSortFullTime(arr, left, mid);
        mergeSortFullTime(arr, mid + 1, right);
        mergeFullTime(arr, left, mid, right);
    }
}

// Merge Sort Algorithm for Part-Time Employees
void mergePartTime(vector<Part_Time> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Part_Time> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<Part_Time> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].getEmpId() <= R[j].getEmpId())
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortPartTime(vector<Part_Time> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSortPartTime(arr, left, mid);
        mergeSortPartTime(arr, mid + 1, right);
        mergePartTime(arr, left, mid, right);
    }
}

vector<Full_Time> fullTimeEmployee;
vector<Part_Time> partTimeEmployee;

int main()
{
    int con;
    do
    {
        cout << "\n************************************\n";
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
                cout << "Employee : " << i + 1 << " Information form\n";
                string empType;
                cout << "Enter Employee type (Full-Time / Part-Time): ";
                cin >> empType;

                if (empType == "Full-Time")
                {
                    Full_Time f;
                    f.set_fulltime_data();
                    if (f.get_basicSalary() == 0)
                    {
                        cout << "Invalid data skipping employee\n";
                        continue;
                    }

                    fullTimeEmployee.push_back(f);
                    cout << endl;
                }
                else if (empType == "Part-Time")
                {
                    Part_Time p;
                    p.set_parttime_data();
                    if (p.get_basicSalary() == 0)
                    {
                        cout << "Invalid data skipping employee\n";

                        continue;
                    }
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
            int updateId;
            bool found = false;
            cout << "Enter the Employee ID to update: ";
            cin >> updateId;

            // Check in Full-Time Employees
            for (int i = 0; i < fullTimeEmployee.size(); i++)
            {
                if (fullTimeEmployee[i].getEmpId() == updateId)
                {
                    cout << "Updating Full-Time Employee Data:\n";
                    fullTimeEmployee[i].set_fulltime_data();
                    cout << "Employee data updated successfully.\n";
                    found = true;
                    break;
                }
            }

            // Check in Part-Time Employees if not found in Full-Time
            if (!found)
            {
                for (int i = 0; i < partTimeEmployee.size(); i++)
                {
                    if (partTimeEmployee[i].getEmpId() == updateId)
                    {
                        cout << "Updating Part-Time Employee Data:\n";
                        partTimeEmployee[i].set_parttime_data();
                        cout << "Employee data updated successfully.\n";
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
            {
                cout << "Employee with ID " << updateId << " not found.\n";
            }

            break;
        }

        case 3:
        {
            mergeSortFullTime(fullTimeEmployee, 0, fullTimeEmployee.size() - 1);

            cout << "\n***** ( Full-Time Employees ) *****\n";
            cout << string(130, '-') << endl;
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Start Date"
                 << setw(15) << "Basic Salary"
                 << setw(15) << "Hourly Wage"
                 << setw(15) << "Leave Days"
                 << setw(15) << "Bonus"
                 << setw(15) << "Net Salary" << endl;
            cout << string(130, '-') << endl;

            for (int i = 0; i < fullTimeEmployee.size(); i++)
            {
                fullTimeEmployee[i].display_fulltime_data();
            }

            cout << string(130, '-') << endl;
            cout << "Total Full-Time Employees: " << fullTimeEmployee.size() << endl;
            break;
        }
        case 4:
        {
            // Sort and display part-time employees
            mergeSortPartTime(partTimeEmployee, 0, partTimeEmployee.size() - 1);

            cout << "\n***** ( Part-Time Employees ) *****\n";
            cout << string(130, '-') << endl;
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Start Date"
                 << setw(15) << "Basic Salary"
                 << setw(15) << "Hourly Wage"
                 << setw(15) << "Work Hours"
                 << setw(15) << "Net Income" << endl;
            cout << string(130, '-') << endl;

            for (int i = 0; i < partTimeEmployee.size(); i++)
            {
                partTimeEmployee[i].display_parttime_data();
            }

            cout << string(130, '-') << endl;
            cout << "Total Part-Time Employees: " << partTimeEmployee.size() << endl;
            break;
        }
        case 5:
        {
            // Sort and display all employees
            mergeSortFullTime(fullTimeEmployee, 0, fullTimeEmployee.size() - 1);
            mergeSortPartTime(partTimeEmployee, 0, partTimeEmployee.size() - 1);

            double totalNetSalary = 0.0;

            cout << "\n***** All Employees *****\n";
            cout << string(130, '-') << endl;

            cout << "Full-Time Employees:\n";
            cout << string(130, '-') << endl;
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Start Date"
                 << setw(15) << "Basic Salary"
                 << setw(15) << "Hourly Wage"
                 << setw(15) << "Leave Days"
                 << setw(15) << "Bonus"
                 << setw(15) << "Net Salary" << endl;
            cout << string(130, '-') << endl;

            for (int i = 0; i < fullTimeEmployee.size(); i++)
            {
                fullTimeEmployee[i].display_fulltime_data();
                totalNetSalary += fullTimeEmployee[i].getNetSalary();
            }
            cout << string(130, '-') << endl;
            cout << "Total Full-Time Employees: " << fullTimeEmployee.size() << endl;

            cout << "\nPart-Time Employees:\n";
            cout << string(130, '-') << endl;
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Start Date"
                 << setw(15) << "Basic Salary"
                 << setw(15) << "Hourly Wage"
                 << setw(15) << "Work Hours"
                 << setw(15) << "Net Income" << endl;
            cout << string(130, '-') << endl;

            for (int i = 0; i < partTimeEmployee.size(); i++)
            {
                partTimeEmployee[i].display_parttime_data();
                totalNetSalary += partTimeEmployee[i].getNetPartTimeFee();
            }

            cout << string(130, '-') << endl;
            cout << "Total Part-Time Employees: " << partTimeEmployee.size() << endl;

            cout << "\n******* Mothly Employee Report *******\n";
            cout << setw(17) << "Total Employees : " << (fullTimeEmployee.size() + partTimeEmployee.size()) << endl;
            cout << setw(17) << "Total Net Salary: " << totalNetSalary << endl;

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

    } while (con != 6);

    return 0;
}
