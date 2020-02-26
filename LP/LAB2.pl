open('obuv','vtornik').
open('obuv','sreda').
open('obuv','chetverg').
open('obuv','pyatnica').
open('obuv','subbota').
close1('obuv','ponedelnik').

open('hoz','ponedelnik').
open('hoz','sreda').
open('hoz','chetverg').
open('hoz','pyatnica').
open('hoz','subbota').
close1('hoz','vtornik').

open('prod','ponedelnik').
open('prod','vtornik').
open('prod','sreda').
open('prod','pyatnica').
open('prod','subbota').
close1('prod','chetverg').

open('parfum', 'ponedelnik').
open('parfum', 'sreda').
open('parfum', 'pyatnica').
close1('parfum', 'vtornik').
close1('parfum', 'chetverg').
close1('parfum', 'subbota').


getLenList([],0).
getLenList([_|L],N):- getLenList(L,N1), N is N1+1.



findmax([L|Ls], Max) :-
    findmax(Ls, L, Max).

findmax([], Max, Max).
findmax([L|Ls], Max0, Max) :-
    Max1 is max(L, Max0),
    findmax(Ls, Max1, Max).

% Номер дня недели, когда они пошли в магазин, а вообще это первое
% вхождение аргумента в список.
num([],N,_):- N is 0.
num([L|_],N,Max) :-N is 1, L = Max.
num([_|Ls],N,Max):- num(Ls,N1,Max), N is N1+1.

day([],_,_,_):-!.
day([L|_],N,L,Num):-N=Num.
day([_|Ls],N,S,Num):-Num1 is Num + 1, day(Ls,N,S,Num1).

poisk(NextDay,PrevDay, S, Name,_,_,_,_,_,_, Name):- member(NextDay,S), member(PrevDay,S).
poisk(NextDay,PrevDay, _, _,S,Name,_,_,_,_, Name):- member(NextDay,S), member(PrevDay,S).
poisk(NextDay,PrevDay, _, _,_,_,S,Name,_,_, Name):- member(NextDay,S), member(PrevDay,S).
poisk(NextDay,PrevDay, _, _,_,_,_,_,S,Name, Name):- member(NextDay,S), member(PrevDay,S).
poisk(_,_, _, _,_,_,_,_,_,_, 'No'):-!.

ira(NextDay, PrevDay,S, Name,_,_,_,_,_,_, Name):-member(PrevDay, S),not(member(NextDay,S)).
ira(NextDay, PrevDay,_, _,S,Name,_,_,_,_, Name):-member(PrevDay, S),not(member(NextDay,S)).
ira(NextDay, PrevDay,_, _,_,_,S,Name,_,_, Name):-member(PrevDay, S),not(member(NextDay,S)).
ira(NextDay, PrevDay,_, _,_,_,_,_,S,Name, Name):-member(PrevDay, S),not(member(NextDay,S)).
ira(_,_, _, _,_,_,_,_,_,_, 'No'):-!.

elem([L|_],L):-!.

work :-
     L = ['ponedelnik','vtornik','sreda','chetverg', 'pyatnica', 'subbota', 'voskresenye'],
     F = [F0,F1,F2,F3,F4,F5,F6],
     findall(X,open(X,'ponedelnik') ,Pn),
     findall(X,open(X,'vtornik') ,Vt),
     findall(X,open(X, 'sreda') ,Sr),
     findall(X,open(X,'chetverg') ,Ch),
     findall(X,open(X,'pyatnica') ,Pt),
     findall(X,open(X,'subbota') ,Sb),
     findall(X,open(X,'voskresenye') ,Vs),
     getLenList(Pn,F0),
     getLenList(Vt,F1),
     getLenList(Sr,F2),
     getLenList(Ch,F3),
     getLenList(Pt,F4),
     getLenList(Sb,F5),
     getLenList(Vs,F6),

     findmax(F,Max),
     num(F,N,Max),
     %здесь становится понятно, что искомый день - среда.
     day(L,N,NowDay,1),
     %дни с которыми я работаю
     N1 is N + 1, N2 is N - 1, N3 is N2 - 1,
     day(L,N1,NextDay,1),
     day(L,N2,PrevDay,1),
     day(L,N3,PrevprevDay,1),

     findall(X,open('obuv',X) ,Ob),
     findall(X,open('hoz',X) ,Hz),
     findall(X,open('prod', X) ,Prd),
     findall(X,open('parfum',X) ,Prf),

     poisk(NextDay,PrevDay, Ob,'obuv',Hz,'hoz',Prd,'prod', Prf, 'parfum', Zhenya),
     poisk(PrevprevDay,PrevDay, Ob,'obuv',Hz,'hoz',Prd,'prod', Prf, 'parfum', Klava),
     findall(X,close1(X,NextDay) ,List1),
     delete(List1,Zhenya,List2),
     delete(List2, Klava, List),
     elem(List,Ira),
     findall(X,open(X,NowDay) ,Result1),
     delete(Result1,Zhenya,Result2),
     delete(Result2, Klava, Result3),
     delete(Result3,Ira,Result),
     elem(Result,Asya),
     write('Ася : '), write(Asya), nl,
     write('Женя : '), write(Zhenya), nl,
     write('Клава : '), write(Klava), nl,
     write('Ира : '), write(Ira), nl,
     !.

















