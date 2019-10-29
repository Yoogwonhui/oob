//
// Created by 김혁진 on 14/10/2019.
//

#include "shared_mut.h"

namespace ptr {
shared_mut::shared_mut() {
    _mgr = new mgr();
}

shared_mut::shared_mut(Object* _obj) {
    _mgr = new mgr(_obj);
}

shared_mut::~shared_mut() {
    release();
}



void shared_mut::increase() {
	(this->_mgr->count)++;
}
Object* shared_mut::get() const {
	if (this->_mgr->ptr == nullptr)
		return nullptr;
	return this->_mgr->ptr;
}
void shared_mut::release() {
	if (this->_mgr->count != 0)
		(this->_mgr->count)--;
	if (this->_mgr->count == 0) 
		this->_mgr->~mgr();
	this->_mgr = new mgr();
}
int shared_mut::count() {
	return this->_mgr->count;
}



shared_mut shared_mut::operator+(const shared_mut& shared) {
	int _this = this->get()->get();
	int _shared = shared.get()->get();
	return shared_mut(new Object(_this + _shared));
}
shared_mut shared_mut::operator-(const shared_mut& shared) {
	int _this = this->get()->get();
	int _shared = shared.get()->get();
	return shared_mut(new Object(_this - _shared));
}
shared_mut shared_mut::operator*(const shared_mut& shared) {
	int _this = this->get()->get();
	int _shared = shared.get()->get();
	return shared_mut(new Object(_this * _shared));
}
shared_mut shared_mut::operator/(const shared_mut& shared) {
	int _this = this->get()->get();
	int _shared = shared.get()->get();
	return shared_mut(new Object(_this / _shared));
}
Object* shared_mut::operator->() {
	return this->_mgr->ptr;
}



shared_mut& shared_mut::operator=(const shared_mut& r) {
	this->release();
	this->_mgr = r._mgr;
	this->increase();
	return *this;
}
} // end of namespace ptr
