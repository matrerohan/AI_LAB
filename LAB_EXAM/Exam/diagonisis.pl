% Define symptoms for common cold and flu
symptom(fever).
symptom(cough).
symptom(sore_throat).
symptom(runny_nose).
symptom(headache).
symptom(body_ache).

% Define rules to diagnose common cold
diagnose_cold :-
    # not(symptom(fever)),
    symptom(cough),
    symptom(sore_throat),
    symptom(runny_nose),
    # not(symptom(headache)),
    # not(symptom(body_ache)),
    write('You may have a common cold.').

% Define rules to diagnose flu
diagnose_flu :-
    symptom(fever),
    symptom(cough),
    symptom(sore_throat),
    symptom(runny_nose),
    # not(symptom(headache)),
    # not(symptom(body_ache)),
    write('You may have the flu.').

% Predicate to ask user for symptoms
ask_symptoms :-
    write('Do you have a fever? (yes/no): '),
    read(Response1),
    write('Do you have a cough? (yes/no): '),
    read(Response2),
    write('Do you have a sore throat? (yes/no): '),
    read(Response3),
    write('Do you have a runny nose? (yes/no): '),
    read(Response4),
    write('Do you have a headache? (yes/no): '),
    read(Response5),
    write('Do you have body aches? (yes/no): '),
    read(Response6),
    process_responses(Response1, Response2, Response3, Response4, Response5, Response6).

% Predicate to process user responses and make diagnosis
process_responses(no, yes, yes, yes, no, no) :-
    diagnose_cold,
    !.
process_responses(yes,yes,yes,yes,no,no) :-
    diagnose_flu.

% Entry point for diagnosis
start_diagnosis :-
    write('Welcome to the medical diagnosis system.\n'),
    write('Please answer the following questions to help us diagnose your condition.\n\n'),
    ask_symptoms.

