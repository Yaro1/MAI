name('Стас').
name('Маёвец').
name('Алкоголик').

loc('дом').
loc('улица').
loc('фонарь').
loc('аптека').

object('мороженое').
object('пироженое').
object('водка').
object('пиво').
object('виски').
object('ром').



getElem([],_,_).
getElem([H|T],T,H).

there_agent(Q,S):- Q == 'Кто';name(S).
there_agent1(Q):- Q == 'Кто'.

there_object1(Q,S):-Q == 'Что';object(S).
there_object1(Q):-Q == 'Что'.

there_loc(Q,S):-Q == 'Где';loc(S).
there_loc1(Q):-Q== 'Где'.
there_loc2(S):-loc(S).

an_q(S):- getElem(S,S1,Quastion), getElem(S1,S2,Do),getElem(S2,S3,Something),
      write(Do), (there_agent(Quastion,Something) ->
                 write("(agent("), (there_agent1(Quastion)-> write("Y),");write(Something),write("),")),
                  ( there_loc(Quastion,Something) ->
                 write("loc("),(there_loc1(Quastion)-> write("Y),");write(Something),write("))"));
                  write("object("),(there_object1(Quastion)-> write("Y),");write(Something),write("))")));
                 write("object("),(there_object1(Quastion)-> write("Y),");write(Something),write("),")),
                 ( write("loc("),(there_loc1(Quastion)-> write("Y),");write(Something),write("))")))).



