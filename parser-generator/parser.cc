// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.
// //                    "%code top" blocks.
#line 59 "parser.y" // lalr1.cc:397

  #include <iostream>

  #include "scanner.h"
  #include "parser.hh"
  #include "interpreter.h"
  #include "location.hh"
  
  // yylex() arguments are defined in parser.y
  static SeqScan::Parser::symbol_type yylex(SeqScan::Scanner &scanner, SeqScan::Interpreter &driver) {
      return scanner.get_next_token();
  }
  
  // you can accomplish the same thing by inlining the code using preprocessor
  // x and y are same as in above static function
  // #define yylex(x, y) scanner.get_next_token()
  

#line 53 "parser.cc" // lalr1.cc:397


// First part of user declarations.

#line 58 "parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hh"

// User implementation prologue.

#line 72 "parser.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 37 "parser.y" // lalr1.cc:479
namespace  SeqScan  {
#line 158 "parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   Parser :: Parser  (SeqScan::Scanner &scanner_yyarg, SeqScan::Interpreter &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

   Parser ::~ Parser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
   Parser ::by_state::by_state ()
    : state (empty_state)
  {}

  inline
   Parser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   Parser ::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
   Parser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   Parser ::symbol_number_type
   Parser ::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
   Parser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   Parser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 27: // unit_list
      case 28: // punit
        value.move<  PTNode*  > (that.value);
        break;

      case 30: // prefix_modifier
        value.move<  PTPreModifier*  > (that.value);
        break;

      case 29: // suffix_modifier
        value.move<  PTSufModifier*  > (that.value);
        break;

      case 3: // "string"
      case 4: // "label"
        value.move< std::string > (that.value);
        break;

      case 5: // "number"
        value.move< uint64_t > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 27: // unit_list
      case 28: // punit
        value.copy<  PTNode*  > (that.value);
        break;

      case 30: // prefix_modifier
        value.copy<  PTPreModifier*  > (that.value);
        break;

      case 29: // suffix_modifier
        value.copy<  PTSufModifier*  > (that.value);
        break;

      case 3: // "string"
      case 4: // "label"
        value.copy< std::string > (that.value);
        break;

      case 5: // "number"
        value.copy< uint64_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   Parser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   Parser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   Parser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   Parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   Parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 27: // unit_list
      case 28: // punit
        yylhs.value.build<  PTNode*  > ();
        break;

      case 30: // prefix_modifier
        yylhs.value.build<  PTPreModifier*  > ();
        break;

      case 29: // suffix_modifier
        yylhs.value.build<  PTSufModifier*  > ();
        break;

      case 3: // "string"
      case 4: // "label"
        yylhs.value.build< std::string > ();
        break;

      case 5: // "number"
        yylhs.value.build< uint64_t > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 128 "parser.y" // lalr1.cc:859
    { 
    driver.set_parse_tree(yystack_[0].value.as<  PTNode*  > ());
  }
#line 602 "parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 135 "parser.y" // lalr1.cc:859
    {
    yystack_[2].value.as<  PTNode*  > ()->children_.push_back(yystack_[0].value.as<  PTNode*  > ());
	yylhs.value.as<  PTNode*  > () = yystack_[2].value.as<  PTNode*  > ();
  }
#line 611 "parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 140 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = new PTNode(PTNode::kComposite);
	yylhs.value.as<  PTNode*  > ()->children_.push_back(yystack_[0].value.as<  PTNode*  > ());
  }
#line 620 "parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 148 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = new PTNode(yystack_[0].value.as< std::string > ());
  }
#line 628 "parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 152 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = new PTNode(PTNode::kReference);
    yylhs.value.as<  PTNode*  > ()->referenced_label_ = yystack_[0].value.as< std::string > ();
  }
#line 637 "parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 157 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = new PTNode(PTNode::kRepeat);
    yylhs.value.as<  PTNode*  > ()->min_repeats_ = yystack_[3].value.as< uint64_t > ();
    yylhs.value.as<  PTNode*  > ()->max_repeats_ = yystack_[1].value.as< uint64_t > ();
    yylhs.value.as<  PTNode*  > ()->children_.push_back(yystack_[5].value.as<  PTNode*  > ());
  }
