#include "Thing.h"
#include <string>
#include <iostream>
using namespace std;

namespace potd
{
  Thing::Thing(int size)
  {
    props_ct_ = 0;
    props_max_ = size;
    properties_ = new string[size];
    values_ = new string[size];
  }

  Thing::Thing(const Thing &o)
  {
    _copy(o);
  }

  void Thing::_copy(const Thing &o)
  {
    props_ct_ = o.props_ct_;
    props_max_ = o.props_max_;
    properties_ = new string[props_max_];
    values_ = new string[props_max_];
    for(int i = 0; i < props_max_; i++)
    {
      properties_[i] = o.properties_[i];
      values_[i] = o.values_[i];
    }

  }

  void Thing::_destroy()
  {
    if(properties_ != NULL)
    {
      delete[] properties_;
      properties_ = nullptr;
    }
    if(values_ != NULL)
    {
      delete[] values_;
      values_ = nullptr;
    }
  }

  Thing & Thing::operator=(const Thing &o)
  {
    if(this != &o)
    {
      _destroy();
      _copy(o);
    }
    return *this;
  }

  Thing::~Thing()
  {
    _destroy();
  }

  int Thing::set_property(string property, string val)
  {
    for(int i = 0; i < props_max_; i++)
    {

      if(properties_[i] == property)
      {
          values_[i] = val;
          return i;
      }
    }
    if(props_ct_>=props_max_)
    {
      return -1;
    }
    int temp = props_ct_;
    properties_[props_ct_] = property;
    values_[props_ct_] = val;
    props_ct_++;
    return temp;

  }

  string Thing::get_property(string name)
  {
    for(int i = 0; i < props_max_; i++)
    {
      if(properties_[i] == name)
      {
        return values_[i];
      }
    }
    return "";
  }
}