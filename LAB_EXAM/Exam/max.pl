max(X, Y, Z, Max) :- X >= Y, X >= Z, Max is X.
max(X, Y, Z, Max) :- Y >= X, Y >= Z, Max is Y.
max(X, Y, Z, Max) :- Z >= X, Z >= Y, Max is Z.

%swipl
%[max].
% max(5, 10, 3, Max).
% max(8, 2, 8, Max).
