класс( а, glas).
класс( b, sog).
класс( с, sog).
класс( d, sog).
класс( e, glas).
класс( f, sog).

work :-
    bagof( X, класс( X, sog), L),
    write(L).
