/* 1 */
CREATE DATABASE './company.fdb'
    USER 'sysdba' PASSWORD 'masterkey'
    page_size = 4096
    DEFAULT CHARACTER SET UTF8;

/* 2 */
/*
    S  == supliers
    P  == details
    SP == supplier_detail
*/
CREATE TABLE suppliers (
    id INTEGER NOT NULL,
    fio VARCHAR(20) NOT NULL,
    money INTEGER NOT NULL,
    city VARCHAR(15) NOT NULL,
    PRIMARY KEY (id)
);
CREATE TABLE details (
    id INTEGER NOT NULL,
    name VARCHAR(20) NOT NULL,
    color CHAR(6) NOT NULL,
    weight INTEGER NOT NULL,
    city VARCHAR(15) NOT NULL,
        PRIMARY KEY (id)
);
CREATE TABLE supplier_detail (
    id_s INTEGER NOT NULL,
    id_d INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
        FOREIGN KEY (id_s) REFERENCES suppliers(id)
            ON DELETE CASCADE
            ON UPDATE CASCADE,
        FOREIGN KEY (id_d) REFERENCES details(id)
            ON DELETE CASCADE
            ON UPDATE CASCADE
);

INSERT INTO suppliers VALUES (1, 'Иванов И.И.',   50000,  'Лондон');
INSERT INTO suppliers VALUES (2, 'Петров П.П.',   20000,  'Москва');
INSERT INTO suppliers VALUES (3, 'Сидоров С.С.',  150000, 'Париж');
INSERT INTO suppliers VALUES (4, 'Васильев В.В.', 300000, 'Лондон');
INSERT INTO suppliers VALUES (5, 'Семенов С.С.',  70000,  'Киев');
INSERT INTO suppliers VALUES (6, 'К. Ласки',      650000, 'Нью-Йорк');
INSERT INTO suppliers VALUES (7, 'Ф. де Костер',  10000,  'Нью-Йорк');
INSERT INTO suppliers VALUES (8, 'Дзержинский Ф.Э.', 10000,  'Москва');
INSERT INTO suppliers VALUES (123, 'Ульянов В.И.',  300000,  'Севастополь');
INSERT INTO details   VALUES (1, 'Болт',        '000000', 34, 'Киев');
INSERT INTO details   VALUES (4, 'Винт',        'ff0000', 67, 'Киев');
INSERT INTO details   VALUES (3, 'Га*ка малая', 'ffff00', 17, 'Лондон');
INSERT INTO details   VALUES (2, 'Гвоздь',      'ffffff', 56, 'Париж');
INSERT INTO details   VALUES (5, 'Петля',       '00ff00', 90, 'Москва');
INSERT INTO details   VALUES (6, 'Га*ка большая','00ff00',25, 'Москва');
INSERT INTO details   VALUES (7, 'Пор*ень',     '00ff00', 120, 'Нью-Йорк');
INSERT INTO details   VALUES (8, 'Вал',         '00ff00', 230, 'Нью-Йорк');
INSERT INTO details   VALUES (9, 'Труба',       '00ff00', 50, 'Киев');
INSERT INTO details   VALUES (10, 'Трубка',     '00ff00', 13, 'Нью-Йорк');
INSERT INTO details   VALUES (11, 'Винт',       'ffffff', 50, 'Севастополь');
INSERT INTO details   VALUES (12, 'Болт',       'ffffff', 50, 'Москва');
INSERT INTO supplier_detail VALUES (2, 3, 120);
INSERT INTO supplier_detail VALUES (2, 4, 190);
INSERT INTO supplier_detail VALUES (2, 5, 15);
INSERT INTO supplier_detail VALUES (1, 4, 18);
INSERT INTO supplier_detail VALUES (3, 5, 190);
INSERT INTO supplier_detail VALUES (5, 5, 200);
INSERT INTO supplier_detail VALUES (1, 5, 100);
INSERT INTO supplier_detail VALUES (2, 2, 20);
INSERT INTO supplier_detail VALUES (3, 1, 150);
INSERT INTO supplier_detail VALUES (6, 1, 621);
INSERT INTO supplier_detail VALUES (6, 2, 34);
INSERT INTO supplier_detail VALUES (7, 4, 69);
INSERT INTO supplier_detail VALUES (4, 3, 30);
INSERT INTO supplier_detail VALUES (5, 4, 18);
INSERT INTO supplier_detail VALUES (2, 1, 25);
INSERT INTO supplier_detail VALUES (1, 3, 14);
INSERT INTO supplier_detail VALUES (4, 5, 22);
INSERT INTO supplier_detail VALUES (1, 2, 67);
INSERT INTO supplier_detail VALUES (3, 3, 15);
INSERT INTO supplier_detail VALUES (4, 1, 18);
INSERT INTO supplier_detail VALUES (5, 1, 217);
INSERT INTO supplier_detail VALUES (8, 8, 200);
INSERT INTO supplier_detail VALUES (2, 12, 926);
INSERT INTO supplier_detail VALUES (123, 11, 590);
INSERT INTO supplier_detail VALUES (123, 5, 621);
INSERT INTO supplier_detail VALUES (123, 2, 267);
INSERT INTO supplier_detail VALUES (123, 1, 409);

