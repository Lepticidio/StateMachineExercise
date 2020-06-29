#pragma once
class Action
{
public:
	virtual void start() const = 0;
	virtual void update() const = 0;
	virtual void end() const = 0;

};

