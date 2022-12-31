/* Создать отношения в БД и заполнить некоторые из них */
CREATE TABLE "service_add_req_state" (
	"name"	TEXT,
	PRIMARY KEY("name")
) WITHOUT ROWID;

CREATE TABLE "service_order_state" (
	"name"	TEXT,
	PRIMARY KEY("name")
) WITHOUT ROWID;

CREATE TABLE "service_worker_role" (
	"name"	TEXT,
	PRIMARY KEY("name")
) WITHOUT ROWID;

CREATE TABLE "service_stage_type" (
	"type"	TEXT,
	PRIMARY KEY("type")
) WITHOUT ROWID;

CREATE TABLE "customer" (
	"id"	INTEGER,
	"first_name"	TEXT NOT NULL,
	"last_name"	TEXT NOT NULL,
	"tel_number"	TEXT NOT NULL,
	"tg_username"	TEXT NOT NULL,
	"tg_chat_id"	INTEGER NOT NULL,
	PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE "worker" (
	"id"	INTEGER,
	"role"	TEXT NOT NULL,
	"first_name"	TEXT NOT NULL,
	"last_name"	TEXT NOT NULL,
	"tel_number"	TEXT NOT NULL,
	"tg_username"	TEXT NOT NULL,
	"tg_chat_id"	INTEGER NOT NULL,
	FOREIGN KEY("role") REFERENCES "service_worker_role"("name") ON UPDATE CASCADE ON DELETE CASCADE,
	PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE "order" (
	"id"	INTEGER,
	"customer_id"	INTEGER NOT NULL,
	"worker_id"	INTEGER NOT NULL,
	"description"	TEXT NOT NULL,
	"price"	INTEGER NOT NULL,
	"state"	TEXT NOT NULL,
	"begin_time"	TEXT NOT NULL DEFAULT (strftime('%Y-%m-%dT%H:%M:%SZ', 'now')),
	"last_state_update_time"	TEXT NOT NULL DEFAULT (strftime('%Y-%m-%dT%H:%M:%SZ', 'now')),
	"end_time"	TEXT NOT NULL,
	FOREIGN KEY("state") REFERENCES "service_order_state"("name") ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY("worker_id") REFERENCES "worker"("id") ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY("customer_id") REFERENCES "customer"("id") ON UPDATE CASCADE ON DELETE CASCADE,
	PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE "additional_requirement" (
	"order_id"	INTEGER,
	"instant"	TEXT DEFAULT (strftime('%Y-%m-%dT%H:%M:%SZ', 'now')),
	"type"	TEXT NOT NULL DEFAULT 'NOTE',
	"description"	TEXT NOT NULL,
	"state"	TEXT NOT NULL DEFAULT 'WAITING',
	"price_delta"	INTEGER NOT NULL,
	FOREIGN KEY("state") REFERENCES "service_add_req_state"("name") ON UPDATE CASCADE ON DELETE CASCADE,
	PRIMARY KEY("order_id","instant")
);

CREATE TABLE "stage" (
	"id"	TEXT,
	"type"	TEXT,
	"data"	TEXT,
	PRIMARY KEY("id"),
	FOREIGN KEY("type") REFERENCES "service_stage_type"("type") ON UPDATE CASCADE ON DELETE CASCADE
) WITHOUT ROWID;

INSERT INTO "service_add_req_state" VALUES ('WAITING'), ('APPROVED'), ('CANCELLED');
INSERT INTO "service_order_state" VALUES ('IN_PROGRESS'), ('READY'), ('COMPLETE');
INSERT INTO "service_worker_role" VALUES ('PLAIN'), ('ADMIN');
INSERT INTO "service_stage_type" VALUES ('CREATE_NEW_CUSTOMER', 'CREATE_NEW_WORKER', 'CHANGE_ORDER_STATE');

/* Работа с БД */
-- Создать покупателя
INSERT INTO "customer" ("first_name", "last_name", "tel_number", "tg_username", "tg_chat_id")
  VALUES (?, ?, ?, ?, ?);

-- Создать работника
INSERT INTO "worker" ("role", "first_name", "last_name", "tel_number", "tg_username", "tg_chat_id")
  VALUES (?, ?, ?, ?, ?, ?);

-- Создать заказ
INSERT INTO "order" ("customer_id", "worker_id", "description", "price", "state", "end_time") VALUES (?, ?, ?, ?, ?, ?);

-- Изменить состояние заказа
UPDATE "order"
  SET "state" = ?, "last_state_update_time" = (strftime('%Y-%m-%dT%H:%M:%SZ', 'now'))
  WHERE "id" = ?;

-- Получить клиента по номеру телефона
SELECT * FROM "customer" WHERE "tel_number" = ?;

-- Получить клиента по Telegram Username
SELECT * FROM "customer" WHERE "tg_username" = ?;

-- Получить заказ по id
SELECT * FROM "order"
  WHERE "id" = ?;

-- Получить все активные заказы клиента
SELECT * FROM "order"
  WHERE "customer_id" = ? AND "state" <> 'COMPLETE';

-- Получить все активные заказы рабочего
SELECT * FROM "order"
  WHERE "worker_id" = ? AND "state" <> 'COMPLETE';

-- Получить заказ по ид клиента и работника, описанию и цене
SELECT * FROM "order"
  WHERE "customer_id" = ?
    AND "worker_id" = ?
    AND "description" = ?
    AND "price" = ?
  ORDER BY "id" DESC;

-- Получить полную информацию о работнике по специфическим полям
SELECT * FROM "worker"
	WHERE "tel_number" = ?;

-- Обновить информацию о работнике
UPDATE "worker"
	SET "role" = ?,
			"first_name" = ?,
			"last_name" = ?,
			"tel_number" = ?,
			"tg_username" = ?,
			"tg_chat_id" = ?
	WHERE "id" = ?;

-- Обновить информацию о клиенте
UPDATE "customer"
	SET	"first_name" = ?,
			"last_name" = ?,
			"tel_number" = ?,
			"tg_username" = ?,
			"tg_chat_id" = ?
	WHERE "id" = ?;

-- Добавить этап диалога
INSERT INTO "stage" ("id", "type", "data") VALUES (?, ?, ?);
-- Обновить этап диалога
UPDATE "stage" SET "data" = ? WHERE "id" = ?;
-- Получить этап диалога по id
SELECT * FROM "stage" WHERE "id" = ?;
-- Удалить этап диалога
DELETE FROM "stage" WHERE "id" = ?;

-- Получить количество работников с указанным username
SELECT COUNT(*) FROM "worker" WHERE "tg_username" = ?;
-- Получить количество клиентов с указанным username
SELECT COUNT(*) FROM "customer" WHERE "tg_username" = ?;

-- Добавить требование
INSERT INTO "additional_requirement"
	("order_id", "description", "price_delta")
	VALUES (?, ?, ?);
-- Выбрать требование по id
SELECT * FROM "additional_requirement" WHERE "order_id" = ?;
-- Обновить данные требования по id
UPDATE "additional_requirement"
	SET "description" = ?,
			"state" = ?,
			"price_delta" = ?
	WHERE "order_id" = ?;
