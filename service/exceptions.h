#pragma once

#include <exception>
#include <stdexcept>
#include <string>


class ValidationException : public std::exception {
private:
	std::string message;
public:
	ValidationException(std::string message) : message{ message } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};


class NotFoundException : public std::runtime_error {
public:
	NotFoundException(std::string message) : std::runtime_error(message) {}
};


class DuplicateElementException : public std::runtime_error {
public:
	DuplicateElementException(std::string message) : std::runtime_error(message) {}
};

