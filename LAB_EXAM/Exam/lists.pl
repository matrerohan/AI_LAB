% Define a predicate to check if a list is empty
is_empty([]).

% Define a predicate to check if an element is a member of a list
is_member(Element, [Element|_]).
is_member(Element, [_|Rest]) :-
    is_member(Element, Rest).

% Define a predicate to append two lists
append_lists([], List, List).
append_lists([Head|Tail1], List2, [Head|Result]) :-
    append_lists(Tail1, List2, Result).

% Define a predicate to reverse a list
reverse_list(List, Reversed) :-
    reverse_list_helper(List, [], Reversed).

reverse_list_helper([], Reversed, Reversed).
reverse_list_helper([Head|Tail], Temp, Reversed) :-
    reverse_list_helper(Tail, [Head|Temp], Reversed).

% Define a predicate to find the length of a list
list_length([], 0).
list_length([_|Tail], Length) :-
    list_length(Tail, TailLength),
    Length is TailLength + 1.
