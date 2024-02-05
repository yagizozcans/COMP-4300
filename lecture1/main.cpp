#include <iostream>
#include <fstream>
#include <vector>

class Student
{
    std::string s_first_name;
    std::string s_last_name;
    int s_id;
    float s_average;
public:
    Student(){}
    Student(std::string first_name,std::string last_name,int id,float average)
    : s_first_name(first_name),s_last_name(last_name),s_id(id),s_average(average)
    {
    }
    std::string getFirstName()
    {
        return s_first_name;
    }
    std::string getLastName()
    {
        return s_last_name;
    }
    int getStudentID()
    {
        return s_id;
    }
    float getAverage()
    {
        return s_average;
    }
    void print()
    {
        std::cout<<s_first_name<<" "<<s_last_name<<" "<<s_id<<" "<<s_average<<std::endl;
    }
};

class Course
{
    std::vector<Student> c_students;
    std::string c_name;
public:
    Course(){}
    Course(std::string name)
    :c_name(name)
    {
    }
    void addStudent(const Student& s)
    {
        c_students.push_back(s);
    }

    void print()
    {
        for(auto& s : c_students)
        {
            s.print();
        }
    }

    void loadStudentsFromData(const std::string& filename)
    {
        std::ifstream fin;
        fin.open(filename);
        std::string first_name,last_name;
        int id;
        float average;
        if(!fin)
        {
            std::cout<<"Error"<<std::endl;
        }
        while(fin >> first_name)
        {
            fin>>last_name>>id>>average;
            c_students.push_back(Student(first_name,last_name,id,average));
        }
        fin.close();
    }
};

int main() {
    Student s1("Caleb","Johan",1001,2.17f);
    s1.print();
    Course cpp("C++");
    cpp.addStudent(s1);
    cpp.loadStudentsFromData("students.txt");
    cpp.print();
    return 0;
}
