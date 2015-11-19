
# Parser generator for SeqScan

Uses flex and bison to generate lexer and parser for SeqScan patterns. The final parser is compiled into `lib/libseqscanparser.a`. The parser is wrapped by the `Interface` class which takes a string-representation of a SeqScan pattern and compiles it into a parse-tree represented by the `PTNode` class. For example, the commands
```
Intepreter i;
PTNode* ptree = i.parse("AA/1 p2=(CC p1=DD) p2/1");
cout<<ptree->str(0)<<endl;
```
will result in the following tree
```
PTNode[0,children=(
  PTNode[1,seq=AA,suf_mod=/1]
  PTNode[0,lbl=p2,children=(
    PTNode[1,seq=CC]
    PTNode[1,lbl=p1,seq=DD])]
  PTNode[3,ref=p2,suf_mod=/1])]
```


Each `PTNode` contains prefix- and suffix-modifiers stored in `PTPreModifier` and `PTSufModifier` classes. Furthermore, the pattern-unit type of each node holds an integer `PTNode::node_type_` which can be one of
```
SeqScan::PTNode::kComposite = 0;
SeqScan::PTNode::kSequence  = 1;
SeqScan::PTNode::kRepeat    = 2;
SeqScan::PTNode::kReference = 3;
```

The generated parser does not perform any sanity checks (such as checking whether mismatches exceeds the length of a specified sequence or whether `PTNode::min_repeats_` is larger than `PTNode::max_repeats_`). It also doesnt convert Parse-trees into `PatternUnit`s.
