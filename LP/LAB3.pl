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

ravn(X,X).

prolong(X,F,NUMOP, P1, MYDICKISBIG, MYBIG):-
NUMOP1 is NUMOP + 1,
NUMOP1 < 30,
length(X,Len),
Len1 is Len - 1,
(
sravnIgorLoh(X,F) ->
ravn(X,P1),ravn(MYDICKISBIG, MYBIG),!;
( not(sravnIgorLoh(X,F)),
getNumIgor(X,N),
N1 is N - 1,
N2 is N - 2,
N3 is N + 1,
N4 is N + 2,
(
(   between(0, Len1,N1),swap_elem(X,N1,N,Res),
not(check(Res, MYDICKISBIG)),
prolong(Res,F,NUMOP1,Res1 ,[Res|MYDICKISBIG], MYBIG),
ravn(Res1,P1)) -> (!);
(   between(0, Len1,N2),swap_elem(X,N,N2,Res),
not(check(Res, MYDICKISBIG)),
prolong(Res,F,NUMOP1, Res1, [Res|MYDICKISBIG], MYBIG),
ravn(Res1,P1)) ->  (!);
(   between(0, Len1,N3),swap_elem(X,N,N3,Res),
not(check(Res, MYDICKISBIG)),
prolong(Res,F,NUMOP1, Res1,[Res|MYDICKISBIG] , MYBIG),
ravn(Res1,P1)) ->  (!);
    between(0, Len1,N4),swap_elem(X,N,N4,Res),
not(check(Res, MYDICKISBIG)),
prolong(Res,F,NUMOP1, Res1, [Res|MYDICKISBIG], MYBIG),
ravn(Res1,P1), !))),!.



uglub(X,MYDICKISBIG, N1, NEWBIG):-
    getNumIgor(X,N),
    length(X,Len), Len1 is Len - 1, between(0, Len1,N1),swap_elem(X,N1,N,Res),
    not(check(Res, MYDICKISBIG)), append([Res], MYDICKISBIG, NEWBIG),!.

check_bdth(_,[],_):-false,!.
check_bdth(F,[H|_],Res):-check(F,H),ravn(H,Res),!.
check_bdth(F,[_|T],_):-check_bdth(F,T).


schet(X,MYDICKISBIG,NEWDICK):-
getNumIgor(X,N),
N1 is N - 1,
N2 is N - 2,
N3 is N + 1,
N4 is N + 2,
(
uglub(X,MYDICKISBIG1,N1,NEWBIGM1), append([NEWBIGM1],MYDICKISBIG,NEWDICK1);
uglub(X,MYDICKISBIG2,N2,NEWBIGM2), append([NEWBIGM2],NEWDICK1,NEWDICK2);
uglub(X,MYDICKISBIG3,N3,NEWBIGP1), append([NEWBIGP1],NEWDICK2,NEWDICK3);
uglub(X,MYDICKISBIG4,N4,NEWBIGP2), append([NEWBIGP2],NEWDICK3,NEWDICK)
),!.


%prolong_bdth(X,F,BIGBIG2,MYBIG):-
%   length(BIGBIG2, K),
%  K == 0,
% schet(X,[],NEWDICK).

prolong_bdth(X,F,[],MYBIG):-
    write('ALL RIGHT!'), nl,
    schet(X,[], NEWDICK),
    (check_bdth(F,NEWDICK,MYBIG) -> !;
    prolong_bdth(X,F,[NEWDICK]),!).

prolong_bdth(X,F,[HBB|TBB],MYBIG):-
    schet(X,HBB, NEWDICK),
    (
     check_bdth(F,NEWDICK,MYBIG) -> !;
    (prolong_bdth(X,F,[NEWDICK,HBB]) -> !; prolong_bdth(X,F,TBB,MYBIG))).


inv_Print([]).
inv_print([A|T]):-inv_print(T), write(A), nl.

% поиск в глубину
search_dpth(A,B):-
    write('DFS START'), nl,
    get_time(DFS),
    prolong(A,B, 0, P1, [], MYBIG), % дописать вывод нормальный!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    write(MYBIG), nl,
    get_time(DFS1),
    write('DFS END'), nl, nl,
    T1 is DFS1 - DFS,
    write('TIME IS '), write(T1), nl, nl.

% поиск в ширину
search_bdth(X,Y):-
    write('BFS START'), nl,
    get_time(BFS),
    bdth(X,Y, T),
    %inv_print(L),
    get_time(BFS1),
    write('BFS END'), nl, nl,
    T1 is BFS1 - BFS,
    write('TIME IS '), write(T1), nl, nl.

bdth(X,R, T):-
    findall(Z,prolong_bdth(X,R,0,P1,[],Z),T),
    write(T), nl.























