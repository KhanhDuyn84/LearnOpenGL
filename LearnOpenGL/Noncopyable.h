#pragma once
class Noncopyable
{
protected:
	Noncopyable() = default;
public:
	Noncopyable(const Noncopyable&) = delete;
	Noncopyable& operator=(const Noncopyable&) = delete;

	Noncopyable(Noncopyable&& other) = default;
	Noncopyable& operator=(Noncopyable&& other) = default;
};