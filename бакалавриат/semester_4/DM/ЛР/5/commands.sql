/* Выбрать всех хирургов, номер лицензий которых выше среднего */
SELECT *
    FROM surgeon s1
    WHERE s1.id >=
    (
        SELECT AVG(s2.id)
            FROM surgeon s2
    );


/* Выбрать всех хирургов, номер патентов которых выше среднего номера патента
    во всех операциях, номер которых больше 10 */
SELECT *
    FROM surgeon s1
    WHERE s1.id >=
    (
        SELECT AVG(s2.patent_id)
            FROM operation s2
            WHERE s2.num > 10
    );

/* Выбрать все лекарства, которые ни разу не применялись в операциях */
SELECT d.name
    FROM drug d
    WHERE NOT EXISTS
    (
        SELECT *
            FROM drug_operation do
            WHERE d.name = do.drug_name
    );

/* Выбрать номера патентов хирургов, не оперировавих пациента 0 */
SELECT s.id
    FROM surgeon s
    WHERE s.id != ALL
    (
        SELECT o.patent_id
            FROM operation o
            WHERE o.patient_id = 0
    );


/* Выбрать номера патентов хирургов, оперировавих пациента 0 */
SELECT s.id
    FROM surgeon s
    WHERE s.id = ANY
    (
        SELECT o.patent_id
            FROM operation o
            WHERE o.patient_id = 0
    );
