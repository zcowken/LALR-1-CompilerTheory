```angular2html

Ordered_LALR**************************************
----------- Node:0--------------
NodeId: 0
index:0	S'->.exp	pos0	select:{$,}
index:2	exp->.term	pos0	select:{$,+,-,}
index:1	exp->.expaddopterm	pos0	select:{$,+,-,}
index:6	term->.factor	pos0	select:{$,*,+,-,/,}
index:5	term->.termmulopfactor	pos0	select:{$,*,+,-,/,}
index:10	factor->.n	pos0	select:{$,*,+,-,/,}
index:9	factor->.(exp)	pos0	select:{$,*,+,-,/,}
Edge:exp	to Node:1
Edge:term	to Node:2
Edge:factor	to Node:3
Edge:n	to Node:4
Edge:(	to Node:5
---------------------------------------end
----------- Node:1--------------
NodeId: 1
reduce -- index:0	S'->exp.	pos1	select:{$,}
index:1	exp->exp.addopterm	pos1	select:{$,+,-,}
index:4	addop->.-	pos0	select:{(,n,}
index:3	addop->.+	pos0	select:{(,n,}
Edge:addop	to Node:6
Edge:-	to Node:7
Edge:+	to Node:8
---------------------------------------end
----------- Node:2--------------
NodeId: 2
reduce -- index:2	exp->term.	pos1	select:{$,),+,-,}
index:5	term->term.mulopfactor	pos1	select:{$,),*,+,-,/,}
index:8	mulop->./	pos0	select:{(,n,}
index:7	mulop->.*	pos0	select:{(,n,}
Edge:mulop	to Node:9
Edge:*	to Node:11
Edge:/	to Node:10
---------------------------------------end
----------- Node:3--------------
NodeId: 3
reduce -- index:6	term->factor.	pos1	select:{$,),*,+,-,/,}
---------------------------------------end
----------- Node:4--------------
NodeId: 4
reduce -- index:10	factor->n.	pos1	select:{$,),*,+,-,/,}
---------------------------------------end
----------- Node:5--------------
NodeId: 5
index:9	factor->(.exp)	pos1	select:{$,),*,+,-,/,}
index:2	exp->.term	pos0	select:{),+,-,}
index:1	exp->.expaddopterm	pos0	select:{),+,-,}
index:6	term->.factor	pos0	select:{),*,+,-,/,}
index:5	term->.termmulopfactor	pos0	select:{),*,+,-,/,}
index:10	factor->.n	pos0	select:{),*,+,-,/,}
index:9	factor->.(exp)	pos0	select:{),*,+,-,/,}
Edge:exp	to Node:12
Edge:term	to Node:2
Edge:factor	to Node:3
Edge:n	to Node:4
Edge:(	to Node:5
---------------------------------------end
----------- Node:6--------------
NodeId: 6
index:1	exp->expaddop.term	pos2	select:{$,),+,-,}
index:6	term->.factor	pos0	select:{$,),*,+,-,/,}
index:5	term->.termmulopfactor	pos0	select:{$,),*,+,-,/,}
index:10	factor->.n	pos0	select:{$,),*,+,-,/,}
index:9	factor->.(exp)	pos0	select:{$,),*,+,-,/,}
Edge:term	to Node:13
Edge:factor	to Node:3
Edge:n	to Node:4
Edge:(	to Node:5
---------------------------------------end
----------- Node:7--------------
NodeId: 7
reduce -- index:4	addop->-.	pos1	select:{(,n,}
---------------------------------------end
----------- Node:8--------------
NodeId: 8
reduce -- index:3	addop->+.	pos1	select:{(,n,}
---------------------------------------end
----------- Node:9--------------
NodeId: 9
index:5	term->termmulop.factor	pos2	select:{$,),*,+,-,/,}
index:10	factor->.n	pos0	select:{$,),*,+,-,/,}
index:9	factor->.(exp)	pos0	select:{$,),*,+,-,/,}
Edge:factor	to Node:14
Edge:n	to Node:4
Edge:(	to Node:5
---------------------------------------end
----------- Node:11--------------
NodeId: 11
reduce -- index:7	mulop->*.	pos1	select:{(,n,}
---------------------------------------end
----------- Node:10--------------
NodeId: 10
reduce -- index:8	mulop->/.	pos1	select:{(,n,}
---------------------------------------end
----------- Node:12--------------
NodeId: 12
index:9	factor->(exp.)	pos2	select:{$,),*,+,-,/,}
index:1	exp->exp.addopterm	pos1	select:{),+,-,}
index:4	addop->.-	pos0	select:{(,n,}
index:3	addop->.+	pos0	select:{(,n,}
Edge:)	to Node:15
Edge:addop	to Node:6
Edge:-	to Node:7
Edge:+	to Node:8
---------------------------------------end
----------- Node:13--------------
NodeId: 13
reduce -- index:1	exp->expaddopterm.	pos3	select:{$,),+,-,}
index:5	term->term.mulopfactor	pos1	select:{$,),*,+,-,/,}
index:8	mulop->./	pos0	select:{(,n,}
index:7	mulop->.*	pos0	select:{(,n,}
Edge:mulop	to Node:9
Edge:*	to Node:11
Edge:/	to Node:10
---------------------------------------end
----------- Node:14--------------
NodeId: 14
reduce -- index:5	term->termmulopfactor.	pos3	select:{$,),*,+,-,/,}
---------------------------------------end
----------- Node:15--------------
NodeId: 15
reduce -- index:9	factor->(exp).	pos3	select:{$,),*,+,-,/,}
---------------------------------------end
AnalyseSheet:**************************************
表头为:$ ( ) * + - / n addop exp factor mulop term 
sheetHeader
          $         (         )         *         +         -         /         n         addop     exp       factor    mulop     term      
id:0      0         shift5    0         0         0         0         0         shift4    0         goto1     goto3     0         goto2     
id:1      Accept    0         0         0         shift8    shift7    0         0         goto6     0         0         0         0         
id:2      reduce2   0         reduce2   shift11   reduce2   reduce2   shift10   0         0         0         0         goto9     0         
id:3      reduce6   0         reduce6   reduce6   reduce6   reduce6   reduce6   0         0         0         0         0         0         
id:4      reduce10  0         reduce10  reduce10  reduce10  reduce10  reduce10  0         0         0         0         0         0         
id:5      0         shift5    0         0         0         0         0         shift4    0         goto12    goto3     0         goto2     
id:6      0         shift5    0         0         0         0         0         shift4    0         0         goto3     0         goto13    
id:7      0         reduce4   0         0         0         0         0         reduce4   0         0         0         0         0         
id:8      0         reduce3   0         0         0         0         0         reduce3   0         0         0         0         0         
id:9      0         shift5    0         0         0         0         0         shift4    0         0         goto14    0         0         
id:10     0         reduce8   0         0         0         0         0         reduce8   0         0         0         0         0         
id:11     0         reduce7   0         0         0         0         0         reduce7   0         0         0         0         0         
id:12     0         0         shift15   0         shift8    shift7    0         0         goto6     0         0         0         0         
id:13     reduce1   0         reduce1   shift11   reduce1   reduce1   shift10   0         0         0         0         goto9     0         
id:14     reduce5   0         reduce5   reduce5   reduce5   reduce5   reduce5   0         0         0         0         0         0         
id:15     reduce9   0         reduce9   reduce9   reduce9   reduce9   reduce9   0         0         0         0         0         0         

```