/* 3 */
SELECT id FROM details ORDER BY id;

/* 4 */
ALTER TABLE details
    ADD material VARCHAR(15);

/* 5 */
SELECT id, city FROM suppliers
    WHERE city != 'Париж';

/* 6 */
SELECT id, money FROM suppliers
    WHERE city = 'Лондон';

/* 7 */
SELECT id, money FROM suppliers
    WHERE city = 'Москва' AND
          money < 30000
    ORDER BY money DESC;

/* 8 */
SELECT 'Поставщик ' || suppliers.fio || ' поставляет ' || details.name || ' из ' || details.city
    FROM suppliers JOIN supplier_detail ON suppliers.id = supplier_detail.id_s
           JOIN details  ON details.id = supplier_detail.id_d;

/* 9 */
SELECT * FROM details
    WHERE weight BETWEEN 20 AND 50;

/* 10 */
SELECT id, weight * 454
    FROM details;

/* 11 */
SELECT id FROM details
    WHERE weight IN (13, 17, 25);

/* 12 */
SELECT id FROM details
    WHERE (name LIKE '%В%');

/* 13 */
SELECT id FROM details
    WHERE (name LIKE '%я');

/* 14 */
SELECT id FROM details
    WHERE (name LIKE '%а%');

/* 15 */
SELECT id FROM details
    WHERE (name LIKE '___з%');

/* 16 */
SELECT id FROM details
    WHERE (name LIKE '% %');

/* 17 */
SELECT details.id, suppliers.id
    FROM details
        JOIN suppliers ON details.city = suppliers.city;

/* 18 */
UPDATE details SET material='Сталь'  WHERE id = 2;
UPDATE details SET city='Неизвестно' WHERE id = 2;
UPDATE details SET weight=(weight+3) WHERE id = 2;
UPDATE details SET color='ffff00'    WHERE id = 2;

/* 19 */
ALTER TABLE details
    DROP material;

/* 20 */
UPDATE suppliers
    SET money = money * 4
    WHERE city = 'Париж';

/* 21 */
DELETE FROM suppliers
    WHERE city = 'Париж';

/* 22 */
INSERT INTO details (id, city, color, name, weight) VALUES (13, 'Севастополь', 'ff9900', 'Лента', 0);
 
/* 23 */
SELECT id FROM details WHERE weight = 0;

/* 24 */
SELECT COUNT(*) FROM suppliers;

/* 25 */
SELECT details.id, supplier_detail.quantity
    FROM details JOIN supplier_detail
        ON details.id = supplier_detail.id_d;

/* 26 */
SELECT details.id, supplier_detail.quantity
    FROM details JOIN supplier_detail
        ON details.id = supplier_detail.id_d
    WHERE supplier_detail.id_s != 3;

/* 27 */
SELECT sd.id_d
    FROM supplier_detail sd
    GROUP BY sd.id_d
    HAVING COUNT(DISTINCT sd.id_s) > 1;

/* 29 */
SELECT s.fio, d.name, sd.quantity
    FROM suppliers s 
        JOIN supplier_detail sd ON s.id = sd.id_s
        JOIN details d ON d.id = sd.id_d;

/* 30 */
SELECT s.fio, d.name
    FROM (suppliers s JOIN supplier_detail sd ON s.id = sd.id_s)
        JOIN details d ON d.id = sd.id_d;

