#include <iostream>
#include <string>

 /* Car parts */
class Wheel
{
public:
	Wheel() { } // constructor
	int size; // should be in private and getter/setter in public
};

class Engine
{
public:
	Engine() { } // constructor
	int horsepower; // should be in private and getter/setter in public
};

class Body
{
public:
	Body() { } // constructor
	std::string shape; // should be in private and getter/setter in public
};

/* Final product -- a car */
class Car
{
public:
	Wheel* wheels[4];
	Engine* engine;
	Body* body;

	void specifications()
	{
		std::cout << "body:" << body->shape << std::endl;
		std::cout << "engine horsepower:" << engine->horsepower << std::endl;
		std::cout << "tire size:" << wheels[0]->size << "'" << std::endl;
	}
};

/* Builder is responsible for constructing the smaller parts */
class Builder
{
public:
	// builder ma miec funkcje puste a nie abstrakcyjne!!!
	virtual Wheel* getWheel() // VIRTUAL!!! 
	{
		return new Wheel();
	}
	virtual Engine* getEngine() // VIRTUAL!!!
	{
		return new Engine();
	}
	virtual Body* getBody() // VIRTUAL!!!
	{
		return new Body();
	}
};

/* Director is responsible for the whole process */
class Director
{
	Builder* builder;

public:
	void setBuilder(Builder* newBuilder)
	{
		builder = newBuilder;
	}

	Car* getCar()
	{
		Car* car = new Car();

		car->body = builder->getBody();

		car->engine = builder->getEngine();

		car->wheels[0] = builder->getWheel();
		car->wheels[1] = builder->getWheel();
		car->wheels[2] = builder->getWheel();
		car->wheels[3] = builder->getWheel();

		return car;
	}
};

/* Concrete Builder for Jeep SUV cars */
class JeepBuilder : public Builder
{
public:
	Wheel* getWheel()
	{
		Wheel* wheel = new Wheel();
		wheel->size = 22;
		return wheel;
	}

	Engine* getEngine()
	{
		Engine* engine = new Engine();
		engine->horsepower = 400;
		return engine;
	}

	Body* getBody()
	{
		Body* body = new Body();
		body->shape = "SUV";
		return body;
	}
};

/* Concrete builder for Nissan family cars */
class NissanBuilder : public Builder
{
public:
	Wheel* getWheel()
	{
		Wheel* wheel = new Wheel();
		wheel->size = 16;
		return wheel;
	}

	Engine* getEngine()
	{
		Engine* engine = new Engine();
		engine->horsepower = 85;
		return engine;
	}

	Body* getBody()
	{
		Body* body = new Body();
		body->shape = "hatchback";
		return body;
	}
};


int main()
{
	Car* car; // Final product

	/* A director who controls the process */
	Director director;

	/* Concrete builders */
	JeepBuilder jeepBuilder;
	NissanBuilder nissanBuilder;

	/* Build a Jeep */
	std::cout << "Jeep" << std::endl;
	director.setBuilder(&jeepBuilder); // using JeepBuilder instance
	car = director.getCar();
	car->specifications();

	std::cout << std::endl;

	/* Build a Nissan */
	std::cout << "Nissan" << std::endl;
	director.setBuilder(&nissanBuilder); // using NissanBuilder instance
	car = director.getCar();
	car->specifications();

	return 0;
}