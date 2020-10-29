#include<iostream>
#include<sstream>
#include<string>
#include<boost/archive/binary_iarchive.hpp> 
#include<boost/archive/binary_oarchive.hpp>
using namespace std;

class EmployeeData
{
private:
	friend class boost::serialization::access;
	string name;
	int age;
	string company;

	template<class Archive>
	void serialize(Archive& archive, const unsigned int version)
	{
		archive& name;
		archive& age;

		if (version > 0)
			archive& company;
	}

public:
	EmployeeData() = default;
	EmployeeData(string n, int a, string c) :name(n), age(a), company(c)
	{

	}
	void showData()
	{
		cout << name << "," << age << "," << company << endl;

	}

	void save(ostringstream& oss)
	{
		boost::archive::binary_oarchive oa(oss);
		oa&* (this);
	}

	void load(ostringstream& oss)
	{
		std::string str_data = oss.str();
		std::istringstream iss(str_data);
		boost::archive::binary_iarchive ia(iss);
		ia&* (this);
	}

	~EmployeeData()
	{

	}
};

BOOST_CLASS_VERSION(EmployeeData, 1)

int main()
{
	EmployeeData emp("chandan", 34, "microsoft");
	std::ostringstream oss;

	//saving data in oss
	emp.save(oss);

	EmployeeData newEmp;
	//loading data in newEmp with binary archive.
	newEmp.load(oss);
	newEmp.showData();
	return 0;
}