/* 31 */
SELECT DISTINCT s1.fio, s2.fio
    FROM suppliers s1, suppliers s2
    WHERE s1.city = s2.city
          AND s1.fio != s2.fio;

/* 32 */
SELECT s.fio
    FROM suppliers s JOIN supplier_detail sd ON s.id = sd.id_s;

/* 33 */
SELECT s.id, s.fio
    FROM suppliers s
        INNER JOIN supplier_detail sd
            ON s.id = sd.id_s
        INNER JOIN details d
            ON d.id = sd.id_d
    WHERE d.color = 'ff0000';

/* 34 */
SELECT DISTINCT sd_outer.id_s
    FROM supplier_detail sd_outer
    WHERE sd_outer.id_d IN (
        SELECT sd_inner.id_d
            FROM supplier_detail sd_inner
            WHERE sd_inner.id_s = 3
    ) AND sd_outer.id_s != 3
    ORDER BY sd_outer.id_s DESC;

/* 35 */
SELECT id_s
    FROM supplier_detail
    GROUP BY id_s
    HAVING count(id_d) > 0;

/* 36 */
SELECT s.id, s.fio
    FROM suppliers s
        LEFT JOIN supplier_detail sd
        ON sd.id_s = s.id
    WHERE sd.id_d IS NULL;

/* 37 */
SELECT sd.id_s
    FROM supplier_detail sd
    GROUP BY sd.id_s
    HAVING (
        SELECT COUNT(d.id) FROM details d
    ) <= COUNT(sd.id_d);

/* 38 */
SELECT DISTINCT id_d
    FROM supplier_detail
    WHERE id_s != 1;

/* 39 */
SELECT DISTINCT d.id
    FROM details d
        INNER JOIN supplier_detail sd
        ON sd.id_d = d.id
    WHERE d.weight > 34
        OR sd.id_s = 3
    ORDER BY d.id DESC;

/* 40 */
SELECT d.name
    FROM details d
        INNER JOIN supplier_detail sd
        ON sd.id_d = d.id
    WHERE sd.id_s = 2
    ORDER BY d.id ASC;

/* 41 */
SELECT id
    FROM suppliers
    WHERE money < (
        SELECT MAX(money)
            FROM suppliers
    );

/* 42 */
SELECT s1.id, s1.fio, s1.city
    FROM suppliers s1
    WHERE s1.money >= (
        SELECT AVG(s2.money)
            FROM suppliers s2
            WHERE s2.city = s1.city
    );

/* 43 */
SELECT d.id, MAX(sd.quantity)
    FROM details d
        LEFT JOIN supplier_detail sd
        ON sd.id_D = d.id
    GROUP BY d.id;

/* 44 */
SELECT s.fio, d.name
    FROM suppliers s
         INNER JOIN supplier_detail sd_outer
         ON sd_outer.id_s = s.id
            INNER JOIN details d
                ON sd_outer.id_d = d.id
    WHERE sd_outer.quantity = (
        SELECT MAX(sd_inner.quantity)
            FROM supplier_detail sd_inner
            WHERE sd_inner.id_d = d.id
    );








/* 1.1 */
SELECT d.id
    FROM suppliers s
        JOIN supplier_detail sd
        ON sd.id_s = s.id
        JOIN details d
        ON d.id = sd.id_d
    WHERE   (d.color = 'ffffff')
        AND (d.city IN ('Севастополь', 'Москва'))
        AND (s.fio LIKE '%П%');
/* 1.2 */
SELECT d.id
    FROM suppliers s, supplier_detail sd, details d
    WHERE s.id = sd.id_s AND d.id = sd.id_d
        AND (d.color = 'ffffff')
        AND (d.city IN ('Севастополь', 'Москва'))
        AND (s.fio LIKE '%П%');

/* 2.1 */
SELECT DISTINCT sd.id_d
    FROM suppliers s
        JOIN supplier_detail sd
        ON sd.id_s = s.id
    WHERE s.city = 'Москва' AND (
        SELECT SUM(sd_inner.quantity)
            FROM supplier_detail sd_inner
            WHERE sd.id_d = sd_inner.id_d
    ) <= 12300;
