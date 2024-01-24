#pragma once

class Person
{
private:
	std::size_t age;
	std::size_t course;
	std::size_t GPA;
	std::size_t PEAttestation;
	std::string name;
public:
	Person(
		std::size_t age,
		std::size_t course,
		float GPA,
		std::size_t PEAttestation,
		std::string name
	) : age(age), course(course), GPA(GPA), PEAttestation(PEAttestation), name(name) {};

	std::size_t GetAge()
	{
		return age;
	}
	std::size_t GetCourse()
	{
		return course;
	}
	float GetGPA()
	{
		return GPA;
	}
	std::size_t GetPEAttestation()
	{
		return PEAttestation;
	}
	std::string GetName()
	{
		return name;
	}
};