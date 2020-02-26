
% получение элемента списка
getNthElem([H|_],H,0):-!.
getNthElem([_|T],X,N):-
    M is N - 1,
    getNthElem(T,X,M).

getNumIgor([H|_], 0):-H == white.
getNumIgor([_|T],N):-getNumIgor(T,M), N is M + 1.

% свапнуть два элемента
swap_elem(L,M,N,ResL):-
    length(L,Len1),
    length(ResL,Len2),
    Len1 =:= Len2,
    append(MH,[Mth|MT],L),
    append(MH,[Nth|MT],Tmp),
    append(NH,[Nth|NT],Tmp),
    append(NH,[Mth|NT],ResL),

    length(MH,M),
    length(NH,N), !.


%OK
% элементы в правильном порядке если условие выполняется, то надо дальше
% менять местами элементы
check_correct(L1,N,L2):-
    getNthElem(L1,X,N),
    getNthElem(L2,Y,N),
    ((X == blue, Y == black);(X == black, Y == blue)),
    !.

mypred(N,Len1,N1,L,X):-between(0, Len1,N1),swap_elem(L,N1,N,X).

% переход между
move([H|_],Res,F):-
    move(H,Res, F).

move(st(L),st(ResL)):-
    length(L,Len),
    Len1 is Len - 1,
    between(0,Len1,A),
    between(0,Len1,B),

    A @< B,
    check_correct(L,A,B),
    swap_elem(L,A,B,X),

    ResL = X.

sravnIgorLoh([],[]).
sravnIgorLoh([H1|R1], [H2|R2]):- H1 = H2, sravnIgorLoh(R1,R2).

check(_,[]):-false.
check(X,[H|_]):- sravnIgorLoh(X,H),!.
check(X,[_|T]):-check(X,T),!.

% запоминать множество состояний в которых я был, добавить для этого
% список списков
%продление пути без зацикливания
%

ravn(X,X).

prolong(X,F,NUMOP, P1, MYDICKISBIG):-
NUMOP1 is NUMOP + 1,
NUMOP1 < 5,
write(NUMOP1), nl,
write(X), nl,
write(F), nl,
write( MYDICKISBIG), nl,
length(X,Len),
Len1 is Len - 1,
sravnIgorLoh(X,F) ->
ravn(X,P1),write('OKE'),nl,true,!;
not(sravnIgorLoh(X,F)),
getNumIgor(X,N),
N1 is N - 1,
between(0, Len1,N1),swap_elem(X,N1,N,Res),
    not(check(Res, MYDICKISBIG)),
    prolong(Res,F,NUMOP1,Res1 ,[Res|MYDICKISBIG]),
    ravn(Res1,P1),!.

prolong(X,F,NUMOP, P1, MYDICKISBIG):-
NUMOP1 is NUMOP + 1,
NUMOP1 < 5,
write(NUMOP1), nl,
write(X), nl,
write(F), nl,
write( MYDICKISBIG), nl,
length(X,Len),
Len1 is Len - 1,
sravnIgorLoh(X,F) ->
ravn(X,P1),write('OKE'),nl,true,!;
not(sravnIgorLoh(X,F)),
getNumIgor(X,N),
N2 is N - 1,
between(0, Len1,N2),swap_elem(X,N2,N,Res),
    not(check(Res, MYDICKISBIG)),
    prolong(Res,F,NUMOP1,Res1 ,[Res|MYDICKISBIG]),
    ravn(Res1,P1),!.

prolong(X,F,NUMOP, P1, MYDICKISBIG):-
NUMOP1 is NUMOP + 1,
NUMOP1 < 5,
write(NUMOP1), nl,
write(X), nl,
write(F), nl,
write( MYDICKISBIG), nl,
length(X,Len),
Len1 is Len - 1,
sravnIgorLoh(X,F) ->
ravn(X,P1),write('OKE'),nl,true,!;
not(sravnIgorLoh(X,F)),
getNumIgor(X,N),
N3 is N - 1,
between(0, Len1,N3),swap_elem(X,N3,N,Res),
    not(check(Res, MYDICKISBIG)),
    prolong(Res,F,NUMOP1,Res1 ,[Res|MYDICKISBIG]),
    ravn(Res1,P1),!.


prolong(X,F,NUMOP, P1, MYDICKISBIG):-
NUMOP1 is NUMOP + 1,
NUMOP1 < 5,
write(NUMOP1), nl,
write(X), nl,
write(F), nl,
write( MYDICKISBIG), nl,
length(X,Len),
Len1 is Len - 1,
sravnIgorLoh(X,F) ->
ravn(X,P1),write('OKE'),nl,true,!;
not(sravnIgorLoh(X,F)),
getNumIgor(X,N),
N4 is N - 1,
between(0, Len1,N4),swap_elem(X,N4,N,Res),
    not(check(Res, MYDICKISBIG)),
    prolong(Res,F,NUMOP1,Res1 ,[Res|MYDICKISBIG]),
    ravn(Res1,P1),!.


invPrint([]).
inv_print([A|T]):-inv_print(T), write(A), nl.

% поиск в глубину
search_dpth(A,B):-
    write('DFS START'), nl,
    get_time(DFS),
    dpth([A],B,L),
    inv_print(L),
    get_time(DFS1),
    write('DFS END'), nl, nl,
    T1 is DFS1 - DFS,
    write('TIME IS '), write(T1), nl, nl.

dpth(X,X,X).
dpth([P|_],F,_):-
    P1 = [],
    prolong(P,F, 0, P1, []), write('HUYHUYHUYHUYHUYHUYHUYHUY'),write(P1), nl.



