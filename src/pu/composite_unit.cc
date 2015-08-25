#include <iostream>
#include "composite_unit.h"

CompositeUnit::CompositeUnit(const Modifiers &modifiers) :
    PatternUnit(modifiers)
{ }

void CompositeUnit::AddUnit(std::unique_ptr<PatternUnit> &unit)
{
  punits_.push_back(std::move(unit));
}


void CompositeUnit::Print()
{
  std::cout<<"CompositeUnit contains "<<punits_.size()<<" units"<<std::endl;
}

void CompositeUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos
)
{
  punits_.at(0)->Initialize(pos, max_pos);
}


bool CompositeUnit::HasNextMatch()
{
  return false;
}


Match& CompositeUnit::NextMatch(){
  Match m(0,0,0);
  return m;
};

