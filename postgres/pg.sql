DROP SCHEMA IF EXISTS notifications CASCADE;

CREATE SCHEMA IF NOT EXISTS notifications;

CREATE TABLE IF NOT EXISTS notifications.users (
   name TEXT NOT NULL,
   last_name TEXT NOT NULL,
   auth_token VARCHAR UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS notifications.users_notifications (
     id SERIAL PRIMARY KEY,
     theme TEXT NOT NULL,
     message TEXT NOT NULL,
     email TEXT NOT NULL,
     sending_time TIMESTAMP WITH TIME ZONE NOT NULL,
     jwt VARCHAR(255) NOT NULL,
     FOREIGN KEY (jwt) REFERENCES notifications.users(auth_token)
);

CREATE UNIQUE INDEX IF NOT EXISTS idx_unique_notifications ON notifications.users_notifications (id, jwt);

CREATE INDEX IF NOT EXISTS name_last_name ON notifications.users(name, last_name);