package com.example.pokemon;

import java.sql.*;
import java.lang.*;

public class ConnectionFactory {
    private String server, port, db, user, password;

    public ConnectionFactory() {
        this.server = "127.0.0.1";
        this.port = "3306";
        this.db = "pokedb";
        this.user = "user";
        this.password = "password";
    }

    public String getServer() {
        return server;
    }

    public String getPort() {
        return port;
    }

    public String getDb() {
        return db;
    }

    public String getUser() {
        return user;
    }

    public String getPassword() {
        return password;
    }

    public Connection Connect() throws ClassNotFoundException, SQLException {
        Class.forName("com.mysql.cj.jdbc.Driver");
        String connString = String.format("jdbc:mysql://%s:%s/%s", getServer(), getPort(), getDb());
        return (Connection) DriverManager.getConnection(connString, getUser(), getPassword());
    }

}