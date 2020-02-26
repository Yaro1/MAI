parents('������� ���������', '������ ���������', '������� ����������').
parents('������� ����������', '���� �������', '���� ��������').
parents('������ ���������', '��������� ���������', '�������� ����������').
parents('����� ������', '��������� ���������', '�������� ����������').
parents('������� �����', '����� ������', '�������� �������').
parents('�������� ������', '���� �������', '���� ��������').
parents('��������� �������', '�������� ������', '���� ��������').
parents('�������� ����������', '������� ���������', '����� ����������').
parents('��������� ���������', '������� ���������', '���� ����������').
parents('���� �������', '������ �������', '��������� ��������').
parents('���� ��������', 'NULL NULL', 'NULL NULL').
parents('������� ���������', '������� ���������', '��������� ����������').
parents('���� ����������', '���� ���������', '��������� ����������').
parents('������� ���������', '������ ���������', '������� ����������').
parents('����� ����������', 'NULL NULL', 'NULL NULL').
parents('������� ���������', 'NULL NULL', 'NULL NULL').
parents('��������� ����������', 'NULL NULL', 'NULL NULL').
parents('���� ���������', 'NULL NULL', 'NULL NULL').
parents('��������� ����������', 'NULL NULL', 'NULL NULL').
parents('������ ���������', 'NULL NULL', 'NULL NULL').
parents('������� ����������', 'NULL NULL', 'NULL NULL').
parents('������ �������', 'NULL NULL', 'NULL NULL').
parents('��������� ��������', 'NULL NULL', 'NULL NULL').
sex('������� ���������', 'm').
sex('�������� ������','m').
sex('����� ������','m').
sex('������� �����','m').
sex('��������� �������','m').
sex('������� ����������', 'f').
sex('������ ���������', 'm').
sex('�������� ����������', 'f').
sex('��������� ���������', 'm').
sex('���� �������', 'm').
sex('���� ��������', 'f').
sex('������� ���������', 'm').
sex('���� ����������', 'f').
sex('������� ���������', 'm').
sex('����� ����������', 'f').
sex('������� ���������', 'm').
sex('��������� ����������', 'f').
sex('���� ���������', 'm').
sex('��������� ����������', 'f').
sex('������ ���������', 'm').
sex('������� ����������', 'f').
sex('������ �������', 'm').
sex('��������� ��������', 'f').

% ������� 3

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



% ������� 4

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




relative_thread(X, Y, Res):- % ������� �����, ����� ������� ������� 2 ��������
    search_bdth(X, Y, Res).

ask_relative(X, Y, Res):- % ������� �������, ����� ������� ������� 2 ��������
    check_relation(Res), !,
    check_link(Res, X, Y).

relative(X, Y, Res):-
    search_bdth(X, Y, Res1), !,
    transform(Res1, Res).

transform([_],[]):-!. % ������������ ������� ������������� � ������� �������
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