#line 648 "parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 164 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = new PTNode(PTNode::kRepeat);
    yylhs.value.as<  PTNode*  > ()->min_repeats_ = yystack_[2].value.as< uint64_t > ();
    yylhs.value.as<  PTNode*  > ()->max_repeats_ = -1;
    yylhs.value.as<  PTNode*  > ()->children_.push_back(yystack_[4].value.as<  PTNode*  > ());
  }
#line 659 "parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 171 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = new PTNode(PTNode::kRepeat);
    yylhs.value.as<  PTNode*  > ()->min_repeats_ = yystack_[1].value.as< uint64_t > ();
    yylhs.value.as<  PTNode*  > ()->max_repeats_ = yystack_[1].value.as< uint64_t > ();
    yylhs.value.as<  PTNode*  > ()->children_.push_back(yystack_[3].value.as<  PTNode*  > ());
  }
#line 670 "parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 178 "parser.y" // lalr1.cc:859
    {
    yystack_[0].value.as<  PTNode*  > ()->add_modifier(yystack_[1].value.as<  PTPreModifier*  > ());
    delete yystack_[1].value.as<  PTPreModifier*  > ();
    yylhs.value.as<  PTNode*  > () = yystack_[0].value.as<  PTNode*  > ();
  }
#line 680 "parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 184 "parser.y" // lalr1.cc:859
    {
    yystack_[1].value.as<  PTNode*  > ()->add_modifier(yystack_[0].value.as<  PTSufModifier*  > ());
    delete yystack_[0].value.as<  PTSufModifier*  > ();
    yylhs.value.as<  PTNode*  > () = yystack_[1].value.as<  PTNode*  > ();
  }
#line 690 "parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 190 "parser.y" // lalr1.cc:859
    {
    yystack_[0].value.as<  PTNode*  > ()->label_ = yystack_[2].value.as< std::string > ();
    yylhs.value.as<  PTNode*  > () = yystack_[0].value.as<  PTNode*  > ();
  }
#line 699 "parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 195 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = yystack_[1].value.as<  PTNode*  > ();
  }
#line 707 "parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 199 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = new PTNode(PTNode::kRepeat);
	yylhs.value.as<  PTNode*  > ()->min_repeats_ = yystack_[4].value.as< uint64_t > ();
	yylhs.value.as<  PTNode*  > ()->max_repeats_ = yystack_[0].value.as< uint64_t > ();
  }
#line 717 "parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 205 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTNode*  > () = new PTNode(PTNode::kRepeat);
	yylhs.value.as<  PTNode*  > ()->min_repeats_ = yystack_[3].value.as< uint64_t > ();
	yylhs.value.as<  PTNode*  > ()->max_repeats_ = yystack_[0].value.as< uint64_t > ();
  }
#line 727 "parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 214 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTSufModifier*  > () = new PTSufModifier();
    yylhs.value.as<  PTSufModifier*  > ()->mismatches_ = yystack_[4].value.as< uint64_t > ();
    yylhs.value.as<  PTSufModifier*  > ()->insertions_ = yystack_[2].value.as< uint64_t > ();
    yylhs.value.as<  PTSufModifier*  > ()->deletions_  = yystack_[0].value.as< uint64_t > ();
  }
#line 738 "parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 221 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTSufModifier*  > () = new PTSufModifier();
    yylhs.value.as<  PTSufModifier*  > ()->mismatches_ = yystack_[2].value.as< uint64_t > ();
    yylhs.value.as<  PTSufModifier*  > ()->indels_     = yystack_[0].value.as< uint64_t > ();
  }
#line 748 "parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 227 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTSufModifier*  > () = new PTSufModifier();
    yylhs.value.as<  PTSufModifier*  > ()->errors_ = yystack_[0].value.as< uint64_t > ();
  }
#line 757 "parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 235 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTPreModifier*  > () = new PTPreModifier();
    yylhs.value.as<  PTPreModifier*  > ()->complement_ = true;
  }
#line 766 "parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 240 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTPreModifier*  > () = new PTPreModifier();
    yylhs.value.as<  PTPreModifier*  > ()->reverse_ = true;
  }
