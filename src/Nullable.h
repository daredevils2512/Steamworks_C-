/*
 * Nullable.h
 *
 *  Created on: Feb 20, 2016
 *      Author: troym
 */

#ifndef SRC_NULLABLE_H_
#define SRC_NULLABLE_H_

template<class T>
class Nullable {
public:
	//constructors
	Nullable();
	Nullable(T value);
	//functions
	bool HasValue();
	T GetValue();

private:
	//variables
	bool hasValue;
	T value;
};

template<class T>
Nullable<T>::Nullable() {
	//constructor used if there is no value
	hasValue = false;
}

template<class T>
Nullable<T>::Nullable(T value) {
	//constructor used if there is a value
	this->value = value;
	hasValue = true;
}

template<class T>
bool Nullable<T>::HasValue() {
	//specifies if there is a value or not
	return hasValue;
}

template<class T>
T Nullable<T>::GetValue() {
	//returns value
	return value;
}

#endif /* SRC_NULLABLE_H_ */
