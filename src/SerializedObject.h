#ifndef __SERIALIZEDOBJECT__
#define __SERIALIZEDOBJECT__

#include <boost/ptr_container/ptr_vector.hpp>

#include "SerializedTypes.h"

struct SOElement
{ // An element in the description of a serialized object
	const char *e_name;
	int e_flag;
	SerializedTypeID e_id;

	SOElement(const char *n, int f, SerializedTypeID i) : e_name(n), e_flag(f), e_id(i) { ; }
};

struct SOType
{ // A type of serialized object
	const char *name;
	std::list<SOElement> elements;
};

class STUObject : public SerializedType
{
protected:
	SOType *type;
	boost::ptr_vector<SerializedType> data;

public:
	STUObject() : type(NULL) { ; }
	STUObject(SOType *t) : type(t) { ; }
	STUObject(SOType *t, SerializerIterator& u);
	virtual ~STUObject() { ; }

	int getLength() const;
	SerializedTypeID getType() const { return STI_OBJECT; }
	STUObject* duplicate() const { return new STUObject(*this); }

	void add(Serializer& s) const;
	std::string getFullText() const;
	std::string getText() const;

	void addObject(const SerializedType& t) { data.push_back(t.duplicate()); }
	void giveObject(SerializedType* t) { data.push_back(t); }
	const boost::ptr_vector<SerializedType>& peekData() const { return data; }
	boost::ptr_vector<SerializedType>& peekData() { return data; }
};


#endif