#line 775 "parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 245 "parser.y" // lalr1.cc:859
    {
    yylhs.value.as<  PTPreModifier*  > () = new PTPreModifier();
    yylhs.value.as<  PTPreModifier*  > ()->reverse_ = true;
    yylhs.value.as<  PTPreModifier*  > ()->complement_ = true;
  }
#line 785 "parser.cc" // lalr1.cc:859
    break;


#line 789 "parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  Parser ::yypact_ninf_ = -14;

  const signed char  Parser ::yytable_ninf_ = -1;

  const signed char
   Parser ::yypact_[] =
  {
      -3,   -14,   -13,    -9,     5,   -14,    -3,     7,    11,    12,
      -3,    -3,     8,   -14,    -5,   -14,    -3,    19,    21,   -14,
      12,    12,    -1,   -14,    12,    20,    15,   -14,    23,    24,
      10,   -14,   -14,    25,    26,   -14,    28,   -14,   -14
  };

  const unsigned char
   Parser ::yydefact_[] =
  {
       0,     5,     6,     0,    20,    21,     0,     0,     2,     4,
       0,     0,     0,    19,     0,     1,     0,     0,     0,    11,
      10,    12,     0,    13,     3,    18,     0,    15,     0,     0,
       0,     9,    14,    17,     0,     8,     0,     7,    16
  };

  const signed char
   Parser ::yypgoto_[] =
  {
     -14,   -14,    29,     0,   -14,   -14
  };

  const signed char
   Parser ::yydefgoto_[] =
  {
      -1,     7,     8,     9,    19,    10
  };

  const unsigned char
   Parser ::yytable_[] =
  {
       1,     2,     3,    16,    27,    11,    12,    15,     4,     5,
      20,    21,    23,     6,    28,    34,    24,    13,    17,    16,
      35,    18,    30,    22,    25,    31,    26,    29,    32,    33,
       0,     0,    36,    38,     0,    14,    37
  };

  const signed char
   Parser ::yycheck_[] =
  {
       3,     4,     5,     8,     5,    18,    15,     0,    11,    12,
      10,    11,    17,    16,    15,     5,    16,    12,     6,     8,
      10,     9,     7,    15,     5,    10,     5,     7,     5,     5,
      -1,    -1,     7,     5,    -1,     6,    10
  };

  const unsigned char
   Parser ::yystos_[] =
  {
       0,     3,     4,     5,    11,    12,    16,    26,    27,    28,
      30,    18,    15,    12,    27,     0,     8,     6,     9,    29,
      28,    28,    15,    17,    28,     5,     5,     5,    15,     7,
       7,    10,     5,     5,     5,    10,     7,    10,     5
  };

  const unsigned char
   Parser ::yyr1_[] =
  {
       0,    25,    26,    27,    27,    28,    28,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    29,    29,    29,    30,
      30,    30
  };

  const unsigned char
   Parser ::yyr2_[] =
  {
       0,     2,     1,     3,     1,     1,     1,     6,     5,     4,
       2,     2,     3,     3,     5,     4,     6,     4,     2,     2,
       1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"string\"", "\"label\"",
  "\"number\"", "\"slash\"", "\"comma\"", "\"space\"", "\"lcurly\"",
  "\"rcurly\"", "\"less\"", "\"tilde\"", "\"or\"", "\"qmark\"", "\"dot\"",
  "\"lpar\"", "\"rpar\"", "\"equal\"", "\"lbrack\"", "\"rbrack\"",
  "\"plus\"", "\"hat\"", "\"dollar\"", "\"star\"", "$accept", "pattern",
  "unit_list", "punit", "suffix_modifier", "prefix_modifier", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
   Parser ::yyrline_[] =
  {
       0,   127,   127,   134,   139,   147,   151,   156,   163,   170,
     177,   183,   189,   194,   198,   204,   213,   220,   226,   234,
     239,   244
  };

  // Print the state stack on the debug stream.
  void
   Parser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   Parser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 37 "parser.y" // lalr1.cc:1167
} //  SeqScan 
#line 1177 "parser.cc" // lalr1.cc:1167
#line 253 "parser.y" // lalr1.cc:1168


// Bison expects us to provide implementation - otherwise linker complains
void SeqScan::Parser::error(const location &loc , const std::string &message) {
  std::cout << "Error: " << message << std::endl << "Error location: " << driver.location() << std::endl;
}