/* 2.2 */
SELECT DISTINCT sd.id_d
    FROM suppliers s, supplier_detail sd
    WHERE sd.id_s = s.id
        AND s.city = 'Москва' AND (
        SELECT SUM(sd_inner.quantity)
            FROM supplier_detail sd_inner
            WHERE sd.id_d = sd_inner.id_d
    ) <= 12300;

/* 3.1 */
SELECT s.fio
    FROM details d
        JOIN supplier_detail sd
        ON sd.id_d = d.id
        JOIN suppliers s
        ON s.id = sd.id_s
    WHERE   d.name LIKE '%*%'
        AND s.city = 'Париж';
/* 3.2 */
SELECT s.fio
    FROM details d, supplier_detail sd, suppliers s
    WHERE   d.id = sd.id_d AND s.id = sd.id_s
        AND d.name LIKE '%*%'
        AND s.city = 'Париж';

/* 4.1 */
SELECT sd.id_d, SUM(sd.quantity)
    FROM suppliers s
        JOIN supplier_detail sd
        ON sd.id_s = s.id
    WHERE s.id = 123
    GROUP BY sd.id_d
    ORDER BY SUM(sd.quantity) ASC;
/* 4.2 */
SELECT sd.id_d, SUM(sd.quantity)
    FROM suppliers s, supplier_detail sd
    WHERE   sd.id_s = s.id
        AND s.id = 123
    GROUP BY sd.id_d
    ORDER BY SUM(sd.quantity) ASC;







/* Создание таблиц данных */
CREATE TABLE employes (
    id INTEGER NOT NULL,
    surname VARCHAR(20) NOT NULL,
    address VARCHAR(20) NOT NULL,
    experience INTEGER NOT NULL,
    specialty VARCHAR(10) NOT NULL,
    div_num INTEGER NOT NULL,
    PRIMARY KEY (id)
);
CREATE TABLE work_activity (
    employee_id INTEGER NOT NULL,
    wr_id INTEGER NOT NULL,
    reg_num INTEGER NOT NULL,
    fio VARCHAR(20) NOT NULL,
    experience INTEGER NOT NULL,
    start_date DATE NOT NULL,
    end_date DATE,
    end_reason VARCHAR(10),
    
    PRIMARY KEY (employee_id),
    UNIQUE (wr_id),
    FOREIGN KEY (employee_id) REFERENCES employes(id)
);
CREATE TABLE company (
    id INTEGER NOT NULL,
    title VARCHAR(10) NOT NULL,
    div_num INTEGER NOT NULL,
    employes_count INTEGER NOT NULL,
    
    PRIMARY KEY (id)
);

/* Заполнение данными */
INSERT INTO employes VALUES (1, 'Михайлов',  'ул. Первая',    4, 'рыболов', 9);
INSERT INTO employes VALUES (2, 'Руднев',    'ул. Вторая',    3, 'слесарь', 5);
INSERT INTO employes VALUES (3, 'Копащенко', 'ул. Третья',    2, 'токарь',  9);
INSERT INTO employes VALUES (4, 'Ализ',      'ул. Четвёртая', 1, 'лесоруб', 1);
INSERT INTO work_activity VALUES (1, 1500, 1515, 'Михайлов', 4, '1982-01-01', '1983-01-01', 'слишкомтру');
INSERT INTO work_activity VALUES (3, 1501, 1525, 'Михайлов', 2, '1982-01-01', '1984-01-01', 'алкоголь');
INSERT INTO company VALUES (789, 'Оз',         5, 15);
INSERT INTO company VALUES (123, 'Морфеус',    9, 20);
INSERT INTO company VALUES (456, 'РосСельМаш', 1, 10);

/* 1 */
SELECT e.id, e.surname
    FROM employes e
        JOIN work_activity wa
        ON wa.employee_id = e.id
        JOIN company c
        ON c.div_num = e.div_num
    WHERE wa.end_reason IS NOT NULL
        AND wa.end_date - wa.start_date <= 366
        AND c.id = 123;

/* 2 */
ALTER TABLE company
    ADD bank_account VARCHAR(20) DEFAULT '0000-0000-0000-0000';
SELECT title
    FROM company
    WHERE employes_count = (
        SELECT MAX(employes_count)
            FROM company
    );
