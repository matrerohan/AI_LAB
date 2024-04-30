% Facts: Symptoms of flu
symptom(runny_nose).
symptom(fever).
symptom(body_ache).

% Rule: If a patient has flu symptoms, they have flu
has_flu(Symptoms) :-
    member(runny_nose, Symptoms),
    member(fever, Symptoms),
    member(body_ache, Symptoms).

% Rule: Prescription for flu
prescribe_medicine(dolo) :- has_flu(_).

% Rule: Diagnosis and prescription based on symptoms
diagnose_and_prescribe(Symptoms, Diagnosis, Prescription) :-
    (   has_flu(Symptoms) ->
        Diagnosis = flu,
        prescribe_medicine(Prescription)
    ;   Diagnosis = 'other',
        Prescription = 'No specific medicine'
    ).

    
% [diagnose].
% diagnose_and_prescribe([runny_nose, fever, body_ache, cough], Diagnosis, Prescription).
