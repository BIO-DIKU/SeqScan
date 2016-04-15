/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#include "repeat_unit.h"

RepeatUnit::RepeatUnit(
    std::unique_ptr<PatternUnit>& pu,
    const Modifiers &modifiers,
    const int &min_repeats,
    const int &max_repeats
) :
    PatternUnit(modifiers),
    child_units_(),
    min_repeats_(min_repeats),
    max_repeats_(max_repeats),
    cur_repeat_(0),
    pos_checked_(false),
    cur_match_(0)
{
  child_units_.push_back(std::move(pu));
}

void RepeatUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos
) {
  child_units_.at(0)->Initialize(pos, max_pos, stay_at_pos);

  sequence_iterator_end_ = max_pos;
  stay_at_pos_ = stay_at_pos;
  cur_repeat_ = 0;
  matches_.clear();
  pos_checked_ = false;
}

bool RepeatUnit::FindMatch() {
  if(!pos_checked_) {
    CollectMatches(0);
    cur_match_ = 0;
    pos_checked_ = true;
  }else{
    cur_match_++;
  }

  return cur_match_ < matches_.size();

}

/** Fill up matches_ */
bool RepeatUnit::CollectMatches(int repeat_lvl){
  //Ensure that child_units_ contains enough repeats
  if((size_t)repeat_lvl==child_units_.size()){
    child_units_.push_back(std::move(
        std::unique_ptr<PatternUnit>(child_units_[repeat_lvl-1]->Clone())
    ));
  }

  if(repeat_lvl>0){
    const Match prev_match = child_units_[repeat_lvl-1]->GetMatch();

    if(prev_match.pos+prev_match.len==sequence_iterator_end_){
      if(repeat_lvl>=min_repeats_){
        // Theres a match; Record it
        std::vector<Match> sub_matches;
        for (int r = 0; r < repeat_lvl; r++)
          sub_matches.push_back(child_units_[r]->GetMatch());
        matches_.push_back(Match(sub_matches));
        return true;
      }
      return false;
    }

    child_units_[repeat_lvl]->Initialize(
            prev_match.pos + prev_match.len,
            sequence_iterator_end_,
            true);
  }

  bool collected_match = false;

  while ( child_units_[repeat_lvl]->FindMatch() ) {
    bool dig_deeper = max_repeats_<0 || repeat_lvl+1<max_repeats_;
    if(dig_deeper){
      bool collected_from_deeper = CollectMatches(repeat_lvl+1);
      if(!collected_from_deeper){
        if(repeat_lvl+1>=min_repeats_){
          if(max_repeats_<0 || repeat_lvl+1<=max_repeats_){
            // Theres a maximal match; Record it
            std::vector<Match> sub_matches;
            for (int r = 0; r <= repeat_lvl; r++)
              sub_matches.push_back(child_units_[r]->GetMatch());
            matches_.push_back(Match(sub_matches));

            if(!overlaps_ && !stay_at_pos_){
              child_units_[0]->Initialize(
                  matches_.back().pos+matches_.back().len,
                  sequence_iterator_end_,
                  stay_at_pos_
              );
            }

            collected_match = true;
          }
        }
      }
    }else{
      if(repeat_lvl+1>=min_repeats_) {
        if (max_repeats_ < 0 || repeat_lvl + 1 <= max_repeats_) {
          // Theres a maximal match; Record it
          std::vector<Match> sub_matches;
          for (int r = 0; r <= repeat_lvl; r++)
            sub_matches.push_back(child_units_[r]->GetMatch());
          matches_.push_back(Match(sub_matches));

          collected_match = true;
        }
      }
    }
  }

  return collected_match;
}

const Match& RepeatUnit::GetMatch() const {
  return matches_.at(cur_match_);
}

std::ostream& operator<<(std::ostream& os, const RepeatUnit& obj) {
  return obj.Print(os);
}

std::ostream& RepeatUnit::Print(std::ostream &os) const {
  modifiers_.PrintPUPrefix(os);

  child_units_.at(0)->Print(os);

  modifiers_.PrintPUSuffix(os);

  os << "{" << min_repeats_ << "," << max_repeats_ << "}";

  return os;
}
