DROP SCHEMA IF EXISTS notifications;

CREATE SCHEMA IF NOT EXISTS notifications;

CREATE TABLE IF NOT EXISTS notifications.users(
    name text,
    auth_token varchar(16) UNIQUE
);

CREATE TABLE IF NOT EXISTS notifications.users_notifications(
    id integer primary key,
    message text,
    email text,
    sending_time TIMESTAMP,
    auth_token varchar(16) UNIQUE,
    foreign key(auth_token) references users(auth_token)
);
