�����( �, glas).
�����( b, sog).
�����( �, sog).
�����( d, sog).
�����( e, glas).
�����( f, sog).

work :-
    bagof( X, �����( X, sog), L),
    write(L).
