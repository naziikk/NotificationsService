DROP SCHEMA IF EXISTS notifications CASCADE;

CREATE SCHEMA IF NOT EXISTS notifications;

CREATE TABLE IF NOT EXISTS notifications.users(
    name text,
    last_name text,
    auth_token varchar UNIQUE
);

CREATE TABLE IF NOT EXISTS notifications.users_notifications(
    id integer primary key,
    message text,
    email text,
    sending_time TIMESTAMP WITH TIME ZONE,
    jwt varchar(16),
    foreign key(jwt) references users(auth_token)
);
