parents('Ярослав Поскряков', 'Сергей Поскряков', 'Наталья Поскрякова').
parents('Наталья Поскрякова', 'Иван Назаров', 'Вера Назарова').
parents('Сергей Поскряков', 'Александр Поскряков', 'Иванесса Поскрякова').
parents('Гарри Поттер', 'Александр Поскряков', 'Иванесса Поскрякова').
parents('Северус Снейп', 'Гарри Поттер', 'Гермиона Грейндж').
parents('Дамблдор Иванов', 'Иван Назаров', 'Вера Назарова').
parents('ИмяНельзя Назвать', 'Дамблдор Иванов', 'Вера Назарова').
parents('Иванесса Поскрякова', 'Евгений Поскряков', 'Алена Поскрякова').
parents('Александр Поскряков', 'Алексей Поскряков', 'Нина Поскрякова').
parents('Иван Назаров', 'Ларион Назаров', 'Ефросинья Назарова').
parents('Вера Назарова', 'NULL NULL', 'NULL NULL').
parents('Алексей Поскряков', 'Дмитрий Поскряков', 'Валентина Поскрякова').
parents('Нина Поскрякова', 'Олег Поскряков', 'Анастасия Поскрякова').
parents('Евгений Поскряков', 'Виктор Поскряков', 'Евгения Поскрякова').
parents('Алена Поскрякова', 'NULL NULL', 'NULL NULL').
parents('Дмитрий Поскряков', 'NULL NULL', 'NULL NULL').
parents('Валентина Поскрякова', 'NULL NULL', 'NULL NULL').
parents('Олег Поскряков', 'NULL NULL', 'NULL NULL').
parents('Анастасия Поскрякова', 'NULL NULL', 'NULL NULL').
parents('Виктор Поскряков', 'NULL NULL', 'NULL NULL').
parents('Евгения Поскрякова', 'NULL NULL', 'NULL NULL').
parents('Ларион Назаров', 'NULL NULL', 'NULL NULL').
parents('Ефросинья Назарова', 'NULL NULL', 'NULL NULL').
sex('Ярослав Поскряков', 'm').
sex('Дамблдор Иванов','m').
sex('Гарри Поттер','m').
sex('Северус Снейп','m').
sex('ИмяНельзя Назвать','m').
sex('Наталья Поскрякова', 'f').
sex('Сергей Поскряков', 'm').
sex('Иванесса Поскрякова', 'f').
sex('Александр Поскряков', 'm').
sex('Иван Назаров', 'm').
sex('Вера Назарова', 'f').
sex('Алексей Поскряков', 'm').
sex('Нина Поскрякова', 'f').
sex('Евгений Поскряков', 'm').
sex('Алена Поскрякова', 'f').
sex('Дмитрий Поскряков', 'm').
sex('Валентина Поскрякова', 'f').
sex('Олег Поскряков', 'm').
sex('Анастасия Поскрякова', 'f').
sex('Виктор Поскряков', 'm').
sex('Евгения Поскрякова', 'f').
sex('Ларион Назаров', 'm').
sex('Ефросинья Назарова', 'f').

% Задание 3

del( X, [X|T], T).
del( X, [H|T], [H | T1] ) :-
 del( X, T, T1).

find_bro([H|T],B):-sex(H,Sex),(Sex == 'm' -> B is H,!;find_bro(T,B)).

my_pred([],[]).
my_pred([H|T],KS1):-my_pred(T,U),findall(K1,(parents(K1,H,_)->sex(K1,Sex)-> Sex == 'm'),KS1),
                                    findall(K2,(parents(K2,_,H)->sex(K2,Sex)-> Sex == 'm'),KS2),
                                                                             append(KS1,KS2,KS), append(KS,U,KS1).

brother(F,M,E,B):-findall(T,parents(T,F,M),X), length(X,N), N > 1,del(E,X,X1),find_bro(X1,B).


dbro(X,S):-parents(X,F,M),parents(F,FF,FM), parents(M,MF,MM),
    findall(T,parents(T,FF,FM),FX), length(FX,FN), FN > 1,del(F,FX,FX1),my_pred(FX1,KS),
    findall(T,parents(T,MF,MM),MX), length(MX,MN), MN > 1,del(M,MX,MX1), my_pred(MX1,LS),
    append(KS,LS,S),write(S), nl.

dbro(X,S):-parents(X,F,_),parents(F,FF,FM),
    findall(T,parents(T,FF,FM),FX), length(FX,FN), FN > 1,del(F,FX,FX1),my_pred(FX1,S), write(S), nl.

dbro(X,S):-parents(X,_,M),parents(M,MF,MM),
    findall(T,parents(T,MF,MM),MX), length(MX,MN), MN > 1,del(M,MX,MX1), my_pred(MX1,S), write(S), nl.



% Задание 4

sibling(Person, Sibling):-
    parents(Person, F,M),
    parents(Sibling,F,M),
    Person \= Sibling.


check_link(husband, Husband, Wife):-
    parents(_, Husband,Wife).

check_link(wife, Wife, Husband):-
    parents(_, Husband,Wife).

check_link(brother, Brother, Y):-
    sibling(Brother, Y),
    sex(Y,'m').

check_link(sister, Sister, Y):-
    sibling(Sister, Y),
    sex(Sister,'f').

check_link(father, Father, Child):-
    parents(Child, Father,_).

check_link(mother, Mother, Child):-
    parents(Child, _,Mother).

check_link(parent, Parent, Child):-
    parents(Child, Parent,_);
    parents(Child,_,Parent).

check_link(son, Child, Parent):-
    (parents(Child, Parent,_);parents(Child,_,Parent)),
    sex(Child,'m').

check_link(daughter, Child, Parent):-
    (parents(Child, Parent,_);parents(Child,_,Parent)),
    sex(Child,'f').

check_link(child, Child, Parent):-
    parents(Child, Parent, _);
    parents(Child,_,Parent).

check_relation(X):-
    member(X, [father, mother, sister, brother, son, daughter, husband, wife]).




relative_thread(X, Y, Res):- % цепочка людей, через которых связаны 2 человека
    search_bdth(X, Y, Res).

ask_relative(X, Y, Res):- % цепочка родства, через которую связаны 2 человека
    check_relation(Res), !,
    check_link(Res, X, Y).

relative(X, Y, Res):-
    search_bdth(X, Y, Res1), !,
    transform(Res1, Res).

transform([_],[]):-!. % переделевает цепочку родственников в цепочку родства
transform([First,Second|Tail],ResList):-
    %length([First,Second|Tail],B),
    %A is B - 1,
    %length(ResList,A),
    check_link(Relation,First,Second),
    ResList = [Relation|Tmp],
    transform([Second|Tail],Tmp),!.

prolong([X|T],[Y,X|T]):-
    move(X,Y),
    \+ member(Y,[X|T]).

move(X,Y):-
    check_link(_,X,Y).

search_bdth(X,Y,P):-
    bdth([[X]],Y,L),
    reverse(L,P).

bdth([[X|T]|_],X,[X|T]).
bdth([P|QI],X,R):-
    findall(Z,prolong(P,Z),T),
    append(QI,T,Q0),
    bdth(Q0,X,R),!.

bdth([_|T],Y,L):-
    bdth(T,Y,L).


stepen_rodstva(Name,[],Name).
stepen_rodstva(Name,[H|T],A):-check_link(H,Name,P),stepen_rodstva(P,T,A).







