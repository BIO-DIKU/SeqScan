#include <iostream>
#include "composite_unit.h"

CompositeUnit::CompositeUnit(const Modifiers &modifiers) : PatternUnit(modifiers)
{ }

void CompositeUnit::AddUnit(std::unique_ptr<PatternUnit> &unit)
{
  punits.push_back(std::move(unit));
}


void CompositeUnit::Print()
{
  std::cout<<"CompositeUnit contains "<<punits.size()<<" units"<<std::endl;
}
