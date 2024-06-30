/* 1 */
CREATE DATABASE './company.fdb'
    USER 'sysdba' PASSWORD 'masterkey'
    page_size = 4096
    DEFAULT CHARACTER SET UTF8;

/* 2 */
CREATE TABLE suppliers (
    id INTEGER PRIMARY KEY,
    fio VARCHAR(20),
    money INTEGER,
    city VARCHAR(15)
);
CREATE TABLE details (
    id INTEGER PRIMARY KEY,
    name VARCHAR(20) NOT NULL,
    color CHAR(6) NOT NULL,
    weight INTEGER NOT NULL,
    city VARCHAR(15) NOT NULL
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
INSERT INTO suppliers VALUES (9, 'Ульянов В.И.',  300000,  'Москва');
INSERT INTO details   VALUES (1, 'Болт',        '000000', 34, 'Киев');
INSERT INTO details   VALUES (4, 'Винт',        'ff0000', 67, 'Киев');
INSERT INTO details   VALUES (3, 'Гайка малая', 'ffff00', 17, 'Лондон');
INSERT INTO details   VALUES (2, 'Гвоздь',      'ffffff', 56, 'Париж');
INSERT INTO details   VALUES (5, 'Петля',       '00ff00', 90, 'Москва');
INSERT INTO details   VALUES (6, 'Гайка большая','00ff00',25, 'Москва');
INSERT INTO details   VALUES (7, 'Поршень',     '00ff00', 120, 'Нью-Йорк');
INSERT INTO details   VALUES (8, 'Вал',         '00ff00', 230, 'Нью-Йорк');
INSERT INTO details   VALUES (9, 'Труба',       '00ff00', 50, 'Киев');
INSERT INTO details   VALUES (10, 'Трубка',     '00ff00', 13, 'Нью-Йорк');
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

/* 3 */
SELECT 'Деталь #', id FROM details;

/* 4 */
ALTER TABLE details
    ADD material VARCHAR(15) NOT NULL;

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
SELECT 'Поставщик', suppliers.fio, 'поставляет', details.name, 'из', details.city
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
    WHERE weight = 13
          OR weight = 17
          OR weight = 25;

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
INSERT INTO details (id, city, color, name, weight) VALUES (6, 'Севастополь', 'ff9900', 'Лента', 0);
 
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
        ON details.id = supplier_detail.id_d;
    WHERE supplier_detail.id_s != 3;

/* 27 */
SELECT sd.id_d, sd.quantity
    FROM supplier_detail sd
    GROUP BY sd.id_s
    HAVING COUNT(DISTINCT sd.id_s) > 1;

/* 29 */
SELECT s.name, d.name, sd.quantity
    FROM (suppliers s JOIN supplier_detail sd ON s.id = sd.id_s)
        JOIN details d ON d.id = sd.id_d;

/* 30 */
SELECT s.name, d.name
    FROM (suppliers s JOIN supplier_detail sd ON s.id = sd.id_s)
        JOIN details d ON d.id = sd.id_d;

/* 31 */
SELECT DISTINCT s1.name, s2.name
    FROM suppliers s1, suppliers s2
    WHERE s1.city = s2.city
          AND s1.name != s2.name;

/* 32 */
SELECT s.name
    FROM suppliers s JOIN supplier_detail sd ON s.id = sd.id_s;

/* 33 */
SELECT s.name
    FROM (suppliers s JOIN supplier_detail sd ON s.id = sd.id_s)
        JOIN details d ON d.id = sd.id_d
    GROUP BY s.name
    HAVING ;
